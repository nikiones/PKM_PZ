#include "ping.h"

unsigned int HashFAQ6(const char * str);

THREAD_VOID handle_connection(void* psocket) {
	CHECK_VOID_IO(psocket, "Empty connection thread data\n");
	SOCKET socket;
	CHECK_VOID_IO((socket = ((SOCKET)psocket)) > 0, "Invalid connection thread data\n");
	sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);
	CHECK_VOID_IO(!getpeername(socket, (sockaddr*)&addr, &addr_len), "Error retrieving peer info\n");
	char* str_in_addr = inet_ntoa(addr.sin_addr);
	printf("[%s:%d]>>%s\n", str_in_addr, ntohs(addr.sin_port), "Establish new connection");

    while (true) {
		char buffer[256] = "";
		int rc = recv(socket, buffer, sizeof(buffer), 0);
		if (rc > 0) {
            printf("Received: %s\n", buffer);
            printf("Hash: %u\n", HashFAQ6(buffer));
        }
		else {
			break;
		}
	}

	close_socket(socket);
	printf("[%s:%d]>>%s\n", str_in_addr, ntohs(addr.sin_port), "Close incoming connection");
}

unsigned int HashFAQ6(const char * str)
{

    unsigned int hash = 0;

    for (; *str; str++)
    {
        hash += (unsigned char)(*str);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;

}