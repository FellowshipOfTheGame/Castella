-- Esse arquivo contém as classes que o ContentTable_Checklist_Factory.hpp
-- deve conhecer/registrar (e o atualiza)
classes = {
	'Actor'
}

-- cria os #includes
includes = {}
for _, classe in ipairs (classes) do
	table.insert (includes, '#include "' .. classe .. '.hpp"')
end
includes = table.concat (includes, '\n')
-- cria os defs pro luabind, incluindo o de string
table.insert (classes, 'string')
defs = {}
for _, classe in ipairs (classes) do
	table.insert (defs, '\t\t\tdef ("ContentTable_' .. classe .. '", (ContentTable<' .. classe .. '> (*) (Window *, int, int, int, int)) &ContentTable_Checklist_Factory::createContentTable<' .. classe .. '>)')
	table.insert (defs, '\t\t\tdef ("Checklist_' .. classe .. '", (Checklist<' .. classe .. '> (*) (Window *, int, int, int, int)) &ContentTable_Checklist_Factory::createChecklist<' .. classe .. '>)')
end
defs = table.concat (defs, ',\n')
-- o arquivo a ser atualizado
factory = io.open ('../include/ContentTable_Checklist_Factory.hpp', 'r')

contents = factory:read ('*a')

factory:close ()

-- põe as coisa nova lá!
contents = contents:gsub ('(// INCLUDES)%s+.*(// END)', '%1\n' .. includes .. '\n%2')
contents = contents:gsub ('(%s*module%s*%(L%)%s*%[)%s*.-(%s*%];)', '%1\n' .. defs .. '%2')

-- e reescreve o bagui
factory = io.open ('../include/ContentTable_Checklist_Factory.hpp', 'w')

factory:write (contents)
factory:close ()
