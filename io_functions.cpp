/******************************** io_functions ********************************
*
*   Purpose:    Contains input and output functions
*
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h> 

#include "io_functions.h"

/******************************* get_number() *********************************
*
*   Purpose:    Get and validate a number from the user
*
*   Input:      errmsg      const char  error message for failed validation
*
*   Output:     num         int         number as integer
*
******************************************************************************/
int get_number(const char *errmsg)
{
    //variable to manage loop
    int numcheck = TRUE;

    //variable to store validity result from validate_digit()
    int valid;

    //variable to store number from user input
    char num[10];

    while (numcheck == TRUE)
    {
        //clear keyboard buffer before input
        fflush(stdin);
        scanf("%s", num);

        //call validate_digit on user input
        valid = validate_digit(num);
        if (valid == 0)
        {
            //display error message if user input not valid
            printf("\n%s", errmsg);
        }
        else
        {
            numcheck = FALSE;
        }
    }

    //convert user input to integer before returning
    return atoi(num);
}

/******************************** get_char() **********************************
*
*   Purpose:    Get and validate a character from the user based on 2 options
*
*   Input:      errmsg      const char  error message for failed validation
*               char1       char        valid character 1
*               char2       char        valid character 2
*
*   Output:     letter      char        valid lowercase letter entered by user
*
******************************************************************************/
char get_char(const char *errmsg, char char1, char char2)
{
    //variable to manage loop
    int charcheck = TRUE;

    //variable to store validity result from validate_char()
    int valid;

    //variable to store user input
    char check_this;

    while (charcheck == TRUE)
    {
        //clear keyboard buffer before input
        fflush(stdin);
        scanf("%c", &check_this);

        //call validate_char on user input, passing 2 valid input options
        valid = validate_char(check_this, char1, char2);
        if (valid == tolower(check_this))
        {
            charcheck = FALSE;
        }
        else
        {
            //display error message if user input not valid
            printf("\n%s", errmsg);
        }
    }
    //return validated user input
    return valid;
}

/***************************** validate_digit() *******************************
*
*   Purpose:    Returns 1 if a string contains only positive digits,
*               otherwise returns 0
*
*   Input:      value       char *      string to be checked
*
*   Output:     valid       int         1 if valid, 0 if not valid
*
******************************************************************************/
int validate_digit(char * value)
{
    //variable to manage 1st loop
    int count;

    //variable to manage 2nd loop
    int valid = FALSE;

    for (count = 0; value[count] != '\0'; count++)
    {
        //verify that value contains only digits
        if (isdigit(value[count]) == 0)
        {
            valid = FALSE;
            /* Note re: feedback about removing the break below:
            The purpose of the break is to stop iterating through
            the string characters to check for non-digits once a
            single non-digit is found. I can't find any other way
            to stop the operation immediately upon failure. Using
            a test variable that is checked as part of a while test
            would require testing for and passing in the lenth of
            characters in the input string each time the function
            is called, which seems like a worse option than simply
            keeping the break. */
            break;
        }
        else
        {
            valid = TRUE;
        }
    }

    if (valid == TRUE)
    {
        //verify that value is > 0
        if ((atoi(value)) <= 0)
        {
            valid = FALSE;
        }
        else
        {
            valid = TRUE;
        }
    }
    return valid;
}

/***************************** validate_char() *******************************
*
*   Purpose:    Returns a lowercase character if it matches one of two passed
*               characters, otherwise returns 0
*
*   Input:      checkthis   char        character to be validated
*               char1       char        1st valid character in lowercase
*               char2       char        2nd valid character in lowercase
*
*   Output:     checkthis   char        validated character in lowercase
*
******************************************************************************/
int validate_char(char checkthis, char char1, char char2)
{
    //convert checkthis to lowercase to avoid capitalization mismatches
    checkthis = tolower(checkthis);

    //verify that checkthis is only a single character
    if (sizeof(checkthis) != sizeof(char1))
    {
        return FALSE;
    }

    //verify that checkthis is the same as one of the two valid options
    if ((checkthis == char1) || (checkthis == char2))
    {
        return checkthis;
    }
    else
    {
        return FALSE;
    }
}

/******************************** get_rand() **********************************
*
*   Purpose:    Generate and return a random integer
*
*   Input:      none
*
*   Output:     randnum         int         random number
*
*   Reference:  http://www.cprogramming.com/tutorial/random.html
*
******************************************************************************/
int get_rand()
{
    //variable to store generated random number
    int randnum;

    //variable to store data for seeding function (srand)
    time_t seconds;

    //assign value to current time to seconds variable
    time(&seconds);

    //seed randum number generator with seconds value
    srand((unsigned int)seconds);

    //generate random number between RANDMAX and RANDMIN values
    randnum = rand() % (RANDMAX - RANDMIN + 1) + RANDMIN;

    //return random number value
    return randnum;
}