#include "../include/dht.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define DHT_PORT 6881  // Example port number for DHT

// Global variable for the DHT socket
static int dht_socket = -1;
static RoutingTable routing_table = { .count = 0 };

// Initialize the DHT system
int dht_init() {
    // Create a UDP socket for the DHT
    dht_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (dht_socket < 0) {
        perror("Failed to create DHT socket");
        return -1;
    }

    // Bind the socket to the DHT port
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(DHT_PORT);

    if (bind(dht_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Failed to bind DHT socket");
        close(dht_socket);
        return -1;
    }

    printf("DHT initialized and listening on port %d\n", DHT_PORT);
    return 0;  // Success
}

// Clean up the DHT system
void dht_cleanup() {
    if (dht_socket >= 0) {
        close(dht_socket);
        dht_socket = -1;
        printf("DHT socket closed.\n");
    }
}

// Poll the DHT for incoming messages
void dht_poll() {
    if (dht_socket < 0) {
        return;
    }

    char buffer[1024];
    struct sockaddr_in src_addr;
    socklen_t addr_len = sizeof(src_addr);

    // Check for incoming DHT messages
    ssize_t received = recvfrom(dht_socket, buffer, sizeof(buffer) - 1, MSG_DONTWAIT,
                                (struct sockaddr *)&src_addr, &addr_len);
    if (received > 0) {
        buffer[received] = '\0';  // Null-terminate the received data
        printf("Received DHT message: %s\n", buffer);
        // Here you would parse the DHT message and handle it (PING, FIND_NODE, etc.)
        handle_dht_message(buffer, &src_addr);
    }
}

// Parse and handle different types of DHT messages
void handle_dht_message(const char *message, struct sockaddr_in *src_addr) {
    if (strncmp(message, "PING", 4) == 0) {
        printf("Handling PING message.\n");
        // You can respond with a PONG or log the event
    } else if (strncmp(message, "FIND_NODE", 9) == 0) {
        printf("Handling FIND_NODE message.\n");
        // Implement FIND_NODE response logic here
    } else {
        printf("Unknown DHT message type.\n");
    }
}

// Send a PING message to a target
void send_ping(DHTNode *target) {
    if (dht_socket < 0) {
        fprintf(stderr, "DHT socket is not initialized.\n");
        return;
    }

    // Construct a simple PING message
    char message[256];
    snprintf(message, sizeof(message), "PING %s %d", target->ip, target->port);

    // Send the PING message to the target's IP and port
    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(target->port);
    inet_pton(AF_INET, target->ip, &dest_addr.sin_addr);

    ssize_t sent = sendto(dht_socket, message, strlen(message), 0,
                          (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (sent < 0) {
        perror("Failed to send PING message");
    } else {
        printf("PING message sent to %s:%d\n", target->ip, target->port);
    }
}

// Handle a PING response
void handle_ping_response() {
    if (dht_socket < 0) {
        return;
    }

    char buffer[256];
    ssize_t received = recv(dht_socket, buffer, sizeof(buffer) - 1, 0);
    if (received > 0) {
        buffer[received] = '\0';
        printf("Received response: %s\n", buffer);
    }
}

// Store a peer in the routing table
void store_peer_info(DHTNode *node) {
    if (routing_table.count < MAX_NODES) {
        routing_table.nodes[routing_table.count++] = *node;
        printf("Stored peer info: %s:%d\n", node->ip, node->port);
    }
}

// Find the closest node to the target ID
DHTNode* find_closest_node(const char *target_id) {
    for (int i = 0; i < routing_table.count; i++) {
        if (strcmp(routing_table.nodes[i].node_id, target_id) == 0) {
            return &routing_table.nodes[i];
        }
    }
    return NULL;  // Node not found
}