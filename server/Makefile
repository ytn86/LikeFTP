
all: mftpd

CFLAGS:

mftpd: command.o getCommand.o putCommand.o dirCommand.o cdCommand.o otherCommand.o utils.o myftpd.o main.o
	g++ command.o getCommand.o putCommand.o dirCommand.o cdCommand.o otherCommand.o utils.o myftpd.o main.o -o mftpd



command.o	: command.cpp  command.h
getCommand.o	: getCommand.cpp getCommand.h
putCommand.o	: putCommand.cpp putCommand.h
dirCommand.o	: dirCommand.cpp dirCommand.h
cdCommand.o	: cdCommand.cpp cdCommand.h
otherCommand.o 	: otherCommand.cpp otherCommand.h
utils.o		: utils.cpp utils.h
myftpd.o	: myftpd.cpp myftpd.h
main.o		: main.cpp


clean:
	rm -f *.o *.gch *~ mftpd
