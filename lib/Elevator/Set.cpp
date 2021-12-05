#include "Set.h"

/**
* Default set constructor. Doesn't define the head of the list.
*/
Set::Set()
{
    head = NULL;
}

/**
* Set constructor. Creates a set where the head, the first entry in the list,
* has a data field of the specified value.
* 
* @param elem The value of the first element in the set.
*/
Set::Set(uint8_t elem)
{
    head = new Node(elem);
    currSize++;
}

/**
* Adds an element of the given value into the set. If the element is already in the list,
* doesn't add it. Increases the size if the element is added.
* 
* @param elem The element to be inserted into the list.
*/
void Set::add(uint8_t elem)
{

    if(head == NULL){
        head = new Node(elem);
    }

    else{
        Node* current = head;

        while(current->getNext() != nullptr){ 
            if(current->getValue() == elem){ //already in list
                return;                      //utilizing contains() increases time complexity
            }
            current = current->getNext();
        }
        
        if(current->getValue() != elem){
            current->setNext(new Node(elem)); 
        }
        else{ //the above code doesn't always check if the last item is in the list, need to make one more comparison
            return;
        }
    }
    currSize++;
}


/**
* Iterates over the set and checks if an element is already in the set.
* 
* @param elem The element to be searched for
* @return A boolean. True if the element was found in the set, false otherwise.
*/
bool Set::contains(uint8_t elem)
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

/**
* Iterates over the set and removes the given element from the set by setting the previous node's next
* field to the node after the one to be removed. If the node is found, deletes it from the program's memory.
* 
* @param elem The element to be removed.
* @return A boolean. True if the element was removed from the set, false otherwise.
*/
bool Set::remove(uint8_t elem){
    Node* toDelete;
     if(head == NULL){
        return false;
    }

    else if(size() == 1 && head->getValue() == elem){ //remove the head
        head = NULL;
        currSize--;
        return true;

    }

    else if(head->getValue() == elem){ //remove head but theres more elements, set the new head one over
        toDelete = head;
        head = head->getNext();
        currSize--;
        delete toDelete; 
        return true;
    }

    else{ //look for the node to be deleted
        Node* current = head;

        while(current->getNext() != nullptr){
            if(current->getNext()->getValue() == elem){
                toDelete = current->getNext();
                current->setNext(current->getNext()->getNext());
                currSize--;
                delete toDelete;
                return true;
            }
            current = current->getNext();
        }
    }
    return false;
}

/**
* Iterates over the set and returns the value of an element at an index.
* 
* @param elem The value of the element at the given index in the set.
* @return The value of the element at the specified index. -1 if an invalid index was accessed.
*/
int Set::get(int index)
{
    if(size() < 1 || index >= size()) return -1;

    if(index == 0) return head->getValue();
    Node* current = head;

    for(int i = 0; i < index; i++){
        current = current->getNext();
    }
    
    return current->getValue();
}

/**
* Clears the set by continously removing the head of the linked list until the size is 0.
*/
void Set::clear()
{
    while(size() != 0){
        remove(head->getValue()); //much faster than iterating continuously over the set
    }
}

/**
* For debugging purposes, prints out every node's value in the set along with the index at which that
* node is located.
*/
void Set::print()
{
    Node* current = head;
    int index = 0;

    while(current != NULL){
        Serial.println("Index: " + String(index) + " with value: " + String(current->getValue()));
        index++;
        current = current->getNext();    
    }
}

/**
* Gives the current size of the set.
*
* @return The value of the current size of the set.
*/
int Set::size()
{
    return this->currSize;
}

/**
* Set destructor. Clears out the set, and as a result, every node from memory.
* Deletes the head of the set at the end, thus freeing all the set's allocated memory.
*/
Set::~Set()
{
    clear();
    delete head;
}