#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/ip_addr.h"

#define UDP_PORT 1337

static void udp_recv_callback(void *arg, struct udp_pcb *pcb,
                              struct pbuf *p, const ip_addr_t *addr, u16_t port) {
    if (!p) return;

    printf("Received %d bytes from %s:%d: %.*s\n",
           p->len,
           ipaddr_ntoa(addr),
           port,
           p->len,
           (char *)p->payload);

    pbuf_free(p);
}

int main() {
    stdio_init_all();

    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed!\n");
        return 1;
    }

    cyw43_arch_enable_sta_mode();

    // Replace with your own credentials
    const char *ssid = "Nacho Wifi";
    const char *pass = "TakisAreFantastic";

    printf("Connecting to Wi-Fi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms(ssid, pass, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
        printf("Failed to connect.\n");
        return 1;
    }
    printf("Connected to Wi-Fi!\n");

    struct udp_pcb *pcb = udp_new();
    if (!pcb) {
        printf("Failed to create UDP PCB.\n");
        return 1;
    }

    if (udp_bind(pcb, IP_ADDR_ANY, UDP_PORT) != ERR_OK) {
        printf("Failed to bind UDP port.\n");
        return 1;
    }

    udp_recv(pcb, udp_recv_callback, NULL);

    while (true) {
        // LwIP background processing
        sleep_ms(100);
    }

    return 0;
}
