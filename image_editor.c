#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct photo {
    char tip[4];
    int max;
    int dim1, dim2;
	int x1, x2, y1, y2;
    int **mat, **copie;
}foto ;

int **alocare_matrice(int m, int n)
{
	//functia de alocare
	//intai se aloca vectorul de linii
	int **a = calloc(m, sizeof(int *));
	if (!a)
		return NULL;
	//apoi aloc coloanele pe fiecare linie
	for (int i = 0; i < m; i++) {
		a[i] = calloc(n, sizeof(int));
		if (!a[i])
		    return NULL;
	}
	return a;
}

int **alocare_binary(int m, int n)
{
	int **a = malloc(m * sizeof(char *));
	if (!a)
		return NULL;
	//apoi aloc coloanele pe fiecare linie
	for (int i = 0; i < m; i++) {
		a[i] = malloc(n * sizeof(char));
		if (!a[i])
		    return NULL;
	}
	return a;
}
void new_line(FILE *in)
{
	while(1) {
		char c;
		fscanf(in, "%c", &c);
		if (c == '\n')
			break;
	}
}

void P2(FILE *in, foto *poza)
{
	char string[40];
	int contor = 0;
	while(fscanf(in, "%s", string)) {
		if (string[0] == '#') {
			new_line(in);
			continue;
			}
		if (contor == 0) {
			poza->dim2 = atoi(string);
			contor++;
			continue;
		}
		if (contor == 1) {
			poza->dim1 = atoi(string);
			contor++;
			continue;
		}
		if (contor == 2) {
			poza->max = atoi(string);	
			contor++;
			continue;
		}
		if (contor == 4)
			break;
		if (contor == 3) {
			poza->mat = alocare_matrice(poza->dim1, poza->dim2);
			for (int i = 0; i < poza->dim1; i++)
				for (int j = 0; j < poza->dim2; j++) {
					poza->mat[i][j] = atoi(string);
					fscanf(in, "%s", string);
				}
			contor++;
			continue;
		}
	}
}

void P3(FILE *in, foto *poza)
{
	char string[40];
	int contor = 0;
	while(fscanf(in, "%s", string)) {
		if (string[0] == '#') {
			new_line(in);
			continue;
			}
		if (contor == 0) {
			poza->dim2 = atoi(string);
			contor++;
			continue;
		}
		if (contor == 1) {
			poza->dim1 = atoi(string);
			contor++;
			continue;
		}
		if (contor == 2) {
			poza->max = atoi(string);;	
			contor++;
			continue;
		}
		if (contor == 4)
			break;
		if (contor == 3 ) {
			poza->mat= alocare_matrice(poza->dim1, poza->dim2 * 3);
			for (int i = 0; i < poza->dim1; i++)
				for (int j = 0; j < 3 * poza->dim2; j++){
					poza->mat[i][j] = atoi(string);
					fscanf(in, "%s", string);
				}
			contor++;
			continue;
		}

	}
}

void P5(FILE *in, foto *poza)
{
	char string[40];
	int contor = 0;
	while(fscanf(in, "%s", string)) {
		if (string[0] == '#') {
			new_line(in);
			continue;
			}
		if (contor == 0) {
			poza->dim2 = atoi(string);
			contor++;
			continue;
		}
		if (contor == 1) {
			poza->dim1 = atoi(string);
			contor++;
			continue;
		}
		if (contor == 2) {
			poza->max = atoi(string);	
			poza->mat= alocare_matrice(poza->dim1, poza->dim2);
			unsigned char c;
			fread(&c, sizeof(unsigned char), 1, in); 
			for (int i = 0; i < poza->dim1; i++)
				for (int j = 0; j < poza->dim2; j++)
					fread(&poza->mat[i][j], sizeof(unsigned char), 1, in);
			break;
		}
	}
}

void P6(FILE *in, foto *poza)
{
	char string[40];
	int contor = 0;
	while(fscanf(in, "%s", string)) {
		if (string[0] == '#') {
			new_line(in);
			continue;
			}
		if (contor == 0) {
			poza->dim2 = atoi(string);
			contor++;
			continue;
		}
		if (contor == 1) {
			poza->dim1 = atoi(string);
			contor++;
			continue;
		}
		if (contor == 2) {
			poza->max = atoi(string);
			poza->mat= alocare_matrice(poza->dim1, 3 * poza->dim2);
			unsigned char c;
			fread(&c, sizeof(unsigned char), 1, in);
			for (int i = 0; i < poza->dim1; i++)
				for (int j = 0; j < poza->dim2; j++) {
					fread(&(poza->mat[i][3 * j]), sizeof(unsigned char), 1, in);
					fread(&(poza->mat[i][3 * j + 1]), sizeof(unsigned char), 1, in);
					fread(&(poza->mat[i][3 * j + 2]), sizeof(unsigned char), 1, in);
				}
				
			break;
		}
	}

}

