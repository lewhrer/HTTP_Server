#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

short int kPort = 8080;
const char kMessage[] = "Hello from socket!\n";

int main()
{
    int sock, listener;
    struct sockaddr_in address;

    listener = socket(AF_INET // IPv4 protocol (AF_INET6 - IPv6 protocol)
                      ,
                      SOCK_STREAM // communication type, SOCK_STREAM:TCP, SOCK_DGRAM: UDP
                      ,
                      0); // protocol 0 - IP

    if (listener < 0)
    {
        std::cout << "Socket\n";
        exit(0);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(kPort);
    address.sin_addr.s_addr = htonl(INADDR_ANY); //INADDR_ANY - Address to accept any incoming messages

    if (bind(listener, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        std::cout << "Bind\n";
        exit(0);
    }

    listen(listener, 1);
    sock = accept(listener, NULL, NULL);

    while (sock == 0)
    {
        sock = accept(listener, NULL, NULL);

        if (sock < 0)
        {
            std::cout << "Accept";
            exit(0);
        }
    }

    send(sock, kMessage, sizeof(kMessage), 0);
    close(sock);

    std::cout << "Happy end!\n";
    return 0;
}