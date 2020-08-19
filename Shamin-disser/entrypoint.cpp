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
				
const double PI = 3.14159265358979323846264338327950288;
unsigned iterations = 0;
const unsigned capacity = 128;
double angles[capacity];
double cos_v[capacity];
double sin_v[capacity];
void init_arrays()
{
	double ang = PI / 4;
	for (unsigned i = 0; i < capacity; i = i + 1)
	{
		angles[i] = ang;
		cos_v[i] = cos(ang);
		sin_v[i] = sin(ang);
		ang = ang / 2;
	}
}

//0.5 ulp, Relative error 2^(-p+1) = 2^-52
double my_tan(double x) /*0 <= x <= PI / 2*/
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
	return R.y/R.x;
}


int main(int argc, char** argv)
{
	init_arrays();
	std::cout << "==tan(31)==\n";
	const double tan_31 = 0.60086061902756041487866442635466;
	for (iterations = 1; iterations < capacity; ++iterations)
	{
		double result = my_tan(31*PI/180);
		double absolute_error = abs(tan_31 - result);
		double relative_error = absolute_error / tan_31;
		std::cout << iterations << '\t' << relative_error << '\n';
	}
	std::cout << "==tan(61)==\n";
	const double tan_61 = 1.804047755271423937381784748237;
	for (iterations = 1; iterations < capacity; ++iterations)
	{
		double result = my_tan(61*PI/180);
		double absolute_error = abs(tan_61 - result);
		double relative_error = absolute_error / tan_61;
		std::cout << iterations << '\t' << relative_error << '\n';
	}
	return 0;
}