void LOAD(foto *poza, char *nume_fisier)
{
    FILE *in = fopen(nume_fisier, "r");
    if (in == NULL)
        printf("Failed to load %s\n", nume_fisier);
    else {
       	printf("Loaded %s\n", nume_fisier);
		fscanf(in, "%s", poza->tip);
		if (strcmp(poza->tip, "P2") == 0)
			P2(in, poza);
		if (strcmp(poza->tip, "P3") == 0)
			P3(in, poza);
		if (strcmp(poza->tip, "P5") == 0)
			P5(in, poza);
		if (strcmp(poza->tip, "P6") == 0)
			P6(in, poza);
		fclose(in);
    }
}

void offload(foto *poza)
{
	for (int i = 0; i < poza->dim1; i++)
		free(poza->mat[i]);
	free(poza->mat);
}

void offload_copie(foto *poza)
{
	for (int i = 0; i < poza->x2 - poza->x1; i++)
		free(poza->copie[i]);
	free(poza->copie);
}
void SELECT_P2(foto *poza, int x1, int y1, int x2, int y2)
{
	poza->copie = alocare_matrice(x2 - x1, y2 - y1);
	for (int i = 0; i < x2 - x1; i++)
		for (int j = 0; j < y2 - y1; j++){
			poza->copie[i][j] = poza->mat[x1 + i][y1 + j];
		}
}

void SELECT_P3(foto *poza, int x1, int y1, int x2, int y2)
{
	poza->copie = alocare_matrice(x2 - x1, 3 * (y2 - y1));
	for (int i = 0; i < x2 - x1; i++)
		for (int j = 0; j < 3 * (y2 - y1); j++)
			poza->copie[i][j] = poza->mat[x1 + i][y1 * 3 + j];
}

void SELECT_P5(foto *poza, int x1, int y1, int x2, int y2)
{
	poza->copie = alocare_matrice(x2 - x1, y2 - y1);
	for (int i = 0; i < x2 - x1; i++)
		for (int j = 0; j < y2 - y1; j++){
			poza->copie[i][j] = poza->mat[x1 + i][y1 + j];
		}
}

void SELECT_P6(foto *poza, int x1, int y1, int x2, int y2)
{
	poza->copie = alocare_matrice(x2 - x1, 3 * (y2 - y1));
	for (int i = 0; i < x2 - x1; i++)
		for (int j = 0; j < 3 * (y2 - y1); j++)
			poza->copie[i][j] = poza->mat[x1 + i][y1 * 3 + j];

}

void SELECT(foto *poza, int x1, int y1, int x2, int y2, int ver)
{
	int ok = 0;
	if (!poza->mat) {
		printf("No image loaded\n");
		ok = 1;
	}
	if ((x1 < 0 || y1 < 0 ||  x2 > poza->dim1 || y2 > poza->dim2) && ok == 0) {
		printf("Invalid coordinates\n");
		ok = 1;
	}
	if (ok == 0) {
		if (ver == 0)
			printf("Selected ALL\n");
		else
			printf("Selected %d %d %d %d\n", y1, x1, y2, x2);
		if (strcmp(poza->tip, "P2") == 0)
			SELECT_P2(poza, x1, y1, x2, y2);
		if (strcmp(poza->tip, "P3") == 0)
			SELECT_P3(poza, x1, y1, x2, y2);
		if (strcmp(poza->tip, "P5") == 0)
			SELECT_P5(poza, x1, y1, x2, y2);
		if (strcmp(poza->tip, "P6") == 0)
			SELECT_P6(poza, x1, y1, x2, y2);
		poza->x1 = x1;
		poza->x2 = x2;
		poza->y1 = y1;
		poza->y2 = y2;
	}
}

