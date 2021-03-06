-- Copyright 2016 The Arken Platform Authors.
-- All rights reserved.
-- Use of this source code is governed by a BSD-style
-- license that can be found in the LICENSE file.

ARKEN_ENV   = os.getenv("ARKEN_ENV") or "test"
local empty  = require('arken.empty')
local test   = require('arken.test')
local buffer = ""

print = function(value)
  buffer = buffer .. tostring(value) .. '\n'
end

local callisto = function(file)

  if not os.exists(file) then
    error(file .. " not exists")
  end

  package.reload()

  local init      = os.microtime()
  local icon      = "ok"
  local flag, res = pcall(dofile, file)

  if flag == false then
    icon = 'failure'
    return icon, res
  end

  if res == false then
    icon = 'failure'
  end

  if empty(res) then
    icon = 'warning'
  end

  if type(res) == 'table' then
    local footer = ""
    local results = test.run(res)

    local count = {}
    count.ok      = 0
    count.failure = 0
    count.pending = 0

    for description, result in pairs(results) do
      count[result.status] = count[result.status] + 1
      if result.status ~= 'ok' then
        buffer = buffer .. '<b>' .. description .. '</b>' .. '\n'
        if result.msg and tostring(result.msg):len() > 0  then
          buffer = buffer .. tostring(result.msg) .. '\n\n'--print(result.msg)
        end
      end

      if count.pending > 0 or count.ok == 0 then
        icon = "warning"
      end

      if count.failure > 0 then
        icon = "failure"
      end

      test.output("\n")
      footer = ""
      for i, v in pairs(count) do
        if footer:len() > 1 then
          footer = footer .. ', '
        end
          footer = footer .. v .. " " .. i
      end
    end
    buffer = buffer .. footer
    test.output(buffer)
  end

  if buffer == '' then
    buffer = "empty..."
  end

  local seconds = string.format("%.6f", os.microtime() - init)
  local result  = buffer .. '\n\nFinished in ' .. seconds .. ' seconds\n'
  buffer = ""
  return icon, result:replace('\n', '<br>')
end

return callisto
