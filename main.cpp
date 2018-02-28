#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

int main() {
	cout<<"hello,this is server!"<<endl;

	//socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//bind
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));

	addr.sin_family = AF_INET;
	//addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(6666);

	int nBind = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if(nBind < 0) {
		cout<<"bind socket errro!"<<strerror(errno)<<errno<<endl;
		return -1;
	}

	//listen
	int nListen = listen(sockfd, 1);
	if(nListen < 0) {
		cout<<"listen socket error:"<<strerror(errno)<<errno<<endl;
		return -1;
	}

	//accept
	while(1) {
		int conn = accept(sockfd, (struct sockaddr*)NULL, NULL);
		if(conn < 0) {
			cout<<"accept socket error:"<<strerror(errno)<<errno<<endl;
			continue;
		} else {
			cout<<"new connection coming."<<" conn="<<conn<<" sockfd="<<sockfd<<endl;
		}

		char buff[256] = {'\0'};
		//recv from conn, not sock
		int n = recv(conn, buff, 256, 0);
		if(n>0) {
			cout<<"buff="<<buff<<" size="<<n<<endl;
		} else {
			cout<<"get buff error:"<<strerror(errno)<<errno<<endl;
		}

		close(conn);
	}

	close(sockfd);
	return 0;
}
