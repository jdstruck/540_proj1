/* Macro */

#ifndef __DEQUE_H_
#define __DEQUE_H_

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>

// Use INT macro for all standard ints.
// Prevents inadvertently replacing with
// "T" when converting to/from macro
// to run int tests
#define INT int

// Redefine for testing; commented out when macro
// struct MyClass { INT id; char name[10]; };


#define CAP 1
#define Deque_DEFINE(TYPE)                                                                          \
    const INT str_##TYPE##_sizeof = sizeof( #TYPE ) + 6;                                            \
    struct Deque_##TYPE##_Iterator {                                                                \
        TYPE *data_ptr;                                                                             \
        int curr_idx;                                                                               \
        int deque_capacity;                                                                         \
        void (*inc)(Deque_##TYPE##_Iterator*);                                                      \
        void (*dec)(Deque_##TYPE##_Iterator*);                                                      \
        TYPE &(*deref)(Deque_##TYPE##_Iterator*);                                                   \
    };                                                                                              \
    struct Deque_##TYPE {                                                                           \
        TYPE *data;                                                                                 \
        size_t capacity;                                                                            \
        size_t curr_size;                                                                           \
        int f_idx;                                                                                  \
        int b_idx;                                                                                  \
        char type_name[str_##TYPE##_sizeof];                                                        \
        void (*push_back)(Deque_##TYPE *, TYPE);                                                    \
        void (*push_front)(Deque_##TYPE *, TYPE);                                                   \
        void (*pop_back)(Deque_##TYPE *);                                                           \
        void (*pop_front)(Deque_##TYPE *);                                                          \
        TYPE &(*at)(Deque_##TYPE *, int i);                                                         \
        TYPE &(*front)(Deque_##TYPE *);                                                             \
        TYPE &(*back)(Deque_##TYPE *);                                                              \
        size_t (*size)(Deque_##TYPE *);                                                             \
        bool (*empty)(Deque_##TYPE *);                                                              \
        bool (*comp)(const TYPE&, const TYPE&);                                                     \
        bool (*full)(Deque_##TYPE *);                                                               \
        void (*dtor)(Deque_##TYPE *);                                                               \
        void (*clear)(Deque_##TYPE *);                                                              \
        Deque_##TYPE##_Iterator (*begin)(Deque_##TYPE *);                                           \
        Deque_##TYPE##_Iterator (*end)(Deque_##TYPE *);                                             \
    };                                                                                              \
                                                                                                    \
    bool Deque_##TYPE##_Iterator_equal(Deque_##TYPE##_Iterator,                                     \
                                    Deque_##TYPE##_Iterator);                                       \
                                                                                                    \
    void Deque_##TYPE##_resize(Deque_##TYPE *deq) {                                                 \
        /* Double size of and reallocate data array */                                              \
        INT old_cap = deq->capacity;                                                                \
        deq->capacity *= 2;                                                                         \
        deq->data = (TYPE *) realloc(deq->data, sizeof(TYPE) * deq->capacity);                      \
        if(deq->f_idx > deq->b_idx) {                                                               \
            for(INT i = deq->f_idx; i < old_cap; ++i) {                                             \
                INT memmove_idx = deq->capacity - ((old_cap) - i);                                  \
                deq->data[memmove_idx] = deq->data[i];                                              \
            }                                                                                       \
            deq->f_idx = deq->capacity - (old_cap - deq->f_idx);                                    \
                                                                                                    \
        }                                                                                           \
    }                                                                                               \
                                                                                                    \
    void printidx(Deque_##TYPE *deq) {                                                              \
        std::cout << "capacity: " << deq->capacity << std::endl;                                    \
        std::cout << "curr_size: " << deq->curr_size << std::endl;                                  \
        std::cout << "f_idx    : " << deq->f_idx << std::endl;                                      \
        std::cout << "b_idx    : " << deq->b_idx << std::endl;                                      \
        std::cout << std::endl;                                                                     \
    }                                                                                               \
                                                                                                    \
    void Deque_##TYPE##_push_back(Deque_##TYPE *deq, TYPE val) {                                    \
        if(deq->full(deq)) {                                                                        \
            Deque_##TYPE##_resize(deq);                                                             \
        }                                                                                           \
        if(deq->empty(deq)) {                                                                       \
            deq->f_idx = deq->b_idx = 0;                                                            \
        } else if(deq->b_idx == (int) deq->capacity-1) {                                            \
            deq->b_idx = 0;                                                                         \
        } else {                                                                                    \
            ++deq->b_idx;                                                                           \
        }                                                                                           \
        deq->data[deq->b_idx] = val;                                                                \
        deq->curr_size++;                                                                           \
    }                                                                                               \
                                                                                                    \
    void Deque_##TYPE##_push_front(Deque_##TYPE *deq, TYPE val) {                                   \
        if(deq->full(deq)) {                                                                        \
            Deque_##TYPE##_resize(deq);                                                             \
        }                                                                                           \
        if(deq->empty(deq)) {                                                                       \
            deq->f_idx = deq->b_idx = 0;                                                            \
        } else if(deq->f_idx == 0) {                                                                \
            deq->f_idx = deq->capacity-1;                                                           \
        } else {                                                                                    \
            --deq->f_idx;                                                                           \
        }                                                                                           \
        deq->data[deq->f_idx] = val;                                                                \
        deq->curr_size++;                                                                           \
    }                                                                                               \
                                                                                                    \
                                                                                                    \
    void Deque_##TYPE##_pop_back(Deque_##TYPE *deq) {                                               \
        if(deq->empty(deq)) {                                                                       \
            deq->f_idx = deq->b_idx = -1;                                                           \
            return;                                                                                 \
        }                                                                                           \
        if(deq->b_idx == 0) {                                                                       \
            deq->b_idx = (int) deq->capacity-1;                                                     \
        } else {                                                                                    \
            --deq->b_idx;                                                                           \
        }                                                                                           \
        --deq->curr_size;                                                                           \
    }                                                                                               \
                                                                                                    \
    void Deque_##TYPE##_pop_front(Deque_##TYPE *deq) {                                              \
        if(deq->empty(deq)) {                                                                       \
            deq->f_idx = deq->b_idx = -1;                                                           \
            return;                                                                                 \
        }                                                                                           \
        if (deq->f_idx == (int) deq->capacity-1) {                                                  \
            deq->f_idx = 0;                                                                         \
        } else {                                                                                    \
            ++deq->f_idx;                                                                           \
        }                                                                                           \
        --deq->curr_size;                                                                           \
    }                                                                                               \
                                                                                                    \
    TYPE &Deque_##TYPE##_front(Deque_##TYPE *deq) {                                                 \
        return deq->data[deq->f_idx];                                                               \
    }                                                                                               \
                                                                                                    \
    TYPE &Deque_##TYPE##_back(Deque_##TYPE *deq) {                                                  \
        return deq->data[deq->b_idx];                                                               \
    }                                                                                               \
                                                                                                    \
    TYPE &Deque_##TYPE##_at(Deque_##TYPE *deq, int i) {                                             \
        int at_idx = (i + deq->f_idx) % (int) deq->capacity;                                        \
        return deq->data[at_idx];                                                                   \
    }                                                                                               \
                                                                                                    \
    void Deque_##TYPE##_destructor(Deque_##TYPE *deq) {                                             \
        free(deq->data);                                                                            \
       /* free(d); */                                                                               \
    }                                                                                               \
                                                                                                    \
    void Deque_##TYPE##_clear(Deque_##TYPE *deq) {                                                  \
        deq->curr_size = 0;                                                                         \
        deq->f_idx = -1;                                                                            \
        deq->b_idx = 0;                                                                             \
    }                                                                                               \
                                                                                                    \
    size_t Deque_##TYPE##_size(Deque_##TYPE *deq) {                                                 \
        return deq->curr_size;                                                                      \
    }                                                                                               \
                                                                                                    \
    bool Deque_##TYPE##_empty(Deque_##TYPE *deq) {                                                  \
        return deq->curr_size == 0;                                                                 \
    }                                                                                               \
                                                                                                    \
    bool Deque_##TYPE##_equal(Deque_##TYPE &deq1, Deque_##TYPE &deq2) {                             \
        if(deq1.curr_size != deq2.curr_size) {                                                      \
            return false;                                                                           \
        } else {                                                                                    \
            Deque_##TYPE##_Iterator it1 = deq1.begin(&deq1);                                        \
            Deque_##TYPE##_Iterator it2 = deq2.begin(&deq2);                                        \
            do {                                                                                    \
                /* Check that dereferenced items both not less than each other                      \
                 * This works for TYPE_less_by_id, hopefully others */                              \
                if (!(!deq1.comp(it1.deref(&it1), it1.deref(&it2)) &&                               \
                      !deq1.comp(it1.deref(&it2), it1.deref(&it1))))                                \
                    return false;                                                                   \
                it1.inc(&it1);                                                                      \
                it2.inc(&it2);                                                                      \
            } while (!Deque_##TYPE##_Iterator_equal(it1, deq1.end(&deq1)));                         \
            return true;                                                                            \
        }                                                                                           \
    }                                                                                               \
                                                                                                    \
    bool Deque_##TYPE##_full(Deque_##TYPE *deq) {                                                   \
        return deq->curr_size == deq->capacity;                                                     \
    }                                                                                               \
                                                                                                    \
    void Deque_##TYPE##_Iterator_increment(Deque_##TYPE##_Iterator *it) {                           \
        if(it->curr_idx == it->deque_capacity-1) {                                                  \
            it->data_ptr = it->data_ptr - it->deque_capacity + 1;                                   \
            it->curr_idx = 0;                                                                       \
        } else {                                                                                    \
            ++it->data_ptr;                                                                         \
            ++it->curr_idx;                                                                         \
        }                                                                                           \
    }                                                                                               \
                                                                                                    \
    void Deque_##TYPE##_Iterator_decrement(Deque_##TYPE##_Iterator *it) {                           \
        if(it->curr_idx == 0) {                                                                     \
            it->data_ptr = it->data_ptr + it->deque_capacity - 1;                                   \
            it->curr_idx = it->deque_capacity-1;                                                    \
        } else {                                                                                    \
            --it->data_ptr;                                                                         \
            --it->curr_idx;                                                                         \
        }                                                                                           \
    }                                                                                               \
                                                                                                    \
    TYPE &Deque_##TYPE##_Iterator_dereference(Deque_##TYPE##_Iterator *it) {                        \
        return *it->data_ptr;                                                                       \
    }                                                                                               \
                                                                                                    \
    Deque_##TYPE##_Iterator Deque_##TYPE##_begin(Deque_##TYPE *deq) {                               \
        Deque_##TYPE##_Iterator it;                                                                 \
        it.curr_idx = deq->f_idx;                                                                   \
        it.data_ptr = &deq->data[it.curr_idx];                                                      \
        it.deque_capacity = deq->capacity;                                                          \
        it.inc = Deque_##TYPE##_Iterator_increment;                                                 \
        it.dec = Deque_##TYPE##_Iterator_decrement;                                                 \
        it.deref = Deque_##TYPE##_Iterator_dereference;                                             \
        return it;                                                                                  \
    }                                                                                               \
                                                                                                    \
    Deque_##TYPE##_Iterator Deque_##TYPE##_end(Deque_##TYPE *deq) {                                 \
        Deque_##TYPE##_Iterator it;                                                                 \
        /* Return one past back index */                                                            \
        it.curr_idx = deq->b_idx+1;                                                                 \
        it.data_ptr = &deq->data[it.curr_idx];                                                      \
        it.deque_capacity = deq->capacity;                                                          \
        it.inc = Deque_##TYPE##_Iterator_increment;                                                 \
        it.dec = Deque_##TYPE##_Iterator_decrement;                                                 \
        it.deref = Deque_##TYPE##_Iterator_dereference;                                             \
        return it;                                                                                  \
    }                                                                                               \
                                                                                                    \
    bool Deque_##TYPE##_Iterator_equal(Deque_##TYPE##_Iterator it1,                                 \
            Deque_##TYPE##_Iterator it2) {                                                          \
        return it1.data_ptr == it2.data_ptr;                                                        \
    }                                                                                               \
                                                                                                    \
    void Deque_##TYPE##_ctor(Deque_##TYPE *deq, bool (*comp)(const TYPE&, const TYPE&)) {           \
        deq->capacity = 4;                                                                          \
        deq->data = ( TYPE *)malloc(sizeof(TYPE) * deq->capacity);                                  \
        deq->curr_size = 0;                                                                         \
        deq->f_idx = -1;                                                                            \
        deq->b_idx = 0;                                                                             \
        sprintf(deq->type_name, "%s", "Deque_" #TYPE);                                              \
        deq->push_front = &Deque_##TYPE##_push_front;                                               \
        deq->push_back = &Deque_##TYPE##_push_back;                                                 \
        deq->pop_front = &Deque_##TYPE##_pop_front;                                                 \
        deq->pop_back = &Deque_##TYPE##_pop_back;                                                   \
        deq->front = &Deque_##TYPE##_front;                                                         \
        deq->back = &Deque_##TYPE##_back;                                                           \
        deq->at = &Deque_##TYPE##_at;                                                               \
        deq->dtor = &Deque_##TYPE##_destructor;                                                     \
        deq->clear = &Deque_##TYPE##_clear;                                                         \
        deq->size = &Deque_##TYPE##_size;                                                           \
        deq->empty = &Deque_##TYPE##_empty;                                                         \
        deq->full = &Deque_##TYPE##_full;                                                           \
        deq->begin = &Deque_##TYPE##_begin;                                                         \
        deq->end = &Deque_##TYPE##_end;                                                             \
        deq->comp = comp;                                                                           \
        /* End Macro */\
    }
#endif // __DEQUE_H_
