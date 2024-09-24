#include <string.h>
#include <openssl/evp.h>

void compute_blake2b(const char *input, unsigned char *output, unsigned int *output_len) {

    EVP_MD_CTX *mdctx; // pointer to an OpenSSL message digest context

    mdctx = EVP_MD_CTX_new();
    if(mdctx == NULL) {
    printf("Failed to create context\n");
    return;
    }

    if(1 != EVP_DigestInit_ex(mdctx, EVP_blake2b512(), NULL)) {
    printf("Failed to initialize BLAKE2b-512\n");
    EVP_MD_CTX_free(mdctx);
    return;
    }

    // Hash the input message
    if(1 != EVP_DigestUpdate(mdctx, input, strlen(input))) {
        printf("Failed to hash input\n");
        EVP_MD_CTX_free(mdctx);
        return;
    }

    // Finalize the hash and store the result in 'output'
    if(1 != EVP_DigestFinal_ex(mdctx, output, output_len)) {
        printf("Failed to finalize hash\n");
        EVP_MD_CTX_free(mdctx);
        return;
    }

    // Clean up and free the context
    EVP_MD_CTX_free(mdctx);
}

int main() {
    const char *message = "Hello, Blockchain!";
    unsigned char hash[EVP_MAX_MD_SIZE];  // Buffer to hold the hash
    unsigned int hash_len;                // Length of the resulting hash

    // Compute BLAKE2b-512 hash
    compute_blake2b(message, hash, &hash_len);

    // Print the resulting hash in hexadecimal format
    printf("BLAKE2b-512 hash of '%s':\n", message);
    for (unsigned int i = 0; i < hash_len; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}