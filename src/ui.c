#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "block.h"

void visualize_blockchain(Blockchain *blockchain) {   

}

void handle_commands(Blockchain *blockchain) {
    char command[256];
    while (1) {
        printf("\nEnter command (e.g., '/open <block_number>', '/back', '/q'): ");
        fgets(command, sizeof(command), stdin);

        command[strcspn(command, "\n")] = 0;

        if (strncmp(command, "/open", 5) == 0) {
            int block_number;
            if (sscanf(command, "open %d", &block_number) == 1) {
                display_block_details(blockchain, block_number - 1);  // Subtract 1 for 0-based index
            } else {
                printf("Invalid command. Use '/open <block_number>'.\n");
            }
        } else if (strcmp(command, "/back") == 0) {
            display_blockchain_summary(blockchain);
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

void visualize_block(Block *block) {

}

