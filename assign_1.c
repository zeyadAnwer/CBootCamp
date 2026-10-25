#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char password[100];
    int has_upper = 0;
    int has_lower = 0;
    int has_digit = 0;
    int has_symbol = 0;
    
    printf("Enter a password to check: ");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

//prapration the password for validation I noticed that fgets() includes the newline character in the input when I enter it, so I need to remove it for accurate validation.
    size_t len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[len - 1] = '\0';
        len--;
    }


// Validate the password
    for (size_t i = 0; i < len; i++) {
        if (isupper(password[i])) {
            has_upper = 1;
        } else if (islower(password[i])) {
            has_lower = 1;
        } else if (isdigit(password[i])) {
            has_digit = 1;
        } else if (ispunct(password[i])) {
            has_symbol = 1;
        }
    }

    int valid = 1;

    printf("\n--- Password Validation Results ---\n");

    if (len < 8) {
        printf("Length condition failed: Password must be more than 8 characters long (Current length: %zu).\n", len);
        valid = 0;
    }
    if (!has_upper) {
        printf(" Uppercase condition failed: Password must contain at least one uppercase letter (A-Z).\n");
        valid = 0;
    }
    if (!has_lower) {
        printf("Lowercase condition failed: Password must contain at least one lowercase letter (a-z).\n");
        valid = 0;
    }
    if (!has_digit) {
        printf("Number condition failed: Password must contain at least one number (0-9).\n");
        valid = 0;
    }
    if (!has_symbol) {
        printf("Symbol condition failed: Password must contain at least one symbol (e.g., !, @, #, $).\n");
        valid = 0;
    }
    printf("\nYour Password: %s\n", password);
    printf("\nYour Password Length: %zu\n", len);
    // Final verdict
    if (valid) {
        printf("\nSuccess! Your password meets our policy.\n");
    } else {
        printf("\nWeak Password: Your password broke our policy.\n");
    }

    return 0;
}