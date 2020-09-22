local Adapter = require('arken.ActiveRecord.Adapter')
local test = {}

test.should_error_insert = function()
  local status, message = pcall(Adapter.insert)
  assert( status == false )
  assert( message:contains('not implemeted') == true )
end

return test
