#include "single_thread_udp_receiver.h"

unsigned int HashFAQ6(const char * str);

bool process_receive_data(SOCKET socket) {
	sockaddr_in incom_addr;
	memset(&incom_addr, 0, sizeof(incom_addr));
	socklen_t len = sizeof(incom_addr);
	char buffer[256] = "";
	int rc = recvfrom(socket, buffer, sizeof(buffer), 0, (sockaddr*)&incom_addr, &len);
	if (rc > 0) {
        printf("[From: %s] Received data [%s]\n", inet_ntoa(incom_addr.sin_addr), buffer);
	    printf("Hash: %u\n", HashFAQ6(buffer));
	}
	else if (rc <= 0) {
	    error_msg("Can't receive data");
	}

	return true;
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