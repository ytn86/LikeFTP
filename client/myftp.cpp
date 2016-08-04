#include <cstring>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>


#include <unistd.h>
#include <netdb.h>

#include <sys/socket.h>

#include "getCommand.h"
#include "putCommand.h"
#include "dirCommand.h"
#include "cdCommand.h"
#include "otherCommand.h"
#include "utils.h"
#include "myftp.h"



int MyFTP::run(const char *host, const char *portno) {
	
	this->soc = MyFTP::make_sock(host, portno);
	if (this->soc < 0)
		return -1;
	MyFTP::main_loop();
	
	return 0;
}


int MyFTP::make_sock(const char *host, const char *portno){

	char nbuf[NI_MAXHOST];
	char sbuf[NI_MAXSERV];
       	struct addrinfo hints, *res0;
	int soc, errcode;
	
	//初期化
	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	
	if (( errcode = getaddrinfo(host, portno, &hints, &res0)) != 0) {
		std::cerr << "getaddrinfo(): "  << gai_strerror(errcode) << std::endl;
		return -1;
	}

	if ((errcode = getnameinfo(res0->ai_addr, res0->ai_addrlen,
				   nbuf, sizeof(nbuf),
				   sbuf, sizeof(sbuf),
				   NI_NUMERICHOST | NI_NUMERICSERV )) != 0) {
		std::cerr << "getnameinfo(): "  << gai_strerror(errcode) << std::endl;
		freeaddrinfo(res0);
		return -1;
	}

			
		
	//ソケット作成
	if (( soc = socket(res0->ai_family, res0->ai_socktype, res0->ai_protocol)) == -1) {
		perror("socket");
		freeaddrinfo(res0);
		return -1;
	}


	//connect
	if (connect(soc, res0->ai_addr, res0->ai_addrlen) == -1) {
		perror("connect");
		close(soc);
		freeaddrinfo(res0);
		return -1;
	}

	freeaddrinfo(res0);

	return soc;
}



int MyFTP::main_loop()
{
	FILE *in, *out;
	char request[1024];
	int method;
	std::string rline, dir;
	std::vector<std::string> elem;
	std::vector<std::string> files;
	
	
	Command *cmd;
	
	if (fdopen_sock(this->soc, &in, &out) < -1) {
		perror("fdopen_sock");
		return -1;
	}

	fflush(in);
	fflush(out);
	
	while(1) {

		std::cout << "> " ;
		std::getline(std::cin, rline);

		if (rline.length() == 0)
			continue;
		
		elem = split(rline, ' ');

		
		method = this->parse_method(elem.at(0));
		
		
		switch (method) {

		case 0:
			std::cerr << "Connection Closed." << std::endl;
			fwrite("EXIT\n\n",1, 6, out);
			fclose(in);
			fclose(out);
			return 0;
		case 1:
			if (elem.size() < 2) {
				std::cerr << "Usage: get file1(,file2,...)" << std::endl;
				continue;
			}
						
			files = split(elem.at(1), ',');
			cmd = new GetCommand(in, out, files);
			break;
		case 2:
			
			if (elem.size() < 2) {
				std::cerr << "Usage: put file1(,file2,...)" << std::endl;
				continue;
			}
			
			files = split(elem.at(1), ',');
			cmd = new PutCommand(in, out, files);
			break;
		case 3:
			cmd = new DirCommand(in, out);
			break;
		case 4:
			dir = elem.at(1);
			if (chdir(dir.c_str()) < 0)
				std::cerr << "Cannot lcd" << std::endl;
			//break;
			continue;
		case 5:
			files = split(elem.at(1), ' ');
			cmd = new CdCommand(in, out, files);
			break;
			
		default:
			cmd = new OtherCommand();
			break;
					
		}
		
		cmd->execute();
		
		delete(cmd);
	}
	
	
}

int MyFTP::fdopen_sock(int soc, FILE **inp, FILE **outp)
{
	int soc2;

	if( (soc2=dup(soc)) < 0 )
	{
		return( -1 );
	}
	if( (*inp = fdopen( soc2, "r" )) == NULL )
	{
		close( soc2 );
		return( -1 );
	}
	if( (*outp = fdopen( soc, "w" )) == NULL )
	{
		fclose( *inp );
		*inp = 0 ;
		return( -1 );
	}
	setvbuf(*outp, (char *)NULL, _IONBF, 0);
	return( 0 );
}


int MyFTP::parse_method(std::string& method) 
{
	if (!method.compare("exit"))
		return 0;
	if (!method.compare("get"))
		return 1;
	if (!method.compare("put"))
		return 2;
	if (!method.compare("dir"))
		return 3;
	if (!method.compare("lcd"))
		return 4;
	if (!method.compare("cd"))
		return 5;
	
        return -1;
}
	
