//
//  MultiThread.cpp
//  LearnCpp
//
//  Created by Wang on 3/28/16.
//  Copyright © 2016 Wang. All rights reserved.
//

#include "MultiThread.hpp"
pthread_mutex_t mymutex;
pthread_cond_t mycond;
pthread_mutex_t coutmutex;
int cnt = 0;
const string TAG1 = "say_hello1";
const string TAG2 = "say_hello2";
int i1 = 11;
int i2 = 22;
void *say_hello1(void *args){
    int j = *((int*)args);
//    sleep(2);
    pthread_mutex_lock(&mymutex);
    cout << TAG1 << ", " << j << ", " << pthread_self() << ", " << getpid() << endl;
    pthread_mutex_unlock(&mymutex);
    pthread_exit((void*)&i1);
}

void *say_hello2(void *args){
//    sleep(1);
    pthread_mutex_lock(&mymutex);
    cout << TAG2 << ", " << *((int*)args) << ", " << pthread_self() << ", " << getpid() << endl;
    pthread_mutex_unlock(&mymutex);
    pthread_exit((void*)&i2);
}

void test_thread_1(){
    time_t t1 = clock();
    pthread_t pt[2];
    pthread_attr_t pt_attr;
    pthread_attr_init(&pt_attr);
    pthread_attr_setdetachstate(&pt_attr, PTHREAD_CREATE_JOINABLE);
//    pthread_attr_setdetachstate(&pt_attr, PTHREAD_CREATE_DETACHED);
    pthread_mutex_init(&mymutex, nullptr);
    volatile int i = 0;
    cout << "Create thread 1" << endl;
    int ret1 = pthread_create(&pt[0], &pt_attr, say_hello1, (void*)&i);
    if (ret1 != 0) {
        cerr << "pthread_create error" << endl;
    }
    i++;
    cout << "Create thread 2" << endl;
    int ret2 = pthread_create(&pt[1], &pt_attr, say_hello2, (void*)&i);
    if (ret2 != 0) {
        cerr << "pthread_create error" << endl;
    }

    int *ptr[2];
//    sleep(3);
    cout << "Begin to wait for threads" << endl;
    for (int i = 0; i < 2; i++) {
        pthread_join(pt[i], (void**)&ptr[i]);
//        pthread_detach(pt[i]);
//        cout << "retrun value:" << *ptr[i] << endl;
    }
    cout << "Now return main thread" << endl;
//    sleep(3);
    
    pthread_mutex_destroy(&mymutex);
//    cout << "Time: " << (clock() - t1) * 1000000/CLOCKS_PER_SEC << " ms" << endl;
}

#define NUM_THREADS  3
#define TCOUNT 10
#define COUNT_LIMIT 12

int     count = 0;
int     thread_ids[3] = {0,1,2};
pthread_mutex_t count_mutex;
pthread_cond_t count_threshold_cv;

void *inc_count(void *idp)
{
    int j,i;
    double result=0.0;
    int *my_id = (int*)idp;
    
    for (i=0; i<TCOUNT; i++) {
        pthread_mutex_lock(&count_mutex);
        ::count++;
        
        /*
         Check the value of count and signal waiting thread when condition is
         reached.  Note that this occurs while mutex is locked.
         */
        if (::count == COUNT_LIMIT) {
            pthread_cond_signal(&count_threshold_cv);
            printf("inc_count(): thread %d, count = %d  Threshold reached.\n",
                   *my_id, ::count);
        }
        printf("inc_count(): thread %d, count = %d, unlocking mutex\n",
               *my_id, ::count);
        pthread_mutex_unlock(&count_mutex);
        
        /* Do some work so threads can alternate on mutex lock */
        for (j=0; j<1000; j++)
            result = result + (double)random();
    }
    pthread_exit(NULL);
}

void *watch_count(void *idp)
{
    int *my_id = (int*)idp;
    
    printf("Starting watch_count(): thread %d\n", *my_id);
    
    /*
     Lock mutex and wait for signal.  Note that the pthread_cond_wait
     routine will automatically and atomically unlock mutex while it waits.
     Also, note that if COUNT_LIMIT is reached before this routine is run by
     the waiting thread, the loop will be skipped to prevent pthread_cond_wait
     from never returning.
     */
    pthread_mutex_lock(&count_mutex);
    if (::count<COUNT_LIMIT) {
        pthread_cond_wait(&count_threshold_cv, &count_mutex);
        printf("watch_count(): thread %d Condition signalreceived.%d\n", *my_id, ::count);
    }
    pthread_mutex_unlock(&count_mutex);
    pthread_exit(NULL);
}
               
void test_thread_2()
{
    int i, rc;
    pthread_t threads[3];
    pthread_attr_t attr;
    
    /* Initialize mutex and condition variable objects */
    pthread_mutex_init(&count_mutex, NULL);
    pthread_cond_init (&count_threshold_cv, NULL);
    
    /* For portability, explicitly create threads in a joinable state */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&threads[0], &attr, inc_count, (void *)&thread_ids[0]);
    pthread_create(&threads[1], &attr, inc_count, (void *)&thread_ids[1]);
    pthread_create(&threads[2], &attr, watch_count, (void *)&thread_ids[2]);
    
    /* Wait for all threads to complete */
    for (i=0; i<NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf ("Main(): Waited on %d  threads. Done.\n", NUM_THREADS);
    
    /* Clean up and exit */
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&count_mutex);
    pthread_cond_destroy(&count_threshold_cv);
    pthread_exit(NULL); 
    
}

int var = 0;
void* add_1(void* args){
    while (var < 10) {
        pthread_mutex_lock(&mymutex);
        var++;
        if (var == 9) {
            pthread_cond_signal(&mycond);
            printf("add_1: thread %d, var = %d thres reached\n", pthread_self(), var);
        }
        
        printf("add_1: thread %d, var = %d\n", pthread_self(), var);
        pthread_mutex_unlock(&mymutex);
    }
    pthread_exit(nullptr);
}

void* sub_1(void* args){
    for (int i = 0; i < 3; i++) {
        pthread_mutex_lock(&mymutex);
        if (var < 9) {
            printf("sub_1: %d\n", var);
            pthread_cond_wait(&mycond, &mymutex);
            printf("sub_1: %d\n", var);
            var = 2;
            printf("sub_1: thread %d, var = %d\n", pthread_self(), var);
        }
        pthread_mutex_unlock(&mymutex);
    }
    pthread_exit(nullptr);
}

void test_thread_3(){
    pthread_t pt[3];
    pthread_mutex_init(&mymutex, nullptr);
    pthread_cond_init(&mycond, nullptr);
    pthread_create(&pt[0], nullptr, add_1, nullptr);
    pthread_create(&pt[1], nullptr, add_1, nullptr);
    pthread_create(&pt[2], nullptr, sub_1, nullptr);
    for (int i = 0; i < 3; i++) {
        pthread_join(pt[i], nullptr);
    }
    pthread_mutex_destroy(&mymutex);
    pthread_cond_destroy(&mycond);
}
