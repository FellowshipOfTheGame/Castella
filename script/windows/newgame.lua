
--Window (x, y, Width, Height):
window = 
{ 
	x = (ScreenWidth/2 - 160), 
	y = 320, 
	w = 320, 
	h = 999  
}

--Buttons ( x, y, img, imgA, callback )
b1 = {0, 0, "buttonStart.png", "buttonStartA.png", start_battle}
b2 = {0, 100, "buttonLoad.png", "buttonLoadA.png", game_load}
b3 = {0, 200, "buttonQuit.png", "buttonQuitA.png", game_quit}

buttons = {b1, b2, b3}



-- Return values to C
buttonCount = #buttons
