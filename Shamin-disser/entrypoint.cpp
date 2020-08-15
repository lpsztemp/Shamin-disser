#include <iostream>
#include <cmath>
using namespace std;
//https://en.cppreference.com/w/

struct vector
{
	double x; //cos
	double y; //sin
};

struct matrix
{
	/*cos*/double a00; /*-sin*/double a01;
	/*sin*/double a10; /*cos*/ double a11;
};

const double PI = 3.1415926535897932384626433832795;
const double angles[] = {PI / 4, PI / 8, PI / 16, PI / 32, PI / 64/*, ...*/};
const double cos_v[] =  {cos(PI/4), cos(PI / 8), cos(PI / 16), cos(PI / 32), cos(PI / 64)/*, ...*/};
const double sin_v[] =  {sin(PI/4), sin(PI / 8), sin(PI / 16), sin(PI / 32), sin(PI / 64)/*, ...*/};
const double tan_v[] =  {tan(PI/4), tan(PI / 8), tan(PI / 16), tan(PI / 32), tan(PI / 64)/*, ...*/};
const unsigned iterations = sizeof(cos_v) / sizeof(double);

//0.5 ulp, Relative error 2^(-p+1) = 2^-52
double my_cos(double x) /*0 <= x <= PI / 2*/
{
	vector R = {0, 1};
	double angle = PI / 2;
	for (unsigned i = 0; i < iterations; i = i + 1)
	{
		vector r;
		matrix T =
		{
			cos_v[i], -sin_v[i],
			sin_v[i], cos_v[i]
		};
		/*T.a00 = cos_v[i];
		T.a01 = -sin_v[i];
		T.a10 = sin_v[i];
		T.a11 = cos_v[i];*/
		if (x >= angle)
		{
			T.a01 = sin_v[i];
			T.a10 = -sin_v[i];
			angle = angle + angles[i];
		}else
		{
			angle = angle - angles[i];
		}
		r = 
		{
			R.x * T.a00 + R.y * T.a10,
			R.x * T.a01 + R.y * T.a11
		};
		R = r;
	}
	return R.x;
}

int main(int argc, char** argv)
{
	cout << "my_cos(PI / 3) = " << my_cos(PI/3);
	return 0;
}
