#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int rem_time;
} process;


int main() {

    /* read in data - DO NOT EDIT (START) */
    int n;
    int quantum;
    scanf("%d", &n);
    scanf("%d", &quantum);
    process *arr;
    arr = malloc(n * sizeof(process));
    for (int i = 0; i < n ; ++i) {
        scanf("%d", &arr[i].pid);
        scanf("%d", &arr[i].arrival_time);
        scanf("%d", &arr[i].burst_time);
    }
    /* read in data - DO NOT EDIT (END) */

    // set the remaining time for each process equal to its burst time
    for (int i = 0 ; i < n ; i++)
        arr[i].rem_time = arr[i].burst_time;

    // for each process in the array
    for (int i = 0; i < n ; ++i) {
        while (arr[i].rem_time > 0){
            printf("%d\n", arr[i].pid);
            arr[i].rem_time--;
        }
    }

    return 0; /* DO NOT EDIT THIS LINE */
}