void HISTOGRAM_Part2(foto *poza, int x, int y)
{
	int *frecv = calloc(256 ,sizeof(double));
	if (!frecv)
		exit(0);
	for (int i = 0; i < poza->dim1; i++)
		for (int j = 0; j < poza->dim2; j++)
			frecv[poza->copie[i][j]]++;
	int *frecv_binuri = calloc(y + 1, sizeof(double));
	if (!frecv_binuri)
		exit(0);	
	int pas = 256 / y;
	int max = -1;
	for(int i = 0; i < y; i++)
		for (int j = i * pas; j < (i + 1) * pas; j++) {
			frecv_binuri[i] += frecv[j];
			if (frecv_binuri[i] > max)
				max = frecv_binuri[i];
		}
	int nr_stele;
	for (int i = 0; i < y; i++) {
		nr_stele = (frecv_binuri[i] / max) * x;
		printf("%d\t|\t", nr_stele);
		for (int i = 0; i < nr_stele; i++)
			printf("*");
		printf("\n");
	}
	free(frecv);
	free(frecv_binuri);	
}

void HISTOGRAM(foto *poza, int x, int y)
{
	int  ok = 0;
	if (!poza->mat){
		printf("No image loaded\n");
		ok = 1;
	}
	if (strcmp(poza->tip, "P3") == 0 || strcmp(poza->tip, "P6") == 0) {
		printf("Black and white image needed\n");
		ok = 1;
	}
	if (ok == 0)
	{
		printf("Histograma\n");
		HISTOGRAM_Part2(poza, x, y);
	}
}

double clamp(double a)
{
	if (a < 0)
		return 0;
	if (a > 255)
		return 255;
	return a;
}

void EQUALIZE(foto *poza)
{
	int  ok = 0;
	if (!poza->mat){
		printf("No image loaded\n");
		ok = 1;
	}
	if (strcmp(poza->tip, "P3") == 0 || strcmp(poza->tip, "P6") == 0) {
		printf("Black and white image needed\n");
		ok = 1;
	}
	if (ok == 0) {
		printf("Equalize done\n");
		double area = poza->dim1 * poza->dim2;
		double *frecv = calloc(256, sizeof(double));
		if (frecv == NULL)
			exit(0);
		for (int i = 0; i < poza->dim1; i++)
			for (int j = 0; j < poza->dim2; j++)
				frecv[poza->mat[i][j]]++;
		for(int i = 0; i < poza->dim1; i++)
			for (int j = 0; j < poza->dim2; j++) {
				int suma = 0;
				for (int k = 0; k < poza->mat[i][j]; k++)
					suma += frecv[k];
				poza->mat[i][j] = clamp((int)(255 * suma / area));
			}
		free(frecv);
	}
}

int convert_to_positive(int unghi)
{
	if (unghi <= 0)
		return unghi + 360;
	return unghi;
}

int verificare_unghi(int angle)
{
	if (angle == 90)
		return 1;
	if (angle == 180)
		return 1;
	if (angle == 270)
		return 1;
	if (angle == 360)
		return 1;
	return 0; 
}

void ROTATE_90_pgm(foto *poza)
{
	int y2 = poza->y2;
	int y1 = poza->y1;
	int x1 = poza->x1;
	int x2 = poza->x2;
	for (int i = 0; i < x2 - x1; i++)
		for (int j = 0; j < y2 - y1; j++)
			poza->copie[i][j] = poza->mat[y2 - 1 - j][i + x1];
}

void ROTATE_90_ppm(foto *poza)
{
	int y2 = poza->y2;
	int y1 = poza->y1;
	int x1 = poza->x1;
	int x2 = poza->x2;
	for (int i = 0; i < x2 - x1; i++)
		for (int j = 0; j < 3 * (y2 - y1); j++)
			poza->copie[i][j] = poza->mat[x2 - 1 - j / 3][i * 3 + j % 3 + y1 * 3];
}

void ROTATE_180_pgm(foto *poza)
{
	int dimensiune = (poza->y2 - poza->y1);
	for (int i = 0; i < poza->x2 - poza->x1; i++)
		for (int j = 0; j < dimensiune; j++)
			poza->copie[i][j] = poza->mat[poza->x2 - 1 - i][poza->y2 - 1 - j];
}

void ROTATE_180_ppm(foto *poza)
{
	int y2 = 3 * poza->y2;
	int y1 = 3 * poza->y1;
	int x2 = poza->x2;
	for (int i = 0; i < poza->x2 - poza->x1; i++)
		for (int j = 0; j < y2 - y1; j++) {
			int sim = (j / 3) * 3;
			poza->copie[i][j] = poza->mat[x2 - 1 - i][y2 - 3 + j % 3 - sim];
		}
}

void ROTATE_270_pgm(foto *poza)
{
	int dimensiune = (poza->y2 - poza->y1);
	for (int i = 0; i < poza->x2 - poza->x1; i++)
		for (int j = 0; j < dimensiune; j++)
			poza->copie[i][j] = poza->mat[j][poza->x2 - 1 - i];
}

