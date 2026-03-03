#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int at;
    int bt;
    int wt;
    int tat;
    int index;  // original position
};

int main() {
    int n;
    scanf("%d", &n);

    struct Process p[100];

    for (int i = 0; i < n; i++) {
        char pname[20];
        scanf("%s %d %d", pname, &p[i].at, &p[i].bt);
        p[i].pid = atoi(pname + 1);
        p[i].index = i;  // store original position
    }

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].at > p[j + 1].at) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }

    int cur = 0;

    for (int i = 0; i < n; i++) {
        if (cur < p[i].at)
            cur = p[i].at;

        p[i].wt = cur - p[i].at;
        cur += p[i].bt;
        p[i].tat = p[i].wt + p[i].bt;
    }

    // Restore original order
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].index > p[j + 1].index) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }

    double avgWT = 0, avgTAT = 0;

    printf("Waiting Time: ");
    for (int i = 0; i < n; i++) {
        printf("P%d %d", p[i].pid, p[i].wt);
        if (i != n - 1)
            printf(" ");
        avgWT += p[i].wt;
    }

    printf("\nTurnaround Time: ");
    for (int i = 0; i < n; i++) {
        printf("P%d %d", p[i].pid, p[i].tat);
        if (i != n - 1)
            printf(" ");
        avgTAT += p[i].tat;
    }

    avgWT /= n;
    avgTAT /= n;

    printf("\nAverage Waiting Time: %.2f", avgWT);
    printf("\nAverage Turnaround Time: %.2f", avgTAT);

    return 0;
}