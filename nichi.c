#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int matrix[n][n], copie[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
            copie[i][j] = matrix[i][j];
            while (abs(matrix[i][j]) > n)
                matrix[i][j] += n;
    }
    int i = 0, j = 0, sum = 0;
    while (matrix[i][j]) {
        sum += abs(copie[i][j]);
        if (i % 2 != j % 2){
            int copie = (i + matrix[i][j]) % n;
            matrix[i][j] = 0;
            i = copie;
            continue;
        }
        if (i % 2 == j % 2) {
            int copie = (j + matrix[i][j]) % n;
            matrix[i][j] = 0;
            j = copie;
        }
    }
    printf("%d\n%d ",sum,  n - i);
    if (j < 26)
        printf("%c", (char)j + 'A');
    if (j > 25 && j < 626)

    return 0;
}