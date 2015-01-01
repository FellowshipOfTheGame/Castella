------------------------------REGION --------------------------------

--[[
--	Region::
-- 		Region:print ()
-- 		Region:getId ()
-- 		Region:getX ()
-- 		Region:getY ()
-- 		Region:getType ()
-- 		Region:getStructure (index)
-- 		Region:getDistance (reg)
-- 		Region:getAdjQuantity ()
-- 		Region:connect (reg)
-- 		Region:disconnect (reg)
-- 		Region.getTypeName (type)
--
--	Structure::
--		Structure:getType ()
--		Structure.getTypeName (type)
--]]


-- função pro botão da estrutura
function pulaStruct (struct)
	return function () vaiPraEstrutura (struct) end
end


--- Iterador pra Region, pega Structures
--
-- @param graph Região
-- @param start Começo do iterador: índice da primeira região. Padrão: zero
-- @param drop Quantidade de estruturas a serem deixadas. Padrão: zero
--
-- @return Índice (começando de 0) e a região
function estruturas (reg, drop)
	local i = -1
	local drop = drop or 0

	return function ()
		i = i + 1
		if i < reg:getStructureQuantity () then
			return i, reg:getStructure (i)
		end
		-- estrutura não encontrada: nullptr
		return nil, nil
	end
end


