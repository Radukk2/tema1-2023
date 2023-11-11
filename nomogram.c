#include <stdio.h>

int foo(int matrix[200][200], int v[200], int rules[200][100], int n, int m)
{
    for (int i = 0; i < n; i++) {
        int k = 0;
            for (int j = 0; j < m; j++){
                if (matrix[i][j] && !v[i])
                    return 0;
                if (matrix[i][j]) { 
                    int ind = j;
                    for (ind = j; ind < m; ind++) {
                        if (matrix[i][ind]) 
                            rules[i][k]--;
                        else
                            break;
                    }
                    if (rules[i][k] != 0)
                        return 1;
                    j = ind - 1;
                    k++;
                }
            }
    }
    for (int i = 0; i < m; i++) {
        int k = 0;
            for (int j = 0; j < n; j++){
                if (matrix[j][i] && !v[i + n])
                    return 0;
                if (matrix[j][i]) { 
                    int ind = j;
                    for (ind = j; ind < n; ind++) {
                        if (matrix[ind][i]) 
                            rules[i + n][k]--;
                        else
                            break;
                    }
                    if (rules[i + n][k] != 0)
                        return 1;
                    j = ind - 1;
                    k++;
                }
            }
    }
    return 0;
}

int main(void) {
    int games;
    scanf("%d", &games);
    while(games) {
        int n, m;
        scanf("%d%d", &n, &m);
        int rules[n + m][100], matrix[200][200], v[n + m];
        for (int i = 0; i < n + m; i++) {
            scanf("%d", &v[i]);
            for (int j = 0; j < v[i]; j++)
                scanf("%d", &rules[i][j]);
            for (int j = v[i]; j < 100; j++)
                rules[i][j] = 0;
        }
        for (int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                scanf("%d", &matrix[i][j]);

        if (!foo(matrix, v, rules, n, m))
            printf("Corect\n");
        else
            printf("Eroare\n");    
        games--;
    }
    return 0;
}