function println( thing )
	io.write(thing .. "\n")
end

println("Executing lua function from lua...")

local randNum = GetRandomNumber()
println(randNum)

local msgBoxTitle = "Message Box Title!"
local msgBoxContent = "Hey, this is the content! Have fun :D";

ShowMessageBox(msgBoxTitle, msgBoxContent, MessageBoxButtons_OK)

return {
	a = "This Is the Value for 'a' :D",
	b = "Hello, C++!",
	c = {
		d = 5123
	},
	func = function ()
			  println("Hello World!")
		   end
}