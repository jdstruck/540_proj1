#ifndef __DEQUE_H_
#define __DEQUE_H_

#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#define Deque_DEFINE(T)                                                                             \
    struct Deque_##T {                                                                              \
        T data[10];                                                                                    \
        size_t deq_size;                                                                            \
        std::string type_name;                                                                            \
        void (*push_back)(Deque_##T *, T);                                                          \
        T &(*at)(Deque_##T *, int i);                                                               \
        size_t (*size)(Deque_##T *);                                                                \
        bool (*empty)(Deque_##T *);                                                                 \
        void (*delet)(Deque_##T *);                                                                 \
    };                                                                                              \
                                                                                                    \
    void Deque_##T##_push_back(Deque_##T *deq, T val) {                                             \
        deq->data[0] = val;                                                                         \
        deq->deq_size++;                                                                            \
    }                                                                                               \
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
    bool Deque_##T##_empty(Deque_##T *deq) {                                                        \
        return deq->deq_size == 0 ? true : false;                                                   \
    }                                                                                               \
                                                                                                    \
    void Deque_##T##_ctor(Deque_##T *deq, bool (*)(const T&, const T&)) {                           \
        deq->deq_size = 0;                                                                          \
        std::string deq_str ("Deque_");                                                                   \
        std::string type_str (#T);                                                                   \
        deq->type_name = deq_str + type_str;\
        std::cout<<deq->type_name<<std::endl;                                                       \
        deq->push_back = &Deque_##T##_push_back;                                                    \
        deq->at = &Deque_##T##_at;                                                                  \
        deq->delet = &Deque_##T##_delete;                                                           \
        deq->size = &Deque_##T##_size;                                                              \
        deq->empty = &Deque_##T##_empty;                                                            \
    }
#endif // __DEQUE_H_
