#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>



struct my_mutex {
    atomic_bool is_locked;
} typedef my_mutex;

int glob = 0;
my_mutex mtx;

void init(my_mutex* mtx) {
    atomic_init(&mtx->is_locked, false);
}

void lock(my_mutex* mtx) {
    while (atomic_exchange(&mtx->is_locked, true)) {
        
    }
}

void unlock(my_mutex* mtx) {
    atomic_store(&mtx->is_locked, false);
}

void* thread1(void* args) {
    int loop = *(int*)args;
    for (int i = 0; i < loop; ++i) {
        lock(&mtx);
        glob++;
        unlock(&mtx);
    }
        return NULL;
}
int main() {
    init(&mtx);
    pthread_t tid1, tid2;
    int loop = 1000000;
    pthread_create(&tid1, NULL, thread1, &loop);
    pthread_create(&tid2, NULL, thread1, &loop);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("%d", glob);

}