#include <stdio.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE] = {0};
int in = 0, out = 0;
int full = 0, empty = BUFFER_SIZE;

void displayBuffer()
{
    int i;
    printf("\nBuffer state: ");

    for(i = 0; i < BUFFER_SIZE; i++)
    {
        if(buffer[i] == 0)
            printf("[ ] ");
        else
            printf("[%d] ", buffer[i]);
    }

    printf("\nFull = %d  Empty = %d\n", full, empty);
}

void producer(int item)
{
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    full++;
    empty--;

    printf("Produced: %d\n", item);
    displayBuffer();
}

void consumer()
{
    int item;

    item = buffer[out];
    buffer[out] = 0;   // clear slot
    out = (out + 1) % BUFFER_SIZE;
    full--;
    empty++;

    printf("Consumed: %d\n", item);
    displayBuffer();
}

int main()
{
    int choice, item;

    while(1)
    {
        printf("\n1. Produce\n2. Consume\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                if(empty != 0)
                {
                    printf("Enter item: ");
                    scanf("%d", &item);
                    producer(item);
                }
                else
                {
                    printf("Buffer Full\n");
                }
                break;

            case 2:
                if(full != 0)
                {
                    consumer();
                }
                else
                {
                    printf("Buffer Empty\n");
                }
                break;

            case 3:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}
