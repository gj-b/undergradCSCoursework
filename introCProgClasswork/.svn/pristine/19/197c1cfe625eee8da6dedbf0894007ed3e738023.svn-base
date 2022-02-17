#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Given a side length, returns the surface area of a cube. 
double surface_area_cube(double edge_length)
{
        double surface_area;
        surface_area = 6*pow(edge_length,2);
        if(edge_length <= 0)
        {
        fprintf(stderr, 
        "error (surface_area_cube): %f is not a valid input. "
        "The edge length must be positive. \n",edge_length);
        return -1;
        }
        else
        {
        return surface_area;
        }
}

//Test function for surface_area_cube.
unsigned int check_surface_area_cube(double input, double expected_output,
double accuracy)
{   
    double output;
    output = surface_area_cube(input);
    if((output >= expected_output - accuracy) 
    && (output <= expected_output + accuracy))
    {
        printf("Test passed: Test surface_area_cube. Edge length: %f."
            " Expected: %f. Output: %f.\n", input,output,expected_output);
        return 1;
    }
    else
    {
        printf("Test failed: Test check_surface_area_cube. "
        "Expected: %f. vs. Output: %f.\n",
        expected_output,output);
        return 0;
    }
}

//Given a side number and side length, returns the area of a figure. 
double sides_to_area(unsigned int num_sides, double side_length)
{
    if(side_length > 0)
    {
        if(num_sides==3)
        {
        return(pow(side_length,2)*(pow(3.0,0.5)/4.0));
        }
        if(num_sides==4)
        {
        return(pow(side_length,2));
        }
        if(num_sides==5)
        {
        return 0.25*pow(5*(5+2*(pow(5,0.5))),0.5)*pow(side_length,2);
        }
         if(num_sides==6)
        {
        return 1.5*pow(3,0.5)*pow(side_length,2);
        }
        if(num_sides==8)
        {
        return 2*(1+pow(2,0.5))*pow(side_length,2);
        }
        if(num_sides==9)
        {
        return 2.25*pow(side_length,2)*(1/tan(0.3490658504));
        }
        else
        {
        fprintf(stderr, "error (sides_to_area):"
        "%d is not a valid amount of sides.\n"
        ,num_sides);
        return -1;
        }
    }
    else
    {
        fprintf(stderr, "error (sides_to_area): "
        "%f is not a valid side length.\n"
        , side_length);
        return -1;
    }
}

//Test function for sides_to_area.
unsigned int check_sides_to_area(unsigned int input_num_sides, double input_side_length,
double expected_output, double accuracy)
{
    double output;
    output = sides_to_area(input_num_sides,input_side_length);
    if((output >= expected_output - accuracy) 
    && (output <= expected_output + accuracy))
    {
        printf("Test passed: Test sides_to_area. Num. sides : %d. Side length: %f."
            " Expected: %f. Output: %f.\n", input_num_sides, input_side_length,
            expected_output,output);
        return 1;
    }
    else
    {
        printf("Test failed: Test sides_to_area. Expected: %f. vs. Output: %f.\n",
        expected_output,output);
        return 0;
    }
}

//Generates a 10 number long row given the first number of that row. 
void row_generator(int first_num_row)
{
    printf("%7d %7d %7d %7d %7d %7d %7d %7d %7d %7d \n", 
        first_num_row, 
        first_num_row + 1,
        first_num_row + 2, 
        first_num_row + 3,
        first_num_row + 4,
        first_num_row + 6,
        first_num_row + 7,
        first_num_row + 8,
        first_num_row + 9,
        first_num_row + 10);
}

//Given the first number, generates a 10 X 10 number grid.
void generate_number_grid(int first_num)
{   
        row_generator(first_num);
        row_generator(first_num + 10);
        row_generator(first_num + 20);
        row_generator(first_num + 30);
        row_generator(first_num + 40);
        row_generator(first_num + 50);
        row_generator(first_num + 60);
        row_generator(first_num + 70);
        row_generator(first_num + 80);
        row_generator(first_num + 90);
}

//Prints out the number grid by calling generate_number_grid and figuring out
//what the first number of the first row should be. 
void print_number_grid(int start_num)
{
    int remainder_start_num = start_num % 10;
    int neg_first_num = start_num - remainder_start_num - 10;
    int pos_first_num = start_num - remainder_start_num;
    if((start_num<0) && (neg_first_num>-1000000))
        {
            generate_number_grid(neg_first_num);
        }
    else if(start_num>0 && ((pos_first_num + 100) < 1000000))
        {
            generate_number_grid(pos_first_num);
        }
    else
    {
        fprintf(stderr, "error: print_number_grid:"
        "%d is either too small or too large. \n", start_num);
        return;
    }
}

