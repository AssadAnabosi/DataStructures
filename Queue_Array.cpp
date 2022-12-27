#include <iostream>
using namespace std;

const unsigned int MAXSIZE = 100;
template <class T>
class Queue {
    T array[MAXSIZE];
    int count; // counter to solve circle queues con 
    int frontP, rearP; // front and rear pointing indexes

public:
    Queue() {
        count = 0;
        frontP = 0;
        rearP = MAXSIZE - 1;
    }

    bool empty() {
        return count == 0;
    }

    bool full() {
        return count == MAXSIZE;
    }

    bool push(T value) {
        // do not push/append when queue is FULL
        if (this->full())
            return false;
        rearP = (rearP + 1) % MAXSIZE;
        count++;
        array[rearP] = value;
        return true;
    }

    bool top(T& value) {
        if (this->empty())
            return false;
        value = array[frontP];
        return true;
    }

    bool pop() {
        // do not pop/serve if queue is empty
        if (this->empty())
            return false;
        frontP = (frontP + 1) & MAXSIZE;
        count--;
        return true;
    }

};

int main() {

    return 0;
}
