require 'pgsql'

ActiveRecord_PostgresAdapter = Class.new("ActiveRecord_PostgresAdapter", "ActiveRecord.Adapter")

------------------------------------------------------------------------------
-- CONNECT
-------------------------------------------------------------------------------

function ActiveRecord_PostgresAdapter:connect()
  if self.instanceConnection == nil then
    local config = ""
    local config = config .. ' dbname=' .. self.database
          config = config .. ' user=' .. self.user
          config = config .. ' password=' .. self.password
          config = config .. ' host=' .. self.host
    self.instanceConnection = pg.connect(config)
  end
  return self.instanceConnection
end

--------------------------------------------------------------------------------
-- EXECUTE
--------------------------------------------------------------------------------

function ActiveRecord_PostgresAdapter:execute(sql)
  -- print(sql)
  return assert(self:connect():exec(sql))
end

--------------------------------------------------------------------------------
-- INSERT
--------------------------------------------------------------------------------

function ActiveRecord_PostgresAdapter:insert(record)
  local sql = 'INSERT INTO'
  local col = ''
  local val = ''
  for column, value in pairs(record) do
    if not self:isReserved(column) then
    --for column, properties in pairs(self:columns(table)) do
      if column ~= 'id' then
        --local value = record[column]
        if #col > 0 then
          col = col .. ', '
        end
        col = col .. column

        if #val > 0 then
          val = val .. ', '
        end
        val = val .. self:escape(value)
      end
    end
  end

  if col:len() == 0 then
    for column, properties in pairs(self:columns(table)) do
      if column ~= self.primary_key then
        if col:len() > 0 then
          col = col .. ', '
        end
        if val:len() > 0 then
          val = val .. ', '
        end
        col = col .. column
        val = val .. ' NULL '
      end
    end
  end

  return 'INSERT INTO ' .. self.table_name .. ' (' .. col .. ') VALUES (' .. val .. ') RETURNING id'
end

--------------------------------------------------------------------------------
-- UPDATE
--------------------------------------------------------------------------------

function ActiveRecord_PostgresAdapter:update(record)
  local sql = 'UPDATE ' .. self.table_name .. ' SET '
  local col = ''
  local key = self.table_name .. '_' .. tostring(record.id)
  local record_cache = self._cache[key]

  for column, properties in pairs(self:columns()) do
    local value = record[column]
    if column ~= self.primary_key then -- and record[column] ~= record_cache[column] then
      if #col > 0 then
        col = col .. ', '
      end
      col = col .. '"' .. column ..'"' .. " = " .. self:escape(value)
    end
  end
  if col:len() > 0 then
    local where = ' WHERE ' .. self.primary_key .. " = " .. self:escape(record[self.primary_key])
    sql = sql .. col .. where
    return self:execute(sql)
  else
    return true
  end
end

--------------------------------------------------------------------------------
-- CREATE
--------------------------------------------------------------------------------

function ActiveRecord_PostgresAdapter:create(record)
  local sql    = self:insert(record)
  local cursor = self:execute(sql)
  local row    = cursor:fetch({}, 'a')
  record.id    = tonumber(row[self.primary_key])
  record.new_record = false

  self.cache[record:cacheKey()] = record
  return record
end

--------------------------------------------------------------------------------
-- FIND
--------------------------------------------------------------------------------

function ActiveRecord_PostgresAdapter:find(params)
  local key = nil
  if params.id then
    key = self.table_name .. '_' .. tostring(params.id)
  end
  if key and self.cache[key] then
    return self.cache[key]
  else
    if self._cache[key] then
      local record = self._cache[key]
      local tmp    = {}
      for k,v in pairs(record) do
        tmp[k] = v
      end
      self.cache[key] = tmp
      return tmp
    end
    local sql = self:select(params)
    if self.cache[sql] then
      return self.cache[sql]
    else
      local data = self:fetch(sql)
      if data == nil then
        return nil
      end
      data.new_record = false
      key = self.table_name .. '_' .. tostring(data.id)
      self._cache[key] = data
      -- print('cache' .. key)
      -- self.cache[sql] = data
      return data
    end
  end
end

--------------------------------------------------------------------------------
-- ALL
--------------------------------------------------------------------------------

function ActiveRecord_PostgresAdapter:all(params)
  local sql    = self:select(params)
  local res    = self:execute(sql)
  local result = {}
  for row in res:rows() do
    table.insert(result, self:parser_fetch(row))
  end
  return result
end

--------------------------------------------------------------------------------
-- COLUMNS
--------------------------------------------------------------------------------

function ActiveRecord_PostgresAdapter:columns()
  if self.instanceColumns == nil then
    sql = [[
      SELECT a.attname, format_type(a.atttypid, a.atttypmod), d.adsrc, a.attnotnull
        FROM pg_attribute a LEFT JOIN pg_attrdef d
          ON a.attrelid = d.adrelid AND a.attnum = d.adnum
        WHERE a.attrelid = ']] .. self.table_name .. [['::regclass
          AND a.attnum > 0 AND NOT a.attisdropped
        ORDER BY a.attnum
    ]]

    local res    = self:execute(sql)
    local result = {}
    for row in res:rows() do
      local format = self:parser_format(row.format_type)
      result[row.attname] = {
        default  = self:parser_default(format, row.adsrc),
        not_null = toboolean(row.attnotnull),
        format   = format
      }
    end
    self.instanceColumns = result
  end
  return self.instanceColumns

