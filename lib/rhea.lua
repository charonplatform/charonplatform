-- Copyright 2016 The Charon Platform Authors.
-- All rights reserved.
-- Use of this source code is governed by a BSD-style
-- license that can be found in the LICENSE file.

require "charon.ByteArrayList"

-------------------------------------------------------------------------------
-- RHEA
-------------------------------------------------------------------------------

local function parseArg(index, arg)
  index = index + 1
  local result = {}
  while (index <= #arg) do
    if arg[index]:startsWith("--") then
      break
    end
    table.insert(result, arg[index])
    index = index + 1
  end

  if #result == 0 then
    return true
  end

  if #result == 1 then
    return result[1]
  end

  return result
end

local function parseArgs()
  local params = {}
  local key = ""

  for index, value in ipairs(arg) do
    if value:startsWith("--") then
      key = value:replace("--", "")
      params[key] = parseArg(index, arg)
    end
  end

  return params
end

local function printHelp(module)
  local help = ""
  local size = 0

  if module.help then

    for k, v in pairs(module.help) do
      if #k > size then
        size = #k
      end
    end

    local margem = '\n' .. string.rep(' ', size + 1)

    for k, v in pairs(module.help) do
      local space = string.rep(' ', size - #k)
      help = help .. k .. space .. ' # ' .. v:trim():replace('\n', margem) .. '\n'
    end

    print(help)
  end
end

rhea = function()
  local path = {}

  if arg[0] == nil then
  local list = tostring(package.path):split(';')
  for i = 1, list:size() do
    local str = list:at(i)
    str = str:replace("/?.lua", ""):replace('.', '/')
    str = os.abspath(str)
    if str:contains('rhea') and os.exists(str) then
      table.insert(path, str)
    else
      str = str .. '/rhea'
      if os.exists(str) then
        table.insert(path, str)
      end
    end
  end

    for _, str in ipairs(path) do
      local list = os.glob(str, "\\.lua$", false)
      for i = 1, list:size() do
        local module = dofile(list:at(i))
        print(module.className:underscore())
        printHelp(module)
      end
    end
  else
    local task   = arg[0]
    local last   = task:lastIndexOf(":")
    local name   = task:left(last):replace(":", ".")
    local action = task:mid(last+1, -1)

    if last < 0 then
      name   = arg[0]
      action = nil
    end

    local module, result
      local rhea_name = 'rhea.' .. name:camelcase()
      local result, module = pcall(require , rhea_name)
      if result == false then
        print(name .. " not work" .. module)
        os.exit()
      end

    -------------------------------------------------------------------------------
    -- EXECUTE
    -------------------------------------------------------------------------------
    local params = parseArgs()

    if module[action] then
      local object = module.new()
      if params.help then
        if object.help[action] then
          local help   = object.help[action]
          local margem = '\n' .. string.rep(' ', #action + 1)
          print(action .. ' # ' .. help:trim():replace('\n', margem))
        else
          print(action .. ": undocumented")
        end
      else
        object:execute(action, params)
      end
    else
      if params.help then
        printHelp(module)
      end
    end
  end
end
