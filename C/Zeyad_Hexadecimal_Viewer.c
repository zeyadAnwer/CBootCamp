#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Syntax: %s <filepath>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "rb");
    if (!fp) {
        fprintf(stderr, "[!] Failed to open target file: %s\n", argv[1]);
        return 1;
    }

    unsigned char buffer[16];
    size_t n;
    size_t total_bytes = 0;

    while ((n = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        for (size_t i = 0; i < 16; i++) {
            if (i < n)
                printf("%02X ", buffer[i]);
            else
                printf("   ");
        }

        printf(" |");
        for (size_t i = 0; i < n; i++) {
            if (buffer[i] >= 32 && buffer[i] <= 126)
                putchar(buffer[i]);
            else
                putchar('.');
        }
        printf("|\n");

        total_bytes += n;
    }

    printf("\n[*] Total bytes inspected: %zu bytes\n", total_bytes);
    fclose(fp);
    return 0;
}
