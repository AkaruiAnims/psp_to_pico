#include <switch.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>  // Add this for close()
#include <string.h>
#include <stdio.h>

#define PORT 1234

int main(int argc, char **argv) {
    // Initialize Switch services
    socketInitializeDefault();
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
    PadState pad;
    padInitializeDefault(&pad);

    consoleInit(NULL);
    printf("Pico W UDP HID Sender\nPress + to exit\n\n");

    // Get Pico's IP
    SwkbdConfig kbd;
    swkbdConfigMakePresetDefault(&kbd);
    swkbdConfigSetGuideText(&kbd, "Enter Pico W's IP");
    char pico_ip[16] = "192.168.1.100";
    swkbdShow(&kbd, pico_ip, sizeof(pico_ip));

    printf("Target IP: %s\n", pico_ip);

    // Create socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(PORT);
    dest_addr.sin_addr.s_addr = inet_addr(pico_ip);

    printf("Press buttons to send...\n");

    while (appletMainLoop()) {
        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);

        if (kDown & HidNpadButton_Plus) break;

        const char *msg = NULL;
        if (kDown & HidNpadButton_A) msg = "A";
        else if (kDown & HidNpadButton_B) msg = "B";
        else if (kDown & HidNpadButton_X) msg = "X";
        else if (kDown & HidNpadButton_Y) msg = "Y";
        else if (kDown & HidNpadButton_Up) msg = "UP";
        else if (kDown & HidNpadButton_Down) msg = "DOWN";
        else if (kDown & HidNpadButton_Left) msg = "LEFT";
        else if (kDown & HidNpadButton_Right) msg = "RIGHT";

        if (msg) {
            sendto(sock, msg, strlen(msg), 0,
                 (struct sockaddr*)&dest_addr, sizeof(dest_addr));
            printf("Sent: %s\n", msg);
        }

        consoleUpdate(NULL);
    }

    // Proper socket cleanup
    close(sock);  // Use closesocket() instead of close()
    socketExit();
    consoleExit(NULL);
    return 0;
}
