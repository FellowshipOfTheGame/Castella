--- Nossa bibliotecazinha pra mexer nas regiões
require ('script/regionGraph')

-- um 'srand'zinho ;]
math.randomseed (os.time ())

local id = 0

for i = 0, RegionGraph.altura - 1 do
	for j = 0, RegionGraph.largura - 1 do
		local x = i * RegionGraph.tamanho_bloco + math.random (RegionGraph.tamanho_bloco - 1)
		local y = j * RegionGraph.tamanho_bloco + math.random (RegionGraph.tamanho_bloco - 1)
		-- cria regiões
		grafo:novaRegiao (id, math.random (4) - 1, x, y)
		id = id + 1
	end
end


