
class MyFTP {

public:
	int run(const char *host, const char *portno);

private:
	
	//Class Variable
	//Accept FD
	int soc;
	
	int make_sock(const char *host, const char *portno);
	int main_loop();
	int fdopen_sock(int acc, FILE **inp, FILE **outp);
	int parse_method(std::string& req);
};
