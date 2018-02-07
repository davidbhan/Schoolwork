// Complex.cpp
// The implementation file of the class Complex

#include <iostream>
#include <string>
#include "Complex.h"
using namespace std;

// Constructor with no parameters
Complex::Complex() {
	a = 0;
	b = 0;
}

// Constructor with two parameters 
Complex::Complex(double real, double imagine) {
	a = real;
	b = imagine;
}

void Complex::setReal( double real ) {
	a = real;
}

void Complex::setImaginary( double imagine ) {
	b = imagine;
}

double Complex::getReal() const {
	return a;
}

double Complex::getImaginary() const {
	return b;
}

// Sum two complex numbers
Complex operator+( const Complex & first, const Complex & second ) {
	Complex sum;
	sum.a = first.a + second.a;
	sum.b = first.b + second.b;
	return sum;
}

// Sum a complex and double
Complex operator+( const Complex & first, const double & second ) {
	Complex sum;
	sum.a = first.a + second;
	sum.b = first.b;
	return sum;
}

// Sum a double and complex
Complex operator+( const double & first, const Complex & second ) {
	Complex sum;
	sum.a = first + second.a;
	sum.b = second.b;
	return sum;
}

// Subtract two complex numbers
Complex operator-( const Complex & first, const Complex & second ) {
	Complex sum;
	sum.a = first.a - second.a;
	sum.b = first.b - second.b;
	return sum;
}

// Subtract a complex and double
Complex operator-( const Complex & first, const double & second ) {
	Complex sum;
	sum.a = first.a - second;
	sum.b = first.b;
	return sum;
}

// Subtract a double and complex
Complex operator-( const double & first, const Complex & second ) {
	Complex sum;
	sum.a = first - second.a;
	sum.b = 0 - second.b;
	return sum;
}

// Multiply two complex numbers
Complex operator*( const Complex & first, const Complex & second ) {
	Complex sum;
	sum.a = (first.a * second.a) - (first.b * second.b);
	sum.b = (first.a * second.b) + (second.a * first.b);
	return sum;
}

// Multiply a complex and double
Complex operator*( const Complex & first, const double & second ) {
	Complex sum;
	sum.a = first.a * second;
	sum.b = first.b * second;
	return sum;
}

// Multiply a double and complex
Complex operator*( const double & first, const Complex & second ) {
	Complex sum;
	sum.a = first * second.a;
	sum.b = first * second.b;
	return sum;
}

// Self-Multiply two complex numbers
void operator*=( Complex & first, const Complex & second ) {
	double tempa = (first.a * second.a) - (first.b * second.b);
	double tempb = (first.a * second.b) + (second.a * first.b);
	first.a = tempa;
	first.b = tempb;
	return;
}

// Self-Multiply a complex and double
void operator*=( Complex & first, const double & second ) {
	first.a = first.a * second;
	first.b = first.b * second;
	return;
}

ostream& operator<<( ostream& cout, const Complex & first ) {
	string s;
	s = "";
	cout << first.getReal();
	if (first.getImaginary() >= 0.0) {
		cout << "+" << first.getImaginary();
	} else {
		cout << first.getImaginary();
	}
	cout << "i";
	return cout;
}



