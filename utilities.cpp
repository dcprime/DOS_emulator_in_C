/********************************* utilities **********************************
*
*   Purpose:    Contains utility programs
*
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h> 

#include "io_functions.h"
#include "utilities.h"

/*************************** calculate_resistance() ***************************
*
*   Purpose:    Displays equivalent resistance for two inputted resistor values
*
*   Input:      res1        float       value of resistor 1
*               res2        float       value of resistor 2
*               sorp        int         series or parallel calculation
*               yorn        int         yes or no for repeating the program
*
*   Output:     eqvRes      float       equivalent value of the resistors
*
******************************************************************************/
void calculate_resistance()
{
    //input variables for [s] or [p] and [y] or [n]
    char sorp;
    char yorn;

    //variables to store resistance values
    int res1;
    int res2;

    //loop variable
    int run = TRUE;

    //variable to store calculation result
    float result;

    //error messages for each input to be passed to validating functions
    const char *numerr = "Resistor values must be numbers \
                         greater than 0. Try again: ";
    const char *sorperr = "Enter [S] for Series or [P] for Parallel: ";
    const char *yornerr = "Enter [Y] for yes or [N] for no: ";

    //welcome message
    printf("***************************************************");
    printf("\n* This program will calculate equivalent          *");
    printf("\n* resistance (ER) in series or parallel.          *");
    printf("\n* Values entered must be positive, whole numbers. *\n");
    printf("***************************************************\n");

    while (run == TRUE)
    {
        //get two resistance values
        printf("\nEnter first resistor value in Ohms: ");
        res1 = get_number(numerr);

        printf("\nEnter second resistor value in Ohms: ");
        res2 = get_number(numerr);

        //input for series or parallel calculation
        printf("\nAre these resistors in [S]eries or [P]arallel? [S/P]: ");
        sorp = get_char(sorperr, 's', 'p');

        //clear keyboard buffer 
        fflush(stdin);

        //get and display equivalent resistance calculation
        result = get_resistance(res1, res2, sorp);
        printf("\nThe equivalent resistance is %0.2f Ohms\n", result);

        //ask user if they want to run program again
        printf("\nWould you like to do another calculation? [Y/N]: ");
        yorn = get_char(yornerr, 'y', 'n');

        //exit loop and function if user enters 'n'
        if (yorn == 'n')
        {
            fflush(stdin);
            run = FALSE;
        }
        fflush(stdin);
    }
    printf("\n");
    return;
}

