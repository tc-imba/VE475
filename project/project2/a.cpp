//
// Created by liu on 17-7-25.
//

#include <iostream>

using namespace std;

class Complex
{
private:
    int a, b;
public:
    Complex(int a, int b)
    {
        this->a = a;
        this->b = b;
    }

    Complex &add(const Complex &that)
    {
        a += that.a;
        b += that.b;
        return *this;
    }
};


int main()
{
    Complex a(1, 1), b(2, 2);
    Complex &result = a.add(b);
    cout << &a << endl << &result;
    return 0;
}
