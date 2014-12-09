------------------------------- REGION GRAPH -----------------------------------

--[[
-- Criando as regiões do RegionGraph no Lua
-- Taê umas funçõezinhas úteis =]
--
-- Exportados:
--
--	RegionGraph::
--		RegionGraph:novaRegiao (ID, tipo, x, y)
-- 		RegionGraph:get (n)
-- 		RegionGraph:criaConexoes (regiao)
-- 		RegionGraph:size ()
-- 		CONSTANTES: RegionGraph.altura, RegionGraph.largura, RegionGraph.tamanho_bloco
--
--	Region::
-- 		Region:print ()
-- 		Region:getX ()
-- 		Region:getY ()
--
--	Variáveis exportadas: grafo -> o grafo mesmo =P
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

--[[ Constantes do grafo pro TileMap ]]--
RegionGraph.altura = 4
RegionGraph.largura = 6
RegionGraph.tamanho_bloco = 3

-- Chances de criar uma tal Região
RegionGraph.castle_ratio = 10
RegionGraph.village_ratio = 20
RegionGraph.cave_ratio = 20
RegionGraph.forest_ratio = 30

local ratios = {
	RegionGraph.castle_ratio,
	RegionGraph.village_ratio,
	RegionGraph.cave_ratio,
	RegionGraph.forest_ratio
}

-- soma de todas as chances, útil na hora de escolher uma, ó ali embaixo
local soma = 0
for _, ratio in ipairs (ratios) do
	soma = soma + ratio
end

function sorteiaRegiao ()
	-- vai tirando a chance da soma, até chegar numa conclusão
	local escolha = math.random (soma)

	for i, ratio in ipairs (ratios) do
		escolha = escolha - ratio
		if escolha <= 0 then
			-- i - 1, pois no c++ o enum começa do 0
			return i - 1
		end
	end
end
