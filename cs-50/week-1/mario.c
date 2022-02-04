#include <stdio.h>
#include <string.h>
#include <cs50.h>

int main(void)
{
    int input = get_int("How many bricks do you want? "); 
    //rows
    for( int r = 1; r <= input+1; r = r + 1 ){
        string row1 = "";
        string row2 = "";
        //columns
        for( int c = 1 ; c <= input+1; c = c + 1 ){
            if( r > c ){
                strcat(row1, " ");
                strcat(row2, "#");
            }
            else {
                strcat(row2, " ");
                strcat(row1, "#");
            }
        }
      printf("%s %s\n", row1, row2);
   }
}
