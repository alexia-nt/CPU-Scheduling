#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int rem_time;
} process;

void swap(process * xp, process* yp)
{
    process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// function that implements bubble sort
void bubbleSort(process *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++){
            if (arr[j].arrival_time == arr[j + 1].arrival_time)
                if (arr[j].burst_time > arr[j + 1].burst_time)
                    swap(&arr[j], &arr[j + 1]);
        }
}

// function that brings the process from index k to index l
// without changing the position of the other processes
void bubbleSwap(process *arr, int k, int l){
    // bring the process from l to k position
    for(int i=l; i>k; --i){
        process temp = arr[i];
        arr[i] = arr[i-1];
        arr[i-1] = temp;
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

    // the first process in the array is the shortest
    // so, it is executed first
    arr[0].completion_time = arr[0].arrival_time + arr[0].burst_time; // completion time of the first process

    // for all the other processes
    for (int i = 1; i < n ; ++i) {
        int compl_time = arr[i-1].completion_time; // completion time of the last process that has been executed
        int min = arr[i].burst_time;
        // for all the other processes
        for (int j = i+1; j < n ; ++j) {
            if(arr[j].arrival_time <= compl_time && arr[j].burst_time < min){
                min = arr[j].burst_time;
                // bring the process from j to i position
                bubbleSwap(arr, i, j);
            }
            if(arr[j].arrival_time > compl_time){
                // the processes are in the correct order in the array
                // no other swaps needed
                break;
            }
        }
        arr[i].completion_time = compl_time + arr[i].burst_time;
    }

    // processes are now in the correct order in the array
    for (int i = 0; i < n ; ++i) {
        while (arr[i].rem_time > 0){
            printf("%d\n", arr[i].pid);
            arr[i].rem_time--;
        }
    }

    return 0; /* DO NOT EDIT THIS LINE */
}
