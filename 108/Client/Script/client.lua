
local socket=require("socket")

host="127.0.0.1"

port =8989

c=assert(socket.connect(host,port))

c:send("client \n")

while 1 do 
	c:send("hihihi")
	io.read()
end

print ("end ")

c:close()
