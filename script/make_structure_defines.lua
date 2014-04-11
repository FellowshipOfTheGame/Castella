--- Esse script cria o script structure_defines.lua, e deve ser rodado
-- cada vez que mudar os valores do Enum Structure_Type no arquivo include/Structure.hpp

require ("io", "string")
io.input ("../include/Structure.hpp")	-- novo input (não mais o stdin)

entire_file = io.read ("*all")	-- lê tudo do arquivo
enum = entire_file:match ("{\n(.-)};")	-- enum é só o pedaço entre { }
enum = enum:gsub ("\t//.-\n", "")	-- não queremos comentários
enum = enum:gsub (",", "")	-- nem as vírgulas


out = io.open ("structure_defines.lua", "w")
out:write ("-- NÃO MODIFIQUE ESSE ARQUIVO: arquivo criado automaticamente pelo programa make_structure_defines.lua\n-- Defines das estruturas: de acordo com o enum Structure_type especificado no include/Structure.hpp\n\n")	-- cabeçalho
out:write ("defines = {\n")	-- table define, que é o que a gente buscou no Structure.hpp

i = 0
-- escreve cada linha, mas entre aspas, pra torná-las strings
for l in enum:gmatch(".-\n") do
	out:write ('\t\"', l:sub(2, -2), '\" = ', i, ',\n')
	i = i + 1
end

out:write ("}\n")