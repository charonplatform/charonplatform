local Object = require('arken.oop.Object')
local test   = {}

test.should_return_empty_string = function()
  assert( Object:__tostring() == '' )
end

return test
