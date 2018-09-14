local rhea = require 'rhea'
local test = {}

test['parse simple name'] = function()
  local name, method = rhea.parseName('migrate:run')
  assert( name == 'Migrate', name )
  assert( method == 'run' )
end

test['parse name with camelcase'] = function()
  local name, method = rhea.parseName('my_task:run')
  assert( name == 'MyTask', name )
  assert( method == 'run' )
end

test['simple name with namespace'] = function()
  local name, method = rhea.parseName('db.migrate:run')
  assert( name == 'db.Migrate', name )
  assert( method == 'run' )
end

test['parse camel case name with large namespace'] = function()
  local name, method = rhea.parseName('namespace1.namespace2.namespace3.my_task:run')
  assert( name == 'namespace1.namespace2.namespace3.MyTask', name )
  assert( method == 'run' )
end

return test
