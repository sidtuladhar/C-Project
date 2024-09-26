#include "../include/ui.h"
#include "../include/block.h"
#include <time.h>
#include <string.h>
#include <stdio.h>


int main() {
    Blockchain blockchain;
    blockchain.blocks = NULL;
    blockchain.block_count = 0;

    // example block 1
    Block block1;
    block1.index = 0;
    block1.timestamp = time(NULL);
    strcpy(block1.prev_hash, "000000000000000000000");
    strcpy(block1.data, "First block data");
    block1.nonce = 0;
    mine_block(&block1);
    add_block(&blockchain, &block1);


    handle_commands(&blockchain);

    return 0;
}