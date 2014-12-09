--- Nossa bibliotecazinha pra mexer nas regiões
require 'script/regionGraph'

janela = {
	x = 0,
	y = 0,
	c = TelaComprimento,
	a = TelaAltura
}

-- Cria os botões a partir das regiões
botoes = {}

for i, reg in regioes (grafo) do
	-- Ícone da região de acordo com seu tipo
	local img = regionTypeName (reg:getType ()) .. ".png"

	botoes[i] = {
		reg:getX () * tilesize,
		reg:getY () * tilesize,
		img, img,
		pula (reg)
	}
	--reg:print ()
end

Win:addButtons (botoes)
