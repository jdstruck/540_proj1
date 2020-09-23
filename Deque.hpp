/* No Macro */

#ifndef __DEQUE_H_
#define __DEQUE_H_

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

// Use INT macro for all standard ints.
// Prevents inadvertently replacing with
// "T" when converting to/from macro
// to run int tests
#define INT int

// Redefine for testing; commented out when macro
/*struct MyClass { INT id; char name[10]; };*/


#define CAP 1
//#define Deque_DEFINE(int)
struct Deque_int_Iterator;
bool Deque_int_Iterator_equal(Deque_int_Iterator,
                              Deque_int_Iterator);
const INT str_int_sizeof = sizeof( "int" ) + 6;
    struct Deque_int_Iterator {
        int *data_ptr;
        INT curr_idx;
        INT deque_capacity;
        void (*inc)(Deque_int_Iterator*);
        void (*dec)(Deque_int_Iterator*);
        int &(*deref)(Deque_int_Iterator*);
        inline bool operator!=( struct Deque_int_Iterator it) {
            return Deque_int_Iterator_equal(*this, it);
        }
        inline bool operator-( struct Deque_int_Iterator it) {
            return this->deref(this) - it.deref(&it);
        }
        inline int operator+( int i) {
            return this->deref(this) + i;
        }
    };
    struct Deque_int {
        int *data;
        size_t capacity;
        size_t curr_size;
        INT f_idx;
        INT b_idx;
        char type_name[str_int_sizeof];
        void (*push_back)(Deque_int *, int);
        void (*push_front)(Deque_int *, int);
        void (*pop_back)(Deque_int *);
        void (*pop_front)(Deque_int *);
        int &(*at)(Deque_int *, INT);
        int &(*front)(Deque_int *);
        int &(*back)(Deque_int *);
        size_t (*size)(Deque_int *);
        bool (*empty)(Deque_int *);
        bool (*comp)(const int&, const int&);
        bool (*full)(Deque_int *);
        void (*dtor)(Deque_int *);
        void (*clear)(Deque_int *);
        void (*sort)(Deque_int *, Deque_int_Iterator, Deque_int_Iterator);
        Deque_int_Iterator (*begin)(Deque_int *);
        Deque_int_Iterator (*end)(Deque_int *);
    };

    void Deque_int_Iterator_decrement(Deque_int_Iterator *);
    void Deque_int_Iterator_increment(Deque_int_Iterator *);
    int &Deque_int_Iterator_dereference(Deque_int_Iterator *);
    Deque_int_Iterator &Deque_int_Iterator_at(Deque_int, INT);



    void Deque_int_resize(Deque_int *deq) {
        /* Double size of and reallocate data array */
        INT old_cap = deq->capacity;
        deq->capacity *= 2;
        deq->data = (int *) realloc(deq->data, sizeof( INT ) * deq->capacity);
        if(deq->f_idx > deq->b_idx) {
            for(INT i = deq->f_idx; i < old_cap; ++i) {
                INT memmove_idx = deq->capacity - ((old_cap) - i);
                deq->data[memmove_idx] = deq->data[i];
            }
            deq->f_idx = deq->capacity - (old_cap - deq->f_idx);

        }
    }

    void printidx(Deque_int *deq) {
        std::cout << "capacity: " << deq->capacity << std::endl;
        std::cout << "curr_size: " << deq->curr_size << std::endl;
        std::cout << "f_idx    : " << deq->f_idx << std::endl;
        std::cout << "b_idx    : " << deq->b_idx << std::endl;
        std::cout << std::endl;
    }

    void Deque_int_push_back(Deque_int *deq, int val) {
        if(deq->full(deq)) {
            Deque_int_resize(deq);
        }
        if(deq->empty(deq)) {
            deq->f_idx = deq->b_idx = 0;
        } else if(deq->b_idx == ( INT ) deq->capacity-1) {
            deq->b_idx = 0;
        } else {
            ++deq->b_idx;
        }
        deq->data[deq->b_idx] = val;
        deq->curr_size++;
    }

    void Deque_int_push_front(Deque_int *deq, int val) {
        if(deq->full(deq)) {
            Deque_int_resize(deq);
        }
        if(deq->empty(deq)) {
            deq->f_idx = deq->b_idx = 0;
        } else if(deq->f_idx == 0) {
            deq->f_idx = deq->capacity-1;
        } else {
            --deq->f_idx;
        }
        deq->data[deq->f_idx] = val;
        deq->curr_size++;
    }


    void Deque_int_pop_back(Deque_int *deq) {
        if(deq->empty(deq)) {
            deq->f_idx = deq->b_idx = -1;
            return;
        }
        if(deq->b_idx == 0) {
            deq->b_idx = ( INT ) deq->capacity-1;
        } else {
            --deq->b_idx;
        }
        --deq->curr_size;
    }

    void Deque_int_pop_front(Deque_int *deq) {
        if(deq->empty(deq)) {
            deq->f_idx = deq->b_idx = -1;
            return;
        }
        if (deq->f_idx == ( INT ) deq->capacity-1) {
            deq->f_idx = 0;
        } else {
            ++deq->f_idx;
        }
        --deq->curr_size;
    }

    int &Deque_int_front(Deque_int *deq) {
        return deq->data[deq->f_idx];
    }

    int &Deque_int_back(Deque_int *deq) {
        return deq->data[deq->b_idx];
    }

    int &Deque_int_at(Deque_int *deq, INT i) {
        INT at_idx = (i + deq->f_idx) % ( INT ) deq->capacity;
        return deq->data[at_idx];
    }
    Deque_int_Iterator Deque_int_Iterator_at(Deque_int *deq, INT i) {
        Deque_int_Iterator it;
        INT at_idx = (i + deq->f_idx) % ( INT ) deq->capacity;
        it.curr_idx = at_idx;\
        it.data_ptr = &deq->data[it.curr_idx];
        it.deque_capacity = deq->capacity;
        it.inc = Deque_int_Iterator_increment;
        it.dec = Deque_int_Iterator_decrement;
        it.deref = Deque_int_Iterator_dereference;
        return it;
    }

    void Deque_int_destructor(Deque_int *deq) {
        free(deq->data);
        /* TODO: Fix destructor! */
        /*free(d); */
    }

    void Deque_int_clear(Deque_int *deq) {
        deq->curr_size = 0;
        deq->f_idx = -1;
        deq->b_idx = 0;
    }

    size_t Deque_int_size(Deque_int *deq) {
        return deq->curr_size;
    }

    bool Deque_int_empty(Deque_int *deq) {
        return deq->curr_size == 0;
    }

    bool Deque_int_equal(Deque_int &deq1, Deque_int &deq2) {
        if(deq1.curr_size != deq2.curr_size) {
            return false;
        } else {
            Deque_int_Iterator it1 = deq1.begin(&deq1);
            Deque_int_Iterator it2 = deq2.begin(&deq2);
            do {
                /* Check that dereferenced items both not less than each other
                 * This works for int_less_by_id, hopefully others */
                if (!(!deq1.comp(it1.deref(&it1), it1.deref(&it2)) &&
                      !deq1.comp(it1.deref(&it2), it1.deref(&it1))))
                    return false;
                it1.inc(&it1);
                it2.inc(&it2);
            } while (!Deque_int_Iterator_equal(it1, deq1.end(&deq1)));
            return true;
        }
    }

    bool Deque_int_full(Deque_int *deq) {
        return deq->curr_size == deq->capacity;
    }

    void Deque_int_print(Deque_int *deq) {

        for (Deque_int_Iterator it = deq->begin(deq);
             !Deque_int_Iterator_equal(it, deq->end(deq)); it.inc(&it)) {
            std::cout  << it.deref(&it) << std::endl;
        }
        std::cout << std::endl;
    }
    void Deque_int_sort(Deque_int *deq,
                        Deque_int_Iterator begin,
                        Deque_int_Iterator end) {
//        Deque_int_print(deq);
        int j, k;
        Deque_int_Iterator it = begin, j_it, j_itp1;
        it.inc(&it);
        for (; !Deque_int_Iterator_equal(it, end); it.inc(&it)) {
            k = it.deref(&it);
            j_it = Deque_int_Iterator_at(deq, it.curr_idx-1);
            j = j_it.deref(&j_it);
//            while(j_it.curr_idx >= begin.curr_idx && deq->comp(k, j)) {
            int jitci = j_it.curr_idx;
            int beginci = begin.curr_idx;
            bool jgteb = jitci >= beginci;
            bool jnebegin = !Deque_int_Iterator_equal(j_it, begin);
            bool compkj = deq->comp(k,j);

            while(jgteb && compkj) {
                int jitp1 = deq->data[j_it.curr_idx + 1];
                int jitp0 = deq->data[j_it.curr_idx];
                deq->data[j_it.curr_idx + 1] = deq->data[j_it.curr_idx];
                j_it.dec(&j_it);
                j = it.deref(&j_it);
                if(jitci == 0 && beginci == 0) break;
                jitci = j_it.curr_idx;
                beginci = begin.curr_idx;
                jgteb = jitci >= beginci;
                jnebegin = !Deque_int_Iterator_equal(j_it, begin);
                compkj = deq->comp(k,j);
            }
            j_itp1 = Deque_int_Iterator_at(deq, j_it.curr_idx+1);
            it.deref(&j_itp1) = k;
//            Deque_int_print(deq);
        }
//        Deque_int_print(deq);
    }

