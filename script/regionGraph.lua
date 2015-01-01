------------------------------- REGION GRAPH -----------------------------------

--[[
-- Criando as regiões do RegionGraph no Lua
-- Taê umas funçõezinhas úteis =]
--
-- Exportados:
--
--	RegionGraph::
--		RegionGraph:novaRegiao (ID, tipo, x, y)
-- 		RegionGraph:get (n)    -- Lembrando que `n' é indexado a partir de 0
-- 		RegionGraph:criaConexoes (regiao)
-- 		RegionGraph:size ()
-- 		CONSTANTES: RegionGraph.altura, RegionGraph.largura, RegionGraph.tamanho_bloco
--
--	Variáveis exportadas: grafo -> o grafo mesmo =P
--		cena -> a cena do mundo
--
-- Nota: faça botões com as regiões, por favor, usando a função pula abaixo ;]
--]]

-- função pro botão da região
function pulaReg (regiao)
	return function () cena:vaiPraRegiao (regiao) end
end


--- Iterador pro RegionGraph, pega Regions
--
-- @param graph Grafo
-- @param drop Quantidade de regiões a serem deixadas. Padrão: zero
--
-- @return Índice (começando de 0) e a região
function regioes (graph, drop)
	local i = -1
	local drop = drop or 0

	return function ()
		i = i + 1
		if i < graph:size () then
			return i, graph:get (i)
		end
		-- região não encontrada
		return nil, nil
	end
end


--[[ Constantes do grafo pro TileMap ]]--
RegionGraph.altura = 4
RegionGraph.largura = 6
RegionGraph.tamanho_bloco = 3

--- Iterador pra achar os índices de possíveis vizinhos
--
-- @return i, índice do vizinho
function vizinhos (index)
	-- todos os movimentos possíveis, em {x,y}
	local movimentos = {
		{-1, -1},
		{-1, 0},
		{-1, 1},
		{0, -1},
		{0, 1},
		{1, -1},
		{1, 0},
		{1, 1}
	}

	local y = math.floor (index / RegionGraph.largura)
	local x = index % RegionGraph.largura

	local retorno = {}

	for _, mov in ipairs (movimentos) do
		local y_teste = y + mov[1]
		local x_teste = x + mov[2]

		-- posição válida: adiciona à table de retorno
		if x_teste >= 0 and x_teste < RegionGraph.largura and 
				y_teste >= 0 and y_teste < RegionGraph.altura then
			table.insert (retorno, y_teste * RegionGraph.largura + x_teste)
		end
	end

	return ipairs (retorno)
end

-- Chances de criar uma tal Região
RegionGraph.castle_ratio = 20
RegionGraph.village_ratio = 20
RegionGraph.cave_ratio = 20
RegionGraph.forest_ratio = 20

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
