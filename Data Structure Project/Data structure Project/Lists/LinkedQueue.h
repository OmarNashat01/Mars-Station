#pragma once

template<class T>
class Node
{
private:
    T item;
    Node<T>* Next;

public:
    Node() { Next = nullptr; }
    Node(const T& it) { item = it; Next = nullptr; }
    Node(const T& it, Node<T>* nextnode) { item = it; Next = nextnode; }
    void setItem(T it) { item = it; }
    void setNext(Node<T>* nx) { Next = nx; }
    T getItem()const { return item; }
    Node<T>* getNext()const { return Next; }

};


template<class T>
class LinkedQueue
{
private:
    Node<T>* Head;
    Node<T>* Tail;
  
public:
    LinkedQueue() { Head = nullptr; Tail = nullptr; }
    LinkedQueue(const LinkedQueue <T>& Q)
    {
        if (Q.Head == nullptr)
        {
            Head = nullptr;
            Tail = nullptr;
            return;
        }
        Node<T>* temp = new Node<T>(Q.Head->getItem());
        Node<T>* H = Q.Head->getNext();
        Head = temp;
        Tail = temp;
      
        while (H)
        {
            temp = new Node<T>(H->getItem());
            Tail->setNext(temp);
            Tail = temp;
            H = H->getNext();
        }
    }

    bool IsEmpty()
    {
        return Head == nullptr;
    }

    bool enqueue(const T& it)
    {
        Node<T>* temp = new Node<T>(it);
        if (IsEmpty())
	        Head = temp;
        else
	        Tail->setNext(temp);
      
        Tail = temp;
      
        return true;
    }

    bool dequeue(T& it)
    {
        if (IsEmpty())
            return false;

        Node<T>* value = Head;
        it = Head->getItem();
        Head = Head->getNext();

        if (value == Tail)
	        Tail = nullptr;

        delete value;

        return true;
    }

    bool peak(T& data)
    {
        if (!Head)
	        return false;

        data = Head->getItem();
        return true;
    }
};
