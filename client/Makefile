
myftp: command.o getCommand.o dirCommand.o putCommand.o cdCommand.o otherCommand.o utils.o myftp.o main.o
	g++ command.o getCommand.o dirCommand.o putCommand.o cdCommand.o otherCommand.o utils.o myftp.o main.o -o mftp



command.o	: command.cpp  command.h
getCommand.o	: getCommand.cpp getCommand.h
dirCommand.o	: dirCommand.cpp dirCommand.h
putCommand.o	: putCommand.cpp putCommand.h
cdCommand.o	: cdCommand.cpp cdCommand.h
otherCommand.o	: otherCommand.cpp otherCommand.h
utils.o		: utils.cpp utils.h
myftp.o		: myftp.cpp myftp.h
main.o		: main.cpp


clean:
	rm -f *.o *.gch *~ myftp
