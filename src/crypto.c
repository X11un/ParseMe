#include <openssl/evp.h>
#include <string.h>

void computeSha256(const char *inputStr, char *outputHex) {
    // Initialize OpenSSL digest context
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    // Compute SHA-256 hash
    EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(mdctx, inputStr, strlen(inputStr));
    EVP_DigestFinal_ex(mdctx, hash, &hash_len);
    
    // Clean up context
    EVP_MD_CTX_free(mdctx);

    // Convert binary hash to hexadecimal string
    for (unsigned int i = 0; i < hash_len; i++) {
        sprintf(outputHex + (i * 2), "%02x", hash[i]);
    }
    outputHex[64] = '\0';
}