#include <iostream>
using namespace std;

template <class N>
class node{
	public:
	N data;
	node <N>* next;
		
	node(){
		next = NULL;
	}
	
	node(N item){
		data = item;
		next = NULL;
	}
	node(N item, node <N>* next){
		data = item;
		this->next = next;
	}
	void print(){
		if (next != NULL){
			cout << data << "\t";
			node<N>* p = next;
			while (p != NULL){
				cout << p->data << "\t";
				p = p->next;
			}
			cout << endl;
		}
		else
			cout << "Empty Node..!" << endl;
	}
};

template <class Q>
class queue{
	node <Q>* front, *rear;
	unsigned int currentSize;
	public:
	queue(){
		currentSize = 0;
		front = rear = NULL;
	}
	queue(queue<Q> &q){	//	copy const.
		node <Q>*p =q.front;
		while (p != NULL){
			Append(p->data);
			p=p->next;
		}
	}
	bool empty(){
		return (currentSize == 0);
	}
	bool Append(Q item){
		node <Q>* tmp = new node <Q> (item);
		if (tmp == NULL)
			return false;
		if (rear == NULL)
			rear = front = tmp;
		else{
			rear->next = tmp->next;	//	double check
			rear = tmp;
		}
		currentSize++;
		return true;
	}
	bool full(){
		node <Q>* tmp = new node <Q> ();
		if (tmp == NULL)
			return false;
		return true;
	}
	bool serve(){
		if(empty())
			return false;
		node <Q>* tmp = front;
		front = front->next;
		if (front == NULL)
			rear = NULL;
		currentSize--;
		delete tmp;
		return true;
	}
	bool retreive(Q &item){
		if (empty())
			return false;
		item = front->data;
		return true;
	}
	void operator=(queue <Q> &q){
		while(serve());
		if (q.empty())
			return;
		node <Q>*p =q.front;
		while (p != NULL){
			Append(p->data);
			p=p->next;
		}
	}
	~queue(){
		while(serve());
	}
};

int main(){
	queue <int> q;
	q.Append(1);
	int item;
	queue <int> q2;
	return 0;
}