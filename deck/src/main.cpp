// IP: 192.168.2.4

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    const char *pico_ip = "192.168.2.4"; // 🛠️ Replace with your Pico W IP
    const int pico_port = 1234;

    // Create socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        perror("Socket creation failed");
        return 1;
    }

    // Prepare destination address
    sockaddr_in dest{};
    dest.sin_family = AF_INET;
    dest.sin_port = htons(pico_port);
    if (inet_pton(AF_INET, pico_ip, &dest.sin_addr) <= 0)
    {
        perror("Invalid IP address");
        close(sock);
        return 1;
    }

    std::cout << "Type messages to send to " << pico_ip << ":" << pico_port << "\n";

    // Loop for user input
    while (true)
    {
        std::string line;
        std::cout << "> ";
        if (!std::getline(std::cin, line))
        {
            std::cout << "\nExiting.\n";
            break;
        }

        ssize_t sent = sendto(sock, line.c_str(), line.length(), 0,
                              reinterpret_cast<sockaddr *>(&dest), sizeof(dest));

        if (sent < 0)
        {
            perror("sendto failed");
        }
        else
        {
            std::cout << "Sent " << sent << " bytes\n";
        }
    }

    close(sock);
    return 0;
}
