local HttpEnv = require "arken.net.HttpEnv"

local test = {}

test['should return GET'] = function()
  local header = os.read(ARKEN_PATH .. '/tests/arken/net/HttpEnv/example-1.txt')
  local parser = HttpEnv.new(header)
  assert(parser:requestMethod() == 'GET')
end

test['show define requestMethod'] = function()
  local parser = HttpEnv.new("")
  parser:setRequestMethod("PUT")
  assert(parser:requestMethod() == 'PUT', parser:requestMethod())
end

return test