void ROTATE_270_ppm(foto *poza)
{
	int y2 = 3 * poza->y2;
	int y1 = 3 * poza->y1;
	int x1 = poza->x1;
	int x2 = poza->x2;
	for (int i = 0; i < x2 - x1; i++)
		for (int j = 0; j < y2 - y1; j++)
			poza->copie[i][j] = poza->mat[x1 + j / 3][y2 + j % 3 - i * 3 - 3];
}

void ROTATE_all_90_pgm(foto *poza)
{
	for (int i = 0; i < poza->dim1; i++)
		free(poza->copie[i]);
	free(poza->copie);
	poza->copie = alocare_matrice(poza->dim2, poza->dim1);
	int y2 = poza->y2;
	int y1 = poza->y1;
	int x1 = poza->x1;
	int x2 = poza->x2;
	for (int i = 0; i < y2 - y1; i++)
		for (int j = 0; j < x2 - x1; j++)
			poza->copie[i][j] = poza->mat[x2 - 1 - j][i + y1];
	int aux1 = poza->y1; 
	poza->x1 = poza->y1;
	poza->y1 = aux1;
	aux1 = poza->x2; 
	poza->x2 = poza->y2;
	poza->y2 = aux1;
}

void ROTATE_all_90_ppm(foto *poza)
{
	for (int i = 0; i < poza->dim1; i++)
		free(poza->copie[i]);
	free(poza->copie);
	poza->copie = alocare_matrice(poza->dim2, 3 * poza->dim1);
	int y2 = poza->y2;
	int y1 = poza->y1;
	int x1 = poza->x1;
	int x2 = poza->x2;
	for (int i = 0; i < y2 - y1; i++)
		for (int j = 0; j < 3 * (x2 - x1); j++)
			poza->copie[i][j] = poza->mat[3 * x2 - 1 - j / 3][i * 3 + j % 3 + y1 * 3];
	int aux1 = poza->y1; 
	poza->x1 = poza->y1;
	poza->y1 = aux1;
	aux1 = poza->x2; 
	poza->x2 = poza->y2;
	poza->y2 = aux1;
}

void ROTATE_all_180_pgm(foto *poza)
{
	for (int i = 0; i < poza->dim1; i++)
		for (int j = 0; j < poza->dim2; j++)
			poza->copie[i][j] = poza->mat[poza->dim1 - i - 1][poza->dim2 - 1 - j];
}

void ROTATE_all_180_ppm(foto *poza)
{
	int y2 = 3 * poza->y2;
	int y1 = 3 * poza->y1;
	int x2 = poza->x2;
	for (int i = 0; i < poza->x2 - poza->x1; i++)
		for (int j = 0; j < y2 - y1; j++) {
			int sim = (j / 3) * 3;
			poza->copie[i][j] = poza->mat[x2 - 1 - i][y2 - 3 + j % 3 - sim];
		}
}
void ROTATE_all_270_pgm(foto *poza)
{
	for (int i = 0; i < poza->dim2; i++)
		free(poza->copie[i]);
	free(poza->copie);
	poza->copie = alocare_matrice(poza->dim2, poza->dim1);
	int y2 = poza->y2;
	int y1 = poza->y1;
	int x1 = poza->x1;
	int x2 = poza->x2;
	for (int i = 0; i < y2 - y1; i++)
		for (int j = 0; j < x2 - x1; j++)
			poza->copie[i][j] = poza->mat[x1 + j][y2 - 1 - i];
	int aux1 = poza->y1; 
	poza->x1 = poza->y1;
	poza->y1 = aux1;
	aux1 = poza->x2; 
	poza->x2 = poza->y2;
	poza->y2 = aux1;
}

