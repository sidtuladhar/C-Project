#include "../include/mongoose.h"
#include "../include/network.h"
#include "../include/dht.h"
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static const char *s_listen_on = "ws://localhost:8000";


void handle_signal(int signal) {
    printf("\nShutting down...\n");
    dht_cleanup();
    exit(0);
}

void start_websocket_server() {
    struct mg_mgr mgr;  // Event manager
    mg_mgr_init(&mgr);  // Initialize event manager
    printf("Starting WS listener on %s/websocket\n", s_listen_on);

    if (mg_http_listen(&mgr, s_listen_on, fn, NULL) == NULL) {
        fprintf(stderr, "Failed to create WebSocket listener\n");
        mg_mgr_free(&mgr);
        exit(EXIT_FAILURE);
    }

    while (1) {
        mg_mgr_poll(&mgr, 1000);
        
        dht_poll();

        usleep(100000);
    }

    mg_mgr_free(&mgr);
}

int main(int argc, char *argv[]) {
    signal(SIGINT, handle_signal);

    if (dht_init() != 0) {
        fprintf(stderr, "Failed to initialize DHT\n");
        return EXIT_FAILURE;
    }

    start_websocket_server();

    dht_cleanup();
    return 0;
}
