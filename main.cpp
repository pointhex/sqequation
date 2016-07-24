#include <iostream>
#include <stdio.h>
#include <math.h>
#include <assert.h>

#define _DEBUG
int Globallvl = 2;

#ifdef _DEBUG
    #define DBG(lvl) if (lvl < Globallvl)
#else
    #define DBG(lvl) if (0)
#endif

const double EPS = 0.000001;
const int SE_INF = -1;
const int SE_DEC_ERR = -3;
const int NO_ROOT = -2;
const int ONE_ROOT = 1;
const int TWO_ROOT = 2;

const int LE_INF = -1;

bool IsZero (double a)
{
    return (fabs(a) < EPS);
}

int LineEquantion (double a, double b, double *x)
{
    assert(x);

    if (IsZero(a))
        if (IsZero(b))
            return LE_INF;
        else
            return NO_ROOT;

    *x = -b / a;

    return ONE_ROOT;
}

int SqEquation(double a, double b, double c, double *x1, double *x2)
{
    assert(x1);
    assert(x2);
    assert(x1 != x2);

    if (IsZero(a) && IsZero(b))
        if (IsZero(c))
            return SE_INF;
        else
            return NO_ROOT;

    if (IsZero(a))
        return LineEquantion(b, c, x1);

    double dec = b * b - 4 * a * c;

    if (dec >= 0) {
        *x1 = (-b - sqrt(dec)) / (2 * a);
        *x2 = (-b + sqrt(dec)) / (2 * a);
        return TWO_ROOT;
    } else
        return SE_DEC_ERR;
}

void SETest(double a, double b, double c)
{
    double x1 = 0;
    double x2 = 0;
    int sq = SqEquation(a, b, c, &x1, &x2);

    DBG(1) {
        std::cout << a << "x^2 + " << b << "x + " << c << " = 0" << std::endl;
        std::cout << "quantity root : " << sq << std::endl;
        std::cout << "first root : " << x1 << std::endl;
        std::cout << "second root : " << x2 << std::endl << std::endl;
    }
}

int main()
{
    SETest(0, 0, 0);
    SETest(0, 2, 4);
    SETest(0, 0, 4);
    SETest(4, 21, 5);
    SETest(1, 0, 5);

    return 0;
}
