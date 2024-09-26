#ifndef UI_H
#define UI_H
#include "block.h"

void visualize_blockchain(Blockchain *blockchain);

void handle_commands(Blockchain *blockchain);

void visualize_block(Block *block);

#endif