/***************************** get_resistance() *******************************
*
*   Purpose:    Calculate equivalent resistance from two resistor values
*               in series or parallel. Returns result as float.
*
*   Input:      res1        int         value of resistor 1
*               res2        int         value of resistor 2
*               sorp        char        series or parallel indicator
*
*   Output:     result      float       calculated result as float
*
******************************************************************************/
float get_resistance(int res1, int res2, char sorp)
{
    //variable to store calculation result
    float result;

    //if resistors in series, run the appropriate calculation formula
    if (sorp == 's')
    {
        result = (res1 + res2);
        return result;
    }

    //if resistors in parallel, run the appropriate calculation formula
    if (sorp == 'p')
    {
        result = (1 / ((1 / (float)res1) + (1 / (float)res2)));
        return result;
    }
}
/**************************** track_assignments() *****************************
*
*   Purpose:    Store and display information about upcoming assignments
*
*   Input:      none
*
*   Output:     none
*
******************************************************************************/
void track_assignments(void)
{
    FILE *fptr;
    ASSIGNMENT *my_assignments = NULL;
    int count = 0;      //variable for to iterate loop counts
    int assnbr = 0;     //input variable for editing assignments
    int nbr = 0;        //stores total number of assignments saved
    int entries = 0;    //input variable for creating new assignments
    int run = TRUE;     //variable to manage main while loop
    int run_c = TRUE;   //variable to manage while loop for case 'c'
    int run_v = TRUE;   //variable to manage while loop for case 'v'
    int run_e = TRUE;   //variable to manage while loop for case 'e'
    int run_m = TRUE;   //variable to manage while loop for case 'm'
    char input;         //variable to manage switch statement
    const char *nory[2] = { "no", "yes" };
    char file_name[] = "assignments.txt";

    //load existing assignments from file_name
    fptr = fopen(file_name, "r");
    if (fptr != NULL)
    {
        //read number of existing assignments from beginning of file_name
        fscanf(fptr, "%d\n", &nbr);

        //reserve memory for "nbr" of assignments
        my_assignments = (ASSIGNMENT *)
            realloc(my_assignments, nbr*sizeof(ASSIGNMENT));

        //verify memory properly allocated
        if (my_assignments != NULL)
        {
            //loop to read assignments from file_name into my_assignments array
            for (count = 0; count < nbr; count++)
            {
                fscanf(fptr, "%254[^\n] %254[^\n] %254[^\n] %d %d\n",
                    &my_assignments[count].subject,
                    &my_assignments[count].prof,
                    &my_assignments[count].ass_name,
                    &my_assignments[count].due_date,
                    &my_assignments[count].complete);
            }
        }

        else
        {
            printf("/nError allocating memory/n");
        }
        
    }
    else
    {
        printf("\nError reading from %s", file_name);
        printf("\nCheck that file exists and is formatted properly\n\n");
    }
    fclose(fptr);

    //welcome message
    printf("****************************************");
    printf("\n* This program will allow you to enter *");
    printf("\n* and track assignments by due date    *");
    printf("\n****************************************\n");

    while (run == TRUE)
    {
        //main menu
        printf("\n----------------------------------");
        printf("\n[C]reate new assignment");
        printf("\n[V]iew assignments");
        printf("\n[E]dit existing assignments");
        printf("\n[M]ark assignment complete/incomplete");
        printf("\n[Q]uit program");
        printf("\n\nPlease enter C, V, E, M, or Q: ");

        fflush(stdin);
        input = tolower(getchar());

        switch (input) {
        case 'c':
            run_c = TRUE;
            while (run_c == TRUE)
            {
                printf("\nChoose number of assignments to enter ");
                printf("(up to %d): ", NBRENTRIES);
                fflush(stdin);
                scanf("%d", &entries);

                if (entries > 0 && entries <= NBRENTRIES)
                {
                    //loads menu for entering assignment data
                    //and updates nbr to reflect total number of assignments
                    nbr = populate_structures(&my_assignments, entries, nbr);
                    run_c = FALSE;
                    break;
                }
                else
                {
                    printf("\nThat is not a valid number. ");
                    printf("Please try again.\n");
                }
            }
            break;
        case 'v':
            //checks if any assignment data has been entered
            if (nbr < 1)
            {
                printf("\nPlease enter assignment data ");
                printf("before viewing assignments\n");
                break;
            }
            else
            {
                run_v = TRUE;
                while (run_v == TRUE)
                {
                    //menu for viewing assignments
                    printf("\nView [N]ext assignment due");
                    printf("\nView [A]ll assignments");
                    printf("\n\nPlease enter N or A: ");

                    fflush(stdin);
                    input = tolower(getchar());

                    switch (input){
                    case 'n':
                    case 'a':
                        //loads function for displaying assigment data
                        print_structures(my_assignments, input, nbr);
                        run_v = FALSE;
                        break;
                    default:
                        printf("\nThat is not a valid menu option. ");
                        printf("Please try again.\n");
                    }
                }
                break;
            }
        case 'e':
            //checks if any assignment data has been entered
            if (nbr < 1)
            {
                printf("\nPlease enter assignment data ");
                printf("before editing assignments\n");
                break;
            }
            else
            {
                run_e = TRUE;
                while (run_e == TRUE)
                {
                    //menu for editing assignments
                    printf("\nExisting assignments:\n");

                    for (count = 0; count < nbr; count++)
                    {
                        printf("\n[%d] ", count+1);
                        printf("%s: ", my_assignments[count].subject);
                        printf("%s", my_assignments[count].ass_name);
                    }
                    
                    printf("\n\nPlease enter number of assignment to edit: ");

                    fflush(stdin);
                    scanf("%d", &assnbr);

                    if (assnbr > 0 && assnbr <= nbr)
                    {
                        //loads function for editing assignment data
                        edit_assignment(&my_assignments, assnbr - 1);
                        run_e = FALSE;
                        break;
                    }
                    else
                    {
                        printf("\nThat is not a valid number. ");
                        printf("Please try again.\n");
                    }
                }
                break;
            }
        case 'm':
            //checks if any assignment data has been entered
            if (nbr < 1)
            {
                printf("\nPlease enter assignment data ");
                printf("before marking assignments complete\n");
                break;
            }
            else
            {
                run_m = TRUE;
                while (run_m == TRUE)
                {
                    //menu for marking assignments complete/incomplete
                    printf("\nExisting assignments:\n");

                    for (count = 0; count < nbr; count++)
                    {
                        printf("\n[%d] ", count + 1);
                        printf("%s: ", my_assignments[count].subject);
                        printf("%s - ", my_assignments[count].ass_name);
                        printf("Complete: ");
                        printf("%s", nory[my_assignments[count].complete]);
                    }

                    printf("\n\nEnter number of assignment to toggle ");
                    printf("complete/incomplete status: ");

                    fflush(stdin);
                    scanf("%d", &assnbr);

                    if (assnbr > 0 && assnbr <= nbr)
                    {
                        //toggle complete/incomplete status
                        toggle_status(my_assignments, assnbr - 1); 
                        run_e = FALSE;
                        break;
                    }
                    else
                    {
                        printf("\nThat is not a valid number. ");
                        printf("Please try again.\n");
                    }
                }
                break;
            }
        case 'q': //quits program
            printf("\n");
            run = FALSE;
            break;
        default:
            printf("\nThat is not a valid menu option. Please try again.\n");
        }
    }

    //write my_assignments data to text file before exiting program
    fptr = fopen(file_name, "w");
    if (fptr != NULL)
    {
        //write number of assignments to beginning of file
        fprintf(fptr, "%d\n", nbr);

        //loop to write my_assignments data
        for (count = 0; count < nbr; count++)
        {
            fprintf(fptr, "%s\n %s\n %s\n %d\n %d\n\n",
                my_assignments[count].subject,
                my_assignments[count].prof,
                my_assignments[count].ass_name,
                my_assignments[count].due_date,
                my_assignments[count].complete);
        }
    }
    else
    {
        printf("\nError writing data to %s\n", file_name);
    }

    void free(void *my_assignments);
    fclose(fptr);
    
    return;
}

