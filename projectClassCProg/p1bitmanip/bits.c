/* 
 * CS:APP Data Lab 
 * 
 * 
 * 
 * bits.c - Source file with your solutions to the project.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the project by
editing the collection of functions in this source file.

CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function.

/*
 * STEP 2: Modify the following functions according to the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest checker to verify that your solutions produce
 *      the correct answers.
 */


#endif
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) 
{
  int y = x >> 31; // -1 for neg. # and 0 for pos. 
  x = x ^ y; //If neg, flips value to abs. val - 1. If pos. nothing changes.
  y = y & 1; //Flips y from -1 to 1 or keeps it at 0.
  x = x + y; //Adds 1 if number is neg. If pos., adds 0.
  return x; 
}

/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) 
{
  //Overflow happens if x and y are same sign but x+y has different sign. 
  int sum = x + y;
  int sign_x = x >> 31; //0 if pos. -1 if neg.
  int sign_y = y >> 31;
  int sign_sum = sum >> 31;
  int xy_same_signs = !(sign_x ^ sign_y); //Returns 0 if diff. sign, 1 if same.
  int xsum_same_signs = !(sign_x ^ sign_sum); //Returns 0 if diff. sign, 1 if same.
  int ysum_same_signs = !(sign_y ^ sign_sum);//Returns 0 if diff. sign, 1 if same.
  int all_same_sign = xsum_same_signs & ysum_same_signs; //Returns 1 if all same same, meaning no overflow possible and 0 otherwise. 
  return (!xy_same_signs)|all_same_sign; //Returns 1 if no overflow as all same or xy have same sign. 
}

/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) 
{
  int y,matches,all_same;
  y = (0x55<<24) | (0x55<<16) | (0x55<<8) | 0x55; //Equiv. of 101010101...
  matches = x & y; //Finds all even bit pos. where they match.
  all_same = !(matches ^ y); //If same, (matches ^ y) = 0 and ! flips it. 
  return all_same;
}

/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) 
{
  //Only the inverse of 0 is 0. Every other # has equiv. but with opp. sign
  //that can be tested for with |. If not 0, it will come up as 1. 
  int sign_x = x >> 31;
  int sign_neg_x = (~x + 1) >> 31;
  return (sign_x | sign_neg_x) + 1;
}

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) 
{
  int temp;
  //Totals the bits in 2^n spaces with below variables and &. 
  int comb_2bit = (0x55<<24) | (0x55<<16) | (0x55<<8) | 0x55;//0x55555555
  int half_comb_4bit = (0x33<<8) | 0x33;
  int comb_4bit = (half_comb_4bit << 16) | half_comb_4bit;//0x33333333;
  int comb_8bit = (0x0F<<24) | (0x0F<<16) | (0x0F<<8) | 0x0F;//0x0F0F0F0F;
  int comb_16bit= (0xFF<<16) | 0xFF;//0x00FF00FF;
  int comb_32bit= (0xFF<<8) | 0xFF;//0x0000FFFF;
  temp = x;
  x = (temp & comb_2bit) + ((temp>>1) & comb_2bit);
  x = (x & comb_4bit) + ((x>>2) & comb_4bit);
  x = (x & comb_8bit) + ((x>>4) & comb_8bit);
  x = (x & comb_16bit) + ((x>>8) & comb_16bit);
  x = (x & comb_32bit) + ((x>>16) & comb_32bit);
  return x;
}

/*
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) 
{
  //~(x|y) same as ~x & ~y
  return ~x & ~y;
}
/*
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) 
{
  int n_byte_shift = n << 3;  //Finds start of wanted bytes.
  int m_byte_shift = m << 3;
  int isolate_n_at_front = (x >> n_byte_shift) & 0xFF; //Isolates them at first
  int isolate_m_at_front = (x >> m_byte_shift) & 0xFF; //byte pos. 
  int put_m_at_n = (isolate_m_at_front) << n_byte_shift; //Swaps them 
  int put_n_at_m = (isolate_n_at_front) << m_byte_shift;
  int mask = ((0xFF) << n_byte_shift) | ((0xFF) << m_byte_shift); 
  int mask_reverse = ~mask; //Sets all non-swapped bytes to orig. values. 
  int x_except_swapped_byte = x & mask_reverse; 
  int answer = x_except_swapped_byte | put_n_at_m | put_m_at_n; //Combines all. 
  return answer;

}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) 
{
  int ret_val;
  x = !!x; //makes it a boolean.
  x = ~x +1; //sets it to all 1s or all 0s in corr. with bool. values
  y = y & x; //E.g. if 1, y remains same, else set to 0.
  z = z & ~x; //if 0, x remains same. 
  ret_val = z | y; //Since 1 now set to all 0s, only true value remains. 
  return ret_val;
}

/*
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x) 
{
  
  int times_3 = (x<<1) + x;  
  int sign = times_3 >> 31; //All 1s if neg. all 0s if pos. 
  int neg_sign = sign & 1; //1 if neg. 0 if pos.  
  int neg_acc = (neg_sign << 1) + neg_sign; //3 if neg. and 0 if pos. 
  int times_3_acc_for_neg = times_3 + neg_acc; //Adds the 3 for negative # 
  int answer = times_3_acc_for_neg >> 2; //Now divides by four
  return answer;
  }

/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15 
 *   Rating: 2
 */
