
class MyFTPd {

public:
	int run(const char *portno);

private:
	
	//Class Variable
	//Accept FD
	int soc;
	
	int make_sock(const char *portno);
	int accept_loop();
	int main_loop(int acc);
	int fdopen_sock(int acc, FILE **inp, FILE **outp);
	int parse_method(char *req);
};
