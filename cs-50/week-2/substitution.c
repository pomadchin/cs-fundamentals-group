#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> 
#include <string.h>
#include <cs50.h>

int main(int argc, string argv[]) {
    if(argc != 2) {
        printf("Usage: ./substitution key\n");
        return 0;
    }

    // 0 is the name of the programm
    // idx 0 = a, ... indx 25 = z
    string key = argv[1];

    // check if the keylength is 26
    if (strlen(key) != 26) {
        printf("Key length must be of 26 chars\n");
        return -1;
    }

    // convert it to lower case
    for(int i = 0; i < strlen(key); i++) {
        key[i] = tolower(key[i]);
    }

    string s = get_string("");

    printf("\n");
    printf("key: %s\n", key);
    printf("plaintext: %s\n", s);

    for(int i = 0; i < strlen(s); i++) {
        char c = s[i];
        if(islower(c)) {
            s[i] = key[(c - 'a')];
        } else if(isupper(c)) {
            s[i] = toupper(key[(tolower(c) - 'A')]);
        }
    }

    printf("ciphertext: %s\n", s);
    printf("\n");

    return 0;
}
