 @mainpage Jogo Castela
@authors Rafael Miranda Lopes (_Brasília_)
@authors Guilherme Nishina Fortes
@authors Henrique Cintra Miranda de Souza Aranha (_Oito_)
@authors Gil Barbosa Reis (_Zumbi_)
@authors Giovanni de Almeida Marazzi

@section Docs Documentação
- @ref About
- @ref Gameplay
- @ref Programação



 @page About Descrição do jogo
 @section Concept Conceito geral
Um herói deverá proteger e administrar suas terras, conquistar aliados, aprimorar suas
habilidades e equipamentos e lutar contra aqueles que se opuserem a ele, em um desafio tático.

 @section Story Sinopse de Cenário e História
O jogo se passa em um cenário medieval fantástico, onde vários senhores feudais lutam pelo
poder. Alguns se aliam em torno de objetivos comuns e de similaridades culturais, a fim de garantir
a sobrevivência ou até a supremacia de seus povos, ou mesmo pela glória dos senhores.
Os heróis NPCs terão traços de personalidade e interesses que influenciam em suas
impressões a respeito de outros heróis e em suas decisões.

 @section Game Gênero e Escopo
RPG/Estratégia: Elementos de RPG como o desenvolvimento das habilidades do herói
serão um aspecto chave do jogo. A estratégia entra tanto na elaboração das habilidades do
personagem conforme ele evolui como nas próprias batalhas e na administração do seu feudo.

As batalhas serão, ao mesmo tempo, táticas e dinâmicas, pois o jogador controlará
diretamente apenas o seu personagem, enquanto os outros serão controlados por uma IA escolhida
pelo prórpio jogador.

A administração da cidade e das relações com os outros heróis (senhores feudais – vassalos,
suseranos, inimigos, amigos - ou mercenários, por exemplo) permitirá uma ampla gama de escolhas
estratégicas em relação a recursos e diplomacia.

 @section Progress Progressão
A progressão no jogo poderá ser feita de três maneiras distintas: campanha, cenário pré-
configurado e cenário configurado pelo jogador.

 @section Visual Estilo Visual
Estilo visual 2D, sendo o mapa global e os feudos vistos por cima e a batalha vista lateralmente.

 @section Target Público Alvo e Aprendizado
Foco em jogadores hardcore que gostam de estudar os detalhes do jogo, mas também deve
dar vez a jogadores um pouco mais casuais, com automatização de algumas decisões. A curva de
aprendizado deverá permitir uma rápida associação de decisões e estratégias básicas, por meio de
inserção gradual de elementos do jogo durante a fase tutorial. Depois dessa fase, vem uma longa
etapa de refinamento.

 @section Engine
A princípio, será feito em C++, com algumas possibilidades de mudanças e complementações.

@ref index



	@page Gameplay Gameplay
 @section Global Visão Geral
O jogo pode ser dividido nestes módulos: navegação, combate, administração e diplomacia.
Cada um deles está relacionado a um tipo de ação que o personagem poderá executar durante o
jogo. O sucesso do jogador dependerá de suas escolhas em cada um desses módulos.

 @section Navegação
A navegação poderá ser realizada em três níveis: global, regional e estrutural, referindo-se,
respectivamente, aos três tipos navegáveis – mundo, região e estrutura.

No mapa global, o jogador poderá navegar entre regiões nele indicadas – como castelos,
vilas, etc – clicando na região desejada. As regiões estarão previamente conectadas em um grafo,
por estradas pré-definidas na criação do mapa. Para mover-se entre uma região e outra, elas devem,
necessariamente, estar conectadas por uma estrada ou por uma seqüência de estradas. A viagem
poderá ser feita em mais de uma etapa, caso as regiões estejam conectadas indiretamente e os
pontos intermediários e final do percurso estejam acessíveis ao jogador. Por exemplo, pode-se
desejar andar a um castelo aliado cujo percurso consiste de uma estrada a um castelo inimigo e de
uma estrada deste castelo até o aliado; como o castelo intermediário é inimigo, a estrada estará
bloqueada (mas ainda possivelmente navegável com pagamento de pedágios ou outras condições).

Os mapas regionais consistem dos elementos pertinentes a cada tipo de região: as estruturas.
O jogador poderá navegar entre as estruturas de uma região simplesmente clicando sobre elas. Na
navegação regional o personagem do jogador não se desloca: apenas se abre a tela da estrutura
selecionada, iniciando o terceiro tipo de navegação (estrutural).