void ROTATE_all_270_ppm (foto *poza)
{
	for (int i = 0; i < poza->dim1; i++)
		free(poza->copie[i]);
	free(poza->copie);
	poza->copie = alocare_matrice(poza->dim2, 3 * poza->dim1);
	int y2 = poza->y2;
	int y1 = poza->y1;
	int x1 = poza->x1;
	int x2 = poza->x2;
	for (int i = 0; i < y2 - y1; i++)
		for (int j = 0; j < 3 * (x2 - x1); j++) {
			int q = 3 * x1;
			poza->copie[i][j] = poza->mat[q + j / 3][y2 + j % 3 - i * 3 + 3];
		}
	int aux1 = poza->y1; 
	poza->x1 = poza->y1;
	poza->y1 = aux1;
	aux1 = poza->x2; 
	poza->x2 = poza->y2;
	poza->y2 = aux1;
}
void ROTATE_ALL(foto *poza, char *string)
{
	int angle = atoi(string);
	int unghi = angle;
	angle = convert_to_positive(angle);
	if (verificare_unghi(angle) == 0) {
		printf("Unsupported rotation angle\n");
		//continue;
	}
	if (angle == 90) {
		if(strcmp(poza->tip, "P2") == 0 || strcmp(poza->tip, "P5") == 0)
			ROTATE_all_90_pgm(poza);
		if(strcmp(poza->tip, "P3") == 0 || strcmp(poza->tip, "P6") == 0)
			ROTATE_all_90_ppm(poza);
	}
	if (angle == 180) {
		if(strcmp(poza->tip, "P2") == 0 || strcmp(poza->tip, "P5") == 0)
			ROTATE_all_180_pgm(poza);
		if(strcmp(poza->tip, "P3") == 0 || strcmp(poza->tip, "P6") == 0)
			ROTATE_all_180_ppm(poza);
	}
	if (angle == 270) {
		if(strcmp(poza->tip, "P2") == 0 || strcmp(poza->tip, "P5") == 0)
			ROTATE_all_270_pgm(poza);
		if(strcmp(poza->tip, "P3") == 0 || strcmp(poza->tip, "P6") == 0)
			ROTATE_all_270_ppm(poza);
	}
	for (int i = 0; i < poza->x2 - poza->x1; i++) {
		for (int j = 0; j < 3 * (poza->y2 - poza->y1); j++)
			printf("%d ", poza->copie[i][j]);
		printf("\n");
	}
	if (verificare_unghi(angle) == 1)
		printf("Rotated %d\n", unghi);
}

void ROTATE(foto *poza, char *string)
{
	int select_all = 0;
	if (!poza->mat) {
		printf("No image loaded\n");
	}
	if (poza->x2 - poza->x1 != poza->y2 - poza->y1) {
		if (poza->x2 - poza->x1 == poza->dim1)
			select_all++;
		if (poza->y2 - poza->y1 == poza->dim2)
			select_all++;
		if (select_all == 2)
			ROTATE_ALL(poza, string);
		else
			printf("The selection must be square\n");
	}
	int angle = atoi(string);
	angle = convert_to_positive(angle);
	if (verificare_unghi(angle) == 0) {
		printf("Unsupported rotation angle\n");
	}
	if (angle == 90 && select_all != 2) {
		if(strcmp(poza->tip, "P2") == 0 || strcmp(poza->tip, "P5") == 0)
			ROTATE_90_pgm(poza);
		if(strcmp(poza->tip, "P3") == 0 || strcmp(poza->tip, "P6") == 0)
			ROTATE_90_ppm(poza);
	}
	if (angle == 180 && select_all != 2) {
		if(strcmp(poza->tip, "P2") == 0 || strcmp(poza->tip, "P5") == 0)
			ROTATE_180_pgm(poza);
		if(strcmp(poza->tip, "P3") == 0 || strcmp(poza->tip, "P6") == 0)
			ROTATE_180_ppm(poza);
	}
	if (angle == 270 && select_all != 2) {
		if(strcmp(poza->tip, "P2") == 0 || strcmp(poza->tip, "P5") == 0)
			ROTATE_270_pgm(poza);
		if(strcmp(poza->tip, "P3") == 0 || strcmp(poza->tip, "P6") == 0)
			ROTATE_270_ppm(poza);
	}
	if (verificare_unghi(angle) == 1 && select_all !=2)
		printf("Rotated %d\n", angle);
}

void CROP_P2(foto *poza)
{
	for (int i = 0; i < poza->dim1; i++)
		free(poza->mat[i]);
	free(poza->mat);
	poza->dim1 = poza->x2 - poza->x1;
	poza->dim2 = poza->y2 - poza->y1;
	poza->mat = alocare_matrice(poza->dim1, poza->dim2);
	for (int i = 0; i < poza->dim1; i++)
		for (int j = 0; j < poza->dim2; j++)
			poza->mat[i][j] = poza->copie[i][j];
}

void CROP_P3(foto *poza)
{
	for (int i = 0; i < poza->dim1; i++)
		free(poza->mat[i]);
	free(poza->mat);
	poza->dim1 = poza->x2 - poza->x1;
	poza->dim2 = (poza->y2 - poza->y1);
	poza->mat = alocare_matrice(poza->dim1, poza->dim2 * 3);
	for (int i = 0; i < poza->dim1; i++)
		for (int j = 0; j < poza->dim2 * 3; j++) 
			poza->mat[i][j] = poza->copie[i][j];
}