/*************************** populate_structures() ****************************
*
*   Purpose:    Allows the user to populate assignment structures
*
*   Input:      assignments ASSIGNMENT  array of assignments
*               nbr         int         number of assignments to populate
*               entries     int         number of existing assignments
*
*   Output:     nbr         int         updated total number of assignments
*
******************************************************************************/
int populate_structures(ASSIGNMENT **assignments, int entries, int nbr)
{

    int count = 0;

    *assignments = (ASSIGNMENT *)realloc(*assignments, 
        (entries + nbr)*sizeof(ASSIGNMENT));

    for (int count = 0; count < entries; count++)
    {
        printf("\nFor new assignment %d\n", count + 1);

        printf("\nEnter assignment subject (or class): ");
        fflush(stdin);
        gets((*assignments)[count + nbr].subject);

        printf("Enter subject professor's name: ");
        fflush(stdin);
        gets((*assignments)[count + nbr].prof);

        printf("Enter assignment name: ");
        fflush(stdin);
        gets((*assignments)[count + nbr].ass_name);

        printf("Enter assignment due date (YYMMDD): ");
        fflush(stdin);
        scanf("%d", &(*assignments)[count + nbr].due_date);

        /* Difficult to validate date entry - use regex?
        Ideally should check that date is in future,
        that month is 1-12 and day is 1-(28||30||31)
        depending on the actual month. This seems outside
        of the scope of this assignment, however. */

        (*assignments)[count + nbr].complete = FALSE;

        printf("\nNew assignment %d saved!\n", count + 1);
    }

    printf("\n%d new assignments saved", entries);
    printf("\n%d assignments total in database\n", nbr + entries);

    return nbr + entries;
}

/***************************** edit_assignment() ******************************
*
*   Purpose:    Allows the user to populate assignment structures
*
*   Input:      assignment  ASSIGNMENT  array with assignment being edited
*               nbr         int         number of asssignment being edited
*
*   Output:     none
*
******************************************************************************/
void edit_assignment(ASSIGNMENT **assignments, int nbr)
{
    int loop = TRUE;
    char input;
    const char *nory[2] = { "no", "yes" };

    //print existing info for assignment being edited
    printf("\nCurrent info for assignment %d\n", nbr + 1);
    printf("\nSubject: %s", (*assignments)[nbr].subject);
    printf("\nProfessor's name: %s", (*assignments)[nbr].prof);
    printf("\nAssignment name: %s", (*assignments)[nbr].ass_name);
    printf("\nDue date (YYMMDD): %d", (*assignments)[nbr].due_date);
    printf("\nComplete: %s\n", nory[(*assignments)[nbr].complete]);

    printf("\nEnter assignment subject (or class): ");
    fflush(stdin);
    gets((*assignments)[nbr].subject);

    printf("Enter subject professor's name: ");
    fflush(stdin);
    gets((*assignments)[nbr].prof);

    printf("Enter assignment name: ");
    fflush(stdin);
    gets((*assignments)[nbr].ass_name);

    printf("Enter assignment due date (YYMMDD): ");
    fflush(stdin);
    scanf("%d", &(*assignments)[nbr].due_date);

    while (loop == TRUE)
    {
        printf("Is assignment complete? [Y/N]: ");

        fflush(stdin);
        input = tolower(getchar());

        switch (input) {
        case 'y':
            (*assignments)[nbr].complete = TRUE;
            loop = FALSE;
            break;
        case 'n':
            (*assignments)[nbr].complete = FALSE;
            loop = FALSE;
            break;
        default:
            printf("\nThat is not a valid option. Please try again.\n");
        }
    }

    printf("\nAssignment updated!\n");
}

/****************************** toggle_status() *******************************
*
*   Purpose:    Toggle status of complete/incomplete for assignments
*
*   Input:      assignment  ASSIGNMENT  array with assignment being toggled
*               nbr         int         number of asssignment being toggled
*
*   Output:     none
*
******************************************************************************/
void toggle_status(ASSIGNMENT assignments[], int nbr)
{
    const char *nory[2] = { "no", "yes" };

    if (assignments[nbr].complete == FALSE)
    {
        assignments[nbr].complete = TRUE;
    }
    else
    {
        assignments[nbr].complete = FALSE;
    }

    printf("\nAssignment %d updated:\n", nbr + 1);
    printf("%s: ", assignments[nbr].subject);
    printf("%s - ", assignments[nbr].ass_name);
    printf("Complete: ");
    printf("%s\n", nory[assignments[nbr].complete]);

    return;
}

/**************************** print_structures() ******************************
*
*   Purpose:    Allows the user to print assignment structures
*
*   Input:      assignments ASSIGNMENT  array of assignments
*               nora        char        choice to print next or all assignments
*               nbr         int         number of assignments
*                                       in assignments array
*
*   Output:     none
*
******************************************************************************/
void print_structures(ASSIGNMENT assignments[], char nora, int nbr)
{
    int most_recent = assignments[0].due_date;
    int lowest = 0;
    int count = 0;
    const char *nory[2] = { "no", "yes" };

    if (nora == 'n')
    {
        lowest = count;

        //loop for finding assignment with closest due date
        for (count = 0; count < nbr; count++)
        {
            if (assignments[count].due_date < most_recent)
            {
                most_recent = assignments[count].due_date;
                lowest = count;
            }
        }
        printf("\nNext assignment due:\n");
        printf("\nSubject: %s", assignments[lowest].subject);
        printf("\nProfessor's Name: %s", assignments[lowest].prof);
        printf("\nAssignment name: %s", assignments[lowest].ass_name);
        printf("\nDue date (YYMMDD): %d", assignments[lowest].due_date);
        printf("\nComplete: ");
        printf("%s\n", nory[assignments[lowest].complete]);
    }
    else
    {
        printf("\nList of all assignments:\n");
        for (count = 0; count < nbr; count++)
        {
            printf("\nAssignment %d\n", count + 1);
            printf("\nSubject: %s", assignments[count].subject);
            printf("\nProfessor's Name: %s", assignments[count].prof);
            printf("\nAssignment name: %s", assignments[count].ass_name);
            printf("\nDue date (YYMMDD): %d", assignments[count].due_date);
            printf("\nComplete: ");
            printf("%s\n", nory[assignments[count].complete]);
        }
    }
}

