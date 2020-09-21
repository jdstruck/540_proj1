/* Macro */

#ifndef __DEQUE_H_
#define __DEQUE_H_

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>

// Use INT macro for all Ts so as to not
// break when converting from macro version
// to standard struct when testing
#define INT int

// Redefine for testing; commented out when macro
// struct MyClass { INT id; char name[10]; };


#define CAP 1024
#define Deque_DEFINE(T)                                                         \
    /*typedef T* Deque_##T##_Iterator;*/                                        \
        const INT T##str_sizeof = sizeof(#T) + 6;                               \
    struct Deque_##T##_Iterator {                                               \
        T *data_ptr;                                                            \
        int curr_idx;                                                           \
        int deque_capacity;                                                     \
        void (*inc)(Deque_##T##_Iterator*);                                     \
        void (*dec)(Deque_##T##_Iterator*);                                     \
        T &(*deref)(Deque_##T##_Iterator*);                                     \
    };                                                                          \
    struct Deque_##T {                                                          \
        T data[CAP];                                                            \
        size_t capacity;                                                        \
        size_t curr_size;                                                       \
        int f_idx;                                                              \
        int b_idx;                                                              \
        char type_name[T##str_sizeof];                                          \
        void (*push_back)(Deque_##T *, T);                                      \
        void (*push_front)(Deque_##T *, T);                                     \
        void (*pop_back)(Deque_##T *);                                          \
        void (*pop_front)(Deque_##T *);                                         \
        T &(*at)(Deque_##T *, int i);                                           \
        T &(*front)(Deque_##T *);                                               \
        T &(*back)(Deque_##T *);                                                \
        size_t (*size)(Deque_##T *);                                            \
        bool (*empty)(Deque_##T *);                                             \
        bool (*comp)(const T&, const T&);                                       \
        bool (*full)(Deque_##T *);                                              \
        void (*dtor)(Deque_##T *);                                              \
        void (*clear)(Deque_##T *);                                             \
        Deque_##T##_Iterator (*begin)(Deque_##T *);                             \
        Deque_##T##_Iterator (*end)(Deque_##T *);                               \
    };                                                                          \
                                                                                \
    bool Deque_##T##_Iterator_equal(Deque_##T##_Iterator,                       \
                                    Deque_##T##_Iterator);                      \
                                                                                \
    void printidx(Deque_##T *d) {                                               \
        std::cout << "capacity: " << d->capacity << std::endl;                  \
        std::cout << "curr_size: " << d->curr_size << std::endl;                \
        std::cout << "f_idx    : " << d->f_idx << std::endl;                    \
        std::cout << "b_idx    : " << d->b_idx << std::endl;                    \
        std::cout << std::endl;                                                 \
    }                                                                           \
                                                                                \
    void Deque_##T##_push_back(Deque_##T *d, T val) {                           \
        if(d->full(d)) return;                                                  \
        if(d->f_idx == -1) {                                                    \
            d->f_idx = d->b_idx = 0;                                            \
        } else if(d->b_idx == (int) d->capacity-1) {                            \
            d->b_idx = 0;                                                       \
        } else {                                                                \
            ++d->b_idx;                                                         \
        }                                                                       \
        d->data[d->b_idx] = val;                                                \
        d->curr_size++;                                                         \
    }                                                                           \
                                                                                \
    void Deque_##T##_push_front(Deque_##T *d, T val) {                          \
        if(d->full(d)) return;                                                  \
        if(d->f_idx == -1) {                                                    \
            d->f_idx = d->b_idx = 0;                                            \
        } else if(d->f_idx == 0) {                                              \
            d->f_idx = d->capacity-1;                                           \
        } else {                                                                \
            --d->f_idx;                                                         \
        }                                                                       \
        d->data[d->f_idx] = val;                                                \
        d->curr_size++;                                                         \
    }                                                                           \
                                                                                \
    void Deque_##T##_pop_back(Deque_##T *d) {                                   \
        if(d->empty(d)) return;                                                 \
        if(d->f_idx == d->b_idx) {                                              \
            d->f_idx = d->b_idx = -1;                                           \
        } else if(d->b_idx == 0) {                                              \
            d->b_idx = d->capacity-1;                                           \
        } else {                                                                \
            --d->b_idx;                                                         \
        }                                                                       \
        d->curr_size--;                                                         \
    }                                                                           \
                                                                                \
    void Deque_##T##_pop_front(Deque_##T *d) {                                  \
        if(d->empty(d)) return;                                                 \
        if(d->f_idx == d->b_idx) {                                              \
            d->f_idx = d->b_idx = -1;                                           \
        } else {                                                                \
            if (d->f_idx == (int) d->capacity-1) {                              \
                d->f_idx = 0;                                                   \
            } else {                                                            \
                ++d->f_idx;                                                     \
            }                                                                   \
        }                                                                       \
        d->curr_size--;                                                         \
    }                                                                           \
                                                                                \
    T &Deque_##T##_front(Deque_##T *d) {                                        \
        return d->data[d->f_idx];                                               \
    }                                                                           \
                                                                                \
    T &Deque_##T##_back(Deque_##T *d) {                                         \
        return d->data[d->b_idx];                                               \
    }                                                                           \
                                                                                \
    T &Deque_##T##_at(Deque_##T *d, int i) {                                    \
        return d->data[i+d->f_idx];                                             \
    }                                                                           \
                                                                                \
    void Deque_##T##_destructor(Deque_##T *d) {                                 \
        /* TODO: Fix destructor!*/                                              \
        /*free(d->data);*/                                                      \
        /*free(d); */                                                           \
    }                                                                           \
                                                                                \
    void Deque_##T##_clear(Deque_##T *d) {                                      \
        d->curr_size = 0;                                                       \
        d->f_idx = -1;                                                          \
        d->b_idx = 0;                                                           \
    }                                                                           \
                                                                                \
    size_t Deque_##T##_size(Deque_##T *d) {                                     \
        return d->curr_size;                                                    \
    }                                                                           \
                                                                                \
    bool Deque_##T##_empty(Deque_##T *d) {                                      \
        return d->f_idx == -1;                                                  \
    }                                                                           \
                                                                                \
    bool Deque_##T##_equal(Deque_##T &d1, Deque_##T &d2) {                      \
        if(d1.curr_size != d2.curr_size) {                                      \
            return false;                                                       \
        } else {                                                                \
            Deque_##T##_Iterator it1 = d1.begin(&d1);                           \
            Deque_##T##_Iterator it2 = d2.begin(&d2);                           \
            do {                                                                \
                /*if(!(it1.deref(&it1) == it2.deref(&it2))) {*/                 \
                    if((memcmp((const void *) &it1.deref(&it1),                 \
                            (const void *) &it2.deref(&it2), sizeof(T)))) {     \
                    return false;                                               \
                }                                                               \
                it1.inc(&it1);                                                  \
                it2.inc(&it2);                                                  \
            } while (!Deque_##T##_Iterator_equal(it1, d1.end(&d1)));            \
            return true;                                                        \
        }                                                                       \
    }                                                                           \
                                                                                \
    bool Deque_##T##_full(Deque_##T *d) {                                       \
        return ((d->f_idx ==  0) && (d->b_idx == (int) d->capacity-1))          \
                || (d->f_idx == d->b_idx+1);                                    \
    }                                                                           \
                                                                                \
    void Deque_##T##_Iterator_increment(Deque_##T##_Iterator *it) {             \
        if(it->curr_idx == it->deque_capacity-1) {                              \
            it->data_ptr = it->data_ptr - it->deque_capacity;                   \
            it->curr_idx = 0;                                                   \
        } else {                                                                \
            ++it->data_ptr;                                                     \
            ++it->curr_idx;                                                     \
        }                                                                       \
    }                                                                           \
                                                                                \
    void Deque_##T##_Iterator_decrement(Deque_##T##_Iterator *it) {             \
        if(it->curr_idx == 0) {                                                 \
            it->data_ptr = it->data_ptr + it->deque_capacity-1;                 \
            it->curr_idx = it->deque_capacity-1;                                \
        } else {                                                                \
            --it->data_ptr;                                                     \
            --it->curr_idx;                                                     \
        }                                                                       \
    }                                                                           \
                                                                                \
    T &Deque_##T##_Iterator_dereference(Deque_##T##_Iterator *it) {             \
        return *it->data_ptr;                                                   \
    }                                                                           \
                                                                                \
    Deque_##T##_Iterator Deque_##T##_begin(Deque_##T *d) {                      \
        Deque_##T##_Iterator it;                                                \
        it.curr_idx = d->f_idx;                                                 \
        it.data_ptr = &d->data[it.curr_idx];                                    \
        it.deque_capacity = d->capacity;                                        \
        it.inc = Deque_##T##_Iterator_increment;                                \
        it.dec = Deque_##T##_Iterator_decrement;                                \
        it.deref = Deque_##T##_Iterator_dereference;                            \
        return it;                                                              \
    }                                                                           \
                                                                                \
    Deque_##T##_Iterator Deque_##T##_end(Deque_##T *d) {                        \
        Deque_##T##_Iterator it;                                                \
        /* Return one past back index */                                        \
        it.curr_idx = d->b_idx+1;                                               \
        it.data_ptr = &d->data[it.curr_idx];                                    \
        it.deque_capacity = d->capacity;                                        \
        it.inc = Deque_##T##_Iterator_increment;                                \
        it.dec = Deque_##T##_Iterator_decrement;                                \
        it.deref = Deque_##T##_Iterator_dereference;                            \
        return it;                                                              \
    }                                                                           \
                                                                                \
    bool Deque_##T##_Iterator_equal(Deque_##T##_Iterator it1,                   \
            Deque_##T##_Iterator it2) {                                         \
        return it1.data_ptr == it2.data_ptr;                                    \
    }                                                                           \
                                                                                \
    void Deque_##T##_ctor(Deque_##T *d, bool (*comp)(const T&, const T&)) {     \
        d->capacity = CAP;                                                      \
        d->curr_size = 0;                                                       \
        d->f_idx = -1;                                                          \
        d->b_idx = 0;                                                           \
        sprintf(d->type_name, "%s", "Deque_" #T);                               \
        d->push_front = &Deque_##T##_push_front;                                \
        d->push_back = &Deque_##T##_push_back;                                  \
        d->pop_front = &Deque_##T##_pop_front;                                  \
        d->pop_back = &Deque_##T##_pop_back;                                    \
        d->front = &Deque_##T##_front;                                          \
        d->back = &Deque_##T##_back;                                            \
        d->at = &Deque_##T##_at;                                                \
        d->dtor = &Deque_##T##_destructor;                                      \
        d->clear = &Deque_##T##_clear;                                          \
        d->size = &Deque_##T##_size;                                            \
        d->empty = &Deque_##T##_empty;                                          \
        d->full = &Deque_##T##_full;                                            \
        d->begin = &Deque_##T##_begin;                                          \
        d->end = &Deque_##T##_end;                                              \
        d->comp = comp;                                                         \
        /* End Macro */\
    }
#endif // __DEQUE_H_
