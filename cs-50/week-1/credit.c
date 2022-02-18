// input cs get_long 

// step 1: 1e13 < length > 1e15 || length == 1e14
// else: validate card & store last 2 values

// AMEX = start with 34 or 37; digits = 15
// MASTERCARD = start with 51, 52, 53, 54, or 55; 16 = digits
// VISA = numbers start with 4; 13- and 16-digit numbers


// Validate card
// step 1: get every other number by modelo 10 (even or odd) starting with the number’s second-to-last digit,
// step 2: multiply those by 2
// step 3: sum the numbers multiplied by 2
// step 4: add that sum to the remaining sum of digits
// step 5: check if last digit is 0
#include <stdio.h>
#include <cs50.h>

int main(void){

    long long credit = get_long_long("Number: ");
    // invalid if not 13, 15, 16 digit number
    if((1e12 <= credit && credit < 1e13) || (1e14 <= credit && credit < 1e16)){
        printf("%lld", credit);
    }
    else {
        printf("INVALID");
    }

}
