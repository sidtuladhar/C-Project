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


void handle_commands(Blockchain *blockchain) {
    char command[256];
    while (1) {
        printf("\nEnter command (e.g., '/open <block_number>', '/back', '/q'): ");
        fgets(command, sizeof(command), stdin);

        command[strcspn(command, "\n")] = 0;

        if (strncmp(command, "/open", 5) == 0) {
            int block_number;
            if (sscanf(command, "/open %d", &block_number) == 1) {
                if (block_number >= 0 && block_number < blockchain->block_count) {
                    visualize_block(&blockchain->blocks[block_number]);
                } else {
                    printf("Block number out of range.\n");
                }
            } else {
                printf("Invalid command.\n");
            }
        } else if (strcmp(command, "/back") == 0) {
            //display_blockchain_summary(blockchain);
        } else if (strcmp(command, "/q") == 0) {
            break;
        } else if (strcmp(command, "") == 0) {
            // Do nothing if the user just pressed Enter
        } else if (strcmp(command, "/help") == 0) {
            printf("Commands:\n");
            printf("  /open <block_number> - Open a specific block for detailed view\n");
            printf("  /back - Return to the blockchain summary view\n");
            printf("  /q - Quit the program\n");
        } else if (strcmp(command, "/m") == 0) {
            
        } else {
            printf("Unknown command. Try 'open <block_number>', 'back', or 'quit'.\n");
        }
    }
}
