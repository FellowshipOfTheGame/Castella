require 'script/cores'
require 'script/region'

--- Window das regiões
janela = { 
	x = 0,
	y = 0,
	c = TelaComprimento,
	a = TelaAltura
}

-- avanço vertical dos botões
AVANCO = 200

buttons = {}
for i, struct in estruturas (reg) do
	buttons[i + 1] = {
		TelaComprimento/2,
		50 + AVANCO * i,
		"estrutura.png", "estrutura.png",
		pulaStruct (struct)
	}
end
Win:addButtons (buttons)

-- teste dos sliders
sliders = {
	{20, 20, "slider1.png", "selector1.png"},
	{20, 70, "slider1vert.png", "selector1.png"}
}
Win:addSliders (sliders)

-- teste de TextArea
textArea = {
	{400, 30, 500, 500, PRETO, BRANCO}
}
Win:addTextAreas (textArea)
