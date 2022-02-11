#include <stdio.h>
#include <string.h>
#include <cs50.h>

int main(void)
{
    int rows = get_int("How many bricks do you want? "); 
    // columns = (rows * 2) + 1
    int columns = ( rows * 2 ) + 1;


    //rows
    for( int r = 1; r <= rows; r = r + 1 ) {
        // 100 is just a large number
        // more on why we need to do this https://stackoverflow.com/questions/25502272/strcat-in-c-program-is-not-working
        char row_string[100] = "";
        //columns
        for( int c = 1 ; c <= columns; c = c + 1 ){
            if ( c < rows - r ) {
                strcat(row_string, " ");
            }
            // middle of bricks case
            else if (c == r + 1) {
                strcat(row_string, " ");
            } 
            else {
                strcat(row_string, "#");
            }
        }
      printf("%s\n", row_string);
   }
}
