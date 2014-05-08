
--Window:
wX = ScreenWidth/2 - 160
wY = 320
wW = 320
wH = 999

--Buttons
b1 = {0, 0, "buttonStart.png", "buttonStartA.png", 3}
b2 = {0, 100, "buttonLoad.png", "buttonLoadA.png", 2}
b3 = {0, 200, "buttonQuit.png", "buttonQuitA.png", 0}

buttons = {b1, b2, b3}



-- Return values to C
buttonCount = #buttons

function get_table_field(i, j)
	return buttons[i][j]
end
