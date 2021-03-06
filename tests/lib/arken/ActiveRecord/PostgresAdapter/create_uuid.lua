local test = {}
local json  = require('arken.json')
local Class  = require('arken.oop.Class')
local Person = Class.new("Person", "ActiveRecord")
Person.tableName = string.format("person_%s", os.uuid():replace('-', '_'))
Person.primaryKey = 'uuid'

test.beforeAll = function()
  ActiveRecord.reset()
  ActiveRecord.config = "config/active_record_postgres.json"
  local sql = [[
  CREATE TABLE %s (
    uuid char(36) PRIMARY KEY, name VARCHAR(250), observation TEXT,
    created_at TEXT, updated_at TEXT
  )]]
  Person.adapter():execute(string.format(sql, Person.tableName))
end

test.before = function()
  ActiveRecord.begin()
end

test.after = function()
  ActiveRecord.rollback()
end

test.afterAll = function()
  Person.adapter():execute(string.format("DROP TABLE %s", Person.tableName))
  ActiveRecord.config = nil
end

test.should_insert_in_the_database = function()
  local p = Person.new()
  p.name = "Chris Weidman"
  p:save()

  local result
  for row in Person.adapter():execute(string.format("SELECT * FROM %s", Person.tableName)):each() do
    result = row
    break
  end

  assert(result.name == 'Chris Weidman', json.encode(result))
end

test.define_primaryKey = function()
  local p = Person.new()
  p.name = "Chris Weidman"
  p:save()

  assert(#p.uuid == 36, json.encode(p))
end

test.define_created_at = function()
  local p = Person.new()
  p.name = "Chris Weidman"
  p:save()

  assert(type(p.created_at) == 'string', p.created_at)
end

test.define_update_at_with_the_value_of_created_at = function()
  local p = Person.new()
  p.name = "Chris Weidman"
  p:save()

  assert(p.created_at == p.updated_at, p.update_at)
end

return test
