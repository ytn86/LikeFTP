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

#include "myftpd.h"



int MyFTPd::run(const char *portno) {
	
	this->soc = MyFTPd::make_sock(portno);
	if (this->soc < 0)
		return -1;
	std::cout << "fd : " << this->soc << std::endl;;
	MyFTPd::accept_loop();
	
	return 0;
}


int MyFTPd::make_sock(const char *portno){
	struct addrinfo hints, *res0;
	int soc, opt, errcode;
	socklen_t opt_len;

	//初期化
	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (( errcode = getaddrinfo(NULL, portno, &hints, &res0)) != 0) {
		fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(errcode));
		return -1;
	}

	//ソケット作成
	if (( soc = socket(res0->ai_family, res0->ai_socktype, res0->ai_protocol)) == -1) {
		perror("socket");
		freeaddrinfo(res0);
		return -1;
	}

	opt = 1;
	opt_len = sizeof(opt);
	if (setsockopt(soc, SOL_SOCKET, SO_REUSEADDR, &opt, opt_len) == -1) {
		perror("setsockopt");
		close(soc);
		freeaddrinfo(res0);
		return -1;
	}

	//アドレス指定
	if (bind(soc, res0->ai_addr, res0->ai_addrlen) == -1) {
		perror("bind");
		close(soc);
		freeaddrinfo(res0);
		return -1;
	}

	//アクセスバックログ
	if (listen(soc, SOMAXCONN) == -1) {
		perror("listen");
		close(soc);
		freeaddrinfo(res0);
		return -1;
	}
	freeaddrinfo(res0);
	return soc;
}


int MyFTPd::accept_loop()
{
	char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
	struct sockaddr_storage from;
	int acc;
	socklen_t len;
	int pid;
	
	while(1) {
		len = sizeof(from);

		//accept
		if ((acc = accept(this->soc, (struct sockaddr *) &from, &len)) == -1) {
			if (errno != EINTR) {
				perror("accept");
				return -1;
			}
		} else {
			
			pid = fork();
			
			if (pid == 0) {
				//child
				//close(this->soc);
				getnameinfo((struct sockaddr *) &from, len,
					    hbuf, sizeof(hbuf),
					    sbuf, sizeof(sbuf),
					    NI_NUMERICHOST | NI_NUMERICSERV);
				std::cerr << "accept: " << hbuf << ":" << sbuf << std::endl;
				
				main_loop(acc);
				close(acc);
				std::cerr << "closed :" << acc << std::endl;;
			} else if(pid > 0) {
				close(acc);
			}
				
		}
	}
	return 0;

}


			

int MyFTPd::main_loop(int acc)
{
	FILE *in, *out;
	char request[1024];
	int method;
	Command *cmd;
	
	if (fdopen_sock(acc, &in, &out) < -1) {
		perror("fdopen_sock");
		return -1;
	}
	
	while(1) {

		std::fgets(request, 1024, in);
		method = this->parse_method(request);

		
		switch (method) {

		case 0:
			
			fclose(in);
			fclose(out);
			return 0;

		case 1:
			cmd = new GetCommand(in, out);
			break;
		case 2:
			cmd = new PutCommand(in, out);
			break;
		case 3:
			cmd = new DirCommand(in, out);
			break;
		case 4:
			cmd = new CdCommand(in, out);
			break;
		default:
			cmd = new OtherCommand(in, out);
			break;


		}

		cmd->execute();
		
		delete(cmd);
	}
	
	
}

int MyFTPd::fdopen_sock(int acc, FILE **inp, FILE **outp)
{
	int acc2 ;

	if( (acc2=dup(acc)) < 0 )
	{
		return( -1 );
	}
	if( (*inp = fdopen( acc2, "r" )) == NULL )
	{
		close( acc2 );
		return( -1 );
	}
	if( (*outp = fdopen( acc, "w" )) == NULL )
	{
		fclose( *inp );
		*inp = 0 ;
		return( -1 );
	}
	setvbuf(*outp, (char *)NULL, _IONBF, 0);
	return( 0 );
}


int MyFTPd::parse_method(char *req) 
{
	if (!strcmp(req, "EXIT\n"))
		return 0;
	if (!strcmp(req, "GET\n"))
		return 1;
	if (!strcmp(req, "PUT\n"))
		return 2;
	if (!strcmp(req, "DIR\n"))
		return 3;
	if (!strcmp(req, "CD\n"))
		return 4;
        return -1;
}
	
