// Complex.h
// The definition file of the class Complex
using namespace std;

class Complex{
    private:
        double a; // real
        double b; // imaginary

    public:
        void setReal( const double real ); // setter for a
        void setImaginary( const double imagine ); // setter for b
        double getReal() const; // getter for a
        double getImaginary() const; // getter for b
        Complex(); // constructor with no parameters
        Complex( const double real, const double imagine); // constructor with two parameters

    friend Complex operator+( const Complex & first, const Complex & second );
    friend Complex operator+( const Complex & first, const double & second );
    friend Complex operator+( const double & first, const Complex & second );
    friend Complex operator-( const Complex & first, const Complex & second );
    friend Complex operator-( const Complex & first, const double & second );
    friend Complex operator-( const double & first, const Complex & second );
    friend Complex operator*( const Complex & first, const Complex & second );
    friend Complex operator*( const Complex & first, const double & second );
    friend Complex operator*( const double & first, const Complex & second );
    friend void operator*=( Complex & first, const Complex & second );
    friend void operator*=( Complex & first, const double & second );
    friend ostream& operator<<( ostream& cout, const Complex & first );
};

Complex operator+( const Complex & first, const Complex & second );
Complex operator+( const Complex & first, const double & second );
Complex operator+( const double & first, const Complex & second );
Complex operator-( const Complex & first, const Complex & second );
Complex operator-( const Complex & first, const double & second );
Complex operator-( const double & first, const Complex & second );
Complex operator*( const Complex & first, const Complex & second );
Complex operator*( const Complex & first, const double & second );
Complex operator*( const double & first, const Complex & second );
void operator*=( Complex & first, const Complex & second );
void operator*=( Complex & first, const double & second );
ostream& operator<<( ostream& cout, const Complex & first );