require "OHttpParser"

local test = {}

test['first example'] = function()
  local header = os.read(OBERON_PATH .. '/specs/OHttpParser/example-1.header')
  local parser = OHttpParser.new(header)
  assert(parser:headerDone() == nil)
end

return test