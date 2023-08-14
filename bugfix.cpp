/*Find and fix the bug in the following code. Write down the explanation about the bug and
fix the code.*/

/*Error: remove_data() function does not handle the case where the list is empty. If we attempt to remove data from an empty list, 
we are accessing memory that we don't have permission to access, resulting in a segmentation fault.
so to fix this, added the condition where List is empty to print the error that list is empty, the remove_data() function 
will print an error message and exit if you try to remove data from an empty list, preventing the segmentation fault.
return null in producer and consumer function to avoid the "no return statement in function returning non void" warning*/


//correct code 


#include <bit/stdc++.h>
using namespace std;
#define BUFFER_SIZE 10

typedef struct node {
int data;
struct node *next;
} Node;

Node *head = NULL, *tail = NULL;
int count = 0;

sem_t full, empty;
pthread_mutex_t lock;

void add_data(int data) {
    Node new_node = (Node)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    if(tail == NULL) {
    head = tail = new_node;
    } else {
    tail->next = new_node;
    tail = new_node;
    }
    count++;
}

int remove_data() {
    if (head == NULL) {
        fprintf(stderr, "List is empty\n");
        exit(1); 
    }
    
    Node *temp = head;
    int data = temp->data;
    head = head->next;
    free(temp); 
    count--;
    return data;
}


void *producer(void *arg) {
    int i, data;
    for(i=0; i<100; i++) {
        data = rand() % 100;
        sem_wait(&empty);
        pthread_mutex_lock(&lock);
        add_data(data);
        printf("Produced: %d\n", data);
        pthread_mutex_unlock(&lock);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg) {
    int i, data;
    for(i=0; i<100; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&lock);
        data = remove_data();
        printf("Consumed: %d\n", data);
        pthread_mutex_unlock(&lock);
        sem_post(&empty);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);
    pthread_mutex_init(&lock, NULL);
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    return 0;
}