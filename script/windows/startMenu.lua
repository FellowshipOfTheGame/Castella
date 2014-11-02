
--Janela {x, y, w, h}:
janela = { 
	x = (TelaComprimento/2 - 180), --Posição na horizontal (esquerda da tela: 0, aumentando p/ a direita)
	y = 300, --Posição na vertical (no topo da tela: 0, aumentando p/ baixo)
	c = 360, --Comprimento
	a = 310,  --Altura

	windowSkin = "windowskin.png"
}

--Botões { x, y, imagem, imagemAtivo, ação do botão }:
botoes = {
	{20, 20, "buttonStart.png", "buttonStartA.png", jogo_iniciar},
	{20, 120, "buttonLoad.png", "buttonLoadA.png", batalha_iniciar},
	{20, 220, "buttonQuit.png", "buttonQuitA.png", jogo_sair}
}
nBotoes = #botoes
