-- Players com actors no Lua

-- Actor {sprite_sheet_name, strength, inteligence, agility, vitality}
actor = {"actor1.png", 5, 5, 5, 5}
actor2 = {"actor1green.png", 5, 5, 5, 5}

players = {
	primeiro = {
		actors = {
			{"actor1black.png", 26, 6, 9, 6}, actor, actor
		}
	},
	segundo = {
		actors = {
			{"actor2.png", 20, 7, 25, 7}, actor2, actor2
		}
	}
}
mundo:addPlayers (players)
