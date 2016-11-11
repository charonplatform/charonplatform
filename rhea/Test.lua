OBERON_ENV = os.getenv("OBERON_ENV") or "test"

local colorize = require 'colorize'
local test     = require 'test'
local Test = Class.new("Test")
--[[
function string:escape()
  local tmp = self
  tmp = tmp:swap("&",  "&amp;")
  tmp = tmp:swap("\"", "&quot;")
  tmp = tmp:swap("'",  "&#039;")
  tmp = tmp:swap("<",  "&lt;")
  tmp = tmp:swap(">",  "&gt;")

  return tmp
end
]]
function Test:console(params)
  t = os.microtime()

  count = {}
  count.ok      = 0
  count.err     = 0
  count.fail    = 0
  count.pending = 0

  color         = {}
  color.ok      = 'green'
  color.fail    = 'red'
  color.err     = 'red_light'
  color.pending = 'yellow'

  results = test.execute(arg)

  for file_name, result in pairs(results) do
    print(file_name)
    for description, result in pairs(result) do
      --print(result.status)
      count[result.status] = count[result.status] + 1
      print(colorize.format(description, color[result.status]))
      if tostring(result.msg):len() > 0  then
        print(result.msg)
      end
    end
    print("")
    buffer = ""
    for i, v in pairs(count) do
      if buffer:len() > 0 then
        buffer = buffer .. ', '
      end
      buffer = buffer .. v .. " " .. i
    end
    buffer = buffer .. "\n"
    buffer = buffer .. 'Time: ' .. tostring((os.microtime() - t))
    print(buffer)
  end

end

function Test:notify(params)
  local time = os.microtime()
  local file = arg[2]
  while true do
    t = QDateTime.currentMSecsSinceEpoch()
    package.reload()
    results = test.execute({file})

    buffer = ""
    titulo = ""

    count = {}
    count.ok      = 0
    count.err     = 0
    count.fail    = 0
    count.pending = 0

    for file_name, result in pairs(results) do
      if titulo:len() > 0 then
        titulo = titulo, ', '
      end
      titulo = titulo .. file_name:swap('specs/models/', '')
    end

    for file_name, result in pairs(results) do
      for description, result in pairs(result) do
        count[result.status] = count[result.status] + 1
        if result.status ~= 'ok' then
          buffer = buffer .. description .. '\n'
          if result.msg and tostring(result.msg):len() > 0  then
            --buffer = buffer .. ' ' .. result.status .. '\n'
            buffer = buffer .. '\n' .. tostring(result.msg) .. '\n'--print(result.msg)
          end
        end
      end
      print("")
      rodape = ""
      for i, v in pairs(count) do
        if rodape:len() > 1 then
          rodape = rodape .. ', '
        end
        rodape = rodape .. v .. " " .. i
      end
      buffer = buffer .. '\n' .. rodape
      buffer = buffer .. '\n\nFinished in ' .. tostring((QDateTime.currentMSecsSinceEpoch() - t) / 1000.0) .. ' seconds'
      print(buffer:replace('\n', '8'))
      icon = "error"
      --buffer = buffer:replace('\n\n', '')
      print(titulo .. "' '\'" .. buffer:escapeHtml() .. "\'")
      --os.execute("notify-send -t 10000 " .. "'" .. titulo .. "' \'" .. buffer:escapeHtml() .. "\'")
      os.execute("puck -timeout 10 " .. " -titulo '" .. titulo .. "' -texto \'" .. buffer:escapeHtml() .. "\' &")
    end
    while os.ctime(file) <= time  do
      os.sleep(0.15)
    end
    os.sleep(0.10)
    time = os.ctime(file)
  end
end

function Test:create()
  local template = require 'template'

  print("Digite o nome da classe:")
  self.class_name = io.read()
  local path = 'specs/models/' .. self.class_name:replace('.', '/')
  os.mkpath( path )

  print("Digite o nome do método:")
  local metodo = io.read()
  local test   = path .. '/' .. metodo .. '.lua'
  local file   = QFile.new(test)
  local tpl    = OBERON_PATH .. "/tasks/templates/test/create/metodo.tpl"
  local buffer = template.execute(tpl, self)
  file:open({"WriteOnly"})
  file:write(buffer)
  file:close()

  print('mkpath '.. path)
  print('test create ' .. test)
end

return Test