//Test function for print_number_grid.
void check_print_number_grid(int start_num)
{
    printf("Starting num is %d. \n", start_num);
    print_number_grid(start_num);
}

//Given a 4-digit number and a requested digit, the function returns the desired
//number. 
unsigned int extract_digit(unsigned int pattern, unsigned int digit)
{
    if(digit==0)
    {
        return pattern%10;
    }
    if(digit==1)
    {
        return (pattern%100)/10;
    }
    if(digit==2)
    {
        return (pattern%1000)/100;
    }
    if(digit==3)
    {
        return (pattern/1000);
    }
}

//Test function for extract_digit.
unsigned int check_extract_digit(unsigned int pattern, unsigned int digit,
int expected_output)
{
    int output;
    output = extract_digit(pattern,digit);
    if(output == expected_output) 
    {
        printf("Test passed: Test extract_digit. Pattern : %d. Digit: %d."
            " Expected: %d. Output: %d.\n", pattern, digit,
            expected_output,output);
        return 1;
    }
    else
    {
        printf("Test failed: Test extract_digit. Expected: %d. vs." 
        " Output: %d.\n",expected_output,output);
        return 0;
    }
}

//Given a color, returns how many times that color appears in pattern. 
unsigned int num_of_color(unsigned int pattern, unsigned int color)
{
    int counter = 0;
    if(color == extract_digit(pattern, 0))
    {
        counter = counter + 1;
    }
    if(color == extract_digit(pattern, 1))
    {
        counter = counter + 1;
    }
    if(color == extract_digit(pattern, 2))
    {
        counter = counter + 1;
    }
    if(color == extract_digit(pattern, 3))
    {
        counter = counter + 1;
    }
    return counter;
}

//Test function for num_of_color.
unsigned int check_num_of_color(unsigned int pattern, unsigned int color, 
unsigned int expected_output)
{
    int output;
    output = num_of_color(pattern,color);
    if(output == expected_output) 
    {
        printf("Test passed: Test num_of_color. Pattern : %d. Color: %d."
            " Expected number: %d. Output: %d.\n", pattern, color,
            expected_output,output);
        return 1;
    }
    else
    {
        printf("Test failed: Test num_of_color. Expected: %d. vs." 
        " Output: %d.\n",expected_output,output);
        return 0;
    }
}

//Returns the number of exact matches occuring between the guess and the
//solution. 
unsigned int count_exact_matches(unsigned int guess, unsigned int solution)
{
    int counter = 0;
    if(extract_digit(guess,0) == extract_digit(solution,0))
    {
        counter = counter + 1;
    }
     if(extract_digit(guess,1) == extract_digit(solution,1))
    {
        counter = counter + 1;
    }
     if(extract_digit(guess,2) == extract_digit(solution,2))
    {
        counter = counter + 1;
    }
     if(extract_digit(guess,3) == extract_digit(solution,3))
    {
        counter = counter + 1;
    }
    return counter;
}

//Test function for count_exact_matches.
unsigned int check_count_exact_matches(unsigned int guess, unsigned int solution, 
unsigned int expected_output)
{
    int output;
    output = count_exact_matches(guess,solution);
    if(output == expected_output) 
    {
        printf("Test passed: Test count_exact_matches. Solution: %d. Guess: %d."
            " Expected: %d. Output: %d.\n", solution, guess,
            expected_output,output);
        return 1;
    }
    else
    {
        printf("Test failed: Test count_exact_matches. Expected: %d. vs." 
        " Output: %d.\n",expected_output,output);
        return 0;
    }
}

