#ifndef __DEQUE_H_
#define __DEQUE_H_

#include <assert.h>
#include <stdlib.h>
#include <iostream>

#define Deque_DEFINE(T)                                                                             \
    struct Deque_##T {                                                                              \
        T *data;                                                                                    \
        size_t deq_size;                                                                            \
        char *type_name;                                                                            \
        T &(*at)(Deque_##T *, int i);                                                               \
        size_t (*size)(Deque_##T *);                                                                \
        void (*delet)(Deque_##T *);                                                                 \
    };                                                                                              \
                                                                                                    \
    T &Deque_##T##_at(Deque_##T *deq, int i) {                                                      \
        assert(i < 10);                                                                             \
        return deq->data[i];                                                                        \
    }                                                                                               \
                                                                                                    \
    void Deque_##T##_delete(Deque_##T *deq) {                                                       \
        free(deq->data);                                                                            \
        free(deq);                                                                                  \
    }                                                                                               \
                                                                                                    \
    size_t Deque_##T##_size(Deque_##T *deq) {                                                       \
        return deq->deq_size;                                                                       \
    }                                                                                               \
                                                                                                    \
    void Deque_##T##_ctor(Deque_##T *deq, bool (*)(const T&, const T&)) {                           \
        deq->deq_size = 0;                                                                          \
        deq->data = (T*)malloc(sizeof(T));                                                          \
        sprintf(deq->type_name, "%s%s", "Deque_", #T);                                              \
        deq->at = &Deque_##T##_at;                                                                  \
        deq->delet = &Deque_##T##_delete;                                                           \
        deq->size = &Deque_##T##_size;                                                              \
    }
#endif // __DEQUE_H_
