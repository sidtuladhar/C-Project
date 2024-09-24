#include <string.h>
#include <openssl/evp.h>

void compute_hash(const char *input, unsigned char *output, unsigned int *output_len) {

    EVP_MD_CTX *mdctx; // pointer to an OpenSSL message digest context

    mdctx = EVP_MD_CTX_new();
    if(mdctx == NULL) {
    printf("Failed to create context\n");
    return;
    }

    if(1 != EVP_DigestInit_ex(mdctx, EVP_blake2s256(), NULL)) {
    printf("Failed to initialize BLAKE2s256\n");
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