A navegação estrutural é simplesmente a escolha entre as possibilidades que aquela estrutura
específica oferece. Por exemplo, dentro de uma estrutura Taverna poderão haver mercenários para
contratar e missões para adquirir. A navegação dentro de uma estrutura assim como dentro de uma
região não implicam movimentação visual do personagem.

 @section Combate
O combate pode ser iniciado pelo jogador ou pelo computador, dependendo da situação. Ao
ser iniciado, abre-se o mapa de combate e o jogador deverá escolher a posição inicial de seu herói e
de seus companheiros. O mapa é gradeado em quadrados, no estilo Final Fantasy Tactics e os
personagens podem movimentar-se por ele de acordo com seus pontos de movimentação. Esses
pontos serão determinados de acordo com atributos do jogador e também com o peso que ele carrega.

A ação dos personagens ocorre em turnos de freqüência ponderada em relação a uma
medida de iniciativa de cada um, ou seja: personagens mais rápidos agirão mais freqüentemente.
Enquanto o jogador tem controle total do seu personagem, seus aliados são controlados por uma
inteligência artificial configurada pelo jogador ou escolhida entre algumas IA's pré-configuradas.
Antes de entrar na batalha, o jogador terá relacionado atalhos do teclado às suas habilidades, de
forma a manter a batalha em um passo mais dinâmico (reduzindo a necessidade de navegar em
menus para escolher habilidades). As estratégias dos aliados poderão ser modificadas durante a
batalha, caso o jogador decida que há uma estratégia mais interessante.

Pontos de estamina são utilizados quando o personagem se movimenta e quando ataca ou
usa uma habilidade.

 @section Administração
A administração dos recursos do jogador será feita em sua tela de região e em suas telas de
estruturas. Ele deverá usar recursos para construir novas estruturas em uma região, bem como para
melhorar as estruturas já existentes. Recursos também podem ser investidos internamente às
estruturas, de forma a, por exemplo, melhorar os itens produzidos pelo ferreiro.
Os itens produzidos por estruturas como um ferreiro serão melhorados conforme
investimentos de recursos direcionados a itens específicos, com a possibilidade de se ajustar,
também, que atributo de cada item deverá ser melhorado. Exemplificando: se quisermos espadas de
duas mãos mais leves e mais afiadas, podemos investir, em um primeiro nível, em espadas de duas
mãos e distribuir esse investimento entre seu material e sua lâmina.

 @section Diplomacia
A diplomacia se refere à relação entre o personagem do jogador e os outros líderes de
regiões, como senhores de castelos ou prefeitos de vilas. A disposição de cada líder para com o
jogador depende de suas ações tomadas durante o jogo e que tenham implicações em sua
personalidade percebida e em seu poder, e também de como essas ações se alinham com a
personalidade de cada líder NPC específico.
O jogador poderá conquistar aliados, inimigos, adquirir a proteção de um senhor suserano
ou mesmo conseguir a cooperação de senhores que desejem ser seus vassalos, assim determinando
o seu próprio reino. Qualquer região poderá fazer parte de um reino, caso um senhor de castelo
consiga influência suficiente sobre ela. O reino é a hierarquia máxima de uma unidade
administrativa/diplomática. As regiões podem livrar-se de seus reinos anteriores, caso desejem trair
os seus reinos para possivelmente associar-se a outro, ou mesmo para tomá-los à força.

@ref index



 @page Programação Programação
- Controle do jogo
		+ @ref Game.h
		+ @ref GameState.h
		+ @ref GameStructure.h

- Controle de saída
		+ @ref Screen.h
		+ @ref Scene.h
		+ @ref SceneControl.h
		+ @ref Scene_MapEditor.h
		+ @ref Scene_StartMenu.h
		+ @ref Scene_World.h
		+ @ref Window.h
		+ @ref Window_StartMenu.h

- Interatividade
		+ @ref Input.h
		+ @ref Button.h

- Controle de arquivos
		+ @ref FileHandler.h
		+ @ref FileContainer.h
		+ @ref ScriptHandler.h

- Estrutura do Jogo
		+ @ref World.h
		+ @ref Region.hpp
		+ @ref Structure.hpp
		+ @ref MapEditor.h

- Outros
		+ @ref Callback.h
		+ @ref simpleSDLfunctions.h
		+ @ref soundManager.hpp

@ref index