void CROP_P5(foto *poza)
{
	for (int i = 0; i < poza->dim1; i++)
		free(poza->mat[i]);
	free(poza->mat);
	poza->dim1 = poza->x2 - poza->x1;
	poza->dim2 = poza->y2 - poza->y1;
	poza->mat = alocare_matrice(poza->dim1, poza->dim2);
	for (int i = 0; i < poza->dim1; i++)
		for (int j = 0; j < poza->dim2; j++)
			poza->mat[i][j] = poza->copie[i][j];
}

void CROP_P6(foto *poza)
{
	for (int i = 0; i < poza->dim1; i++)
		free(poza->mat[i]);
	free(poza->mat);
	poza->dim1 = poza->x2 - poza->x1;
	poza->dim2 = poza->y2 - poza->y1;
	poza->mat = alocare_matrice(poza->dim1, 3 * poza->dim2);
	for (int i = 0; i < poza->dim1; i++)
		for (int j = 0; j < 3 * poza->dim2; j++)
			poza->mat[i][j] = poza->copie[i][j];
}

void CROP(foto *poza)
{
	if (!poza->mat)
		printf("No image loaded\n");
	else {
		printf("Image cropped\n");
		if (strcmp(poza->tip, "P2") == 0)
			CROP_P2(poza);
		if (strcmp(poza->tip, "P3") == 0)
			CROP_P3(poza);
		if (strcmp(poza->tip, "P5") == 0)
			CROP_P5(poza);
		if (strcmp(poza->tip, "P6") == 0)
			CROP_P6(poza);
		poza->x1 = 0;
		poza->x2 = poza->dim1;
		poza->y2 = poza->dim2;
		poza->y1 = 0;
	}
}

void EDGE(foto *poza, int i, int j)
{
	poza->copie[i][j] = 0;
	poza->copie[i][j] = poza->mat[i][j] * 9;
	poza->copie[i][j] -= poza->mat[i - 1][j - 3];
	poza->copie[i][j] -= poza->mat[i - 1][j];
	poza->copie[i][j] -= poza->mat[i - 1][j + 3];
	poza->copie[i][j] -= poza->mat[i][j - 3];
	poza->copie[i][j] -= poza->mat[i][j + 3];
	poza->copie[i][j] -= poza->mat[i + 1][j - 3];
	poza->copie[i][j] -= poza->mat[i + 1][j];
	poza->copie[i][j] -= poza->mat[i + 1][j + 3];	
}

void SHARPEN(foto *poza, int i, int j)
{
	poza->copie[i][j] = poza->copie[i][j] * 5;
	poza->copie[i][j] -= poza->copie[i - 1][j];
	poza->copie[i][j] -= poza->copie[i][j - 3];
	poza->copie[i][j] -= poza->copie[i][j + 3];
	poza->copie[i][j] -= poza->copie[i + 1][j];	
	if (poza->copie[i][j] < 0)
		poza->copie[i][j] = 0;
	if (poza->copie[i][j] > 255)
		poza->copie[i][j] = 255;	
}

void BLUR(foto *poza, int i, int j)
{
	poza->copie[i][j] = poza->mat[i][j];
	poza->copie[i][j] += poza->mat[i - 1][j - 3];
	poza->copie[i][j] += poza->mat[i - 1][j];
	poza->copie[i][j] += poza->mat[i - 1][j + 3];
	poza->copie[i][j] += poza->mat[i][j - 3];
	poza->copie[i][j] += poza->mat[i][j + 3];
	poza->copie[i][j] += poza->mat[i + 1][j - 3];
	poza->copie[i][j] += poza->mat[i + 1][j];
	poza->copie[i][j] += poza->mat[i + 1][j + 3];	
	poza->copie[i][j] = poza->copie[i][j] / 9;

}

void GAUSSIAN_BLUR(foto *poza, int i, int j)
{
	poza->copie[i][j] = poza->mat[i][j] * 4;
	poza->copie[i][j] += poza->mat[i - 1][j - 3];
	poza->copie[i][j] += poza->mat[i - 1][j] * 2;
	poza->copie[i][j] += poza->mat[i - 1][j + 3];
	poza->copie[i][j] += poza->mat[i][j - 3] * 2;
	poza->copie[i][j] += poza->mat[i][j + 3] * 2;
	poza->copie[i][j] += poza->mat[i + 1][j - 3];
	poza->copie[i][j] += poza->mat[i + 1][j] * 2;
	poza->copie[i][j] += poza->mat[i + 1][j + 3];
	poza->copie[i][j] = poza->copie[i][j] / 16;
}

