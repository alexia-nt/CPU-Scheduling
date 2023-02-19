#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int rem_time;
} process;

void swap(process * xp, process* yp) {
    process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// function that implements bubble sort
// by burst time in case arrival times are the same
// array is already sorted by arrival time
void bubbleSort(process *arr, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++){
            if (arr[j].arrival_time == arr[j + 1].arrival_time)
                if (arr[j].burst_time > arr[j + 1].burst_time)
                    swap(&arr[j], &arr[j + 1]);
        }
}

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

    // sort by burst time in case arrival times are the same
    bubbleSort(arr,n);

    // set the remaining time for each process equal to its burst time
    for (int i = 0 ; i < n ; i++)
        arr[i].rem_time = arr[i].burst_time;

    // the first process in the array arrives first and is the shortest
    // so, it starts being executed first
    printf("%d\n", arr[0].pid); // time == 0
    arr[0].rem_time--;

    int completed = 0;
    // if the first process had burst time == 1
    // it is now completed
    if(arr[0].rem_time == 0)
        completed++;

    // adding a process at the end of the array with remaining time = 100000
    arr = realloc(arr, (n+1) * sizeof(process));
    arr[n].rem_time=100000;

    // for loop until all the processes are completed
    for(int time = 1; completed != n; time++){
        int min_pos=n;
        // for each process
        for(int i = 0; i < n; i++){
            // finding the process with the shortest remaining time
            if(arr[i].arrival_time <= time && arr[i].rem_time < arr[min_pos].rem_time && arr[i].rem_time > 0)
                min_pos=i;
        }
        // process with the shortest remaining time is executed
        printf("%d\n", arr[min_pos].pid);
        arr[min_pos].rem_time--;

        if(arr[min_pos].rem_time==0){
            completed++;
        }
    }

    return 0; /* DO NOT EDIT THIS LINE */
}
