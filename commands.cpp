/********************************** commands **********************************
*
*   Purpose:    Runs commands user can run from DOS prompt
*
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "commands.h"
//insert other libraries here

/********************************* showHelp() *********************************
*
*   Purpose:    Displays a list of available commands and programs
*
*   Input:      none
*
*   Output:     list of available commands
*
******************************************************************************/
void showHelp()
{
    printf("\nThe following options are available:\n");
    printf("\n");
    printf("\ns    Clear [S]creen");
    printf("\nh    Display [H]elp");
    printf("\nt    Display [T]ime and Date");
    printf("\nc    [C]alculate Resistance");
    printf("\nn    [N]umber Guessing Game");
    printf("\na    [A]ssignment Tracker");
    printf("\nm    Telescope [M]essaging");
    printf("\nb    [B]itmap Analysis");
    printf("\nq    [Q]uit DOS");
    printf("\n\n");
    return;
}

/********************************* showTime() *********************************
*
*   Purpose:    Displays a list of available commands and programs
*
*   Input:      none
*
*   Output:     list of available commands
*
*   Note:       Code derived from sample at:
*               www.dailyfreecode.com/code/display-current-date-time-589.aspx
*
******************************************************************************/
void showTime()
{
    time_t today;

    //retrieve a time object based on system clock and save it as "today"
    time(&today);

    //display time object with appropriate formatting
    printf("Today's date and time is: %s\n", ctime(&today));

    return;
}
