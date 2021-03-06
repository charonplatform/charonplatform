local json       = require('arken.json')
local dispatcher = require('arken.dispatcher')
local test = {}
package.path = package.path .. ';util/?.lua'

test.beforeAll = function()
  dispatcher.output = function() end
end

test.afterAll = function()
end

test.should_return_error_if_action_not_found = function()
  local env = {}
  env.requestPath = function()
    return "/order/unknow"
  end

  dispatcher.prefix = ""
  local status, headers, body = dispatcher.dispatchController(env)
  assert( status == 500, status )
  assert( #headers == 0, json.encode(headers) )
  assert( type(headers) == 'table', json.encode(headers) )
  assert( body:contains('action: "unknowAction" not found') == true, body )
end

test.should_return_error_if_action_save = function()
  local env = {}
  env.requestPath = function()
    return "/order/save"
  end

  dispatcher.prefix = ""
  local status, headers, body = dispatcher.dispatchController(env)
  assert( status == 200, status )
  assert( headers[1] == 'Content-Type: text/html; charset=utf-8', headers[1] )
  assert( type(headers) == 'table', json.encode(headers) )
  assert( body == 'save !', body )
end

return test
