--- Nossa bibliotecazinha pra mexer nas regiões
require ('script/regionGraph')

janela = {
	x = 0,
	y = 0,
	c = TelaComprimento,
	a = TelaAltura
}

-- Cria os botões a partir das regiões
botoes = {}

for i, reg in regioes (grafo) do
	botoes[i] = {
		reg:getX () * tilesize,
		reg:getY () * tilesize,
		"region.png", "region.png",
		pula (reg)
	}

	grafo:criaConexoes (reg)
	--reg:print ()
end

Win:addButtons (botoes)
