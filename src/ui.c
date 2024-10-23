#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/block.h"

void visualize_blockchain(Blockchain *blockchain) {   

}

void visualize_block(Block *block) {
    char time_str[26];
    struct tm *tm_info;

    tm_info = localtime(&block->timestamp);
    strftime(time_str, 26, "%Y-%m-%d %H:%M:%S", tm_info);

    printf("+-----------------------+\n");
    printf("|       Block #%d        |\n", block->index);
    printf("+-----------------------+\n");
    printf("|  Previous Hash: %.5s |\n", block->prev_hash);  // Printing first 10 chars of hash
    printf("|  Timestamp: %.10s|\n", time_str);
    printf("|  Nonce: %d        |\n", block->nonce);
    printf("|  Data: %.10s     |\n", block->data);              // Limiting to 10 chars for formatting
    printf("+-----------------------+\n");
    printf("|   Hash: %.10s    |\n", block->hash);          // Printing first 10 chars of hash
    printf("+-----------------------+\n");

}