end

-------------------------------------------------------------------------------
-- PARSER DEFAULT
-------------------------------------------------------------------------------

function ActiveRecord_PostgresAdapter:parser_default(format, value)
  if format == nil or value == nil then
    return nil
  else
    return self['parser_' .. format](value)
  end
end

function ActiveRecord_PostgresAdapter.parser_string(value)
  return value
end

function ActiveRecord_PostgresAdapter.parser_time(value)
  return value
end

function ActiveRecord_PostgresAdapter.parser_date(value)
  return value
end

function ActiveRecord_PostgresAdapter.parser_number(value)
  return tonumber(value)
end

function ActiveRecord_PostgresAdapter.parser_boolean(value)
  return toboolean(value)
end

-------------------------------------------------------------------------------
-- PARSER FORMAT
-------------------------------------------------------------------------------

function ActiveRecord_PostgresAdapter:parser_format(format_type)
  if string.contains(format_type, 'character') then
    return 'string'
  end

  if string.contains(format_type, 'timestamp') then
    return 'timestamp'
  end

  if string.contains(format_type, 'time') then
    return 'time'
  end

  if string.contains(format_type, 'double') then
    return 'number'
  end

  if string.contains(format_type, 'numeric') then
    return 'number'
  end

  if format_type == 'integer' then
    return 'number'
  end

  if format_type == 'bigint' then
    return 'number'
  end

  if format_type == 'text' then
    return 'string'
  end

  if format_type == 'boolean' then
    return 'boolean'
  end

  if format_type == 'date' then
    return 'date'
  end

  if format_type == 'bytea' then
    return 'bytea'
  end

  error('format_type: ' .. format_type ..' not resolved')
end

--------------------------------------------------------------------------------
-- FETCH
--------------------------------------------------------------------------------

function ActiveRecord_PostgresAdapter:fetch(sql)
  local result = self:execute(sql)
  local res    = result:fetch()
  if res == nil then
    return nil
  else
    return self:parser_fetch(res)
  end
end

-------------------------------------------------------------------------------
-- PARSER FETCH
-------------------------------------------------------------------------------

function ActiveRecord_PostgresAdapter:parser_fetch(res)
  res.new_record = false
  for column, properties in pairs(self:columns()) do
    res[column] = self:parser_value(properties.format, res[column])
  end
  return res
end

function ActiveRecord_PostgresAdapter:parser_value(format, value)
  if format == nil or value == nil then
    return nil
  else
    --print('parser_value_' .. format)
    return self['parser_value_' .. format](value)
  end
end

function ActiveRecord_PostgresAdapter.parser_value_string(value)
  return value
end

function ActiveRecord_PostgresAdapter.parser_value_time(value)
  return value
end

function ActiveRecord_PostgresAdapter.parser_value_date(value)
  return value
end

function ActiveRecord_PostgresAdapter.parser_value_number(value)
  return tonumber(value)
end

function ActiveRecord_PostgresAdapter.parser_value_boolean(value)
  return toboolean(value)
end

function ActiveRecord_PostgresAdapter.parser_value_timestamp(value)
  return value
end

--------------------------------------------------------------------------------
-- BEGIN
--------------------------------------------------------------------------------
function ActiveRecord_PostgresAdapter:begin()
  return self:execute("BEGIN")
end

--------------------------------------------------------------------------------
-- BEGIN
--------------------------------------------------------------------------------
function ActiveRecord_PostgresAdapter:rollback()
  return self:execute("ROLLBACK")
end

--------------------------------------------------------------------------------
-- READ
--------------------------------------------------------------------------------

function ActiveRecord_PostgresAdapter:read(record, column)
  local value = record[column]
  column = self:columns()[column]
  if value == nil or column == nil then
    return nil
  else
    return self:read_value(column.format, value)
  end
end

function ActiveRecord_PostgresAdapter:read_value(format, value)
  if format == nil or value == nil then
    return nil
  else
    -- print('read ' .. format)
    return self['read_value_' .. format](value)
  end
end

function ActiveRecord_PostgresAdapter.read_value_string(value)
  return value
end

function ActiveRecord_PostgresAdapter.read_value_time(value)
  return value
end

function ActiveRecord_PostgresAdapter.read_value_timestamp(value)
  return value:toDateTime()
end

function ActiveRecord_PostgresAdapter.read_value_date(value)
  return value
end

function ActiveRecord_PostgresAdapter.read_value_number(value)
  return tonumber(value)
end

function ActiveRecord_PostgresAdapter.read_value_boolean(value)
  return toboolean(value)
end

return ActiveRecord_PostgresAdapter