/*************************** telescope_messaging() ****************************
*
*   Purpose:    Create and print messages to the telescope system devices
*
*   Input:      none
*
*   Output:     none
*
******************************************************************************/
void telescope_messaging(void)
{
   
    INFO my_messages[NBRMSSGS]; //array of INFO to save valid user messages
    int union_size;             //size of element in union for writing data
    int union_nbr;              //number of times union element must be written
    int nbr = 0;                //total number of messages
    int entries = 0;            //number of new messages created by user
    int count = 0;              //variable to manage reading/writing loop
    int run = TRUE;             //variable to manage main while loop
    int run_c;                  //variable to manage while loop for case 'c'
    int run_p;                  //variable to manage while loop for case 'p'
    char input;                 //user input for menu choices

    FILE *fptr;                 
    char file_name[] = "telescope_messages.dat";

    //read data file to populate my_messages
    fptr = fopen(file_name, "rb");
    if (fptr != NULL)
    {
        //read number of messages from beginning of file
        fread(&nbr, sizeof(nbr), 1, fptr);

        //loop to write my_messages data
        for (count = 0; count < nbr; count++)
        {
            fread(&my_messages[count].messagetype, sizeof(int), 1, fptr);
            fread(&my_messages[count].deviceID, sizeof(int), 1, fptr);

            //capture size of data in union for writing and
            //number of times to write union elements
            if (my_messages[count].messagetype == INSTRUCTION)
            {
                union_size = STRSIZE;
                union_nbr = 1;
            }
            else if (my_messages[count].messagetype == CODE)
            {
                union_size = sizeof(int);
                union_nbr = 1;
            }
            else
            {
                union_size = sizeof(float);
                union_nbr = 2;
            }
            fread(&my_messages[count].message, union_size, union_nbr, fptr);
        }
    }
    else
    {
        printf("\nError reading data from %s\n", file_name);
    }
    fclose(fptr);

    //welcome message
    printf("**********************************************");
    printf("\n* Welcome to the telescope messaging system  *");
    printf("\n* Please choose from the menu below          *");
    printf("\n**********************************************\n");

    while (run == TRUE)
    {
        //main menu
        printf("\n----------------------------------");
        printf("\n[C]reate new message");
        printf("\n[P]rint previously written message(s)");
        printf("\n[Q]uit program");
        printf("\n\nPlease enter C, P, or Q: ");

        fflush(stdin);
        input = tolower(getchar());

        switch (input) {
        case 'c':
            run_c = TRUE;
            while (run_c == TRUE)
            {
                printf("\nChoose number of messages to create ");
                printf("(up to %d): ", NBRMSSGS);
                fflush(stdin);
                scanf("%d", &entries);

                if (entries > 0 && entries <= NBRMSSGS)
                {
                    //load menu for message creation
                    create_messages(my_messages, entries, nbr);
                    nbr = entries + nbr;
                    run_c = FALSE;
                    break;
                }
                else
                {
                    printf("\nThat is not a valid number. ");
                    printf("Please try again.\n");
                }
            }
            break;
        case 'p':
            //check that message data exists before attempting to print
            if (nbr < 1)
            {
                printf("\nPlease enter message data ");
                printf("before printing messages\n");
                break;
            }
            else
            {
                run_p = TRUE;
                while (run_p == TRUE)
                {
                    //main printing menu
                    printf("\nChoose to print by");
                    printf("\n  Message [T]ype");
                    printf("\n  [D]estination Device");
                    printf("\n  Message [N]umber");
                    printf("\n\nPlease enter T, D or N: ");

                    fflush(stdin);
                    input = tolower(getchar());

                    switch (input){
                    case 't':
                    case 'd':
                    case 'n':
                        //load second printing menu
                        print_messages(my_messages, input, nbr);
                        run_p = FALSE;
                        break;
                    default:
                        printf("\nThat is not a valid menu option. ");
                        printf("Please try again.\n");
                    }
                }
                break;
            }
        case 'q': //quit program
            printf("\n");
            run = FALSE;
            break;
        default:
            printf("\nThat is not a valid menu option. Please try again.\n");
        }
    }

    //write my_messages to data file
    fptr = fopen(file_name, "wb");
    if (fptr != NULL)
    {
        //write number of messages to beginning of file
        fwrite(&nbr, sizeof(nbr), 1, fptr);

        //loop to write my_messages data
        for (count = 0; count < nbr; count++)
        {
            fwrite(&my_messages[count].messagetype, sizeof(int), 1, fptr);
            fwrite(&my_messages[count].deviceID, sizeof(int), 1, fptr);

            //capture size of data in union for writing and
            //number of times to write union elements
            if (my_messages[count].messagetype == INSTRUCTION)
            {
                union_size = STRSIZE;
                union_nbr = 1;
            }
            else if (my_messages[count].messagetype == CODE)
            {
                union_size = sizeof(int);
                union_nbr = 1;
            }
            else
            {
                union_size = sizeof(float);
                union_nbr = 2;
            }
            fwrite(&my_messages[count].message, union_size, union_nbr, fptr);
        }
    }
    else
    {
        printf("\nError writing data to %s\n", file_name);
    }
    fclose(fptr);

    return;
}

