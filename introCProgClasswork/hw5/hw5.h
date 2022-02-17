#include "warmup5_provided.h"

#ifndef HW5_H
#define HW5_H

typedef unsigned int uint;

typedef struct {
	char *str;
	uint allocated_length;
} safe_string;

/* Creates an empty string. Length 1 and null pointer : \0 */
safe_string* make_empty_string();

/*Takes the char * and converts it into a safe string. 
It needs to allocate new space for the string inside the safe string and initialize
 the string to match str.*/
safe_string* make_string(char *str);

/* Copies a given string into its destination safely by re-allocating memory if needed.
*/
void safe_str_cpy(safe_string *dest, safe_string *src);

/* Adds a given with another safely by re-allocating memory if needed.
*/
void safe_str_cat(safe_string *dest, safe_string *src);

/* safe_strchr returns a pointer that points within the string that s holds - 
the first occurrence of the letter c within s's string. If c is not 
within s's string, it returns NULL. */
char *safe_strchr(safe_string *s, int c);

//Helper function for strcmp. Given two characters, Says which one is bigger.
//-1: first is earlier. 0: identical 1: second is earlier.
int bigger_alphabetically(char c_1, char c_2);

/*safe_strcmp returns 0 if the strings within s1 and s2 are identical, -
1 if s1 is earlier alphabetically and 1 if s2 is later alphabetically. */
int safe_strcmp(safe_string *s1, safe_string *s2);































#endif