//    void Deque_int_sort(Deque_int *deq,
//                        Deque_int_Iterator begin,
//                        Deque_int_Iterator end) {
//        Deque_int_print(deq);
//        std::sort(begin, end, deq->comp);
//        Deque_int_print(deq);
//    }


void Deque_int_Iterator_increment(Deque_int_Iterator *it) {
    if(it->curr_idx == it->deque_capacity-1) {
            it->data_ptr = it->data_ptr - it->deque_capacity + 1;
            it->curr_idx = 0;
        } else {
            ++it->data_ptr;
            ++it->curr_idx;
        }
    }

    void Deque_int_Iterator_decrement(Deque_int_Iterator *it) {
        if(it->curr_idx == 0) {
            it->data_ptr = it->data_ptr + it->deque_capacity - 1;
            it->curr_idx = it->deque_capacity-1;
        } else {
            --it->data_ptr;
            --it->curr_idx;
        }
    }

    int &Deque_int_Iterator_dereference(Deque_int_Iterator *it) {
        return *it->data_ptr;
    }

    Deque_int_Iterator Deque_int_begin(Deque_int *deq) {
        Deque_int_Iterator it;
        it.curr_idx = deq->f_idx;
        it.data_ptr = &deq->data[it.curr_idx];
        it.deque_capacity = deq->capacity;
        it.inc = Deque_int_Iterator_increment;
        it.dec = Deque_int_Iterator_decrement;
        it.deref = Deque_int_Iterator_dereference;
        return it;
    }

    Deque_int_Iterator Deque_int_end(Deque_int *deq) {
        Deque_int_Iterator it;
        /* Return one past back index */
        it.curr_idx = deq->b_idx+1;
        it.data_ptr = &deq->data[it.curr_idx];
        it.deque_capacity = deq->capacity;
        it.inc = Deque_int_Iterator_increment;
        it.dec = Deque_int_Iterator_decrement;
        it.deref = Deque_int_Iterator_dereference;
        return it;
    }

    bool Deque_int_Iterator_equal(Deque_int_Iterator it1,
            Deque_int_Iterator it2) {
        return it1.data_ptr == it2.data_ptr;
    }

    void Deque_int_ctor(Deque_int *deq, bool (*comp)(const int&, const int&)) {
        deq->capacity = 4;
        deq->data = ( int *)malloc(sizeof(int) * deq->capacity);
        deq->curr_size = 0;
        deq->f_idx = -1;
        deq->b_idx = 0;
        sprintf(deq->type_name, "%s", "Deque_" "int");
        deq->push_front = &Deque_int_push_front;
        deq->push_back = &Deque_int_push_back;
        deq->pop_front = &Deque_int_pop_front;
        deq->pop_back = &Deque_int_pop_back;
        deq->front = &Deque_int_front;
        deq->back = &Deque_int_back;
        deq->at = &Deque_int_at;
        deq->dtor = &Deque_int_destructor;
        deq->clear = &Deque_int_clear;
        deq->size = &Deque_int_size;
        deq->empty = &Deque_int_empty;
        deq->full = &Deque_int_full;
        deq->begin = &Deque_int_begin;
        deq->end = &Deque_int_end;
        deq->comp = comp;
        deq->sort = &Deque_int_sort;
        /* End Macro */\
    }
#endif // __DEQUE_H_
