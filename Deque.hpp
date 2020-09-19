#ifndef __DEQUE_H_
#define __DEQUE_H_

#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#define Deque_DEFINE(T)                                                        \
    /*typedef T* Deque_##T##_Iterator;*/                                       \
    struct Deque_##T##_Iterator {                                      \
        T *tptr;                                                        \
        void (*inc)(Deque_##T##_Iterator*);                                     \
        T &(*deref)(Deque_##T##_Iterator*);                                     \
    };                                                                         \
    struct Deque_##T {                                                         \
        T data[1024];                                                          \
        size_t capacity;                                                       \
        size_t curr_size;                                                      \
        int f_idx;                                                             \
        int b_idx;                                                             \
        char type_name[14];                                                    \
        void (*push_back)(Deque_##T *, T);                                     \
        void (*push_front)(Deque_##T *, T);                                    \
        void (*pop_back)(Deque_##T *);                                         \
        void (*pop_front)(Deque_##T *);                                        \
        T &(*at)(Deque_##T *, int i);                                          \
        T &(*front)(Deque_##T *);                                              \
        T &(*back)(Deque_##T *);                                               \
        size_t (*size)(Deque_##T *);                                           \
        bool (*empty)(Deque_##T *);                                            \
        bool (*full)(Deque_##T *);                                             \
        void (*delet)(Deque_##T *);                                            \
        Deque_##T##_Iterator (*begin)(Deque_##T *);                            \
        Deque_##T##_Iterator (*end)(Deque_##T *);                              \
    };                                                                         \
                                                                               \
    void printidx(Deque_##T *d) {                                              \
        std::cout << "capacity: " << d->capacity << std::endl;                 \
        std::cout << "curr_size: " << d->curr_size << std::endl;               \
        std::cout << "f_idx    : " << d->f_idx << std::endl;                   \
        std::cout << "b_idx    : " << d->b_idx << std::endl;                   \
        std::cout << std::endl;                                                \
    }                                                                          \
                                                                               \
    void Deque_##T##_push_front(Deque_##T *d, T val) {                         \
        if(d->full(d)) return;                                                 \
        if(d->f_idx == -1) {                                                   \
            d->f_idx = d->b_idx = 0;                                           \
        } else if(d->f_idx == 0) {                                             \
            d->f_idx = d->capacity-1;                                          \
        } else {                                                               \
            --d->f_idx;                                                        \
        }                                                                      \
        d->data[d->f_idx] = val;                                               \
        d->curr_size++;                                                        \
        printidx(d);                                                           \
    }                                                                          \
                                                                               \
    void Deque_##T##_push_back(Deque_##T *d, T val) {                          \
        if(d->full(d)) return;                                                 \
        if(d->f_idx == -1) {                                                   \
            d->f_idx = d->b_idx = 0;                                           \
        } else if(d->b_idx == (int) d->capacity-1) {                           \
            d->b_idx = 0;                                                      \
        } else {                                                               \
            ++d->b_idx;                                                        \
        }                                                                      \
        d->data[d->b_idx] = val;                                               \
        d->curr_size++;                                                        \
        printidx(d);                                                           \
    }                                                                          \
                                                                               \
    void Deque_##T##_pop_front(Deque_##T *d) {                                 \
        if(d->empty(d)) return;                                                \
        if(d->f_idx == d->b_idx) {                                             \
            d->f_idx = d->b_idx = -1;                                          \
        } else {                                                               \
            if (d->f_idx == (int) d->capacity-1) {                             \
                d->f_idx = 0;                                                  \
            } else {                                                           \
                ++d->f_idx;                                                    \
            }                                                                  \
        }                                                                      \
        d->curr_size--;                                                        \
    }                                                                          \
                                                                               \
    void Deque_##T##_pop_back(Deque_##T *d) {                                  \
        if(d->empty(d)) return;                                                \
        if(d->f_idx == d->b_idx) {                                             \
            d->f_idx = d->b_idx = -1;                                          \
        } else if(d->b_idx == 0) {                                             \
            d->b_idx = d->capacity-1;                                          \
        } else {                                                               \
            --d->b_idx;                                                        \
        }                                                                      \
        d->curr_size--;                                                        \
    }                                                                          \
                                                                               \
    T &Deque_##T##_front(Deque_##T *d) {                                       \
        return d->data[d->f_idx];                                              \
    }                                                                          \
                                                                               \
    T &Deque_##T##_back(Deque_##T *d) {                                        \
        return d->data[d->b_idx];                                              \
    }                                                                          \
                                                                               \
    T &Deque_##T##_at(Deque_##T *d, int i) {                                   \
        return d->data[i];                                                     \
    }                                                                          \
                                                                               \
    void Deque_##T##_delete(Deque_##T *d) {                                    \
        free(d->data);                                                         \
        free(d);                                                               \
    }                                                                          \
                                                                               \
    size_t Deque_##T##_size(Deque_##T *d) {                                    \
        return d->curr_size;                                                   \
    }                                                                          \
                                                                               \
    bool Deque_##T##_empty(Deque_##T *d) {                                     \
        return d->f_idx == -1 ? true : false;                                  \
    }                                                                          \
                                                                               \
    bool Deque_##T##_full(Deque_##T *d) {                                      \
        return ((d->f_idx ==  0) && (d->b_idx == (int) d->capacity-1))         \
                || (d->f_idx == d->b_idx+1) ? true : false;                    \
    }                                                                          \
                                                                               \
    Deque_##T##_Iterator Deque_##T##_begin(Deque_##T *d) {                     \
        Deque_##T##_Iterator it;                                               \
        return it;                                                             \
    }                                                                          \
                                                                               \
    Deque_##T##_Iterator Deque_##T##_end(Deque_##T *d) {                       \
        Deque_##T##_Iterator it;                                               \
        return it;                                                             \
    }                                                                          \
                                                                               \
    bool Deque_##T##_Iterator_equal(Deque_##T##_Iterator it1,                  \
            Deque_##T##_Iterator it2) {                                        \
        return true;                                                           \
    }                                                                          \
                                                                               \
    bool Deque_##T##_Iterator_increment(Deque_##T##_Iterator it1,              \
            Deque_##T##_Iterator it2) {                                        \
        return true;                                                           \
    }                                                                          \
                                                                               \
    bool Deque_##T##_Iterator_dereference(Deque_##T##_Iterator it1,            \
            Deque_##T##_Iterator it2) {                                        \
        return true;                                                           \
    }                                                                          \
                                                                               \
    void *Iterator_inc (Deque_##T##_Iterator*);                                \
    T & Iterator_deref (Deque_##T##_Iterator*);                                \
    void Deque_##T##_ctor(Deque_##T *d, bool (*)(const T&, const T&)) {        \
        d->capacity = 10;                                                      \
        d->curr_size = 0;                                                      \
        d->f_idx = -1;                                                         \
        d->b_idx = 0;                                                          \
        /*std::string d_str ("Deque_");                                        \
        std::string type_str (#T);*/                                           \
        strcpy(d->type_name, "Deque_");                                        \
        strcat(d->type_name, #T);                                              \
        d->push_front = &Deque_##T##_push_front;                               \
        d->push_back = &Deque_##T##_push_back;                                 \
        d->pop_front = &Deque_##T##_pop_front;                                 \
        d->pop_back = &Deque_##T##_pop_back;                                   \
        d->front = &Deque_##T##_front;                                         \
        d->back = &Deque_##T##_back;                                           \
        d->at = &Deque_##T##_at;                                               \
        d->delet = &Deque_##T##_delete;                                        \
        d->size = &Deque_##T##_size;                                           \
        d->empty = &Deque_##T##_empty;                                         \
        d->full = &Deque_##T##_full;                                           \
    }
#endif // __DEQUE_H_