void APPLY(foto *poza, char *str)
{
	if (!poza->mat) {
		printf("No image loaded\n");
	}
	int ok = 0;
	if (strcmp(str, "EDGE") == 0)
		ok = 1;
	if (strcmp(str, "BLUR") == 0)
		ok = 1;
	if (strcmp(str, "SHARPEN") == 0)
		ok = 1;
	if (strcmp(str, "GAUSSIAN_BLUR") == 0)
		ok = 1;
	if (ok == 0) {
		printf("APPLY parameter invalid\n");
		//continue;
	}
	if (strcmp(poza->tip, "P2") == 0 || strcmp(poza->tip, "P5") == 0) {
		printf("Easy Charlie Chaplin\n");
		//continue;
	}
	for (int i = 1; i < poza->x2 - poza->x1 - 1; i++)
		for (int j = 3; j < 3 * (poza->y2 - poza->y1 - 1); j++) {
			if (strcmp(str, "EDGE") == 0)
				EDGE(poza, i, j);
			if (strcmp(str, "BLUR") == 0 || ok == 0)
				BLUR(poza, i, j);
			if (strcmp(str, "SHARPEN") == 0 || ok == 0) {
				SHARPEN(poza, i, j);
			}
			if (strcmp(str, "GAUSSIAN_BLUR") == 0 || ok == 0)
				GAUSSIAN_BLUR(poza, i, j);
		}
	printf("APPLY %s done\n", str);
}

void SAVE_P2(foto *poza ,FILE *fout)
{
	if (poza->copie != NULL) {
		for (int i = 0; i < poza->x2 - poza->x1; i++)
			for (int j = 0; j < poza->y2 - poza->y1; j++) {
				poza->mat[poza->x1 + i][poza->y1 + j] = poza->copie[i][j];
			}
	}
	for (int i = 0; i < poza->dim1; i++) {
		for (int j = 0; j < poza->dim2; j++) {
			fprintf(fout, "%d", poza->mat[i][j]);
				fprintf(fout, " ");
		}
			fprintf(fout, "\n");
	}
}

void SAVE_P5(foto *poza, FILE *fout) {
    if (poza->copie != NULL) {
        for (int i = 0; i < poza->x2 - poza->x1; i++) {
            for (int j = 0; j < poza->y2 - poza->y1; j++) {
                poza->mat[poza->x1 + i][poza->y1 + j] = poza->copie[i][j];
            }
        }
    }
    for (int i = 0; i < poza->dim1; i++) {
        for (int j = 0; j < poza->dim2; j++) {
            fwrite(&poza->mat[i][j], sizeof(unsigned char), 1, fout);
        }
    }
}


void SAVE_P3(foto *poza ,FILE *fout)
{
	if (poza->copie != NULL) {
		for (int i = 0; i < poza->x2 - poza->x1; i++)
			for (int j = 0; j < 3 * (poza->y2 - poza->y1); j++) {
				poza->mat[poza->x1 + i][3 * poza->y1 + j] = poza->copie[i][j];
			}
	}
	for (int i = 0; i < poza->dim1; i++) {
		for (int j = 0; j < poza->dim2 * 3; j++) {
			fprintf(fout, "%d", poza->mat[i][j]);
				fprintf(fout, " ");
		}
			fprintf(fout, "\n");
	}
}

void SAVE_P6(foto *poza ,FILE *fout)
{
	if (poza->copie != NULL) {
		for (int i = 0; i < poza->x2 - poza->x1; i++)
			for (int j = 0; j < 3 * (poza->y2 - poza->y1); j++) {
				poza->mat[poza->x1 + i][3 * poza->y1 + j] = poza->copie[i][j];
			}
	}
	for (int i = 0; i < poza->dim1; i++) {
        for (int j = 0; j < 3 * poza->dim2; j++) {
            fwrite(&poza->mat[i][j], sizeof(unsigned char), 1, fout);
        }
    }
}

void convert_to_binary(foto *poza)
{
	if (strcmp(poza->tip, "P2") == 0)
		strcpy(poza->tip, "P5");
	if (strcmp(poza->tip, "P3") == 0)
		strcpy(poza->tip, "P6");
}

void convert_to_ascii(foto *poza)
{
	if (strcmp(poza->tip, "P5") == 0)
		strcpy(poza->tip, "P2");
	if (strcmp(poza->tip, "P6") == 0)
		strcpy(poza->tip, "P3");
}

