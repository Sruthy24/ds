#include <stdio.h>
#define MAX 5
int deque[MAX];
int front = -1, rear = -1;
int isFull() {
    return ((front == 0 && rear == MAX - 1) || (front == rear + 1));
}
int isEmpty() {
    return front == -1;
}
void insertFront(int item) {
    if (isFull()) {
        printf("Deque is full!\n");
        return;
    }
    if (isEmpty()) {
        front = rear = 0;
    } else if (front == 0) {
        front = MAX - 1;
    } else {
        front--;
    }
    deque[front] = item;
}
void insertRear(int item) {
    if (isFull()) {
        printf("Deque is full!\n");
        return;
    }
    if (isEmpty()) {
        front = rear = 0;
    } else if (rear == MAX - 1) {
        rear = 0;
    } else {
        rear++;
    }
    deque[rear] = item;
}
void deleteFront() {
    if (isEmpty()) {
        printf("Deque is empty! Nothing to delete.\n");
        return;
    }
    printf("Deleted from front: %d\n", deque[front]);
    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % MAX;
    }
}
void deleteRear() {
    if (isEmpty()) {
        printf("Deque is empty! Nothing to delete.\n");
        return;
    }
    printf("Deleted from rear: %d\n", deque[rear]);
    if (front == rear) {
        front = rear = -1;
    } else if (rear == 0) {
        rear = MAX - 1;
    } else {
        rear--;
    }
}
void displayDeque() {
    if (isEmpty()) {
        printf("Deque is empty!\n");
        return;
    }
    printf("Deque contents: ");
    int i = front;
    while (1) {
        printf("%d ", deque[i]);
        if (i == rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}
int main() {
    int n, value, direction, deletions, del_dir;
    printf("Enter number of values to insert: ");
    scanf("%d", &n);
    if (n > MAX) {
        printf("Error: Insertion count exceeds max size (%d)\n", MAX);
        return 1;
    }
    for (int i = 0; i < n; i++) {
        printf("Enter value %d: ", i + 1);
        scanf("%d", &value);
        printf("Insert at 1.Front or 2.Rear? ");
        scanf("%d", &direction);

        if (direction == 1) {
            insertFront(value);
        } else if (direction == 2) {
            insertRear(value);
        } else {
            printf("Invalid direction! Skipping this input.\n");
        }
    }
    displayDeque();
    printf("\nEnter number of deletions: ");
    scanf("%d", &deletions);
    for (int i = 0; i < deletions; i++) {
        if (isEmpty()) {
            printf("Deque is empty! Cannot delete more.\n");
            break;
        }
        printf("Delete from 1.Front or 2.Rear? ");
        scanf("%d", &del_dir);
        if (del_dir == 1) {
            deleteFront();
        } else if (del_dir == 2) {
            deleteRear();
        } else {
            printf("Invalid delete direction! Skipping.\n");
        }
    }
    displayDeque();
    return 0;
}
