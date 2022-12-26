#include <iostream>
using namespace std;

template <class N>
class Node
{
public:
    Node *next;
    N value;

    Node()
    {
        this->next = NULL;
    }

    Node(N value)
    {
        this->value = value;
        this->next = NULL;
    }

    Node(N value, Node<N> *next)
    {
        this->value = value;
        this->next = next;
    }
};

template <class Q>
class Queue
{
    Node<Q> *front, *rear;
    int count;

    void clear()
    {
        while (this->Serve())
            ;
    }

public:
    Queue()
    {
        this->front = this->rear = NULL;
        this->count = 0;
    }

    Queue(Queue<Q> &received)
    {
        this->front = this->rear = NULL;
        this->count = 0;
        this->operator=(received);
    }

    bool Empty()
    {
        return this->count == 0;
    }

    bool Append(Q item)
    {
        Node<Q> *temp = new Node<Q>(item);
        // memory is Full
        if (temp == NULL)
            return false;
        // adding the first node
        else if (this->rear == NULL)
            this->rear = this->front = temp;
        // adding non-first node
        else
        {
            this->rear->next = temp;
            this->rear = temp;
        }
        this->count++;
        return true;
    }

    bool Serve()
    {
        if (this->Empty())
            return false;
        Node<Q> *temp = this->front;
        this->front = this->front->next;
        // front reached end, then rear needs to be NULL
        if (this->front == NULL)
            this->rear = NULL;
        delete temp;
        this->count--;
        return true;
    }

    bool Front(Q &item)
    {
        if (this->Empty())
            return false;
        item = this->front->value;
        return true;
    }

    void operator=(Queue<Q> &received)
    {
        clear();
        // if received queue is empty then they are the same
        if (received.Empty())
            return;
        // we copy the received queue
        Node<Q> *rptr = received.front; //  received tmp ptr
        while (rptr != NULL)
        {
            this->Append(rptr->value);
            rptr = rptr->next;
        }
    }

    ~Queue()
    {
        clear();
    }
};

int main()
{
    
    return 0;
}
