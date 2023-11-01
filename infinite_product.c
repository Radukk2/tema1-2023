#include <stdio.h>
#include <math.h>

int convert_to_base_10(int x)
{
    int copie = x, nr_cif = 0;
    while (copie) {
        nr_cif++;
        copie /= 10;
    }
    int new_number = 0, ctr = 0;
    while (nr_cif != ctr) {
       new_number += pow(8, ctr) * (x % 10);
       ctr++;
       x /= 10;
    }
    return new_number;
}   

int main() {
    int lung;
    double norm1 = 0, norm2 = 0;
    scanf("%d", &lung);
    int v1[lung], v2[lung];
    int prod = 0;
    for (int i = 0; i < lung; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        v1[i] = convert_to_base_10(x);
        v2[i] = convert_to_base_10(y);
        prod += v1[i] * v2[i];
        norm1 += v1[i] * v1[i];
        // norm1 = sqrt(norm1);
        norm2 += v2[i] * v2[i];
        // norm2 = sqrt(norm2);
    }
    for (int i = 0; i < lung - 1; i++)
        for (int j = i; j < lung; j++) {
            if (v1[i] < v1[j]) {
                int aux = v1[i];
                v1[i] = v1[j];
                v1[j] = aux;
            }
            if (v2[i] < v2[j]) {
                int aux = v2[i];
                v2[i] = v2[j];
                v2[j] = aux;
            }
        }
    printf("%d\n%d %d\n%.7f %.7f", prod, v1[1], v2[1], norm1, norm2);
    return 0;
}