package.msecs = QDateTime.currentMSecsSinceEpoch()
package.temp  = {}
package.last  = ""
package.mixed = {}
-- require_old   = require
require_reload = function(path, mixin)
  if package.loaded[path] then
    if package.isPathUpdated(path) then
      return package._reload(path)
    end
  else
    if mixin then
      package.mixed[package.last] = package.mixed[package.last] or {}
      table.insert(package.mixed[package.last], path)
    else
      package.last = path
    end
  end
  return require(path)
end

package.isPathUpdated = function(path)
  local filename = package.path_to_filename(path)
  if filename then
    if package.isFilenameUpdated(filename) then
      return true
    else
      if type(package.mixed[path]) == 'table' then
        for _, mixin_path in ipairs(package.mixed[path]) do
          local file_mixin = package.path_to_filename(mixin_path)
          if file_mixin then
            if package.isFilenameUpdated(file_mixin) then
              return true
            end
          end
        end
      end
    end
  end
  return false
end

package.path_to_filename = function(path)
  for str in string.gmatch(package.path, "([^;]+)") do
    local file_name = tostring(str:gsub("?", path:replace('.', '/')))
    if QFileInfo.exists(file_name) then
      return file_name
    end
  end

  return nil
end

package.isFilenameUpdated = function(file_name)
  local  fileInfo = QFileInfo.new(file_name)
  return fileInfo:lastModified():toMSecsSinceEpoch() > package.msecs
end

package._reload = function(path)
  if not package.isReloaded(path) then
    print('reload: ' .. path)
    local filename = package.path_to_filename(path)
    if filename then
      package.loaded[path] = loadfile(filename)()
    end
     table.insert(package.temp, path)
  end
  return package.loaded[path]
end

package.isReloaded = function(path)
  for _, value in ipairs(package.temp) do
    if value == path then
      return true
    end
  end

  return false
end

package.reload = function()
  package.temp = {}
  for path, table in pairs(package.loaded) do
    require_reload(path)
  end
  package.msecs = QDateTime.currentMSecsSinceEpoch()
end