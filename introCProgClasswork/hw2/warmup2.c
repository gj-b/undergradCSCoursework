#include <stdlib.h>
#include <stdio.h>
#include "warmup2.h"
/* print_asterisk_letter
 * input: char letter - the letter to print out
 * output: nothing returned, just printed to the screen.
 * Given a character, print the corresponding upper-case letter of the 
 * alphabet using asterisks. The letter can be anything from 'N' to 'R'. 
 */
void print_asterisk_letter(char letter)
{
        if(letter == 'N')
        {
        printf("*   *\n"
               "**  *\n"
               "* * *\n"
               "*  **\n"
               "*   *\n");
        }
        else if(letter == 'O')
        {
        printf(" *** \n"
        "*   *\n"
        "*   *\n"
        "*   *\n"
        " *** \n");
        }
        else if(letter == 'P')
        {
        printf("**** \n"
        "*   *\n"
        "**** \n"
        "*\n"
        "*\n");
        }
        else if(letter == 'R')
        {
        printf("**** \n");
        printf("*   *\n");
        printf("**** \n");
        printf("*  * \n");
        printf("*   *\n");
        }
        else
        {
        fprintf(stderr, "%s\n", "Not a valid letter.");
        }
}
void printstar(unsigned int width)
{
        int i = 0;
        while(i<width)
        {
                i++;
                printf("*");
        }
        printf("\n");
}
/* draw_sideways_wedge_rec
 * draws a sideways wedge with asterisks. implemented recursively.
 * inputs:
 *   uint width - the  minimum width of the wedge
 *   uint height - the number of rows to print of the wedge
 * outputs:
 *   nothing returned, just printed to the screen
 */
void draw_sideways_wedge_rec(unsigned int width, unsigned int height)
{ 
        if(height == 0)
        {
                return;
        }        
        else if(height == 1)
        {
                for(int i=0; i<width; i++)
                {
                    printf("*");
                }
                printf("\n");
        }
        else 
        {
                for(int i=0; i<width; i++)
                {
                    printf("*");
                }
                printf("\n");
                draw_sideways_wedge_rec(width + 1, height - 2);
                for(int i=0; i<width; i++)
                {
                    printf("*");
                }
                printf("\n");
        }
}        
/* draw_sideways_wedge_iter
 * draws a sideways wedge with asterisks. Implemented iteratively.
 * inputs:
 *   uint width - the minimum width of the wedge
 *   uint height - the number of rows to print of the wedge
 * outputs:
 *   nothing returned, just printed to the screen
 */

void draw_sideways_wedge_iter(unsigned int width, unsigned int height)
{ 
        int i = 0;
        int k;
        for(int i=0; i<height; i++)
        {        
                if(i < height/2)
                {
                        k = 1;
                }
                else if((i == height/2) && (height % 2 == 0))
                {
                    k = 0;
                }
                else if(i > height/2)
                {
                        k = -1;
                }
                width = width + k;
                for(int i=0; i<(width -1); i++)
                {
                    printf("*");
                }
                printf("\n");
        }
}
/* draw_halves_down
 * Draws a set of rows of asterisks, each with half as many asterisks as 
 * the previous one. It stops after a row with 1 asterisk in it. It returns
 * the number of rows of asterisks printed out.
 * inputs:
 *    uint start - number of asterisks in the first row
 * outputs:
 *    uint - number of rows of asterisks draw
 */
void draw_halves_down(unsigned int width)
{
        if (width <= 1)
        {
                printf("*\n");
                return;
        }
        else
        {
                for(int i=0; i<width; i++)
                {
                    printf("*");
                }
                printf("\n");
                draw_halves_down(width/2);
        }
} 
/* draw_halves_up
 * Draws a set of rows of asterisks, each with half as many asterisks as 
 * the following one. It begins with a row with 1 asterisk in it. It returns
 * the number of rows of asterisks printed out.
 * inputs:
 *    uint start - number of asterisks in the last row
 * outputs:
 *    uint - number of rows of asterisks draw
 */
void draw_halves_up(unsigned int width)
{ 
        if (width <= 1)
        {
                printf("*\n");
                return;
        }
        else
        {
                draw_halves_up(width/2);
                for(int i=0; i<width; i++)
                {
                    printf("*");
                }
                printf("\n");
                
        }
} 