/***************************** create_messages() ******************************
*
*   Purpose:    Allows the user to populate assignment structures
*
*   Input:      messages    INFO        array of INFO structures
*               entries     int         number of INFO messages to populate
*               nbr         int         total number of INFO messages 
*
*   Output:     none
*
******************************************************************************/
void create_messages(INFO my_messages[], int entries, int nbr)
{
    int count = 0;      //loop iterator variable
    char type;          //variable to store type of message to create
    int loop;           //variable to manage main while loop
    int code_loop;      //variable to manage while loop for case CODE
    int coord_loop;     //variable to manage while loop for case COORD
    int valid;          //stores result of validate_digit check

    //variables for message input
    char code[STRSIZE]; //stores user input for CODE
    int icode;          //stores CODE input as int after validation
    float xcoord;       //stores x-coordinate for COORD
    float ycoord;       //stores y-coordinate for COORD

    for (int count = 0; count < entries; count++)
    {
        printf("\n\nFor new message %d\n", count + 1);

        //loop to capture message type
        loop = TRUE;
        while (loop == TRUE)
        {
            //menu for selecting message type
            printf("\nSelect message type:");
            printf("\n[I]nstruction");
            printf("\n[C]ode");
            printf("\nCoo[R]dinate");
            printf("\n\nPlease enter I, C, or R: ");

            fflush(stdin);
            type = tolower(getchar());

            //sets messagetype and deviceID based on messagetype
            switch (type) {
            case 'i':
                my_messages[count + nbr].messagetype = INSTRUCTION;
                my_messages[count + nbr].deviceID = TECH1;
                loop = FALSE;
                break;
            case 'c':
                my_messages[count + nbr].messagetype = CODE;
                my_messages[count + nbr].deviceID = MOTOR1;
                loop = FALSE;
                break;
            case 'r':
                my_messages[count + nbr].messagetype = COORD;
                my_messages[count + nbr].deviceID = PLOTTER;
                loop = FALSE;
                break;
            default:
                printf("\nThat is not a valid menu option. ");
                printf("Please try again.\n");
            }
        } //end loop for message type

        //switch case for entering message content
        switch (my_messages[count + nbr].messagetype){
        case INSTRUCTION:
            printf("\nEnter instruction: ");
            fflush(stdin);
            gets(my_messages[count + nbr].message.instruction);
            break;
        case CODE:
            code_loop = TRUE;
            while (code_loop == TRUE)
            {
                printf("\nEnter code (1-%d): ", CODEMAX);

                fflush(stdin);
                scanf("%s", &code);

                //checks that user input is > 0 and does not contain alpha
                valid = validate_digit(code);

                switch (valid){
                case TRUE:
                    //checks that code is less than CODEMAX
                    icode = atoi(code);
                    if (icode <= CODEMAX)
                    {
                        code_loop = FALSE;
                        break;
                    }
                    else
                    {
                        //fall through to default error message
                    }
                default:
                    printf("\nThat is not a valid code entry. ");
                    printf("Please try again.\n");
                }
            }
            my_messages[count + nbr].message.code = icode;
            break;
        case COORD:
            coord_loop = TRUE;
            //loop to capture x-coordinate input
            while (coord_loop == TRUE)
            {
                printf("\nEnter x-coordinate ");
                printf("(%.3f - %.3f): ", COORDMIN, COORDMAX);

                fflush(stdin);

                //checks that float input is valid and within limits
                switch (scanf("%f", &xcoord)){
                case TRUE:
                    if (xcoord >= COORDMIN && xcoord <= COORDMAX)
                    {
                        coord_loop = FALSE;
                        break;
                    }
                    else
                    {
                        //fall through to default error message
                    }
                default:
                    printf("\nThat is not a valid cooordinate entry. ");
                    printf("Please try again.\n");
                }
            }
            my_messages[count + nbr].message.coords[0] = xcoord;

            coord_loop = TRUE;
            //loop to capture y-coordinate input
            while (coord_loop == TRUE)
            {
                printf("\nEnter y-coordinate ");
                printf("(%.3f - %.3f): ", COORDMIN, COORDMAX);

                fflush(stdin);

                //checks that float input is valid and within limits
                switch (scanf("%f", &ycoord)){
                case TRUE:
                    if (ycoord >= COORDMIN && ycoord <= COORDMAX)
                    {
                        coord_loop = FALSE;
                        break;
                    }
                    else
                    {
                        //fall through to default error message
                    }
                default:
                    printf("\nThat is not a valid cooordinate entry. ");
                    printf("Please try again.\n");
                }
            }
            my_messages[count + nbr].message.coords[1] = ycoord;
            break;
        default:
            printf("\nIf you see this something is wrong\n");
        }//end switch case for entering message content

        printf("\nNew message %d saved!", count + 1);
    }

    printf("\n%d new messages saved\n", entries);
    printf("\n%d messages total in database\n", entries + nbr);

    return;
}

