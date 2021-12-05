#pragma once
#include <Arduino.h>

/**
* @file Set.h
*
* @brief A set implemented with a singly linked list. Utilized to store the requested floors.
*        The set's properties prevent a floor from being requested multiple times.
*
* @author Yariel Mercado
*/
class Set{ 
    private:
        /**
        *
        * @brief The node class, the building blocks of the singly linked list. Stores
        *        data, in this class the requested floor, and a reference to the next
        *        node in the singly linked list.
        *
        * @author Yariel Mercado
        */
        class Node{
            private:
                /* The data to be stored in the node, in this case, each floor number. */
                uint8_t data;
                /* A reference to the next node in the singly linked list. */
                Node* next;
    
            public:
                /**
                * Gets the next node in the singly linked list.
                * 
                * @return The next node object in the linked list. NULL if it's the last item
                *         in the singly linked list.
                */ 
                Node* getNext(){
                    return next;
                };

                /**
                * Retrieves the current node's value.
                * 
                * @return The current value of the node, in other words, its floor number.
                */ 
                uint8_t getValue(){
                    return data;
                };

                /**
                * Sets a reference to the next node in the singly linked list.
                * 
                * @param nextNode The node object of the next node in the list.
                */ 
                void setNext(Node* nextNode){
                    next = nextNode;
                };


                /**
                * Node constructor. Creates a node with the specified data. The next node in the list
                * isn't specified and has a default value of null.
                * 
                * @param elem The value given to the created node.
                */ 
                Node(uint8_t elem){
                    data = elem;
                    next = nullptr;
                };

                /**
                * Node constructor. Creates a node with the specified data and the next element in the list.
                * 
                * @param elem The value given to the created node.
                * @param nextNode The node object of the next node in the list.
                */ 
                Node(uint8_t elem, Node* nextNode){
                    data = elem;
                    next = nextNode;
                };

                /**
                * Default node constructor. Creates a node with no set data and no references to the next element
                * in the list.
                */ 
                ~Node(){
                    next = NULL;
                }
        };

        /* A node object specifying the head of the singly linked list. */
        Node* head;
        /* The current size of the singly linked list. */
        int currSize = 0;

    public:
        Set();
        Set(uint8_t elem);
        ~Set();
        
        void add(uint8_t elem);
        int get(int index);
        bool contains(uint8_t elem);
        bool remove(uint8_t elem);
        void clear(); 
        int size();
        void print();
};