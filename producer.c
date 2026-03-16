#include <stdio.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE] = {0};
int in = 0, out = 0;

// Semaphores
int mutex = 1;           // binary semaphore for mutual exclusion
int empty = BUFFER_SIZE;  // counts empty slots
int full = 0;             // counts full slots

void wait(int *s) {
    (*s)--;
}

void signal(int *s) {
    (*s)++;
}

void displayBuffer() {
    int i;
    printf("\nBuffer state: ");
    for(i = 0; i < BUFFER_SIZE; i++) {
        if(buffer[i] == 0)
            printf("[ ] ");
        else
            printf("[%d] ", buffer[i]);
    }
    printf("\nFull = %d  Empty = %d\n", full, empty);
}

void producer(int item) {
    if(empty == 0) {
        printf("Buffer Full\n");
        return;
    }

    wait(&empty);   // wait if no empty slot
    wait(&mutex);   // enter critical section

    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    full++;

    printf("Produced: %d\n", item);
    displayBuffer();

    signal(&mutex); // leave critical section
    signal(&full);  // increment full slots
}

void consumer() {
    if(full == 0) {
        printf("Buffer Empty\n");
        return;
    }

    wait(&full);    // wait if buffer empty
    wait(&mutex);   // enter critical section

    int item = buffer[out];
    buffer[out] = 0;
    out = (out + 1) % BUFFER_SIZE;
    empty++;

    printf("Consumed: %d\n", item);
    displayBuffer();

    signal(&mutex); // leave critical section
    signal(&empty); // increment empty slots
}

int main() {
    int choice, item;

    while(1) {
        printf("\n1. Produce\n2. Consume\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter item: ");
                scanf("%d", &item);
                producer(item);
                break;

            case 2:
                consumer();
                break;

            case 3:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}
