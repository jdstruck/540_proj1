/* No Macro */

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
struct MyClass { INT id; char name[10]; };


#define CAP 1
//#define Deque_DEFINE(MyClass)
    const INT MyClassstr_sizeof = sizeof( "MyClass" ) + 6;
    struct Deque_MyClass_Iterator {
        MyClass *data_ptr;
        int curr_idx;
        int deque_capacity;
        void (*inc)(Deque_MyClass_Iterator*);
        void (*dec)(Deque_MyClass_Iterator*);
        MyClass &(*deref)(Deque_MyClass_Iterator*);
    };
    struct Deque_MyClass {
        MyClass *data;
        size_t capacity;
        size_t curr_size;
        int f_idx;
        int b_idx;
        char type_name[MyClassstr_sizeof];
        void (*push_back)(Deque_MyClass *, MyClass);
        void (*push_front)(Deque_MyClass *, MyClass);
        void (*pop_back)(Deque_MyClass *);
        void (*pop_front)(Deque_MyClass *);
        MyClass &(*at)(Deque_MyClass *, int i);
        MyClass &(*front)(Deque_MyClass *);
        MyClass &(*back)(Deque_MyClass *);
        size_t (*size)(Deque_MyClass *);
        bool (*empty)(Deque_MyClass *);
        bool (*comp)(const MyClass&, const MyClass&);
        bool (*full)(Deque_MyClass *);
        void (*dtor)(Deque_MyClass *);
        void (*clear)(Deque_MyClass *);
        Deque_MyClass_Iterator (*begin)(Deque_MyClass *);
        Deque_MyClass_Iterator (*end)(Deque_MyClass *);
    };

    bool Deque_MyClass_Iterator_equal(Deque_MyClass_Iterator,
                                    Deque_MyClass_Iterator);

    void Deque_MyClass_resize(Deque_MyClass *deq) {
        /* Double size of and reallocate data array */
        INT old_cap = deq->capacity;
        deq->capacity *= 2;
        deq->data = (MyClass *) realloc(deq->data, sizeof(MyClass) * deq->capacity);
        if(deq->f_idx > deq->b_idx) {
            for(INT i = deq->f_idx; i < old_cap; ++i) {
                INT memmove_idx = deq->capacity - ((old_cap) - i);
//                memmove ( &deq->data[memmove_idx], &deq->data[i], sizeof( MyClass ));
                deq->data[memmove_idx] = deq->data[i];
            }
            deq->f_idx = deq->capacity - (old_cap - deq->f_idx);

        }
    }

    void printidx(Deque_MyClass *deq) {
        std::cout << "capacity: " << deq->capacity << std::endl;
        std::cout << "curr_size: " << deq->curr_size << std::endl;
        std::cout << "f_idx    : " << deq->f_idx << std::endl;
        std::cout << "b_idx    : " << deq->b_idx << std::endl;
        std::cout << std::endl;
    }

    void Deque_MyClass_push_back(Deque_MyClass *deq, MyClass val) {
        if(deq->full(deq)) {
            Deque_MyClass_resize(deq);
        }
        if(deq->empty(deq)) {
            deq->f_idx = deq->b_idx = 0;
        } else if(deq->b_idx == (int) deq->capacity-1) {
            deq->b_idx = 0;
        } else {
            ++deq->b_idx;
        }

//        std::cout << deq->b_idx << " " << deq->data[deq->b_idx].id << " " << deq->data[deq->b_idx].name << std::endl;
//        memcpy ( &deq->data[deq->b_idx], &val, sizeof(MyClass) );
        deq->data[deq->b_idx] = val;
        deq->curr_size++;
    }

    void Deque_MyClass_push_front(Deque_MyClass *deq, MyClass val) {
        if(deq->full(deq)) {
            Deque_MyClass_resize(deq);
        }
        if(deq->empty(deq)) {
            deq->f_idx = deq->b_idx = 0;
        } else if(deq->f_idx == 0) {
            deq->f_idx = deq->capacity-1;
        } else {
            --deq->f_idx;
        }
//        std::cout << deq->f_idx << " " << deq->data[deq->f_idx].id << " " << deq->data[deq->f_idx].name << std::endl;
//        memcpy ( &deq->data[deq->f_idx], &val, sizeof(MyClass) );
        deq->data[deq->f_idx] = val;
        deq->curr_size++;
    }


    void Deque_MyClass_pop_back(Deque_MyClass *deq) {
        if(deq->empty(deq)) {
            deq->f_idx = deq->b_idx = -1;
            return;
        }
        if(deq->b_idx == 0) {
            deq->b_idx = deq->capacity-1;
        } else {
            --deq->b_idx;
        }
        --deq->curr_size;
    }

    void Deque_MyClass_pop_front(Deque_MyClass *deq) {
        if(deq->empty(deq)) {
            deq->f_idx = deq->b_idx = -1;
            return;
        }
        if (deq->f_idx == (int) deq->capacity-1) {
            deq->f_idx = 0;
        } else {
            ++deq->f_idx;
        }
        --deq->curr_size;
    }

    MyClass &Deque_MyClass_front(Deque_MyClass *deq) {
//        std::cout << deq->f_idx << " " << deq->data[deq->f_idx].id << " " << deq->data[deq->f_idx].name << std::endl;
        return deq->data[deq->f_idx];
    }

    MyClass &Deque_MyClass_back(Deque_MyClass *deq) {
//        std::cout << deq->b_idx << " " << deq->data[deq->b_idx].id << " " << deq->data[deq->b_idx].name << std::endl;
        return deq->data[deq->b_idx];
    }

    MyClass &Deque_MyClass_at(Deque_MyClass *deq, int i) {
        int at_idx = (i + deq->f_idx) % deq->capacity;
        return deq->data[at_idx];
    }

    void Deque_MyClass_destructor(Deque_MyClass *deq) {
        free(deq->data);
        //free(d);
    }

    void Deque_MyClass_clear(Deque_MyClass *deq) {
        deq->curr_size = 0;
        deq->f_idx = -1;
        deq->b_idx = 0;
    }

    size_t Deque_MyClass_size(Deque_MyClass *deq) {
        return deq->curr_size;
    }

    bool Deque_MyClass_empty(Deque_MyClass *deq) {
        return deq->curr_size == 0;
    }

