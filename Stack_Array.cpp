#include <iostream>
using namespace std;

const unsigned int MAXSIZE = 100;
template <class T>
class Stack{
    T array[MAXSIZE];
    int rearP;   //  rear pointing index

    public:
    Stack(){
        rearP = 0;
    }

    bool empty(){
        return rearP == 0;
    }

    bool full(){
        return rearP == MAXSIZE;
    }

    bool push(T value){
        if(this->full())
            return false;
        array[rearP++] = value;
        return true;
    }

    bool top(T& value){
        if (this->empty())
            return false;
        value = array[rearP - 1];
        return true;
    }

    bool pop(){
        if (this->empty())
            return false;
        rearP--;
        return true;
    }

};

int main(){

    return 0;
}
