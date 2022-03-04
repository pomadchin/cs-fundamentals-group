#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> 
#include <string.h>
#include <cs50.h>

// ** Caesar Cipher math thought process
// ** Formula:  Ci = (Pi + k)mod26
// **
// ** EG:  (plaintext[i] + key) % 26)
char rotate(char c, int key) {
    if(islower(c)) return 'a' + ((c - 'a' + key) % 26);
    if(isupper(c)) return 'A' + ((c - 'A' + key) % 26);
    // dunno though do we need it?
    if(isdigit(c)) return '0' + ((c - '0' + key) % 10);
    return c;
}

int main(int argc, string argv[]) {
    if(argc != 2) {
        printf("Usage: ./caesar key\n");
        return 0;
    }

    // first arg is the shift key 
    // 0 is the name of the programm
    int key = atoi(argv[1]);

    string s = get_string("");

    printf("\n");
    printf("plaintext: %s\n", s);

    for(int i = 0; i < strlen(s); i++) {
        s[i] = rotate(s[i], key);
    }

    printf("ciphertext: %s\n", s);
    printf("\n");

    return 0;
}
