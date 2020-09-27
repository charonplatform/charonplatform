local Adapter = require("arken.ActiveRecord.Adapter")
local test = {}

test.should_return_NULL = function()
  assert( Adapter:escape(nil) == ' NULL ' )  
end

test.should_return_number = function()
  assert( Adapter:escape(1234.35) == '1234.35' )  
end

test.should_return_string = function()
  assert( Adapter:escape('hello') == [['hello']] )  
end

test.should_return_escape_string = function()
  assert( Adapter:escape([[It's]]) == [['It\'s']], Adapter:escape([[It's]]) )
end

return test
