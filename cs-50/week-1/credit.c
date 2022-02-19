#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <cs50.h>

int main(void) {
    long long n = get_long_long("Enter the credit card number: ");
    printf("Entered number: %llu \n", n);

    // copy
    long long x = n;
    bool f = false;
    
    // accumulator
    int evens = 0;
    int odds = 0;

    // last two digits track
    // if by the end f is true than the first is od else ed
    int ed = 0;
    int od = 0;
    
    while(x != 0) {
        int d = x % 10;
        if(f) {
            ed = d;
            // could be a two digit number
            int dd = (d * 2);
            while(dd != 0) {
              evens += dd % 10;
              dd /= 10;  
            }
            f = false;

        } else {
            od = d;
            odds += d;
            f = true;
        }

        x /= 10;
    }

    // change values so od is the first always
    if(!f) { 
        int tmp = ed;
        ed = od;
        od = tmp;
    }

    int sum = evens + odds;

    if(sum % 10 != 0) {
        printf("INVALID\n");
        return -1;
    }

    int mk = od * 10 + ed;

    if(mk == 34 || mk == 37) {
        printf("AMEX\n");
        return 0;
    }

    if(mk >= 51 && mk <= 55) {
        printf("MasterCard\n");
        return 0;
    }

    if(od == 4) {
        printf("VISA\n");
        return 0;
    }

    printf("A mysterious card with a valid checksum.\n");

    printf("\n");
    return 0;
}