/***************************** print_messages() *******************************
*
*   Purpose:    Allows the user to print the contents of INFO structures
*
*   Input:      my_messages INFO        array of INFO structures
*               tdorn       char        choice to print by type, destination
*                                       or message number
*               nbr         int         number of INFO structures
*                                       in my_messages
*
*   Output:     none
*
******************************************************************************/
void print_messages(INFO my_messages[], char tdorn, int nbr)
{
    int loop;                       //manages while loops for switch cases
    char type;                      //user input for type of message to print
    int msg_nbr;                    //user chosen message number to print
    int icr;                        //type of single message to print
    INFO single_message[TRUE];      //array of 1 message for print by number

    switch (tdorn){
    case 't':
        //loop to capture message type to print
        loop = TRUE;
        while (loop == TRUE)
        {
            //second printing menu (message type)
            printf("\nSelect message type to print:");
            printf("\n[I]nstruction");
            printf("\n[C]ode");
            printf("\nCoo[R]dinate");
            printf("\n\nPlease enter I, C, or R: ");

            fflush(stdin);
            type = tolower(getchar());

            if (type == 'i' || type == 'c' || type == 'r')
            {
                /* checks if messages of selected type exist
                and if so, prints them. Otherwise, prints error
                message and returns TRUE to continue loop */
                loop = sort_info(my_messages, nbr, type);
            }
            else
            {
                printf("\nThat is not a valid menu option. ");
                printf("Please try again.\n");
            }
        } //end loop to capture message type to print
        break;
    case 'd':
        //loop to capture device type to print
        loop = TRUE;
        while (loop == TRUE)
        {
            //second printing menu (device ID)
            printf("\nSelect device type to print:");
            printf("\n[T]echnician 1");
            printf("\n[M]otor");
            printf("\n[P]lotter");
            printf("\n\nPlease enter T, M, or P: ");

            fflush(stdin);
            type = tolower(getchar());

            if (type == 't' || type == 'm' || type == 'p')
            {
                /* checks if messages of selected type exist
                and if so, prints them. Otherwise, prints error
                message and returns TRUE to continue loop */
                loop = sort_info(my_messages, nbr, type);
            }
            else
            {
                printf("\nThat is not a valid menu option. ");
                printf("Please try again.\n");
            }
        }//end loop to capture device type to print
        break;
    case 'n':
        //start loop to print single message by number
        loop = TRUE;
        while (loop == TRUE)
        {
            printf("\nSelect message number to print (1-%d): ", nbr);
            fflush(stdin);
            scanf("%d", &msg_nbr);

            //check to see if message number exists
            if ((msg_nbr > nbr) || (msg_nbr <= 0))
            {
                printf("\nThat message number does not exist. ");
                printf("please try again\n");
            }
            else
            {
                //capture messagetype of single message to print
                icr = my_messages[msg_nbr - 1].messagetype;
                printf("\n\nLoading message number %d...", msg_nbr);

                //create new INFO array containing single message to print
                single_message[0] = my_messages[msg_nbr - 1];

                switch (icr){
                case INSTRUCTION:
                    print_info(single_message, 1, 'i');
                    break;
                case CODE:
                    print_info(single_message, 1, 'c');
                    break;
                case COORD:
                    print_info(single_message, 1, 'r');
                    break;
                default:
                    printf("\nIf you see this something is wrong\n");
                }
                loop = FALSE;
            }
        }
        //end loop to print single message by number
        break;
    default:
        printf("\nIf you see this something is wrong\n");
    }
    return;
}

/******************************* sort_info() *********************************
*
*   Purpose:    Sorts and prints contents of sorted INFO structures
*
*   Input:      my_messages INFO        array of INFO structures
*               nbr         int         number of INFO structures
*                                       in my_messages
*               type        char        type of message to print
*
*   Output:     int         int         TRUE or FALSE to manage calling loop
*
******************************************************************************/
int sort_info(INFO my_messages[], int nbr, char type)
{
    int count;                      //interator for for loops
    int sort_type;                  //int representation of char "type"
    char type_string[STRSIZE];      //string representation of char "type"
    int result_length;              //length of array of INFO structs to print
    INFO sorted_messages[NBRMSSGS]; //array of sorted INFO structs

    //set sort_type and text for error and confirmation messages
    switch (type) {
    case 'i':
        sort_type = INSTRUCTION;
        strcpy(type_string, "type Instruction ");
        break;
    case 'c':
        sort_type = CODE;
        strcpy(type_string, "type Code ");
        break;
    case 'r':
        sort_type = COORD;
        strcpy(type_string, "type Coordinates ");
        break;
    case 't':
        sort_type = INSTRUCTION;
        strcpy(type_string, "device type Technician 1 ");
        break;
    case 'm':
        sort_type = CODE;
        strcpy(type_string, "device type Motor 1 ");
        break;
    case 'p':
        sort_type = COORD;
        strcpy(type_string, "device type Plotter ");
        break;
    default:
        printf("If you see this something is wrong");
    }

    result_length = 0;

    for (count = 0; count < nbr; count++)
    {
        //run loop only on messages matching sort_type
        if (my_messages[count].messagetype == sort_type)
        {
            //create new array containing only matching messages
            sorted_messages[result_length] = my_messages[count];
            result_length++;
        }
    }
    if (result_length == 0)
    {
        printf("\n\nThere are no messages of %s", type_string);
        printf("to print\nPlease choose again\n");
        return TRUE;
    }
    else
    {
        //print all messages in sorted array of messages
        printf("\nAll messages of %s\n", type_string);
        print_info(sorted_messages, result_length, type);

        //ends while loop in calling function
        return FALSE;
    }
}

/******************************* print_info() *********************************
*
*   Purpose:    Prints contents of sorted INFO structures
*
*   Input:      sorted_messages INFO    array of INFO structures to print
*               nbr             int     number of INFO structures
*                                       in sorted_messages
*               type            char    type of message to print
*
*   Output:     none
*
******************************************************************************/
void print_info(INFO sorted_messages[], int nbr, char type)
{
    int count;

    for (count = 0; count < nbr; count++)
    {
        printf("\nMessage %d of %d\n", count + 1, nbr);
        printf("\nDestination device: ");

        switch (type){
        case 'i': //case designed to fall through
        case 't':
            printf("Technician 1");
            printf("\nMessage: ");
            printf("%s\n", sorted_messages[count].message.instruction);
            break;
        case 'c': //case designed to fall through
        case 'm':
            printf("Motor 1");
            printf("\nCode: ");
            printf("%d\n", sorted_messages[count].message.code);
            break;
        case 'r': //case designed to fall through
        case 'p':
            printf("Plotter");
            printf("\nX-Coordinate: ");
            printf("%.3f", sorted_messages[count].message.coords[0]);
            printf("\nY-Coordinate: ");
            printf("%.3f\n", sorted_messages[count].message.coords[1]);
            break;
        default:
            printf("If you see this something is wrong");
        }
    }
    return;
}

