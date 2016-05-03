local should = require "test.should"
local test   = {}

test['should be zero for first string'] = function()
  str = "this is a test"
  should.be_equal( str:indexOf('t'), 0 )
end

test['should be zero for second string'] = function()
  str = "this is a test"
  should.be_equal( str:indexOf('h'), 1 )
end

test['should be zero for third string'] = function()
  str = "this is a test"
  should.be_equal( str:indexOf('i'), 2 )
end

test['should be zero for fourth string'] = function()
  str = "this is a test"
  should.be_equal( str:indexOf('s'), 3 )
end

test['should be zero for last string'] = function()
  str = "this is a test\n"
  should.be_equal( str:indexOf('\n'), 14 )
end

return test