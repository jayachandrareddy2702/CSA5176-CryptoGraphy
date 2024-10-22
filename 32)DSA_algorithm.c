#include <openssl/dsa.h>
#include <openssl/sha.h>
#include <openssl/err.h>
#include <string.h>
#include <stdio.h>

void handle_errors() {
    ERR_print_errors_fp(stderr);
    abort();
}

int main() {
    // Initialize OpenSSL
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    // Generate DSA key
    DSA *dsa = DSA_new();
    if (dsa == NULL) handle_errors();

    if (DSA_generate_parameters_ex(dsa, 1024, NULL, 0, NULL, NULL, NULL) == 0)
        handle_errors();
    
    if (DSA_generate_key(dsa) == 0) handle_errors();

    // Message to sign
    unsigned char message[] = "This is a message to sign";
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    // Hash the message
    SHA256(message, strlen((char *)message), hash);

    // Sign the hash
    unsigned int sig_len;
    unsigned char *signature = (unsigned char *)malloc(DSA_size(dsa));

    if (DSA_sign(0, hash, SHA256_DIGEST_LENGTH, signature, &sig_len, dsa) == 0)
        handle_errors();

    printf("Message signed successfully!\n");

    // Verify the signature
    if (DSA_verify(0, hash, SHA256_DIGEST_LENGTH, signature, sig_len, dsa) == 1)
        printf("Signature is valid.\n");
    else
        printf("Signature is invalid.\n");

    // Sign the same message again to show different signature
    unsigned char *signature2 = (unsigned char *)malloc(DSA_size(dsa));
    if (DSA_sign(0, hash, SHA256_DIGEST_LENGTH, signature2, &sig_len, dsa) == 0)
        handle_errors();

    printf("Message signed again!\n");

    if (memcmp(signature, signature2, sig_len) != 0)
        printf("The two signatures are different, demonstrating DSA's use of a unique 'k'.\n");
    else
        printf("The two signatures are the same, which shouldn't happen in DSA.\n");

    // Free memory and clean up
    free(signature);
    free(signature2);
    DSA_free(dsa);
    EVP_cleanup();
    ERR_free_strings();

    return 0;
}
