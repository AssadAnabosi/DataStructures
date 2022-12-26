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

template <class S>
class Stack
{
    Node<S> *head;

    void destroy()
    {
        while (this->Pop())
            ;
    }

public:
    Stack()
    {
        this->head = NULL;
    }

    Stack(Stack<S> &received)
    {
        this->head = NULL;
        this->operator=(received);
    }

    bool Empty()
    {
        return this->head == NULL;
    }

    bool Push(S item)
    {
        Node<S> *temp = new Node<S>(item);
        if (temp == NULL)
            return false;
        temp->next = this->head;
        this->head = temp;
        return true;
    }

    bool Pop()
    {
        if (this->empty())
            return false;
        Node<S> *temp = this->head;
        this->head = this->head->next;
        delete temp;
        return true;
    }

    bool Top(S &value)
    {
        if (this->empty())
            return false;
        value = this->head->value;
        return true;
    }

    void operator=(Stack<S> &received)
    {
        destroy();
        // if received stack is empty then they are the same
        if (received.empty())
            return;
        // we copy the received stack
        Node<S> *rptr = received.head; //  received tmp ptr
        Node<S> *cptr, *copyHead;      //  copy tmp ptr and copy head ptr
        cptr = copyHead = new Node<S>(rptr->value);
        while (rptr->next != NULL)
        {
            rptr = rptr->next;
            cptr->next = new Node<S>(rptr->value);
            cptr = cptr->next;
        }
        this->head = copyHead;
        return;
    }

    ~Stack()
    {
        destroy();
    }
};

int main()
{

    return 0;
}
