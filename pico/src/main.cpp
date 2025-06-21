#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/ip_addr.h"
#include <cstring>
#include <cstdio>

#define UDP_PORT 1234

void udp_recv_callback(void *arg, struct udp_pcb *pcb, struct pbuf *p,
                       const ip_addr_t *addr, u16_t port) {
    if (!p) return;
    printf("Received %d bytes from %s:%d\n", p->len, ipaddr_ntoa(addr), port);
    pbuf_free(p);
}

int main() {
    stdio_usb_init();
    sleep_ms(2000); // USB initialization delay

    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed!\n");
        return -1;
    }

    // Open network configuration
    const char *ssid = "Nothing";
    const char *pass = NULL;  // or "" for empty password

    cyw43_arch_enable_sta_mode();  // ← Add this line
    printf("Connecting to open network: %s\n", ssid);

    int retry = 0;
    while (retry < 5) {
        printf("Attempt %d...\n", retry + 1);
        if (cyw43_arch_wifi_connect_timeout_ms(ssid, NULL, CYW43_AUTH_OPEN, 10000) == 0) {
            printf("Connected!\n");
            break;
        }
        printf("Failed. Retrying...\n");
        sleep_ms(2000);
        retry++;
    }
    if (retry >= 5) {
        printf("Gave up after 5 attempts.\n");
        return -1;
    }

    printf("Connected! IP: %s\n", ip4addr_ntoa(netif_ip4_addr(netif_default)));

    // UDP setup
    struct udp_pcb *pcb = udp_new();
    if (!pcb) {
        printf("Failed to create UDP PCB\n");
        return -1;
    }

    if (udp_bind(pcb, IP_ADDR_ANY, UDP_PORT) != ERR_OK) {
        printf("UDP bind failed\n");
        return -1;
    }

    udp_recv(pcb, udp_recv_callback, nullptr);
    printf("Listening for UDP on port %d\n", UDP_PORT);

    while (true) {
        cyw43_arch_poll();
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(500);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(500);
    }
}
