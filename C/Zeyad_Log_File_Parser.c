#include <stdio.h>
#include <string.h>

void parse_security_log(const char *filename, const char *keyword) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "[Error] Could not read file: %s\n", filename);
        return;
    }

    char line[512];
    int current_line = 0;
    int matches = 0;

    printf("\n[+] Scanning '%s' for indicator '%s'...\n", filename, keyword);
    printf("------------------------------------------------------------\n");

    while (fgets(line, 512, fp) != NULL) {
        current_line++;

        if (strstr(line, keyword) != NULL) {
            matches++;
            printf("Line %-5d : %s", current_line, line);
            if (line[strlen(line) - 1] != '\n') {
                printf("\n");
            }
        }
    }

    printf("------------------------------------------------------------\n");
    printf("[*] Extraction complete. Total alerts detected: %d (out of %d lines)\n", matches, current_line);

    fclose(fp);
}

int main(void) {
    char file_input[256];
    char keyword_input[64];

    printf("Enter log file path: ");
    if (scanf("%255s", file_input) != 1) return 1;

    printf("Enter suspicious keyword (e.g. FAILED or 404): ");
    if (scanf("%63s", keyword_input) != 1) return 1;

    parse_security_log(file_input, keyword_input);
    return 0;
}
