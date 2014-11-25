------------------------------- REGION GRAPH -----------------------------------

--[[
-- Criando as regiões do RegionGraph no Lua
-- Taê umas funçõezinhas úteis =]
--
-- Variáveis exportadas: grafo -> o grafo mesmo =P
--
-- grafo:novaRegiao (ID, tipo, x, y)
-- grafo:get (n)
-- grafo:criaConexoes (regiao)
-- grafo:size ()
-- CONSTANTES: RegionGraph.altura, RegionGraph.largura, RegionGraph.tamanho_bloco
--
-- regiao:print ()
-- regiao:getX ()
-- regiao:getY ()
--
-- Nota: faça botões com as regiões, por favor, usando a função pula abaixo ;]
--]]

-- função pro botão da região
function pula (regiao)
	return function () vaiPraRegiao (regiao) end
end

-- iterador pro RegionGraph, retornando o índice (começando de 0) e a região
function regioes (graph)
	local i = -1
	return function ()
		i = i + 1
		if i >= graph:size () then return nil, nil end
		return i, graph:get (i)
	end
end

