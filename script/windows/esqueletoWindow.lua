--- Como escrever sua Window no lua
-- Variável exportada: Win -> a Window criada

-- Geometria da janela {
--		x: posição horizontal em relação à Screen (canto esquerdo = 0, aumentando)
--		y: posição vertical em relação à Screen (canto superior = 0, aumentando)
--		c: comprimento
--		a: altura
-- }
--
-- Nota:
--     Variáveis exportadas: TelaComprimento, TelaAltura
--     Essa sessão é obrigatória!
janela = { 
	x = (TelaComprimento/2 - 160),
	y = 320,
	c = 320,
	a = 999
}
------------------------------------- WIDGETS ----------------------------------

-- Botões {
--	{
--		x: posição horizontal em relação à Window
--		y: posição vertical em relação à Window
--		imagem: nome da imagem (arquivo) do botão inativo
--		imagemAtivo: nome da imagem (arquivo) do botão ativo
--		ação do botão: função de callback a ser chamada
--	},
--	{}...
-- }
botoes = {
	{0, 0, "buttonStart.png", "buttonStartA.png", batalha_iniciar},
	{0, 100, "buttonLoad.png", "buttonLoadA.png", jogo_carregar},
	{0, 200, "buttonQuit.png", "buttonQuitA.png", jogo_sair},
}
-- Adiciona nossos botões na Window
Win:addButtons (botoes)

-- Sliders {
--	{
--		x: posição horizontal em relação à Window
--		y: posição vertical em relação à Window
--		imagemSlider: nome da imagem de fundo do slider
--		imagemSeletor: nome da imagem do seletor do slider
--	},
--	{}...
-- }
sliders = {
	{20, 20, "slider1.png", "selector1.png"}
}
-- Adiciona nossos sliders na Window
Win:addSliders (sliders)
