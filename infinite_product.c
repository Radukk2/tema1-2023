#include <stdio.h>
#include <math.h>

long long convert_8_to_10(long long n)
{
	long long i = 0, new = 0;
	while (n > 0) {
		new = new + (n % 10) * pow(8, i);
		i++;
		n = n / 10;
		}
	return new;
}

int main(void)
{
	long long N, a, b, ps = 0;
	long long ma1 = -1, ma2 = -1, mb1 = -1, mb2 = -1;
	double norma_a, norma_b, n1 = 0, n2 = 0;
	scanf("%lld", &N);
	while (N > 0) {
		scanf("%lld%lld", &a, &b);
		a = convert_8_to_10(a);
		b = convert_8_to_10(b);
		ps += a * b;
		N = N - 1;
		if (a > ma1) {
			ma2 = ma1;
			ma1 = a;
		}
		if (b > mb1) {
			mb2 = mb1;
			mb1 = b;
		}
		if (a > ma2 && a < ma1)
			ma2 = a;
		if (b > mb2 && b < mb1)
			mb2 = b;
		n1 += (double)a * (double)a;
		n2 += (double)b * (double)b;
	}
	norma_a = sqrt(n1);
	norma_b = sqrt(n2);
	printf("%lld\n", ps);
	printf("%lld %lld\n", ma2, mb2);
	printf("%.7lf %.7lf\n", norma_a, norma_b);
	return 0;
}
