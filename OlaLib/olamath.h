#include <math.h>

extern "C"
{
	extern const double E        = 2.71828182845904523536;  
	extern const double LOG2E    = 1.44269504088896340736;  
	extern const double LOG10E   = 0.434294481903251827651;  
	extern const double LN2      = 0.693147180559945309417;  
	extern const double LN10     = 2.30258509299404568402;  
	extern const double PI       = 3.14159265358979323846;  
	extern const double PI_2     = 1.57079632679489661923;  
	extern const double PI_4     = 0.785398163397448309616;  
	extern const double SQRT2    = 1.41421356237309504880;  
	extern const double SQRT1_2  = 0.707106781186547524401;  

	double Fabs(double x)
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

	int64_t Abs(int64_t x)
	{
		return x > 0 ? x : -x;
	}
	int64_t Min(int64_t x, int64_t y)
	{
		return x < y ? x : y;
	}
	int64_t Max(int64_t x, int64_t y)
	{
		return x > y ? x : y;
	}
}