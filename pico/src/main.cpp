#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/ip_addr.h"
#include <cstring>
#include <cstdio>

#define UDP_PORT 1234 // Any port you want

void udp_recv_callback(void *arg, struct udp_pcb *pcb, struct pbuf *p,
                       const ip_addr_t *addr, u16_t port)
{
    if (!p)
        return;

    printf("Received %d bytes from %s:%d:\n", p->len, ipaddr_ntoa(addr), port);
    for (int i = 0; i < p->len; i++)
    {
        putchar(((char *)p->payload)[i]);
    }
    putchar('\n');

    pbuf_free(p); // Always free!
}

int main()
{
    stdio_usb_init();
    sleep_ms(2000); // Give USB time to settle

    if (cyw43_arch_init())
    {
        printf("Wi-Fi init failed!\n");
        return -1;
    }

    const char *ssid = "Nacho Wifi";
    const char *pass = "TakisAreFantastic";

    printf("Connecting to Wi-Fi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms(ssid, pass, CYW43_AUTH_WPA2_AES_PSK, 30000))
    {
        printf("Failed to connect to Wi-Fi.\n");
        return -1;
    }
    netif_set_hostname(netif_default, "pico-wifi");
    ip4_addr_t ip = netif_default->ip_addr;

    printf("Connected! IP: %s\n", ip4addr_ntoa(netif_ip4_addr(netif_default)));

    struct udp_pcb *pcb = udp_new();
    if (!pcb)
    {
        printf("Failed to create UDP PCB\n");
        return -1;
    }

    if (udp_bind(pcb, IP_ADDR_ANY, UDP_PORT) != ERR_OK)
    {
        printf("UDP bind failed\n");
        return -1;
    }

    udp_recv(pcb, udp_recv_callback, nullptr);

    printf("Listening for UDP packets on port %d...\n", UDP_PORT);

    // Main loop
    while (true)
    {
        cyw43_arch_poll(); // Needed for background arch
        //print packets or print ip
        if (cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN))
        {
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0); // Turn off LED
        }
        else
        {
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1); // Turn on LED
        }

        ip4_addr_t ip = netif_default->ip_addr;
        printf("✅ Pico IP Address: %s\n", ip4addr_ntoa(&ip));
        sleep_ms(10);
    }
}

// // include pico-sdk and wifi libraries
// #include <iostream>
// #include "pico/stdlib.h"
// #include "pico/cyw43_arch.h"

// int main() {
//     // Initialize the standard I/O
//     stdio_init_all();

//     // wait for input before proceeding
//     std::cout << "Press Enter to continue..." << "\n";
//     std::cin.get();

//     std::cout << "Hello, Pico!" << "\n";

//     // Initialize the CYW43 Wi-Fi chip
//     if (cyw43_arch_init()) {
//         std::cerr << "Failed to initialize CYW43 Wi-Fi chip!" << "\n";
//         return 1;
//     }
//     std::cout << "CYW43 Wi-Fi chip initialized successfully!" << "\n";

//     while ( true ) {
//         // Main loop: keep the program running
//         //blink the onboard LED
//         cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);  // Turn on the LED
//         sleep_ms(500);  // Sleep for 0.5 seconds
//         cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);  // Turn off the LED
//         sleep_ms(1000);  // Sleep for 1 second
//     };

//     return 0;
// };