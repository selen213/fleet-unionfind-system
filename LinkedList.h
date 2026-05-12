#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>

template <class Key, class Data>
class Element{//like node
public:
    Key m_key;
    Data m_info;
    Element* m_next;
    Element* m_prev;

    Element() = default;
    explicit Element(const Key& key,const Data& info):m_key(key),m_info(info), m_next(nullptr), m_prev(nullptr){}
    ~Element() = default;
};

template <class Key, class Data>
class LinkedList{

    Element<Key,Data>* m_head;
public:
    LinkedList() :m_head(nullptr){}

    ~LinkedList(){
        this->DestroyList();
    }

    Element<Key,Data>* getHead() const{
        return m_head;
    }
    void setHead(Element<Key,Data>* new_head){
        m_head=new_head;
    }

    Element<Key,Data>* InsertInfo(const Key& key,const Data& info,  Element<Key,Data>* currentElement){
        Element<Key,Data>* newElement = new  Element<Key,Data>(key,info);
        if (m_head == nullptr && currentElement == nullptr){
            m_head = newElement;
            return m_head;
        }
        if (key > currentElement->m_key){
            Element<Key,Data>* tempNext = currentElement->m_next;
            currentElement->m_next = newElement;
            newElement->m_next = tempNext;
            newElement->m_prev = currentElement;
            if (tempNext != nullptr){
                tempNext->m_prev = newElement;
            }
        } else if (key < currentElement->m_key){
            Element<Key,Data>* tempPrev = currentElement->m_prev;
            currentElement->m_prev = newElement;
            newElement->m_next = currentElement;
            newElement->m_prev = tempPrev;
            if (tempPrev != nullptr){
                tempPrev->m_next = newElement;
            } else{
                this->m_head=newElement;
            }

        }
        return newElement;
        //we dont reach here since the tree should throw the exception that we are adding a player that already exists
    }

    void RemoveInfo( Element<Key,Data>* toBeDeleted){
        if (toBeDeleted->m_next == nullptr && toBeDeleted->m_prev){
            toBeDeleted->m_prev->m_next = nullptr;
            delete toBeDeleted;
        }else if (toBeDeleted->m_prev == nullptr && toBeDeleted->m_next){
            m_head = toBeDeleted->m_next;
            m_head->m_prev = nullptr;
            delete toBeDeleted;
        }else if (toBeDeleted->m_prev == nullptr && toBeDeleted->m_next == nullptr){
            m_head = nullptr;
            delete toBeDeleted;
        }else {
            Element<Key,Data> *tempNext = toBeDeleted->m_next;
            Element<Key,Data> *tempPrev = toBeDeleted->m_prev;
            tempNext->m_prev = tempPrev;
            tempPrev->m_next = tempNext;
            delete toBeDeleted;
        }
    }

    void DestroyList(){
        while (m_head != nullptr){
            Element<Key,Data>* temp = m_head;
            m_head = m_head->m_next;
            delete temp;
        }
    }


    void DestroyListData(){
        while (m_head != nullptr){
            Element<Key,Data>* temp = m_head;
            m_head = m_head->m_next;
            // Assuming Data needs explicit deletion or clean-up:
            //delete temp->m_info;  // Uncomment if needed
            delete temp;
        }
    }
    void DestroyListDataFinal(){
        while (m_head != nullptr){
            Element<Key,Data>* temp = m_head;
            m_head = m_head->m_next;
            // Assuming Data needs explicit deletion or clean-up:
            delete temp->m_info;  // Uncomment if needed
            delete temp;
        }
    }



};


#endif //LINKEDLIST_H_
