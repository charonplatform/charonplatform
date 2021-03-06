local test = {}
local json = require('arken.json')
local rhea = require('rhea')
local App  = require('rhea.App')

App.output = function(value)
end

test.should_copy_of_skel = function()
  local dir    = 'tmp/' .. os.uuid()
  local params = {}
  params[0] = 'app:create'
  params[1] = dir

  rhea.run(params)

  assert( os.exists(os.pwd() .. '/' .. dir) == true, string.format("dir %s not exists", dir) )
  assert( os.exists(dir .. '/app') == true )
  assert( os.exists(dir .. '/config/active_record.json') == true )
end

test.should_error_if_dir_exists = function()
  local dir    = 'tmp/' .. os.uuid()
  local params = {}
  params[0] = 'app:create'
  params[1] = dir

  os.mkdir(dir)
  local status, message = pcall(rhea.run, params)

  assert( status == false )
  assert( message:contains('exists') == true )
end

test.should_config_database_postgres = function()
  local dir    = 'tmp/' .. os.uuid()
  local params = {}
  params[0] = 'app:create'
  params[1] = dir
  params[2] = '--postgres'

  rhea.run(params)
  local data = json.decode( os.read(dir .. '/config/active_record.json') )
  assert( os.exists(dir .. '/config/active_record.json') == true )
  assert( data.production.adapter == 'arken.ActiveRecord.PostgresAdapter' , data.production.adapter )
end

test.should_config_database_mysql = function()
  local dir    = 'tmp/' .. os.uuid()
  local params = {}
  params[0] = 'app:create'
  params[1] = dir
  params[2] = '--mysql'

  rhea.run(params)
  local data = json.decode( os.read(dir .. '/config/active_record.json') )
  assert( os.exists(dir .. '/config/active_record.json') == true )
  assert( data.production.adapter == 'arken.ActiveRecord.MysqlAdapter' , data.production.adapter )
end

test.should_config_database_sqlite = function()
  local dir    = 'tmp/' .. os.uuid()
  local params = {}
  params[0] = 'app:create'
  params[1] = dir
  params[2] = '--sqlite'

  rhea.run(params)
  local data = json.decode( os.read(dir .. '/config/active_record.json') )
  assert( os.exists(dir .. '/config/active_record.json') == true )
  assert( data.production.adapter == 'arken.ActiveRecord.SqliteAdapter' , data.production.adapter )
end

return test