//Returns 1 if the given color is present in the solution. 
unsigned int color_present(unsigned int pattern, unsigned int color)
{
    int first, second, third, fourth;
    first = extract_digit(pattern,0);
    second = extract_digit(pattern,1);
    third = extract_digit(pattern,2);
    fourth = extract_digit(pattern,3);
    if(first == color || second == color || third == color || fourth == color)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//Test function for color_present.
unsigned int check_color_present(unsigned int pattern, unsigned int color, 
unsigned int expected_output)
{
    int output;
    output = color_present(pattern,color);
    if(output == expected_output) 
    {
        printf("Test passed: Test color_present. Pattern: %d. Color: %d."
            " Expected: %d. Output: %d.\n", pattern, color,
            expected_output,output);
        return 1;
    }
    else
    {
        printf("Test failed: Test color_present. Expected: %d. vs." 
        " Output: %d.\n",expected_output,output);
        return 0;
    }
}

//Given pattern and solution, returns how many times they have similar colors. 
unsigned int color_match_count(unsigned int pattern, unsigned int solution)
{
    int counter;
    counter =   color_present(solution, extract_digit(pattern,0))
              + color_present(solution, extract_digit(pattern,1))
              + color_present(solution, extract_digit(pattern,2))
              + color_present(solution, extract_digit(pattern,3));
    return counter;
}

//Test function for color_match_count.
unsigned int check_color_match_count(unsigned int pattern, unsigned int solution,
unsigned int expected_output)
{
    int output;
    output = color_match_count(pattern,solution);
    if(output == expected_output) 
    {
        printf("Test passed: Test color_match_count. Pattern: %d. Solution: %d."
            " Expected: %d. Output: %d.\n", pattern, solution,
            expected_output,output);
        return 1;
    }
    else
    {
        printf("Test failed: Test color_match_count. Expected: %d. vs." 
        " Output: %d.\n",expected_output,output);
        return 0;
    }
}

//Given a guess and solution, returns the number of exact matches in 10th
//position and the number of additional color mathes in 0s position. 
unsigned int get_guess_feedback(unsigned int guess, unsigned int solution)
{
    if(guess>6666)
    {
    fprintf(stderr, "error: get_guess_feedback: your guess is too large. \n");
    return -1;
    }
    if(guess<1111)
    {
    fprintf(stderr, "error: get_guess_feedback: your guess is too small. \n");
    return -1;
    }
    if(solution>6666)
    {
    fprintf(stderr, "error: get_guess_feedback: "
    "your solution is too large. \n");
    return -1;
    }
    if(solution<1111)
    {
    fprintf(stderr, "error: get_guess_feedback: your solution "
    "is too small. \n");
    return -1;
    }
    if(extract_digit(guess,0)<1 || extract_digit(guess,1)<1
    || extract_digit(guess,2)<1 || extract_digit(guess,3)<1 
    || extract_digit(guess,0)>6 || extract_digit(guess,1)>6 
    || extract_digit(guess,2)>6 || extract_digit(guess,3)>6)
    {
    fprintf(stderr, "error: get_guess_feedback: for your guess, "
    "all colors must be in the 1 to  6 range.\n");
    return -1;
    }
    if(extract_digit(solution,0)<1 || extract_digit(solution,1)<1
    || extract_digit(solution,2)<1 || extract_digit(solution,3)<1
    || extract_digit(solution,0)>6 || extract_digit(solution,1)>6 
    || extract_digit(solution,2)>6 || extract_digit(solution,3)>6)
    {
    fprintf(stderr, "error: get_guess_feedback: for your solution, "
    "all colors must be in the 1 to  6 range.\n");
    return -1;
    }
    int exact_matches, color_matches, feedback;
    exact_matches = count_exact_matches(guess,solution);
    color_matches = color_match_count(guess,solution) - exact_matches;
    feedback = exact_matches*10 + color_matches;
    return feedback;
}

//Test function for get_guess_feedback.
unsigned int check_get_guess_feedback(unsigned int guess, unsigned int solution,
unsigned int expected_output)
{
    int output;
    output = get_guess_feedback(guess,solution);
    if(output == expected_output) 
    {
        printf("Test passed: Test get_guess_feedback. Pattern: %d. Solution: %d."
            " Expected: %d. Output: %d.\n", guess, solution,
            expected_output,output);
        return 1;
    }
    else
    {
        printf("Test failed: Test get_guess_feedback. Expected: %d. vs." 
        " Output: %d.\n",expected_output,output);
        return 0;
    }
}

int main()
{
    unsigned int total_tests = 0;
    unsigned int passed_tests = 0;
    passed_tests = passed_tests + check_surface_area_cube(0,-1.0, 0.01);
    total_tests++;
    passed_tests = passed_tests + check_surface_area_cube(-10,-1.0, 0.01);
    total_tests++;
    passed_tests = passed_tests + check_surface_area_cube(6,216, 0.01);
    total_tests++;
    passed_tests = passed_tests + check_surface_area_cube(2.4,34.56, 0.01);
    total_tests++;
    passed_tests = passed_tests + check_sides_to_area(10, 0, -1, 0.01);
    total_tests++;
    passed_tests = passed_tests + check_sides_to_area(10, -10, -1, 0.01);
    total_tests++;
    passed_tests = passed_tests + check_sides_to_area(10, 3, -1, 0.01);
    total_tests++;
    passed_tests = passed_tests + check_sides_to_area(-10, 3, -1, 0.01);
    total_tests++;
    passed_tests = passed_tests + check_sides_to_area(3, 3, 3.9, 0.01);
    total_tests++;
    passed_tests = passed_tests + check_sides_to_area(3, 4.5, 8.77, 0.01);
    total_tests++;
    passed_tests = passed_tests + check_sides_to_area(4, 4, 16, 0.01);
    total_tests++;
    passed_tests = passed_tests + check_sides_to_area(4, 5.34, 28.52, 0.01);
    total_tests++;
    passed_tests = passed_tests + check_sides_to_area(5, 5, 43.01, 0.01);
    total_tests++;
    passed_tests = passed_tests + check_sides_to_area(5, 6.7, 77.23, 0.01);
    total_tests++;
    passed_tests = passed_tests + check_sides_to_area(6, 6, 93.53, 0.01);
    total_tests++;
    passed_tests = passed_tests + check_sides_to_area(6, 20.54, 1096.11, 0.01);
    total_tests++;
    passed_tests = passed_tests + check_sides_to_area(8, 3, 43.46, 0.01);
    total_tests++;
    passed_tests = passed_tests + check_sides_to_area(8, 56.23, 15266.58, 0.01);
    total_tests++;
    passed_tests = passed_tests + check_sides_to_area(9, 5, 154.55, 0.01);
    total_tests++;
    passed_tests = passed_tests + check_sides_to_area(9, 20.1, 2497.52, 0.01);
    total_tests++;
    
    check_print_number_grid(43);
    check_print_number_grid(4);
    check_print_number_grid(101);
    check_print_number_grid(-43);
    check_print_number_grid(-1000000000);
    check_print_number_grid(999900);
    
    passed_tests = passed_tests + check_extract_digit(2497,0,7);
    total_tests++;
    passed_tests = passed_tests + check_extract_digit(2497,1,9);
    total_tests++;
    passed_tests = passed_tests + check_extract_digit(2497,2,4);
    total_tests++;
    passed_tests = passed_tests + check_extract_digit(2497,3,2);
    total_tests++;
    passed_tests = passed_tests + check_num_of_color(1234,1,1);
    total_tests++;
    passed_tests = passed_tests + check_num_of_color(4444,4,4);
    total_tests++;
    passed_tests = passed_tests + check_num_of_color(1111,2,0);
    total_tests++;
    passed_tests = passed_tests + check_count_exact_matches(1234,1234,4);
    total_tests++;
    passed_tests = passed_tests + check_count_exact_matches(1234,2341,0);
    total_tests++;
    passed_tests = passed_tests + check_count_exact_matches(1234,3256,1);
    total_tests++;
    passed_tests = passed_tests + check_color_present(1234,1,1);
    total_tests++;
    passed_tests = passed_tests + check_color_present(4353,1,0);
    total_tests++;
    passed_tests = passed_tests + check_color_match_count(1234, 1234, 4);
    total_tests++;
    passed_tests = passed_tests + check_color_match_count(1214,3421,4);
    total_tests++;
    passed_tests = passed_tests + check_color_match_count(5241,1214,3);
    total_tests++;
    passed_tests = passed_tests + check_get_guess_feedback(5241,1214,12);
    total_tests++;
    passed_tests = passed_tests + check_get_guess_feedback(1234,1234,40);
    total_tests++;
    passed_tests = passed_tests + check_get_guess_feedback(3131,1313,04);
    total_tests++;
    passed_tests = passed_tests + check_get_guess_feedback(93139,1313,-1);
    total_tests++;
    passed_tests = passed_tests + check_get_guess_feedback(3135,0,-1);
    total_tests++;
    passed_tests = passed_tests + check_get_guess_feedback(3139,1313,-1);
    total_tests++;
    passed_tests = passed_tests + check_get_guess_feedback("a",1414,-1);
    total_tests++;
    printf("Passed %u out of %u tests.\n", passed_tests,total_tests);
    return(0);
}