/**************************** bitmap_analysis() *******************************
*
*   Purpose:    Extracts and displays info about 8-bit BMP files
*               NOTE: Only for use with 8-bit (256 colour palette) BMP files
*
*   Input:      none
*
*   Output:     none
*
******************************************************************************/
void bitmap_analysis(void)
{
    int run = TRUE;
    FILE *fptr;
    char file_name[STRSIZE];

    //welcome message
    printf("**********************************************");
    printf("\n* Welcome to the bitmap analysis utility.    *");
    printf("\n* Currently analysis is limited to 8-bit     *");
    printf("\n* BMP files (256 max colour palette) and     *");
    printf("\n* less than 80KB in total file size.         *");
    printf("\n*                                            *");
    printf("\n* If system crashes because inputted image   *");
    printf("\n* is too large, increase MAXROWS value in    *");
    printf("\n* the utilities.h header file.               *");
    printf("\n**********************************************\n");

    while (run == TRUE)
    {
        //main menu
        printf("\n----------------------------------");
        printf("\nEnter BMP filename or press [Enter] to quit: ");

        fflush(stdin);
        gets(file_name);

        if (file_name[0] == '\0')
        {
            run = FALSE;
        }
        else
        {
            fptr = fopen(file_name, "rb");

            if (fptr != NULL)
            {
                fclose(fptr);
                analyze_bitmap(file_name);
            }
            else
            {
                printf("\nThat is not a valid BMP file.");
                printf("\nMake sure filename ends with .bmp");
                printf("\nCheck the filename and path and try again.\n");
            }
        }
    }
    printf("\n");
    return;
}

