/******************************************************************************

Program: RetroDOS
Purpose: Emulate a basic DOS environment
Author:  Darren Conley - Oct 1, 2016
Change log:
Darren Conley - Oct 1, 2016
1. First fully operational version of all functions complete.

Darren Conley - Oct 2, 2016
1. Added braces to all if/else if statements in response to
RSM report output.

Darren Conley - Oct 24, 2016
1. Split single .cpp file into multiple header files and .cpp files

Darren Conley - Nov 1, 2016 (Sprint 2)
1. Added Assignment Tracker program
2. Added Telescope Messaging program
3. Added clear screen function

Darren Conley - Nov 13, 2016 (Sprint 3)
1. Added BMP Analysis program
2. Modified Assignment structure include complete/incomplete info
3. Added edit_assignment() function to assignment tracker

Darren Conley - Nov 14, 2016 (Sprint 3)
1. Added toggle_status() function for assignment tracker
- Code for "nory" array adapted from info found at:
stackoverflow.com/questions/6599707/2d-character-array-initialization-in-c
2. Added functionality to save and retrieve assignments from assignments.txt
- Code for fscanf function that allows spaces to be read in strings found at:
stackoverflow.com/questions/1950057/can-fscanf-read-whitespace
5. Added functionality to save and retrieve messages to data file in 
Telescope Messaging

Darren Conley - Nov 18, 2016 (Sprint 3)
1. Altered starting value for low_colour_tot variable in pixel occurance
calculations for bmp_analysis() to accomodate high values for lowest occuring
colour

Darren Conley - Nov 21, 2016 (Sprint 3)
1. Altered calculation for padding amounts to correct calculation error 
for bitmap analysis program
2. Added help message to error message in DOS menu

Darren Conley - Dec 5, 2016 (Sprint 4)
1. Modified assignment tracker to make use of dynamic arrays for data storage
 - Changed array creation code
 - Modified populate_structures() function
 - Modified edit_assignment() function

 Darren Conley - Dec 7, 2016 (Sprint 4)
 1. Added code to free memory being used for dynamic structures

********************************* LIBRARIES **********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "sprint4.h"
#include "utilities.h"
#include "games.h"
#include "commands.h"

/********************************* MAIN FUNCTION *****************************/
void main(void)
{
    int run = TRUE;
    char input;

    //loop to return user to prompt after running other functions
    while (run == TRUE)
    {
        printf("C:/> ");

        //clear keyboard buffer before new input
        fflush(stdin);
        input = tolower(getchar());

        //verify input is one of the valid options
        switch (input) {
        case 'h':
            showHelp();
            break;
        case 't':
            showTime();
            break;
        case 's':
            //clear screen command
            system("cls");
            break;
        case 'c':
            calculate_resistance();
            break;
        case 'n':
            number_guess();
            break;
        case 'a':
            track_assignments();
            break;
        case 'm':
            telescope_messaging();
            break;
        case 'b':
            bitmap_analysis();
            break;
        case 'q':
            run = FALSE;
            break;
        default:
            printf("\nError: Unrecognized function or program name");
            printf("\nType 'h' for list of possible commands\n\n");
        }
    }
    return;
}