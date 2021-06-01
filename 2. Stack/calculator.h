#ifndef CALCULATOR_H
#define CALCULATOR_H

//
// Assignment 2: Simple calculator using Stack
//

#include <iostream>
#include <cassert>
#include <math.h>
#include <string.h>
#include "stack.h"
#define MULT '*'
#define DIV '/'
#define ADD '+'
#define DIFF '-'
#define LEFT '('
#define RIGHT ')'


Stack<double> opr; // stack for operands
Stack<char> opt;   // stack for operators


//
// Modify Eval() below to evaluate the given expression
//
void postcalc() {
	float a = -1, b = -1, res = 0;
	char oper = 0;

	a = opr.Top();
	opr.Pop();

	b = opr.Top();
	opr.Pop();

	oper = opt.Top();
	opt.Pop();

	if (oper == MULT)
		res = b * a;
	else if (oper == DIV)
		res = b / a;
	else if (oper == ADD)
		res = b + a;
	else if (oper == DIFF)
		res = b - a;
	opr.Push(res);
}

double Eval(char* in)
{
	double out = 0;
	double tmpInt = -1;
	double tmpDouble = 1;
	bool firstminus = true;
	bool isSosu = false;

	for (int i = 0; in[i]; i++) {
		if (in[i] != '.' && tmpInt != -1 && !('0' <= in[i] && in[i] <= '9')) {
			opr.Push(tmpInt);
			tmpInt = -1;
			isSosu = false;
			tmpDouble = 1;
		}

		if (in[i] == LEFT) {
			opt.Push(LEFT);
			firstminus = true;
		}
		else if (in[i] == RIGHT) {
			while (!opt.IsEmpty() && opt.Top() != LEFT)
				postcalc();
			opt.Pop();
		}
		else if (in[i] == MULT || in[i] == DIV || in[i] == ADD || in[i] == DIFF) {
			int lev;

			if (in[i] == MULT || in[i] == DIV)
				lev = 2;
			else
				lev = 1;

			while (!opt.IsEmpty()) {
				// lev <= opt.Top().lev
				char tmp = opt.Top();
				int topLev;
				if (tmp == MULT || tmp == DIV) {
					topLev = 2;
				}
				else if (tmp == ADD || tmp == DIFF) {
					topLev = 1;
				}
				else {
					topLev = 0;
				}
				if (lev <= topLev)
					postcalc();
				else
					break;
			}

			if (firstminus)
				opr.Push(0);
			opt.Push(in[i]);
			firstminus = false;
		}
		else if (in[i] == ' ') {

		}
		else if (in[i] == '.') {
			isSosu = true;
		}
		else {
			if (isSosu == false) { // 소수가 아닐 때
				if (tmpInt == -1) tmpInt = 0;
				tmpInt = tmpInt * 10 + (in[i] - '0');
				if (!in[i + 1]) opr.Push(tmpInt);
				firstminus = false;
			}
			else { // 소수 일 때
				tmpDouble /= 10;
				tmpInt += (in[i] - '0') * tmpDouble;
			}
		}
	}
	while (!opt.IsEmpty())
		postcalc();

	out = opr.Top();
	while (!opr.IsEmpty())
		opr.Pop();
	return out;
}

#endif