/**************************** analyze_bitmap() ********************************
*
*   Purpose:    Extracts and displays info about 8-bit BMP files
*               NOTE: Only for use with 8-bit (256 colour palette) BMP files
*
*   Input:      file_name   char    BMP file name as a string
*
*   Output:     none
*
******************************************************************************/
void analyze_bitmap(char file_name[])
{
    FILE *fptr;

    //all arrays used in program:
    int header_array[HEADERROWS][DATACOLUMNS];    //all data in bmp header
    int palette_array[MAXROWS][SORTCOLS]; //all data in bmp palette
    unsigned short pixel_array[MAXROWS][PIXELCOLS];  //all pixels for bmp image
    int low_colour[ARRAYSIZE];  //all colours which are the least frequent
    int high_colour[ARRAYSIZE]; //most frequently used colour in image

    //other variables
    char input;                 //input variable for detailed or basic report
    int run = TRUE;             //manages while loop for printing results
    int rows = 0;               //iterator for rows in 2D array loop
    int cols = 0;               //iterator for columns in 2D array loop
    int high_index = 0;         //stores index number of most frequent colour 
    int low_index = 0;          //stores index number of least frequent colour 
    int palette_row;            //iterator for 2D palette_array loop
    int filesize;               //size of bmp file in bytes
    int palette_start;          //starting address of palette data
    int palette_size;           //size of palette data in bytes
    int palette_colours;        //total number of colours in palette
    int num_colours = 0;        //number of colours actually used in image
    int high_colour_tot = 0;    //# occurances of most frequently used colour
    int low_colour_tot;         //# occurances of least frequently used colour
    int img_start_address;      //starting address of pixel array
    int num_pixels;             //total number of pixels in image
    int padding;                //bytes of padding in pixel array
    int pixels_plus_padding;    //number of pixels plus padding in image
    int padding_per_row;

    //get all data from bmp header (minus first two useless bytes)
    fptr = fopen(file_name, "rb");
    if (fptr != NULL)
    {
        fseek(fptr, 2, SEEK_SET);
        for (rows = 0; rows < HEADERROWS; rows++)
        {
            for (cols = 0; cols < DATACOLUMNS; cols++)
            {
                fread(&header_array[rows][cols], 4, 1, fptr);
            }
        }
    }
    else
    {
        printf("header_array creation failed");
    }
    fclose(fptr);

    //populate variable values
    palette_start = header_array[0][3] + BMPFILEHEADERBYTES;
    palette_size = header_array[0][2] - palette_start;
    num_pixels = header_array[1][0] * header_array[1][1];
    padding_per_row = 4 - (header_array[1][0] % 4);
    //correct for image width divisible by 4 error
    if (padding_per_row == 4)
    {
        padding_per_row = 0;
    }
    padding = padding_per_row * header_array[1][1];
    pixels_plus_padding = num_pixels + padding;
    palette_colours = palette_size / 4;
    img_start_address = header_array[0][2];

    //populate pixel_array with zeros to eliminate garbage data
    for (rows = 0; rows < (pixels_plus_padding / PIXELCOLS); rows++)
    {
        for (cols = 0; cols < PIXELCOLS; cols++)
        {
            pixel_array[rows][cols] = 0;
        }
    }

    //get all pixel data for sorting
    fptr = fopen(file_name, "rb");
    if (fptr != NULL)
    {
        fseek(fptr, img_start_address, SEEK_SET);
        for (rows = 0; rows < (pixels_plus_padding / PIXELCOLS); rows++)
        {
            for (cols = 0; cols < PIXELCOLS; cols++)
            {
                fread(&pixel_array[rows][cols], 1, 1, fptr);
            }
        }
    }
    else
    {
        printf("pixel_array creation failed");
    }
    fclose(fptr);

    //get all data in colour palette
    fptr = fopen(file_name, "rb");
    if (fptr != NULL)
    {
        fseek(fptr, palette_start, SEEK_SET);
        for (rows = 0; rows < palette_colours; rows++)
        {
            fread(&palette_array[rows][0], 4, 1, fptr);
            palette_array[rows][1] = rows;
            palette_array[rows][2] = 0;
        }
        fclose(fptr);
    }
    else
    {
        printf("palette_array creation failed");
    }

    //populate pallette array with colour usage data

    //loop through all pixel_array values
    for (rows = 0; rows < (pixels_plus_padding / PIXELCOLS); rows++)
    {
        for (cols = 0; cols < PIXELCOLS; cols++)
        {
            for (palette_row = 0; palette_row < palette_colours; palette_row++)
            {
                //for each value, compare to all palette_array values
                if (pixel_array[rows][cols] == palette_array[palette_row][1])
                {
                    //if value matches, increment palette_array 
                    //index [2] for that value
                    palette_array[palette_row][2]++;
                }
            }
        }
    }

    //remove padding data from frequency results in palette_array
    palette_array[0][2] = palette_array[0][2] - padding;

    //count number of colours used in pixel data
    for (palette_row = 0; palette_row < palette_colours; palette_row++)
    {
        //for each colour, check if frequency is > 0 
        if (palette_array[palette_row][2] > 0)
        {
            //if frequency > 0 increment num_colours
            num_colours++;
        }
    }

    //find # occurances of most frequently used colour in image
    for (palette_row = 0; palette_row < palette_colours; palette_row++)
    {
        if (palette_array[palette_row][2] > high_colour_tot)
        {
            high_colour_tot = palette_array[palette_row][2];
        }
    }

    //find most frequently used colour in image
    for (palette_row = 0; palette_row < palette_colours; palette_row++)
    {
        if (palette_array[palette_row][2] == high_colour_tot)
        {
            high_colour[high_index] = palette_array[palette_row][0];
            high_index++;
        }
    }

    //find # occurances of least frequently used colour in image

    //start counting from the occurances of the highest occuring colour
    low_colour_tot = high_colour_tot;

    for (palette_row = 0; palette_row < palette_colours; palette_row++)
    {
        if (palette_array[palette_row][2] > 0)
        {
            if (palette_array[palette_row][2] < low_colour_tot)
            {
                low_colour_tot = palette_array[palette_row][2];
            }
        }
    }

    //populate low_colour array with lowest occuring colours

    //loop through all pixel_array values
    for (palette_row = 0; palette_row < palette_colours; palette_row++)
    {
        //for each occurance value, compare to low_colour_tot)
        if (palette_array[palette_row][2] == low_colour_tot)
        {
            //if value matches, add colour to  low_colour array
            low_colour[low_index] = palette_array[palette_row][0];
            low_index++;
        }
    }

    //print results *************************************************

    while (run == TRUE)
    {
        //print menu
        printf("\nSelect [B]asic or [D]etailed report");
        printf("\n\nPlease enter B or D: ");

        fflush(stdin);
        input = tolower(getchar());

        switch (input) {
        case 'b':
            //print number of image colours
            printf("\nNumber of colours in image is %d\n", num_colours);

            //print highest occuring colour values

            printf("\nThe highest occuring colours are: \n");
            for (rows = 0; rows < high_index; rows++)
            {
                printf("[%d]: ", rows + 1);
                printf("colour: %.8X\n", high_colour[rows]);
            }
            printf("Occurrence per colour: %d\n", high_colour_tot);

            //print lowest occuring colour values
            printf("\nThe lowest occuring colours are: \n");
            for (rows = 0; rows < low_index; rows++)
            {
                printf("[%d]: ", rows + 1);
                printf("colour: %.8X\n", low_colour[rows]);
            }
            printf("Occurance per colour: %d\n", low_colour_tot);

            run = FALSE;
            break;
        case 'd':
            //print colour palette 

            printf("\nIndex row   | Colour   | Address | Frequency\n");
            for (rows = 0; rows < palette_colours; rows++)
            {
                printf("Index [%.3d] | %.8X ", rows, palette_array[rows][0]);
                printf("| %.2X   ", palette_array[rows][1]);
                printf("   | %d\n", palette_array[rows][2]);
            }

            //print number of image colours
            printf("\nNumber of colours in image is %d\n", num_colours);

            //print highest occuring colour values

            printf("\nThe highest occuring colours are: \n");
            for (rows = 0; rows < high_index; rows++)
            {
                printf("[%d]: ", rows + 1);
                printf("colour: %.8X\n", high_colour[rows]);
            }
            printf("Occurrence per colour: %d\n", high_colour_tot);

            //print lowest occuring colour values
            printf("\nThe lowest occuring colours are: \n");
            for (rows = 0; rows < low_index; rows++)
            {
                printf("[%d]: ", rows + 1);
                printf("colour: %.8X\n", low_colour[rows]);
            }
            printf("Occurance per colour: %d\n", low_colour_tot);

            //print other image values
            printf("\nImage data starts at address %X", img_start_address);
            printf("\nPalette size is %d bytes", palette_size);
            printf("\nNumber of colours in palette is %d", palette_colours);
            printf("\nNumber of pixels is %d", num_pixels);
            printf("\nPadding pixels per row: %d", padding_per_row);
            printf("\nBytes used for padding in pixel array: %d\n", padding);

            run = FALSE;
            break;
        default:
            printf("\nThat is not a valid menu option. Please try again.\n");
        }
    }
    return;
}