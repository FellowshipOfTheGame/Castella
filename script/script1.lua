
-- print ("hello from lua")
-- print ("lua code is capable of reading the value set from C++", cppvar)
-- luavar = cppvar *3

-- function myluafunction(times)
	-- return string.rep("(-)", times)
-- end

-- function myfunction(arg)
	-- return cppfunction(arg)
-- end


function entries(arg) -- iterator
	return function()
		return arg:pop();
		end
end

for i in entries(thelist) do
	io.write("From LUA: " i, "\n")
end

for i=1,10 do
	the_list:push(50+i*100);
end