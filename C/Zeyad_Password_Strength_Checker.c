#include <stdio.h>
#include <string.h>
#include <ctype.h>

void check_policy_compliance(char pass[]) {
    int len = (int)strlen(pass);
    int has_upper = 0, has_lower = 0, has_digit = 0, has_sym = 0;
    int pts = 0;

    for (int i = 0; i < len; i++) {
        unsigned char ch = (unsigned char)pass[i];
        if (isupper(ch)) {
            has_upper = 1;
        } else if (islower(ch)) {
            has_lower = 1;
        } else if (isdigit(ch)) {
            has_digit = 1;
        } else if (ispunct(ch)) {
            has_sym = 1;
        }
    }

    if (len >= 8) pts += 2;
    pts += (has_upper + has_lower + has_digit + has_sym);

    printf("\n[+] Length detected: %d chars\n", len);

    if (len >= 8 && has_upper && has_lower && has_digit && has_sym) {
        printf("[+] All security requirements are met.\n");
    } else {
        printf("[!] Remaining requirements to fulfill:\n");
        if (len < 8)      printf("    - Minimum length of 8 characters (need %d more)\n", 8 - len);
        if (!has_upper)   printf("    - At least one uppercase letter (A-Z)\n");
        if (!has_lower)   printf("    - At least one lowercase letter (a-z)\n");
        if (!has_digit)   printf("    - At least one number (0-9)\n");
        if (!has_sym)     printf("    - At least one special symbol (!@#$...)\n");
    }

    if (len < 8 || pts <= 3) {
        printf("[*] Final Rating: Weak Password\n");
    } else if (pts <= 5) {
        printf("[*] Final Rating: Acceptable Password\n");
    } else {
        printf("[*] Final Rating: Strong Password\n");
    }
}

int main(void) {
    char input_buf[100];

    printf("Password > ");
    if (scanf("%99s", input_buf) == 1) {
        check_policy_compliance(input_buf);
    }

    return 0;
}
