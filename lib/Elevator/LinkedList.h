#pragma once
#include <stdint.h>
#include <Arduino.h>

//TESTED WITH INTS, WORKS
class LinkedList{ //singly linked

    private:
        class Node{
            private:
                uint8_t data;
                Node* next;
    
            public:
                Node* getNext(){
                    return next;
                };

                uint8_t getValue(){
                    return data;
                };

                void setNext(Node* nextNode){
                    next = nextNode;
                };

                Node(uint8_t elem){
                    data = elem;
                    next = nullptr;
                };

                Node(uint8_t elem, Node* nextNode){
                    data = elem;
                    next = nextNode;
                };
        };

        Node* head;
        int currSize = 0;

    public:
        LinkedList();
        LinkedList(uint8_t elem);

        void add(uint8_t elem);
        bool contains(uint8_t elem);
        bool remove(uint8_t elem);
        void clear(); 
        int size(){return currSize;} 
};