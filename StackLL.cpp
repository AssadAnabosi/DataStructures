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
	bool print(){
		if (next != NULL){
			cout << data << "\t";
			node<N>* p = next;
			while (p != NULL){
				cout << p->data << "\t";
				p = p->next;
			}
			cout << endl;
			return true;
		}
		else
			return false;
	}
};
template <class N>
class stack{
	node <N>* topIndex;
	public:
	stack(){
		topIndex = NULL;
	}
	stack(stack<N> &s){
		node <N>* p = s.topIndex;
		stack <N> S;
		while(p != NULL){
			S.push(p->data);
			p = p->next;
		}
		p = S.topIndex;
		while(p != NULL){
			push(p->data);
			p = p->next;
		}
	}
	/*
	stack(stack<N> &s){
		node <N>* p = s.topIndex;
		if (p != NULL){
			node <N>*newCopy;
			newCopy = topIndex = new node<N> (p->data);
			while(p->next != NULL){
				p = p-> next;
				newCopy->next = new node <N>(p->data);
				newCopy = newCopy->next;
			}
		}
	}
	*/
	bool empty(){
		return (topIndex == NULL);
	}
	bool push(N item){
		node <N>* tmp = new node<N>(item);
		if (tmp == 0){
			return false;
		}
		else{
			tmp -> next = topIndex;
			topIndex = tmp;
			return true;
		}
	}
	bool pop(){
		if (empty()){
			return false;
		}
		else{
			node <N>* tmp = topIndex;
			topIndex = topIndex->next;
			delete tmp;
			return true;
		}
	}
	N top(){
		return topIndex->data;
	}
	void operator=(stack<N> &s){
		while(pop());
		if (!s.empty()){
			node <N>* p = s.topIndex;
			stack <N> S;
			while(p != NULL){
				S.push(p->data);
				p = p->next;
			}
			p = S.topIndex;
			while(p != NULL){
				push(p->data);
				p = p->next;
			}
		}
		return;
	}
	/*
	void operator=(stack<N> &s){
		while(pop());
		if (!s.empty()){
			node <N>* tmp = s.topIndex;
			node <N>* p, *newCopy;
			p = newCopy = new node<N> (tmp->data);
			while(tmp->next != NULL){
				tmp = tmp-> next;
				p->next = new node <N>(tmp->data);
				p = p->next;
			}
			topIndex = newCopy;
		}
	}
	*/
	~stack(){
		while(pop());
	}
};
template <class N>
bool print(stack <N> s){
	if (s.empty())
		return false;
	else{
		while(!s.empty()){
			cout << s.top() << "\t";
			s.pop();
		}
		cout << endl;
		return true;
	}
}
int main(){
	{
		stack <int> s;
		s.push(10);
		s.push(20);
		s.push(30);
			for (int i = 0; i < 5; i++){
				stack<int> s1;
				s1.push(i);
				s1=s;
			}
			
	}
	stack <int> s;
		s.push(10);
		s.push(20);
		s.push(30);
	print(s);
	print(s);
	print(s);
	stack <int> s2;
	s2 = s;
	print(s2);
	print(s2);
//	stack<int> s1(s);
	return 0;
}