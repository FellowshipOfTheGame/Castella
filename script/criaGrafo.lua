--- Nossa bibliotecazinha pra mexer nas regiões
require 'script/regionGraph'

-- um 'srand'zinho ;]
math.randomseed (os.time ())

local id = 0

for i = 0, RegionGraph.altura - 1 do
	for j = 0, RegionGraph.largura - 1 do
		local y = i * RegionGraph.tamanho_bloco + math.random (RegionGraph.tamanho_bloco - 1) - 1
		local x = j * RegionGraph.tamanho_bloco + math.random (RegionGraph.tamanho_bloco - 1) - 1
		-- cria regiões
		grafo:novaRegiao (id, sorteiaRegiao (), x, y)

		grafo:criaConexoes (grafo:get (id))

		id = id + 1
	end
end


