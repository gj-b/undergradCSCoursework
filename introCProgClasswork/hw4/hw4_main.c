#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include "hw4_provided.h"
#include "hw4.h"


int main()
{

	//Hiding happyface within uchicago image. 
	encode("uchicago.png","happyface.png","result.png");
	decode("result.png","happyfacedecoded.png");	

	//Reverse: Hiding uchicago within happy face image.
	encode("happyface.png","uchicago.png","result_test2.png");
	decode("result_test2.png","uchicagodecoded.png");

	return 0;
}
//dud
