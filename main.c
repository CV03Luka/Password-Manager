#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h> // For toupper()

#define MAX_LENGTH 30
#define MIN_LENGTH 8

void generatePassword(int length, int includeNumbers, int includeSpecialChars);

int main() {
    int length;
    char includeNumbersInput, includeSpecialCharsInput;
    int includeNumbers, includeSpecialChars;
    char generateAnotherInput;

    do {
        // Get password length from user
        do {
            printf("Enter password length (min %d, max %d): ", MIN_LENGTH, MAX_LENGTH);
            scanf("%d", &length);
            if (length < MIN_LENGTH || length > MAX_LENGTH) {
                printf("Invalid length. Please enter a length between %d and %d.\n", MIN_LENGTH, MAX_LENGTH);
            }
        } while (length < MIN_LENGTH || length > MAX_LENGTH);

        // Ask user for complexity options
        printf("Include numbers (y/n): ");
        scanf(" %c", &includeNumbersInput);
        includeNumbers = (toupper(includeNumbersInput) == 'Y') ? 1 : 0;

        printf("Include special characters (y/n): ");
        scanf(" %c", &includeSpecialCharsInput);
        includeSpecialChars = (toupper(includeSpecialCharsInput) == 'Y') ? 1 : 0;

        // Seed random number generator
        srand(time(NULL));

        // Generate and print password
        generatePassword(length, includeNumbers, includeSpecialChars);

        // Ask the user if they want to generate another password
        printf("Generate another password? (y/n): ");
        scanf(" %c", &generateAnotherInput);

    } while (toupper(generateAnotherInput) == 'Y');

    printf("Exiting...\n");

    return 0;
}

void generatePassword(int length, int includeNumbers, int includeSpecialChars) {
    const char* lowercase = "abcdefghijklmnopqrstuvwxyz";
    const char* uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char* numbers = "0123456789";
    const char* specialChars = "!@#$%^&*()-_=+[{]}|;:',<.>/?";

    // Determine character set based on user choices
    char* charset;
    int charsetSize = 0;
    if (includeNumbers && includeSpecialChars) {
        charsetSize = 62 + 16; // 26 lowercase + 26 uppercase + 10 numbers + 16 special characters
        charset = malloc(charsetSize + 1);
        snprintf(charset, charsetSize + 1, "%s%s%s%s", lowercase, uppercase, numbers, specialChars);
    } else if (includeNumbers) {
        charsetSize = 62; // 26 lowercase + 26 uppercase + 10 numbers
        charset = malloc(charsetSize + 1);
        snprintf(charset, charsetSize + 1, "%s%s%s", lowercase, uppercase, numbers);
    } else {
        charsetSize = 52; // 26 lowercase + 26 uppercase
        charset = malloc(charsetSize + 1);
        snprintf(charset, charsetSize + 1, "%s%s", lowercase, uppercase);
    }

    // Generate password
    char password[MAX_LENGTH + 1];
    for (int i = 0; i < length; i++) {
        int index = rand() % charsetSize;
        password[i] = charset[index];
    }
    password[length] = '\0';

    printf("Generated password: %s\n", password);

    // Free allocated memory
    free(charset);
}
