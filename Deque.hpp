/* No Macro */

#ifndef __DEQUE_H_
#define __DEQUE_H_

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
// Use INMyClass macro for all MyClasss so as to not
// break when converting from macro version
// to standard struct when testing
#define INMyClass int

// Redefine for testing; commented out when macro
struct MyClass { INMyClass id; char name[10]; };


#define CAP 5
//#define Deque_DEFINE(MyClass)                                                       
    /*typedef MyClass* Deque_MyClass_Iterator;*/                                      
    struct Deque_MyClass_Iterator {                                             
        MyClass *data_ptr;                                                          
        int curr_idx;                                                         
        int deque_capacity;                                                   
        void (*inc)(Deque_MyClass_Iterator*);                                   
        void (*dec)(Deque_MyClass_Iterator*);                                   
        MyClass &(*deref)(Deque_MyClass_Iterator*);                                   
    };                                                                        
    struct Deque_MyClass {                                                        
        MyClass data[CAP];                                                          
        size_t capacity;                                                      
        size_t curr_size;                                                     
        int f_idx;                                                            
        int b_idx;                                                            
        char type_name[14];                                                   
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
                                                                              
    void printidx(Deque_MyClass *d) {                                             
        std::cout << "capacity: " << d->capacity << std::endl;                
        std::cout << "curr_size: " << d->curr_size << std::endl;              
        std::cout << "f_idx    : " << d->f_idx << std::endl;                  
        std::cout << "b_idx    : " << d->b_idx << std::endl;                  
        std::cout << std::endl;                                               
    }                                                                         
                                                                              
    void Deque_MyClass_push_back(Deque_MyClass *d, MyClass val) {                         
        if(d->full(d)) return;                                                
        if(d->f_idx == -1) {                                                  
            d->f_idx = d->b_idx = 0;                                          
        } else if(d->b_idx == (int) d->capacity-1) {                          
            d->b_idx = 0;                                                     
        } else {                                                              
            ++d->b_idx;                                                       
        }                                                                     
        d->data[d->b_idx] = val;                                              
        d->curr_size++;                                                       
        // printidx(d);
    }                                                                         
                                                                              
    void Deque_MyClass_push_front(Deque_MyClass *d, MyClass val) {                        
        if(d->full(d)) return;                                                
        if(d->f_idx == -1) {                                                  
            d->f_idx = d->b_idx = 0;                                          
        } else if(d->f_idx == 0) {                                            
            d->f_idx = d->capacity-1;                                         
        } else {                                                              
            --d->f_idx;                                                       
        }                                                                     
        d->data[d->f_idx] = val;                                              
        d->curr_size++;                                                       
        // printidx(d);
    }                                                                         
                                                                              
    void Deque_MyClass_pop_back(Deque_MyClass *d) {                                 
        if(d->empty(d)) return;                                               
        if(d->f_idx == d->b_idx) {                                            
            d->f_idx = d->b_idx = -1;                                         
        } else if(d->b_idx == 0) {                                            
            d->b_idx = d->capacity-1;                                         
        } else {                                                              
            --d->b_idx;                                                       
        }                                                                     
        d->curr_size--;                                                       
    }                                                                         
                                                                              
    void Deque_MyClass_pop_front(Deque_MyClass *d) {                                
        if(d->empty(d)) return;
        if(d->f_idx == d->b_idx) {                                            
            d->f_idx = d->b_idx = -1;                                         
        } else {                                                              
            if (d->f_idx == (int) d->capacity-1) {                            
                d->f_idx = 0;                                                 
            } else {                                                          
                ++d->f_idx;                                                   
            }                                                                 
        }                                                                     
        d->curr_size--;                                                       
    }                                                                         
                                                                              
    MyClass &Deque_MyClass_front(Deque_MyClass *d) {                                      
        return d->data[d->f_idx];                                             
    }                                                                         
                                                                              
    MyClass &Deque_MyClass_back(Deque_MyClass *d) {                                       
        return d->data[d->b_idx];                                             
    }                                                                         
                                                                              
    MyClass &Deque_MyClass_at(Deque_MyClass *d, int i) {                                  
        return d->data[i+d->f_idx];
    }                                                                         
                                                                              
    void Deque_MyClass_destructor(Deque_MyClass *d) {                               
        /* MyClassODO: Fix destructor!*/                                            
        /*free(d->data);*/                                                    
        /*free(d); */                                                         
    }                                                                         
                                                                              
    void Deque_MyClass_clear(Deque_MyClass *d) {                                    
        d->curr_size = 0;                                                     
        d->f_idx = -1;                                                        
        d->b_idx = 0;                                                         
    }                                                                         
                                                                              
    size_t Deque_MyClass_size(Deque_MyClass *d) {                                   
        return d->curr_size;                                                  
    }                                                                         
                                                                              
    bool Deque_MyClass_empty(Deque_MyClass *d) {                                    
        return d->f_idx == -1;
    }                                                                         
                                                                              
    bool Deque_MyClass_equal(Deque_MyClass &d1, Deque_MyClass &d2) {                    
        if(d1.curr_size != d2.curr_size) {                                    
            return false;                                                     
        } else {                                                              
            Deque_MyClass_Iterator it1 = d1.begin(&d1);                         
            Deque_MyClass_Iterator it2 = d2.begin(&d2);                         
            do {                                                              
                /*if(!(it1.deref(&it1) == it2.deref(&it2))) {*/
                std::cout << &it1.deref(&it1) << std::endl;
                std::cout << &it2.deref(&it2) << std::endl;
                std::cout << memcmp((const void *) &it1.deref(&it1),
                            (const void *) &it2.deref(&it2), sizeof(MyClass)) << std::endl;
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
                                                                              
    bool Deque_MyClass_full(Deque_MyClass *d) {                                     
        return ((d->f_idx ==  0) && (d->b_idx == (int) d->capacity-1))        
                || (d->f_idx == d->b_idx+1);
    }                                                                         
                                                                              
    void Deque_MyClass_Iterator_increment(Deque_MyClass_Iterator *it) {           
        if(it->curr_idx == it->deque_capacity-1) {                            
            it->data_ptr = it->data_ptr - it->deque_capacity;                 
            it->curr_idx = 0;                                                 
        } else {                                                              
            ++it->data_ptr;                                                   
            ++it->curr_idx;                                                   
        }                                                                     
    }                                                                         
                                                                              
    void Deque_MyClass_Iterator_decrement(Deque_MyClass_Iterator *it) {           
        if(it->curr_idx == 0) {                                               
            it->data_ptr = it->data_ptr + it->deque_capacity-1;               
            it->curr_idx = it->deque_capacity-1;                              
        } else {                                                              
            --it->data_ptr;                                                   
            --it->curr_idx;                                                   
        }                                                                     
    }                                                                         
                                                                              
    MyClass &Deque_MyClass_Iterator_dereference(Deque_MyClass_Iterator *it) {           
        return *it->data_ptr;                                                 
    }                                                                         
                                                                              
    Deque_MyClass_Iterator Deque_MyClass_begin(Deque_MyClass *d) {                    
        Deque_MyClass_Iterator it;
        it.curr_idx = d->f_idx;
        it.data_ptr = &d->data[it.curr_idx];
        it.deque_capacity = d->capacity;
        it.inc = Deque_MyClass_Iterator_increment;                              
        it.dec = Deque_MyClass_Iterator_decrement;                              
        it.deref = Deque_MyClass_Iterator_dereference;                          
        return it;                                                            
    }                                                                         
                                                                              
    Deque_MyClass_Iterator Deque_MyClass_end(Deque_MyClass *d) {                      
        Deque_MyClass_Iterator it;                                              
        /* Return one past back index */
        it.curr_idx = d->b_idx+1;
        it.data_ptr = &d->data[it.curr_idx];
        it.deque_capacity = d->capacity;
        it.inc = Deque_MyClass_Iterator_increment;                              
        it.dec = Deque_MyClass_Iterator_decrement;                              
        it.deref = Deque_MyClass_Iterator_dereference;                          
        return it;                                                            
    }                                                                         
                                                                              
    bool Deque_MyClass_Iterator_equal(Deque_MyClass_Iterator it1,                 
            Deque_MyClass_Iterator it2) {                                       
        std::cout << "it1: " << it1.data_ptr << std::endl;                    
        std::cout << "it2: " << it2.data_ptr << std::endl;                    
        return it1.data_ptr == it2.data_ptr;
    }                                                                         
                                                                              
    void Deque_MyClass_ctor(Deque_MyClass *d, bool (*comp)(const MyClass&, const MyClass&)) {   
        d->capacity = CAP;                                                    
        d->curr_size = 0;                                                     
        d->f_idx = -1;                                                        
        d->b_idx = 0;                                                         
        /*std::string d_str ("Deque_");                                       
        std::string type_str (#MyClass);*/                                          
        strcpy(d->type_name, "Deque_");                                       
        strcat(d->type_name, "MyClass");                                             
        d->push_front = &Deque_MyClass_push_front;                              
        d->push_back = &Deque_MyClass_push_back;                                
        d->pop_front = &Deque_MyClass_pop_front;                                
        d->pop_back = &Deque_MyClass_pop_back;                                  
        d->front = &Deque_MyClass_front;                                        
        d->back = &Deque_MyClass_back;                                          
        d->at = &Deque_MyClass_at;                                              
        d->dtor = &Deque_MyClass_destructor;                                    
        d->clear = &Deque_MyClass_clear;                                        
        d->size = &Deque_MyClass_size;                                          
        d->empty = &Deque_MyClass_empty;                                        
        d->full = &Deque_MyClass_full;                                          
        d->begin = &Deque_MyClass_begin;                                        
        d->end = &Deque_MyClass_end;                                            
        d->comp = comp;                                                      
        /* End Macro */\
    }
#endif // __DEQUE_H_
