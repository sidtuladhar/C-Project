#ifndef NETWORK_H
#define NETWORK_H
#include "../include/mongoose.h"
#include <stdio.h>
#include <string.h>

void start_server();

void send_request(const char *ip, int port, const char *message);

void handle_websocket_message(struct mg_connection *c, struct mg_ws_message *wm);

void fn(struct mg_connection *c, int ev, void *ev_data);

#endif

