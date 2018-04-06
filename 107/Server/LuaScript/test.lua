
--require "socket"  

--require "log"

function start_lua()
	--local log=require("log")
	--log.log("start test lua")
	--log.log("ok")
	print("start lua ok")
end


function test_download()
	host = "www.w3.org"  
	  
	function download(host,file)  
	    local f = io.open("test.html","w+")  
	    local c = assert(socket.connect(host,80));  
	    c:send("GET "..file.." HTTP/1.0\r\n\r\n")  
	    while true do  
	        local s,status,partial = c:receive(1024);  
	        f:write(s or partial)  
	        if status == "closed" then  
	            break  
	        end  
	  
	    end  
	    c:close()  
	    f:close()  
	end  
	  
	download(host,"/TR/REC-html32.html")  
end


function sayHi()
	print "hi"
end
