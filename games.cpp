/************************************ games ***********************************
*
*   Purpose:    Contains code for games
*
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h> 

#include "games.h"
#include "io_functions.h"

/****************************** number_guess() ********************************
*
*   Purpose:    Game where users guess a random number between 1 and 50
*
*   Input:      none
*
*   Output:     none
*
******************************************************************************/
void number_guess()
{
    //variable to store user input for guesses
    int guess;

    //variable to store randomly number generated
    int target;

    //variable to count number of guesses
    int count;

    //variable to mangage loop
    int run = TRUE;

    //variable to store 'y' or 'n' choice for running program again
    char yorn;

    //constants to store error messages for user input
    const char *numerr = "Make sure it's a number between 1 and 50! \
                         Try again: ";
    const char *yornerr = "Enter [Y] for yes or [N] for no: ";

    //welcome message
    printf("***************************************************");
    printf("\n* Welcome to the number guessing game!            *");
    printf("\n* Guess a random number between 1 and 50.         *");
    printf("\n* Try to guess it in as few guesses as possible.  *\n");
    printf("***************************************************\n");

    while (run == TRUE)
    {
        count = 0;

        //generate random number and store in target
        target = get_rand();

        printf("\nRandom number generated!");
        printf("\nWhat is your first guess?: ");

        do
        {
            //increment guess count value
            count++;

            //clear keyboard buffer before each user input
            fflush(stdin);

            //call get_number() to get user input for guess
            guess = get_number(numerr);

            //provide user with feedback for next guess
            if (guess > 50)
            {
                printf("\nYour guess should not be above 50. Try again: ");
            }
            else if (guess > target)
            {
                printf("\nYour guess is too high. Try again: ");
            }
            else if (guess < target)
            {
                printf("\nYour guess is too low. Try again: ");
            }

            //continue to run the loop until user guesses target
        } while (guess != target);

        printf("\nExcellent! You guessed it in %d guesses!\n", count);
        printf("\nWould you like to play again? [Y/N]: ");

        yorn = get_char(yornerr, 'y', 'n');

        if (yorn == 'n')
        {
            //clear keyboard buffer before user input
            fflush(stdin);

            //exit run loop and application if user enters 'n'
            run = FALSE;
        }
    }

    printf("\n");
    return;
}