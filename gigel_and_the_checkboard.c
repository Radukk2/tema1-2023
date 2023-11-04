#include <stdio.h>

int modul_de(int numar)
{
	if (numar < 0)
		return -numar;
	else
		return numar;
}

int transf_neg(int numar, int d)
{
	if (numar >= 0)
		return numar;
	else
		return transf_neg(numar + d, d);
}

int transformare(int numar, int baza)
{
	if (numar < baza)
		return numar;
	else
		return transformare(numar - baza, baza);
}

void conversie(int i)
{
	int k = 0;
	if (i < 26 && k == 0) {
		printf("%c", (char)((i % 26) + 65));
		k = 1;
	}
	if (i >= 26) {
		printf("%c", (char)((i / 26) + 64));
		i = i % 26;
	}
	if (i < 26 && k == 0) {
		printf("%c", (char)((i % 26) + 65));
		k = 1;
	}
}

int matrice_de_frecventa[1001][1001];

int main(void)
{
	int n, tabla[1001][1001], i, j;
	long long k = 0;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			scanf("%d", &tabla[i][j]);
	i = 0;
	j = 0;
	while (tabla[i][j] != 0 && matrice_de_frecventa[i][j] == 0) {
	if ((i + j) % 2 == 0) {
		matrice_de_frecventa[i][j] = 1;
		k += modul_de(tabla[i][j]);
		j = transformare(j + transf_neg(tabla[i][j], n), n);
	} else {
		matrice_de_frecventa[i][j] = 1;
		k += modul_de(tabla[i][j]);
		i = transformare(i + transf_neg(tabla[i][j], n), n);
		}
	}
	printf("%lld\n", k);
	printf("%d ", n - i);
	conversie(j);
	printf("\n");
	return 0;
}
