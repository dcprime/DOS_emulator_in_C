#ifndef _IO_FUNCTIONS_H
#define _IO_FUNCTIONS_H

#include "sprint4.h"

#define RANDMIN 1
#define RANDMAX 50

int validate_digit(char *);
int validate_char(char, char, char);
int get_number(const char *);
char get_char(const char *, char, char);
int get_rand(void);

#endif /* _IO_FUNCTIONS_H */