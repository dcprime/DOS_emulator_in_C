#ifndef _UTILITIES_H
#define _UTILITIES_H

#include "sprint4.h"

/********************************* Constants *********************************/

/*  Reference: Syntax for nory array taken from code at :
http://stackoverflow.com/questions/6599707/
2d-character-array-initialization-in-c
*/


#define STRSIZE 255

//constants for assignments
#define NBRASSMTS 50    //total assignments that can be stored
#define NBRENTRIES 5    //max number of assignments to populate at once

//array sizes for telescope messaging
#define NBRMSSGS 5
#define NBRCOORDS 2

//device IDs for telescope messaging INFO
#define TECH1 123
#define MOTOR1 1001
#define PLOTTER 9999

//values for telescope messaging message types
#define CODEMAX 9999
#define COORDMIN 0.000
#define COORDMAX 360.000

//values for bitmap analysis header data
#define HEADERROWS 4            //rows for header array
#define DATACOLUMNS 4           //values per row in header array
#define BMPFILEHEADERBYTES 14   //size of header portion of file

//values for various arrays in bitmap analysis app
#define ARRAYSIZE 50            //default array size
#define SORTCOLS 3              //columns in sorted palette array
#define PIXELCOLS 8             //columns in pixel array

/*** NOTE *** The following value establishes the upper limit for the size 
 in bytes of bmp images that can be analyzed. If the application crashes 
 because too large an image is attempted to be processed, increase the 
 value of MAXROWS and try again.*/
#define MAXROWS 10000           //rows for palette array and pixel array

/****************************** Structure Defs *******************************/

//ASSIGNMENT structure for assigment tracking
typedef struct
{
    char subject[STRSIZE];  // Class-subject
    char prof[STRSIZE];     // Professor name
    char ass_name[STRSIZE]; // Assignment name
    int due_date;           // Assignment due date (YYMMDD)
    int complete;           // Flag assignment as complete or not
} ASSIGNMENT;

enum mess_types{ INSTRUCTION, CODE, COORD };

//INFO structure for telescope messaging
typedef struct
{
    mess_types messagetype;
    int deviceID;

    union
    {
        char instruction[STRSIZE]; //text message
        int code; //numeric code
        float coords[NBRCOORDS]; //set of coordinates
    } message;
}INFO;

/******************************** Prototypes *********************************/

//resistance calculator
void calculate_resistance(void);
float get_resistance(int, int, char);

//assignment tracker
void track_assignments(void);
int populate_structures(ASSIGNMENT **assignments, int entries, int nbr);
void edit_assignment(ASSIGNMENT **assignments, int nbr);
void toggle_status(ASSIGNMENT assignments[], int nbr);
void print_structures(ASSIGNMENT assignments[], char nora, int nbr);

//telescope messaging
void telescope_messaging(void);
void create_messages(INFO my_messages[], int entries, int nbr);
void print_messages(INFO my_messages[], char tdorn, int nbr);
int sort_info(INFO my_messages[], int nbr, char type);
void print_info(INFO sorted_messages[], int nbr, char type);

//bitmap analysis
void bitmap_analysis(void);
void analyze_bitmap(char file_name[]);

#endif /* _UTILITIES_H */