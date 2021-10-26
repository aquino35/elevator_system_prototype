#include "LinkedList.h"

LinkedList::LinkedList()
{
    head = NULL;
}

LinkedList::LinkedList(uint8_t elem)
{
    head = new Node(elem);
    currSize++;
}

void LinkedList::add(uint8_t elem)
{

    if(head == NULL){
        head = new Node(elem);
    }

    else{
        Node* current = head;

        while(current->getNext() != nullptr){
            current = current->getNext();
        }

        current->setNext(new Node(elem)); 
    }
    currSize++;
}

bool LinkedList::contains(uint8_t elem)
{

    if(head == NULL){
        return false;
    }

    else{
        Node* current = head;

        while(current != nullptr){
            if(current->getValue() == elem){
                return true;
            }
            current = current->getNext();
        }

        return false; 
    }
}

bool LinkedList::remove(uint8_t elem){
     if(head == NULL){
        return false;
    }

    else if(size() == 1 && head->getValue() == elem){ //remove the head
        head = NULL;
        currSize--;
        return true;

    }

    else if(head->getValue() == elem){ //remove head but theres more elements
        head = head->getNext();
        currSize--;
        return true;
    }

    else{
        Node* current = head;

        while(current->getNext() != nullptr){
            if(current->getNext()->getValue() == elem){
                current->setNext(current->getNext()->getNext());
                currSize--;
                return true;
            }
            current = current->getNext();
        }
    }
    return false;
}

void LinkedList::clear()
{
    head = NULL;
    currSize = 0;
}