int fitsBits(int x, int n) 
{
    int num_bits = 32 + (~n + 1); //32 - n
    int fitting = (x << num_bits) >> num_bits; //If fits, should be same thing
    int equals = !(fitting ^ x); //Returns 1 if equal
    return equals;
}

/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  int n_times_8 = n << 3; //The number of shifts needed to get wanted bit at bit 0 
  x = x >> n_times_8; //Shifts x to that 0 position. 
  x = x & 0xff; //Clears all other bits.
  return x;
}
/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70 d
 *   Rating: 4 
 */
int greatestBitPos(int x) 
{
  //Makes everything to right of greatest bit pos. 1. 
  int x_reverse, x_reverse_shift_one, answer;
  x = x | x >> 1;
  x = x | x >> 2;
  x = x | x >> 4;
  x = x | x >> 8;
  x = x | x >> 16;
  x_reverse = ~x; //Reverses and ensures it works if greatest bit in last
  x_reverse_shift_one = (x_reverse >> 1) | (1 << 31); // pos. possible
  answer = x_reverse_shift_one & x; //Isolates the greatest bit
  return answer;
}

/*
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y)
{
  int same_val = !(x^y); //Returns 1 if same value as each comp. would turn to 0 
                        //with ^ if same value. Use ! to then flip.
  return y | same_val;  //Holds true to truth table of implication.
}

/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) 
{
  int sec_byte = x >> 4;
  int sec_byte_3 = (sec_byte ^ 0x3); //Tests that second byte is 3.

  //Now need to check that 1st byte is between 0 and 9.
  int isolate_1st_byte = (0x0f & x);//Excludes everything but 1st byte.
  int add_6 = isolate_1st_byte + 6; //Max val. after add 6 is 0x0f.
  int with_range = add_6 >> 4; //So, if goes over into 5th bit, not in range. 
  return !(sec_byte_3 | with_range); 
}

/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) 
{
  //If equal XOR should be 0. Can then just flip with !. 
  return !(x^y);
}

/*
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) 
{
  //1. x and y have same sign and result of x - y is ne
  //2. x and y have opp signs: x is neg y is pos. 

  int x_min_y = x + (~y + 1); //x - y
  int sign_x = (x >> 31) & 1; //If pos 0. If neg 1.
  int sign_y = (y >> 31) & 1; //If pos 0. If neg 1.
  int x_neg_y_pos = sign_x & !sign_y; //Returns 1 if x is neg and y is pos.
  int x_less_than = (~(x ^ y)) & x_min_y; 
  int x_less_than_bool = (x_less_than >> 31) & 1;
  int answer = x_neg_y_pos | x_less_than_bool;
  return answer;
}

/*
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) 
{
  int x_sign = x >> 31;
  return !(x_sign);
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) 
{
  //3 cases need to be true.
  //1. x is positive. 
  //2. x isn't zero.
  //3. x only has one bit set. 
  int sign_x = !(x >> 31); //Returns 1 if x is positive.
  int not_zero = !!x; //Returns 1 if x isn't 0.
  int x_minus_1 = x + ~1 + 1; //x - 1
  int x_and_x_minus_1 = !(x & x_minus_1); //Returns 1 if only 1 bit set.
  int all_3_cases_true = sign_x & not_zero & x_and_x_minus_1; 
  return all_3_cases_true;
}
/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) 
{
  int neg = ~x + 1;
  int comp = x ^ neg;
  int check = comp + !x; 
  return !check;
}

/*
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) 
{
  int neg_1 = ~0;
  return neg_1;
}
/*
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n) 
{
  //1. Capture bits that will be put at beg.
  //2. Shift them to left and mask. 
  //3. Shift originial to right.
  //4. Add together. 
  int shift_right_amount = 32 + (~n + 1); //32 - n
  int bits_wanted = x >> shift_right_amount;
  int mask = ~(~0 << n);
  int isolated_bits_wanted = bits_wanted & mask;
  int shift_x_left = x << n;
  int answer = shift_x_left | isolated_bits_wanted;
  return answer;
}

/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x60000000) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) 
{
  //1. No Overflow - Product
  //2. Pos. Over - If sign of product is (-) but orig (+)
  //3. Neg. Over - If sign of product is (+) but orig (-)
  int sign_x = x >> 31; //0 if pos. all 1s if neg. 
  int product = x << 1; //Times 2.
  int sign_product = product >> 31; //0 if pos. all 1s if neg. 
  int diff_sign = sign_x ^ sign_product; //Returns all 1s if diff, 0 if same
  //If prod. is pos, returns t_min. If neg, t_max. 
  int t_min_or_t_max = sign_product ^ (1<<31); //0x80000000
  int flip_sign = product ^ t_min_or_t_max; //If prod is pos, adds neg. sign.
  //Returns 0 if same sign and t-max or t-min otherwise. 
  int overflow = diff_sign & flip_sign; 
  int answer = product ^ overflow;
  return answer;
}

