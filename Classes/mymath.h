#ifndef _MYMATH_H_
#define _MYMATH_H_
double myabs(double a)
{
	if (a < 0) return -a; else return a;
}
#define ACCURACY 0.001 
double mysqrt(double n)
{
	double low, high, mid, tmp;

	// 获取上下界 
	if (n > 1)  {
		low = 1;
		high = n;
	}
	else {
		low = n;
		high = 1;
	}

	// 二分法求开方 
	while (low <= high) {
		mid = (low + high) / 2.000;

		tmp = mid * mid;

		if (tmp - n <= ACCURACY && tmp - n >= ACCURACY * -1) {
			return mid;
		}
		else if (tmp > n) {
			high = mid;
		}
		else {
			low = mid;
		}
	}
}
double mysin(double x)
{
	double result = x, temp = x;
	double den = x, fac = 1;
	int n = 1, sign = 1;
	while ((temp>1e-5) || (temp<-1e-5))
	{
		n++, fac *= n, den *= x;
		n++, fac *= n, den *= x;
		temp = den / fac; sign = -sign;
		result = sign>0 ? result + temp : result - temp;
	}
	return result;

}
double mycos(double x)
{
	x = 1.57079 - x;
	return mysin(x);
}
#define PI 3.1415926
double myatan2(double a, double b)
{
	if (b == 0)
	{
		if (a >= 0) return PI / 2; else return -PI / 2;
	}
	else
	{
		float k = a / b;
		float min = -PI / 2, max = PI / 2;
		float temptan = 0;
		float mid;
		while (myabs(temptan - k) >= ACCURACY)
		{
			mid = (min + max) / 2;
			temptan = mysin(mid) / mycos(mid);
			if (temptan > k) max = mid; else min = mid;
		}
		if (b < 0){
			if (a < 0)mid = PI - mid;	else mid = PI + mid;
		}
		return temptan;
	}
}
#endif