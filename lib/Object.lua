-- Object
-- primitives ajustes for main objects
Object = Object or {}

------------------------------------------------------------------------------
-- METAMETHOD __index
------------------------------------------------------------------------------

Object.__index = Object

------------------------------------------------------------------------------
-- METAMETHOD __newindex
------------------------------------------------------------------------------

Object.__newindex = function(t, k, v)
  rawset(t, k, v)
  if k == 'inherit' and v ~= nil then
    v(t)
  end
end

------------------------------------------------------------------------------
-- CONSTRUTOR
------------------------------------------------------------------------------

function Object:initialize()
  -- print('initialize Object')
end

------------------------------------------------------------------------------
-- GENERIC CONTRACT
------------------------------------------------------------------------------

function Object:prepare(params)
end

function Object:validate(params)
end

function Object:before(params)
end

function Object:after(params)
end

function Object:execute(method, params)
  self:prepare(params)
  self:validate(params)
  self:before(params)
  local result = self[method](self, params)
  self:after(params)
  return result
end

------------------------------------------------------------------------------
-- SPECIFIC CONTRACT
------------------------------------------------------------------------------
--[[
function Object:contract(name)
  local contract = require('contract')
  contract.create(self, name)
end
]]
------------------------------------------------------------------------------
-- TRY
------------------------------------------------------------------------------

function Object:try(column, params)
  local result = nil;
  if type(self[column]) == 'function' then
    result = self[column](self, params)
  end
  if result == nil then
    result = Object.new()
  end
  return result
end

------------------------------------------------------------------------------
-- NEW
------------------------------------------------------------------------------

function Object.new(record)
  local obj = record or {}
  setmetatable(obj, Object)
  obj:initialize()
  return obj
end

------------------------------------------------------------------------------
-- IS BLANK
------------------------------------------------------------------------------

function Object:isBlank(column)
  if self[column] == nil or self[column] == '' then
    return true
  else
    return false
  end
end

--------------------------------------------------------------------------------
-- BANG !
--------------------------------------------------------------------------------

function Object:bang()
  local flag = false
  for k, v in pairs(self.errors) do
    flag = true
    break
  end
  if flag then
    local errors  = self.errors
    self.errors = {}
    errors.traceback = debug.traceback()
    error(errors)
  end
end

return Object
