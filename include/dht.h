#ifndef DHT_H
#define DHT_H

#include <netinet/in.h>  
#include <time.h>        

#define MAX_NODES 100

typedef struct {
    char node_id[20];    
    char ip[16];         
    int port;            
    time_t last_seen;    
} DHTNode;

typedef struct {
    DHTNode nodes[MAX_NODES];
    int count;           
} RoutingTable;

int dht_init();

void dht_cleanup();

void dht_poll();

void handle_dht_message(const char *message, struct sockaddr_in *src_addr);

void send_ping(DHTNode *target);

void handle_ping_response();

void store_peer_info(DHTNode *node);

DHTNode* find_closest_node(const char *target_id);

#endif  // DHT_H