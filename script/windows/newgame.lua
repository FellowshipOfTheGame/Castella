
--Janela {x, y, w, h}:
janela = { 
	x = (ScreenWidth/2 - 160), --Posição na horizontal (esquerda da tela: 0, aumentando p/ a direita)
	y = 320, --Posição na vertical (no topo da tela: 0, aumentando p/ baixo)
	w = 320, --Comprimento
	h = 999  --Altura
}

--Botões { x, y, imagem, imagemAtivo, ação do botão }:
b1 = {0, 0, "buttonStart.png", "buttonStartA.png", batalha_iniciar}
b2 = {0, 100, "buttonLoad.png", "buttonLoadA.png", jogo_carregar}
b3 = {0, 200, "buttonQuit.png", "buttonQuitA.png", jogo_sair}

botoes = {b1, b2, b3}

--Contar botões
nBotoes = #botoes
