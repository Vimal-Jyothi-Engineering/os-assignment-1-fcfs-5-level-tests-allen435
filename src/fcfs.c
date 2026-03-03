#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int pid[100], at[100], bt[100];
    int wt[100], tat[100];

    for (int i = 0; i < n; i++) {
        char pname[20];
        scanf("%s %d %d", pname, &at[i], &bt[i]);
        pid[i] = atoi(pname + 1);
    }

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (at[j] > at[j + 1]) {
                int t;
                t=at[j]; at[j]=at[j+1]; at[j+1]=t;
                t=bt[j]; bt[j]=bt[j+1]; bt[j+1]=t;
                t=pid[j]; pid[j]=pid[j+1]; pid[j+1]=t;
            }

    int cur = 0;
    for (int i = 0; i < n; i++) {
        if (cur < at[i])
            cur = at[i];

        wt[i] = cur - at[i];
        cur += bt[i];
        tat[i] = wt[i] + bt[i];
    }

    double avgWT = 0, avgTAT = 0;
    for (int i = 0; i < n; i++) {
        avgWT += wt[i];
        avgTAT += tat[i];
    }

    avgWT /= n;
    avgTAT /= n;

    printf("Waiting Time: ");
    for (int i = 0; i < n; i++) {
        printf("P%d %d", pid[i], wt[i]);
        if (i != n - 1)
            printf(" ");
    }

    printf("\nTurnaround Time: ");
    for (int i = 0; i < n; i++) {
        printf("P%d %d", pid[i], tat[i]);
        if (i != n - 1)
            printf(" ");
    }

    printf("\nAverage Waiting Time: %.2f", avgWT);
    printf("\nAverage Turnaround Time: %.2f", avgTAT);

    return 0;
}