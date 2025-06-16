#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>


int pthread_key_create(pthread_key_t *key, void (*destructor)(void*)) {
    pthread_t* self = pthread_self(); // Получить текущий поток
    for (int i = 0; i < PTHREAD_KEYS_MAX; ++i) {
        if (!self->tsd[i]) {
            self->tsd[i] = malloc(sizeof(tsdata));
            self->tsd[i]->destructors = destructor;
            self->tsd[i]->data = NULL;
            *key = i;
            return 0;
        }
    }
    return -1; // Нет свободных ключей
}

int pthread_key_delete(pthread_key_t key) {
    pthread_t* self = pthread_self(); // Получить текущий поток
    if (key < 0 || key >= PTHREAD_KEYS_MAX || !self->tsd[key])
        return -1;
    free(self->tsd[key]);
    self->tsd[key] = NULL;
    return 0;
}

int pthread_setspecific(pthread_key_t key, const void *value) {
    pthread_t* self = pthread_self(); // Получить текущий поток
    if (key < 0 || key >= PTHREAD_KEYS_MAX)
        return -1;
    self->tsd[key]->data = (void*)value;
    return 0;
}

void* pthread_getspecific(pthread_key_t key) {
    pthread_t* self = pthread_self();
    if (key < 0 || key >= PTHREAD_KEYS_MAX)
        return NULL;
    return self->tsd[key]->data;
}
