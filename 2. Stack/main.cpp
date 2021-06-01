#include "stack.h"
#include "calculator.h"
#include <iostream>

//
// Assignment 2 : Simple calculator using Stack
//
// COSE213 Spring 2021
//
// Won-Ki Jeong (wkjeong@korea.ac.kr)
//

// stack & calculator test

int main()
{
	// Stack test
	Stack<int> s;
	
	s.Push(23);
	s.Push(102);
	s.Print();
	printf("--\n");
	
	s.Push(345);
	s.Push(77);
	s.Print();
	printf("--\n");
	
	s.Pop();
	s.Push(678);
	s.Push(91011);
	s.Print();
	printf("--\n");

	// Calculator test
	char str1[] ="-10-((-2+(2+4*3))-12) + 122 * (123 + (120+888) - 300)";
	// The correct result is 101372
	double res1 = Eval(str1);
	std::cout << "Result : " << res1 << std::endl;
	
	
	char str2[] = "1.2 + 2.4 + 3.0*2";
	// The correct result is 9.6
	double res2 = Eval(str2);
	std::cout << "Result : " << res2 << std::endl;
		
	return 0;
}
