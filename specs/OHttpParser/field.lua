require "OHttpParser"
local should = require "test.should"
local test   = {}

test['first example'] = function()
  local header = os.read(OBERON_PATH .. '/specs/OHttpParser/example-1.header')
  local parser = OHttpParser.new(header)
  should.be_equal(parser:field("User-Agent"), "Mozilla/5.0 (X11; Linux x86_64; rv:38.0)")
end

return test