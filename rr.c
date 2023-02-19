#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int rem_time;
} process;

int ProcessScheduler[10000]; // array that stores which process is executed each second (max total 10000 seconds)
unsigned int time = 0;

typedef struct el {
    int pid;
    struct el * next;
}Q;

Q * queue = NULL;

// function that adds the process with pid==i in the queue
void addToQueue(int id) {
    Q *n, *n1;
    n = (Q *)malloc(sizeof(Q));
    n->next = NULL;
    n->pid = id;
    if(queue == NULL) {
        queue = n;
    }
    else {
        for(n1 = queue; n1->next!=NULL; n1=n1->next); // point at the end of the queue
        n1 -> next = n;
    }
}

// function to add the arrived processes into the queue
void addArrivedProcessesToQueue(process *arr, int numOfProc) {
    for(int i=0; i<numOfProc; i++) {
        if(arr[i].arrival_time == time){
            addToQueue(arr[i].pid);
        }
    }
}

// function that returns 1 if a process is not finished yet
unsigned int executionRemained(process *arr, int numOfProc) {
    for(int i=0; i<numOfProc; i++) {
        if(arr[i].rem_time > 0)
            return 1;
    }
    return 0;
}


// function that returns the next process in the queue
int getNextProcess() {
    Q *n;
    int x;
    if(queue == NULL) {
        return -1;
    }
    else {
        x = queue -> pid;
        n = queue;
        queue = queue -> next;
        free(n);
        return x;
    }
}

// function that finds the index of the process with pid in arr
int findIndex(process *arr, int numOfProc, int pid){
    for(int i = 0; i < numOfProc; i++) {
        if(arr[i].pid == pid)
            return i;
    }
    return -1;
}

// function to get the schedule of the process
void schedule(process *arr, int numOfProc, int quantum) {
    int nextProc;
    unsigned int q;

    addArrivedProcessesToQueue(arr, numOfProc);

    while(executionRemained(arr,numOfProc)) {
        nextProc = getNextProcess(); // get next process and remove it from the list
        int ind = findIndex(arr, numOfProc, nextProc); // find index of next process in arr

        q = quantum;
        // if the remaining time of the process is shorter than the quantum
        if(arr[ind].rem_time < q)
            q = arr[ind].rem_time;

        for(unsigned int i = q; i > 0; i--){
            ProcessScheduler[time]=nextProc;
            time++;
            arr[ind].rem_time--;
            // if a process arrives, add it to the queue
            addArrivedProcessesToQueue(arr, numOfProc);
        }

        // if the process is not completed
        // add it to the end of the queue
        if(arr[ind].rem_time > 0)
            addToQueue(nextProc);
    }
}

void printScheduling() {
    for(int i = 0; i < time; i++) {
        printf("%d\n",ProcessScheduler[i]);
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

    // set the remaining time for each process equal to its burst time
    for (int i = 0 ; i < n ; i++)
        arr[i].rem_time = arr[i].burst_time;

    schedule(arr, n, quantum);
    printScheduling();

    return 0; /* DO NOT EDIT THIS LINE */
}