bool Deque_MyClass_equal(Deque_MyClass &d1, Deque_MyClass &d2) {
        if(d1.curr_size != d2.curr_size) {
            return false;
        } else {
            Deque_MyClass_Iterator it1 = d1.begin(&d1);
            Deque_MyClass_Iterator it2 = d2.begin(&d2);
            do {
                /*if(!(it1.deref(&it1) == it2.deref(&it2))) {*/
                    if((memcmp((const void *) &it1.deref(&it1),
                            (const void *) &it2.deref(&it2), sizeof(MyClass)))) {
                    return false;
                }
                it1.inc(&it1);
                it2.inc(&it2);
            } while (!Deque_MyClass_Iterator_equal(it1, d1.end(&d1)));
            return true;
        }
    }

    bool Deque_MyClass_full(Deque_MyClass *deq) {
        return deq->curr_size == deq->capacity;
    }

    void Deque_MyClass_Iterator_increment(Deque_MyClass_Iterator *it) {
        if(it->curr_idx == it->deque_capacity-1) {
            it->data_ptr = it->data_ptr - it->deque_capacity + 1;
            it->curr_idx = 0;
        } else {
            ++it->data_ptr;
            ++it->curr_idx;
        }
    }

    void Deque_MyClass_Iterator_decrement(Deque_MyClass_Iterator *it) {
        if(it->curr_idx == 0) {
            it->data_ptr = it->data_ptr + it->deque_capacity - 1;
            it->curr_idx = it->deque_capacity-1;
        } else {
            --it->data_ptr;
            --it->curr_idx;
        }
    }

    MyClass &Deque_MyClass_Iterator_dereference(Deque_MyClass_Iterator *it) {
        return *it->data_ptr;
    }

    Deque_MyClass_Iterator Deque_MyClass_begin(Deque_MyClass *deq) {
        Deque_MyClass_Iterator it;
        it.curr_idx = deq->f_idx;
        it.data_ptr = &deq->data[it.curr_idx];
        it.deque_capacity = deq->capacity;
        it.inc = Deque_MyClass_Iterator_increment;
        it.dec = Deque_MyClass_Iterator_decrement;
        it.deref = Deque_MyClass_Iterator_dereference;
        return it;
    }

    Deque_MyClass_Iterator Deque_MyClass_end(Deque_MyClass *deq) {
        Deque_MyClass_Iterator it;
        /* Return one past back index */
        it.curr_idx = deq->b_idx+1;
        it.data_ptr = &deq->data[it.curr_idx];
        it.deque_capacity = deq->capacity;
        it.inc = Deque_MyClass_Iterator_increment;
        it.dec = Deque_MyClass_Iterator_decrement;
        it.deref = Deque_MyClass_Iterator_dereference;
        return it;
    }

    bool Deque_MyClass_Iterator_equal(Deque_MyClass_Iterator it1,
            Deque_MyClass_Iterator it2) {
        return it1.data_ptr == it2.data_ptr;
    }

    void Deque_MyClass_ctor(Deque_MyClass *deq, bool (*comp)(const MyClass&, const MyClass&)) {
        deq->capacity = 4;
        deq->data = ( MyClass *)malloc(sizeof(MyClass) * deq->capacity);
        deq->curr_size = 0;
        deq->f_idx = -1;
        deq->b_idx = 0;
        sprintf(deq->type_name, "%s", "Deque_" "MyClass");
        deq->push_front = &Deque_MyClass_push_front;
        deq->push_back = &Deque_MyClass_push_back;
        deq->pop_front = &Deque_MyClass_pop_front;
        deq->pop_back = &Deque_MyClass_pop_back;
        deq->front = &Deque_MyClass_front;
        deq->back = &Deque_MyClass_back;
        deq->at = &Deque_MyClass_at;
        deq->dtor = &Deque_MyClass_destructor;
        deq->clear = &Deque_MyClass_clear;
        deq->size = &Deque_MyClass_size;
        deq->empty = &Deque_MyClass_empty;
        deq->full = &Deque_MyClass_full;
        deq->begin = &Deque_MyClass_begin;
        deq->end = &Deque_MyClass_end;
        deq->comp = comp;
        /* End Macro */\
    }
#endif // __DEQUE_H_
