local list = {'.'} --'app', 'lib', 'tests', 'util', 'importacoes', 'api'}
for _, dir in ipairs(list) do
  local list = os.glob(dir, '\\.txt$', true)

  for fileName in list:each() do

    print(fileName)

    local buffer = os.read(fileName)
    local buffer = buffer:replace('charon', 'arken')
    local buffer = buffer:replace('CHARON', 'ARKEN')
    local buffer = buffer:replace('Charon', 'Arken')

    local file = io.open(fileName, 'w')
    file:write(buffer)
    file:close()
  end
end
