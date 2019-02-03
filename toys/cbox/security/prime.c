#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <openssl/bn.h>

void prime_status(int code, int arg, void *cb_arg)
{
    return;
    if (code == 0) {
        printf("\n  * Found potential prime #%d ...", (arg+1));
    } else if (code == 1 && arg && !(arg % 10)) {
        printf(".");
    } else {
        printf("\n Got one!\n");
    }
}

BIGNUM *generate_prime(int bits, int safe)
{
    char *str;
    BIGNUM *prime;

    printf("Searching for a %sprime %d bits in size ...", (safe ? "safe " : ""), bits);

    prime = BN_generate_prime(NULL, bits, safe, NULL, NULL, prime_status, NULL);
    if (!prime) return NULL;

    str = BN_bn2dec(prime);
    if (str) {
        printf("Found prime: %s\n", str);
        OPENSSL_free(str);
    }

    return prime;
}

int main()
{
    BIGNUM *prime = generate_prime(64, 1);
    BN_print_fp(stdout, prime); puts("\n");
}

