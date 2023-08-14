/*Program a multi-threaded producer and consumer with locks on concurrent access to a memory location using C/C++/Golang.
Explanation: Have a global list / array where two or more producers append randomly
generated numbers concurrently. A consumer thread must dequeue from the global list and print it!*/
#include<bits/stdc++.h>
using namespace std;

#define BUF_SIZE 10
#define NUM_PRODUCE 100

int buf[BUF_SIZE];
int c = 0;
pthread_mutex_t lock;

void *producer(void *arg) {
    for (int i = 0; i < NUM_PRODUCE; i++) {
        int value = rand() % 100;
        pthread_mutex_lock(&lock);
        
        if (c < BUF_SIZE) {
            buf[c++] = value;
            cout<<"Produced:"<<endl;
            cout<<value;
        }
        
        pthread_mutex_unlock(&lock);
        usleep(rand() % 1000); // Simulate some work
    }
    
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < NUM_PRODUCE; i++) {
        pthread_mutex_lock(&lock);
        
        if (c > 0) {
            int value = buf[--c];
            cout<<"Consumed:"<<endl;
            cout<<value;
        }
        
        pthread_mutex_unlock(&lock);
        usleep(rand() % 1000); // Simulate some work
    }
    
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t producer_thread, consumer_thread;
    pthread_mutex_init(&lock, NULL);
    
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    pthread_mutex_destroy(&lock);
    
    return 0;
}
