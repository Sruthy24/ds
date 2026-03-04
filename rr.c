#include <stdio.h>

int main() {
    int n, i, time = 0, remain, tq;
    int pid[10], bt[10], rt[10];
    int ct[10], tat[10], wt[10];
    int total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    remain = n;

    for(i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Burst time of P%d: ", pid[i]);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];   // Remaining time = Burst time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    while(remain != 0) {
        for(i = 0; i < n; i++) {
            if(rt[i] > 0) {
                if(rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    ct[i] = time;
                    rt[i] = 0;
                    remain--;
                }
            }
        }
    }

    printf("\nPID\tBT\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++) {
        tat[i] = ct[i];
        wt[i] = tat[i] - bt[i];

        total_tat += tat[i];
        total_wt += wt[i];

        printf("P%d\t%d\t%d\t%d\t%d\n",
               pid[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat / n);

    return 0;
}
