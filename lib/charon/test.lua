-- Copyright 2016 The Charon Platform Authors.
-- All rights reserved.
-- Use of this source code is governed by a BSD-style
-- license that can be found in the LICENSE file.

-------------------------------------------------------------------------------
-- CHARON_ENV
-------------------------------------------------------------------------------

CHARON_ENV = os.getenv("CHARON_ENV") or "test"

-------------------------------------------------------------------------------
-- TEST MODULE
-------------------------------------------------------------------------------

local colorize = require 'charon.colorize'
local test     = {}
test.output    = io.write

function test.process(file_name)
  local results   = {}
  local status, specs = pcall(dofile, file_name)
  -- arquivo com erro de sintaxe
  if not status then
    test.output(file_name)
    test.output(specs)
    results[file_name] = { status = 'failure', msg = specs }
    return results
  end
  if specs == nil then
    error "empty tests..."
  end
  local before    = specs.before    or function() end
  local after     = specs.after     or function() end
  local beforeAll = specs.beforeAll or function() end
  local afterAll  = specs.afterAll  or function() end
  local states    = specs.states
  specs.before    = nil
  specs.after     = nil
  specs.beforeAll = nil
  specs.afterAll  = nil
  specs.states    = nil
  status, message = pcall(beforeAll)
  if status == false then
    error(message)
  end
  for description, func in pairs(specs) do
    local status, message
    if type(func) == 'function' then
      status, message = pcall(before)
      if status then
        status, message = pcall(func)
      end
      -- require( 'charon.record' ).cache = {}
      if status == false then
        if type(message) == 'table' then
          local text = ""
          local traceback = message.traceback or ''
          message.traceback = nil
          local trace = ""
          local list  = string.split(traceback, "\n")
          for i = 1, list:size() do
            if list:at(i):contains(file_name) then
              trace = trace .. list:at(i):simplified() .. '\n'
            end
          end
          trace = trace .. '\n\n' .. traceback

          for k, v in pairs(message) do
            text = text .. k .. ': ' .. v .. '\n'
          end
          if trace then
            text = text .. '\n' .. trace
          end
          results[description] = {status = 'failure', msg = text}
          test.output(colorize.format('.', 'red'))
        else
          results[description] = {status = 'failure', msg = message}
          test.output(colorize.format('.', 'red'))
        end
      else
        results[description] = {status = "ok", msg = ''}
        test.output(colorize.format('.', 'green'))
      end
      status, message = pcall(after)
      if status == false then
        results['after'] = {status = 'failure', msg = message}
        test.output(colorize.format('.', 'red'))
      end
    else
      results[description] = {status = 'pending', msg = func}
      test.output(colorize.format('.', 'yellow'))
    end
    io.flush()
  end
  status, message = pcall(afterAll)
  if status == false then
    error(message)
  end

  if states then
    if type(states) == 'table' then
      for _, state in ipairs(states) do
        local flag = true
        for pattern in io.lines("tests/states/" .. state) do
          print(pattern)
          for description, _ in pairs(specs) do
            if description:match('^' .. pattern .. '$') then
              flag = false
              break
            end
          end
          if flag then
            results[pattern] = { status = 'pending' }
          end
        end
      end
    end
  end

  return results
end

function test.execute(argfiles)
  local files = {}
  for _, file_name in ipairs(argfiles) do
    if file_name:endsWith(".lua") then
      if os.exists(file_name) then
        table.insert(files, file_name)
      else
        error(file_name .. " not exists")
      end
    end
  end
  local result = {}
  for i, file in ipairs(files) do
    result[file] = test.process(file)
  end
  return result
end

return test
