#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int grades[n], weights[n];
    int points = 0;
    for (int i = 0; i < n; i++)
        scanf("%d", &grades[i]);
    for (int i = 0; i < n; i++) {
        scanf("%d", &weights[i]);
        points += weights[i] *  grades[i];
    }
    int final_score, contor = 0;
    scanf("%d", &final_score);
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++) {
            if ((10 - grades[i]) * weights[i] < (10 - grades[j]) * weights[j]) {
                int aux1 = grades[i], aux2 = weights[i];
                grades[i] = grades[j];
                weights[i] = weights[j];
                grades[j] = aux1;
                weights[j] = aux2;
            }
        }
    if (final_score <= points)
        printf("-1");
    else {
        int i = 0;
        while (final_score > points && i < n) {
            points -= grades[i] * weights[i];
            points += 10 * weights[i];
            contor++;
            i++;
        }
        if (final_score > points)
            printf("-1");
        else
            printf("%d", contor);
    }
    return 0;
}