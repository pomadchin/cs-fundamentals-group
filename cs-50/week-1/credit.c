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

    int sum_evens = 0;
    int sum_odds = 0;
    int first_two_digits = 0;
    long long credit = get_long_long("Number: ");
    // invalid if not 13, 15, 16 digit number
    if(!((1e12 <= credit && credit < 1e13) || (1e14 <= credit && credit < 1e16))){
        printf("INVALID");
        return -1;
    }
    int value_check = 1;
    while(credit > 0){
        if(9 < credit && credit < 100){
            first_two_digits = credit;
        }
        int digit = credit % 10;
        if(value_check % 2 == 0){
            int multiple = (digit * 2);
            while(multiple > 0){
                int other_digit = multiple % 10;
                sum_evens += other_digit;
                multiple = multiple / 10;
            }
        }
        else{
            sum_odds += digit;
        }
        credit = credit / 10;
        value_check = value_check + 1;
    }
    int total_sum = sum_evens + sum_odds;
    if (total_sum % 10 != 0){
        printf("INVALID");
        return -1;
    }
    if(50 < first_two_digits && first_two_digits < 56){
        printf("MASTERCARD");
        return 0;
    }
    if(first_two_digits / 10 == 4){
        printf("VISA");
        return 0;
    }
    if(first_two_digits == 34 || first_two_digits == 37){
        printf("American Express");
        return 0;
    }
    printf("OTHER");
    return 0;
}
