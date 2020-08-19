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
const double angles[] = {PI / 4, PI / 8, PI / 16, PI / 32, PI / 64, PI / 128, 
						PI / 256, PI / 512, PI / 1024, PI / 2048,
						PI / 4096, PI / 8192, PI / 16384, PI / 32768, PI / 65536 /*...*/};
const double cos_v[] =  {cos(PI/4), cos(PI / 8), cos(PI / 16), cos(PI / 32), cos(PI / 64), cos(PI /128), 
						cos(PI / 256), cos(PI / 512), cos(PI / 1024), cos(PI / 2048),
						cos(PI / 4096), cos(PI / 8192), cos(PI / 16384), cos(PI / 32768), cos(PI / 65536)  /*...*/ };
const double sin_v[] =  {sin(PI/4), sin(PI / 8), sin(PI / 16), sin(PI / 32), sin(PI / 64), sin(PI / 128), 
						sin(PI / 256), sin(PI / 512), sin(PI / 1024), sin(PI / 2048),
						sin(PI / 4096), sin(PI / 8192), sin(PI / 16384), sin(PI / 32768), sin(PI / 65536) /* ...*/};
const double tan_v[] =  {tan(PI/4), tan(PI / 8), tan(PI / 16), tan(PI / 32), tan(PI / 64), tan(PI / 128), 
						tan(PI / 256), tan(PI / 512), tan(PI / 1024), tan(PI / 2048),
						tan(PI / 4096), tan(PI / 8192), tan(PI / 16384), tan(PI / 32768),  tan(PI / 65536) /* ...*/};
const unsigned iterations = sizeof(cos_v) / sizeof(double);

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
	cout << "my_cos() = " << R.x << endl;
	cout << "my_sin() = " << R.y << endl;
	return R.y/R.x;
}


int main(int argc, char** argv)
{
	cout << "my_tan(31PI/180) = " << my_tan(31*PI/180) << endl;
	cout << "my_tan(61PI/180) = " << my_tan(61 * PI / 180);
	return 0;
}
