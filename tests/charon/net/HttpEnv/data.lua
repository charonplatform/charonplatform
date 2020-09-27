local HttpEnv = require "arken.net.HttpEnv"

local test = {}

test['should return path /pedido/varejo'] = function()
  local header  = os.read(ARKEN_PATH .. '/tests/arken/net/HttpEnv/example-1.txt')
  local request = HttpEnv.new(header)
  assert(request:data() == header)
end

return test
