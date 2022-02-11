#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <cs50.h>

int main(void) {
    int rows;
    do {
        rows = get_int("How many bricks do you want? "); 
        printf("Height: %d \n", rows);
    } while (rows < 1 || rows > 8);

    printf("\n");

    //  # #
    // ## ##
    for(int r = 1; r <= rows; r++) {
        // front spaces
        string string_row = (char*) malloc((rows - r) + 2 * r * sizeof(char));

        // doing from 0
        // insert
        // r = 1
        // c = 0 until 2 - 1;
        for(int c = 0; c < rows - r; c++) {
            strcat(string_row, " ");
        }

        // we always populate 2 * n + 1 chars
        // starting from 0
        // r = 1
        // c = 0; until 3
        // c == 0 => #
        // if c == 1 => " "
        // c > 1 => "#" 
        for(int c = 0; c < 2 * r + 1; c++) {
            if(c == r) { strcat(string_row, " "); }
            else strcat(string_row, "#");
        }

        // // front spaces
        // for(int i = 0; i < rows - r; i++) { printf(" "); }
        // // populate 2 * r + 1 chars
        // // the mid would be the space
        // for(int i = 0; i < 2 * r + 1; i++) { 
        //     if(i == r) { printf(" "); }
        //     else { printf("#"); }
        // }

        printf("%s\n", string_row);
    }
    printf("\n");
}