void SAVE(foto *poza, char *file_name, int indice)
{
	FILE *fout = fopen(file_name, "w");
	if (indice == 1)
		convert_to_ascii(poza);
	if (indice == 0)
		convert_to_binary(poza);
	fprintf(fout, "%s\n", poza->tip);
	fprintf(fout, "%d %d\n", poza->dim2, poza->dim1);
	fprintf(fout, "255\n");
	if (strcmp(poza->tip, "P2") == 0)
		SAVE_P2(poza, fout);
	if (strcmp(poza->tip, "P5") == 0)
		SAVE_P5(poza, fout);
	if (strcmp(poza->tip, "P3") == 0)
		SAVE_P3(poza, fout);
	if (strcmp(poza->tip, "P6") == 0)
		SAVE_P6(poza, fout);
	printf("Saved %s\n", file_name);
	fclose(fout);
}

void invalid_command(char *comm)
{
	int ok = 0;
	if (strcmp(comm, "LOAD") == 0)
		ok = 1;
	if (strcmp(comm, "SELECT") == 0)
		ok = 1;
	if (strcmp(comm, "APPLY") == 0)
		ok = 1;
	if (strcmp(comm, "HISTOGRAM") == 0)
		ok = 1;
	if (strcmp(comm, "ROTATE") == 0)
		ok = 1;
	if (strcmp(comm, "EQUALIZE") == 0)
		ok = 1;
	if (strcmp(comm, "CROP") == 0)
		ok = 1;
	if (strcmp(comm, "SAVE") == 0)
		ok = 1;
	if (strcmp(comm, "EXIT") == 0)
		ok = 1;
	if (ok == 0) {
		printf("Invalid command\n");
	}
}

int main(void)
{
    char comanda[MAX];
	char *comm;
    foto *poza = malloc(sizeof(foto));
    	if (poza == NULL)
            exit(0);
	int ok = 0, select = 0;
    while (1)
    {
        fgets(comanda, MAX, stdin);
		comm = strtok(comanda, " ,\n");
		invalid_command(comm);
        if (strcmp(comm, "LOAD") == 0) {
			if (ok == 1) {
				offload(poza);
				ok = 0;
			}
			LOAD(poza, strtok(NULL, " ,\n"));
			ok++;
		}
        if (strcmp(comm, "SELECT") == 0) {
			if (select != 0) {
				offload_copie(poza);
				select = 0;
			}
			char *str = strtok(NULL, " ,\n");
			int x = 0;
			if(strcmp(str, "ALL") != 0){
				x = 1;
				int y1 = atoi(str);
				int x1 = atoi(strtok(NULL, " ,\n"));
				int y2 = atoi(strtok(NULL, " ,\n"));
				int x2 = atoi(strtok(NULL, " ,\n"));
				SELECT(poza, x1, y1, x2, y2, x);
			} else
				SELECT(poza, 0, 0 ,poza->dim1, poza->dim2, x);
			select = select + 1;
		}
        if (strcmp(comanda, "HISTOGRAM") == 0) {
			int x = atoi(strtok(NULL, " ,\n"));
			int y = atoi(strtok(NULL, " ,\n"));
            HISTOGRAM(poza, x, y);
		}
        if (strcmp(comanda, "EQUALIZE") == 0)
            EQUALIZE(poza);
        if (strcmp(comanda, "ROTATE") == 0)
            ROTATE(poza, strtok(NULL, " ,\n"));
        if (strcmp(comanda, "CROP") == 0)
            CROP(poza);
        if (strcmp(comanda, "APPLY") == 0){
			char *str = strtok(NULL, " ,\n");
			APPLY(poza, str);
		}
        if (strcmp(comanda, "SAVE") == 0) {
			char *str = strtok(NULL, " ,\n");
			if (!str) {
				printf("Invalid command\n");
				continue;
			}
			int ascii = 1;
			char *str1;
			str1 = strtok(NULL, " ,\n");
			if (str1 == NULL)
				ascii = 0;
        	SAVE(poza, str, ascii);
		}
        if (strcmp(comm, "EXIT") == 0) {
			if (!poza->mat) {
				printf("No image loaded\n");
				continue;
			} else {
					for (int i = 0; i < poza->dim1; i++)
						free(poza->mat[i]);
    				free(poza->mat);
					for (int i = 0; i < poza->x2 - poza->x1; i++)
						free(poza->copie[i]);
					free(poza->copie);
            		free(poza);
					break;
			}
		}
	}
	return 0;
}