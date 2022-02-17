#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "warmup2.h"  // note this new include file!!!


/* Principle 2: Design a good set of test cases
 * they check the base case (0), right above the base case (1), well
 * above the base case (5, 8), and error conditions (-1, -5).
 * -1, 0, 1 are the boundary test cases - base, base+1, base-1.
 */
int main()
{

	// I am only putting one line in for each to make sure it compiles
	// you need to write your own test code

	print_asterisk_letter('N');
	printf("\n");
	print_asterisk_letter('O');
	printf("\n");
	print_asterisk_letter('P');
	printf("\n");
	print_asterisk_letter('R');
	printf("\n");
	print_asterisk_letter('r');
	printf("\n");
	print_asterisk_letter('A');
	printf("\n");
	draw_sideways_wedge_rec(3, 10);
	printf("\n");
	draw_sideways_wedge_rec(5, 5);
	printf("\n");
	draw_sideways_wedge_rec(1, 6);
	printf("\n");
	draw_sideways_wedge_iter(3, 10);
	printf("\n");
	draw_sideways_wedge_iter(5, 5);
	printf("\n");
	draw_sideways_wedge_iter(1, 6);
	printf("\n");
	draw_halves_down(20);
	printf("\n");
	draw_halves_down(10);
	printf("\n");
	draw_halves_down(1);
	printf("\n");
	draw_halves_down(100);
	printf("\n");
	draw_halves_up(20);
	printf("\n");
	draw_halves_up(10);
	printf("\n");
	draw_halves_up(1);
	printf("\n");
	draw_halves_up(100);
	printf("\n");
	
}
