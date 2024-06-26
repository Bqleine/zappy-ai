/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Private key generation
*/

#include <stdlib.h>
#include <sodium.h>

int main(void)
{
    unsigned char key[crypto_aead_xchacha20poly1305_ietf_KEYBYTES];

    if (sodium_init() == -1) {
        fprintf(stderr, "Failed to initialize libsodium\n");
        return 1;
    }
    crypto_aead_xchacha20poly1305_ietf_keygen(key);
    printf("{ ");
    for (size_t i = 0; i < crypto_aead_xchacha20poly1305_ietf_KEYBYTES; i++) {
        if (i != 0)
            printf(", ");
        printf("0x%X", key[i]);
    }
    printf(" }\n");
    return EXIT_SUCCESS;
}
