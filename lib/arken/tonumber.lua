local tonumberold = tonumber
return function(value, base)
  -- TODO improve with i18n
  if type(value) == 'string' and string.match(value, '%d,%d') then
    value = value:replace('.', ''):replace(',', '.')
  end
  return tonumberold(value, base)
end
