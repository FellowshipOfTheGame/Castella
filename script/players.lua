-- Players com actors no Lua

-- Actor {sprite_sheet_name, strength, inteligence, agility, vitality}
actor = {"actor1.png", 5, 5, 5, 5}
actor2 = {"actor1green.png", 5, 5, 5, 5}

players = {
	{
		actors = {
			{"actor1black.png", 26, 6, 9, 6}, actor, actor
		}
	},
	{
		actors = {
			{"actor2.png", 20, 7, 250, 7}, actor2, actor2
		}
	}
}
mundo:addPlayers (players)
