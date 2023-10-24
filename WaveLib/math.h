#include <math.h>

extern "C"
{
	extern int PI = 3;

	double Abs(double x)
	{
		return fabs(x);
	}
	double Fmod(double x, double y)
	{
		return fmod(x, y);
	}
	double Ffma(double x, double y, double z)
	{
		return fma(x, y, z);
	}
	double Fmax(double x, double y)
	{
		return fmax(x, y);
	}
	double Fmin(double x, double y)
	{
		return fmin(x, y);
	}

	double Ceil(double x)
	{
		return ceil(x);
	}
	double Floor(double x)
	{
		return floor(x);
	}
	double Round(double x)
	{
		return round(x);
	}
	double Trunc(double x)
	{
		return trunc(x);
	}

	double Sqrt(double x)
	{
		return sqrt(x);
	}
	double Cbrt(double x)
	{
		return cbrt(x);
	}
	double Pow(double x, double y)
	{
		return pow(x, y);
	}
	double Log(double x)
	{
		return log(x);
	}
	double Log2(double x)
	{
		return log2(x);
	}
	double Log10(double x)
	{
		return log10(x);
	}
	double Exp(double x)
	{
		return exp(x);
	}

	double Sin(double x)
	{
		return sin(x);
	}
	double Cos(double x)
	{
		return cos(x);
	}
	double Tan(double x)
	{
		return tan(x);
	}
	double Asin(double x)
	{
		return asin(x);
	}
	double Acos(double x)
	{
		return acos(x);
	}
	double Atan(double x)
	{
		return atan(x);
	}
	double Atan2(double y, double x)
	{
		return atan2(y, x);
	}
}