#include "polynomial.h"
#include <iostream>
#include <math.h>


//
// Implementation
//

// Default constructor p(x) = 0
Polynomial::Polynomial()
{
	this->capacity = 5;
	this->terms = 0;
	this->termArray = new Term[capacity];
}

// Copy constructor
Polynomial::Polynomial(const Polynomial& source)
{
	this->capacity = source.Capacity();
	this->terms = source.terms;
	this->termArray = new Term[this->capacity];
	for (int i = 0; i < this->terms; ++i)
		this->termArray[i] = source.GetTerm(i);
}	

// Destructor
Polynomial::~Polynomial()
{
	capacity = terms = 0;
	delete[] termArray;
}


Polynomial& Polynomial::operator = (const Polynomial& source)
{
	delete[] this->termArray;
	this->termArray = new Term[source.Capacity()];
	for (int i = 0; i < source.Terms(); ++i) 
		this->termArray[i] = source.GetTerm(i);
	this->terms = source.terms;
	this->capacity = source.Capacity();
	return *this;
}



// Sum of *this and source polynomials
Polynomial Polynomial::operator +(const Polynomial& source)
{
	Polynomial c;

	bool* chk1 = new bool[this->terms];
	for (int i = 0; i < this->terms; ++i)
		chk1[i] = false;
	bool* chk2 = new bool[source.terms];
	for (int i = 0; i < source.terms; ++i)
		chk2[i] = false;
	for (int i = 0; i < this->terms; ++i) {
		for (int j = 0; j < source.Terms(); ++j) {
			if (this->termArray[i].exp == source.GetTerm(j).exp) {
				float sum = this->termArray[i].coef + source.GetTerm(j).coef;
				int exp = this->termArray[i].exp;

				if (sum != 0)
					c.CreateTerm(sum, exp);

				chk1[i] = chk2[j] = true;
				break;
			}
		}
		if (!chk1[i])
			c.CreateTerm(this->termArray[i].coef, this->termArray[i].exp);
	}
	for (int i = 0; i < source.Terms(); ++i)
		if(!chk2[i])
			c.CreateTerm(source.GetTerm(i).coef, source.GetTerm(i).exp);

	return c;
}

Polynomial Polynomial::operator - (const Polynomial& source)
{
	Polynomial c;

	bool* chk1 = new bool[this->terms];
	for (int i = 0; i < this->terms; ++i)
		chk1[i] = false;
	bool* chk2 = new bool[source.terms];
	for (int i = 0; i < source.terms; ++i)
		chk2[i] = false;
	for (int i = 0; i < this->terms; ++i) {
		for (int j = 0; j < source.Terms(); ++j) {
			if (this->termArray[i].exp == source.GetTerm(j).exp) {
				float diff = this->termArray[i].coef - source.GetTerm(j).coef;
				int exp = this->termArray[i].exp;

				if (diff != 0)
					c.CreateTerm(diff, exp);

				chk1[i] = chk2[j] = true;
				break;
			}
		}
		if (!chk1[i])
			c.CreateTerm(this->termArray[i].coef, this->termArray[i].exp);
	}
	for (int i = 0; i < source.Terms(); ++i)
		if (!chk2[i])
			c.CreateTerm(-source.GetTerm(i).coef, source.GetTerm(i).exp);

	return c;
}


Polynomial Polynomial::operator * (const Polynomial& source)
{
	Polynomial c;

	for (int i = 0; i < this->terms; ++i) {
		Polynomial tmp;
		for (int j = 0; j < source.Terms(); ++j) {
			float mul = this->termArray[i].coef * source.GetTerm(j).coef;
			int exp = this->termArray[i].exp + source.GetTerm(j).exp;
			if (mul != 0)
				tmp.CreateTerm(mul, exp);
		}
		c = c + tmp;
	}

	return c;	
}


float Polynomial::Eval(float x)
{
	float ret = 0;
	
	float cur = 1;
	int exp = 0;
	for (int i = terms - 1; i >= 0; --i) {
		while (exp < termArray[i].exp) {
			++exp;
			cur *= x;
		}
		ret += termArray[i].coef * cur;
	}

	return ret;
}




// Compute derivative of the current polynomial
Polynomial Polynomial::Derivative()
{
	Polynomial c;
	for (int i = 0; i < this->terms; ++i) {
		if (this->termArray[i].exp == 0) continue;
		c.CreateTerm(this->termArray[i].coef * this->termArray[i].exp, this->termArray[i].exp - 1);
	}
	return c;	

}


void Polynomial::CreateTerm(const float coef, const int exp)
{
	if (coef == 0) {
		if (terms == 0) return;
		int i;
		for (i = 0; i < terms; ++i)
			if (termArray[i].exp == exp)
				break;
		if (i == terms) return;
		for (; i < terms - 1; ++i) 
			termArray[i] = termArray[i + 1];
		--terms;
		if (terms < capacity / 2 && capacity >= 5) {
			capacity /= 2;
			Term* tmp = new Term[capacity];
			for (int i = 0; i < terms; ++i)
				tmp[i] = termArray[i];
			delete[] termArray;
			termArray = tmp;
		}
		return;
	}
	for (int i = 0; i < terms; ++i) {
		if (termArray[i].exp == exp) {
			termArray[i].coef = coef;
			return;
		}
	}
	if (terms >= capacity) {
		capacity *= 2;
		Term* tmp = new Term[capacity];
		for (int i = 0; i < terms; ++i)
			tmp[i] = termArray[i];
		delete[] termArray;
		termArray = tmp;
	}
	termArray[terms].coef = coef;
	termArray[terms].exp = exp;
	for (int i = terms; i > 0; --i) {
		if (termArray[i - 1].exp < termArray[i].exp) {
			Term tmp = termArray[i - 1];
			termArray[i - 1] = termArray[i];
			termArray[i] = tmp;
		}
		else
			break;
	}
	++terms;
}

