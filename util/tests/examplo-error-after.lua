local test = {}

test.after = function()
  error("error after...")
end

test.my_test_ok= function()
  local value = true
  assert( value == true )
end

return test
