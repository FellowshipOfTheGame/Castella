--------------------------------- PLAYERS --------------------------------------

--[[
-- Criando Players com actors no Lua
--
-- Actors = {
--	{
--		sprite_sheet_name,
--		strength,
--		inteligence,
--		agility,
--		vitality
--	},
--	{}...
-- }
--
-- Players = {
--	{
--		actors = {actor1, actor2, ...}
--	},
--	{}...
-- }
--]]
actor = {"actor1.png", 5, 5, 5, 5}
actor2 = {"actor1green.png", 5, 5, 5, 5}

players = {
	{
		nome = "primero",
		actors = {
			{"actor1black.png", 26, 6, 9, 6}, actor, actor
		}
	},
	{
		nome = "segundo",
		actors = {
			{"actor2.png", 20, 7, 25, 7}, actor2, actor2
		}
	}
}
-- Adiciona os players no mundo
mundo:addPlayers (players)
