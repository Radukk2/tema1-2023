#include <stdio.h>

int main() {
    int games;
    scanf("%d", &games);
    while(games) {
        int n, m;
        scanf("%d%d", &n, &m);
        int rules[n + m][101], matrix[n][m];
        for (int i = 0; i < n + m; i++) {
            int x;
            scanf("%d", &x);
            rules[i][0] = x;
            for (int j = 1; j < x; j++)
                scanf("%d", &rules[i][j]);
            for (int j = x; j < 100; j++)
                rules[i][j] = 0;
        }
        for (int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                scanf("%d", &matrix[i][j]);
        int wrong = 0;
        for (int i = 0; i < n; i ++) {
            if (rules[i][0] == 0)
                for (int j = 0; j < m; j++)
                    if (rules[i][j] != 0) {
                        wrong = 1;
                        break;
                    }
        }        
        games--;
    }
    return 0;
}