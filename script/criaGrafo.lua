--- Nossa bibliotecazinha pra mexer nas regiões
require 'script/regionGraph'

local id = 0

-- cria todas as regiões
for i = 0, RegionGraph.altura - 1 do
	for j = 0, RegionGraph.largura - 1 do
		local y = i * RegionGraph.tamanho_bloco + math.random (RegionGraph.tamanho_bloco - 1) - 1
		local x = j * RegionGraph.tamanho_bloco + math.random (RegionGraph.tamanho_bloco - 1) - 1

		grafo:novaRegiao (id, sorteiaRegiao (), x, y)

		id = id + 1
	end
end

-- Regiões já visitadas
ja_visitado = {}
-- Fila de regiões a serem processadas
a_visitar = {0}

-- conecta as regiões, formando uma árvore (pra ser conexo)
repeat
	-- próxima região, com seu índice
	index = table.remove (a_visitar, 1)
	if ja_visitado[index] then goto continue end

	reg = grafo:get (index)

	-- adiciona ele na table de visitados
	ja_visitado[index] = true

	-- auxiliares pra saber qual o mais perto
	min_distancia = math.huge
	--mais_perto = 0

	-- Acha qual região tá mais perto
	for _, j in vizinhos (index) do
		local candidato = grafo:get (j)
		local dist = reg:getDistance (candidato)

		if not ja_visitado[j] then
			table.insert (a_visitar, j)

			if dist < min_distancia then
				min_distancia = dist
				mais_perto = j
			end
		end
	end

	reg:connect (grafo:get (mais_perto))

	::continue::
until #a_visitar == 0
