#include <stdio.h>

int main(void) {
    int games;
    scanf("%d", &games);
    while(games) {
        int n, m;
        scanf("%d%d", &n, &m);
        int rules[n + m][100], matrix[n][m], v[n + m];
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
        int wrong = 0;
        for (int i = 0; i < n + m; i++) {
            printf("%d ",  v[i]);
            for (int j = 0; j < 100; j++)
                if(rules[i][j])
                printf("%d ", rules[i][j]);
            printf("\n");
        }
        if (wrong == 0)
            printf("Corect\n");
        else
            printf("Eroare\n");    
        games--;
    }
    return 0;
}