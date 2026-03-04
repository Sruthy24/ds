#include <stdio.h>

int main() {
    int n, i, j, choice;
    int bt[20], wt[20], tat[20], ct[20];
    int priority[20];
    int pid[20];
    int total_wt = 0, total_tat = 0;
    int time, tq, remain, rt[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Burst time of P%d: ", pid[i]);
        scanf("%d", &bt[i]);
    }

    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. FCFS\n");
    printf("2. SJF\n");
    printf("3. Priority\n");
    printf("4. Round Robin\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch(choice) {

    // ---------------- FCFS ----------------
    case 1:
        ct[0] = bt[0];
        wt[0] = 0;
        for(i = 1; i < n; i++) {
            ct[i] = ct[i-1] + bt[i];
            wt[i] = ct[i-1];
        }

        for(i = 0; i < n; i++) {
            tat[i] = bt[i] + wt[i];
            total_wt += wt[i];
            total_tat += tat[i];
        }
        break;

    // ---------------- SJF ----------------
    case 2:
        for(i = 0; i < n-1; i++) {
            for(j = i+1; j < n; j++) {
                if(bt[i] > bt[j]) {
                    int temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                    temp = pid[i]; pid[i] = pid[j]; pid[j] = temp;
                }
            }
        }

        ct[0] = bt[0];
        wt[0] = 0;
        for(i = 1; i < n; i++) {
            ct[i] = ct[i-1] + bt[i];
            wt[i] = ct[i-1];
        }

        for(i = 0; i < n; i++) {
            tat[i] = bt[i] + wt[i];
            total_wt += wt[i];
            total_tat += tat[i];
        }
        break;

    // ---------------- Priority ----------------
    case 3:
        for(i = 0; i < n; i++) {
            printf("Enter priority of P%d: ", pid[i]);
            scanf("%d", &priority[i]);
        }

        for(i = 0; i < n-1; i++) {
            for(j = i+1; j < n; j++) {
                if(priority[i] > priority[j]) {
                    int temp;
                    temp = priority[i]; priority[i] = priority[j]; priority[j] = temp;
                    temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                    temp = pid[i]; pid[i] = pid[j]; pid[j] = temp;
                }
            }
        }

        ct[0] = bt[0];
        wt[0] = 0;
        for(i = 1; i < n; i++) {
            ct[i] = ct[i-1] + bt[i];
            wt[i] = ct[i-1];
        }

        for(i = 0; i < n; i++) {
            tat[i] = bt[i] + wt[i];
            total_wt += wt[i];
            total_tat += tat[i];
        }
        break;

    // ---------------- Round Robin ----------------
    case 4:
        printf("Enter Time Quantum: ");
        scanf("%d", &tq);

        for(i = 0; i < n; i++)
            rt[i] = bt[i];

        time = 0;
        remain = n;

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

        for(i = 0; i < n; i++) {
            tat[i] = ct[i];
            wt[i] = tat[i] - bt[i];
            total_wt += wt[i];
            total_tat += tat[i];
        }
        break;

    default:
        printf("Invalid Choice!\n");
        return 0;
    }

    // ================= Output =================
    printf("\nPID\tBT\tCT\tWT\tTAT\n");
    for(i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\n", pid[i], bt[i], ct[i], wt[i], tat[i]);

    printf("\nAverage Waiting Time = %.2f", (float)total_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat/n);

    return 0;
}

