local test = {}
local callisto = require 'callisto'

test.should_error_not_exists_file = function()
  local test = require('charon.test')
  test.output = function() end
  local result, message = pcall(callisto, "lib/callisto/example-not-exists.lua")
  test.output = io.write
  assert(result == false)
  assert(message:contains("lib/callisto/example-not-exists.lua not exists"), message)
end

test.should_result_ok = function()
  local test = require('charon.test')
  test.output = function() end
  local icon, result = callisto("lib/callisto/example-ok.lua")
  test.output = io.write
  assert(icon == "ok", icon)
end

test.should_result_warning = function()
  local test = require('charon.test')
  test.output = function() end
  local icon, result = callisto("lib/callisto/example-warning.lua")
  test.output = io.write
  assert(icon == "warning", icon)
end

test.should_result_failure = function()
  local test = require('charon.test')
  test.output = function() end
  local icon, result = callisto("lib/callisto/example-failure.lua")
  test.output = io.write
  assert(icon == "failure", icon)
  assert(result:contains("lib/callisto/example-failure.lua:4: failure"), result)
end

return test
