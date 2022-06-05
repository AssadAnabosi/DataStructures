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
class list{
	protected:
	node <N>* head;
	int currentSize;
	
	node <N>* setPos(int pos){
		node <N>* tmp = head;
		for (int i = 0; i < pos; i++)
			tmp = tmp->next;
		return tmp;
	}
	
	public:
	list(){
		head = NULL;
		currentSize = 0;
	}
	list(list <N> &L){
		node<N>*tmp = L.head;
		while (tmp != NULL){
			this->insert(this->currentSize, tmp->data);
			tmp = tmp->next;
		}
	}
	bool empty(){
		return (head == NULL);
	}
	int size(){
		return currentSize;
	}
	bool insert(int pos, N item){
		if (pos < 0 || pos > currentSize)
			return false;
		node <N>* tmp = new node <N>(item);
		if (tmp == NULL)
			return false;
		node <N>* prev, *follow;
		if (pos > 0){
			prev = setPos(pos - 1);
			follow = prev->next;
		}
		else
			follow = head;
		tmp->next = follow;
		if (pos > 0)
			prev->next = tmp;
		else
			head = tmp;
		currentSize++;
		return true;
	}
	bool remove(int pos){
		if (pos < 0 || pos >= currentSize)
			return false;
		node <N>* prev, *follow;
		if (pos > 0){
			prev = setPos(pos - 1);
			follow = prev->next;
		}
		else
			follow = head;
		if (pos > 0)
			prev = follow->next;
		else
			head = follow->next;
		delete follow;
		currentSize--;
		return true;
	}
	bool retrieve(int pos, N&item){
		if(pos < 0 || pos >= currentSize)
			return false;
		node <N>* tmp = setPos(pos);
		item = tmp->data;
		return true;
	}
	bool replace (int pos, N item){
		if(pos < 0 || pos >= currentSize)
			return false;
		node <N>* tmp = setPos(pos);
		tmp->data= item;
		return true;
	}
	void destroy(){
		while(remove(0));
	}
	void operator=(list <N>&L){
		this->destroy();
		if (L.empty())
			return;
		node<N>*tmp = L.head;
		while (tmp != NULL){
			this->insert(this->currentSize, tmp->data);
			tmp = tmp->next;
		}
	}
	/*
	void operator=(list <N>&L){
		node <N>* newHead = 0, *q=L.head, *tmp;
		if (!L.empty()){
			tmp = newHead = new node <N>(q->data);
			while(q->next != NULL){
				q = q->next;
				tmp->next = new node<N>(q->data);
				tmp = tmp->next;
			}
		}
		this->destroy();
		this->head = newHead;
		this->currentSize = L.size();
	}
	*/
	~list(){
		destroy();
	}
};
template <class N>
class orderedList:public list<N>{
	public:
	bool insert(N item){
		int pos;
		node <N>* tmp = list<N>::head;
		for (pos = 0; pos < list<N>::size(); pos++){
			if (tmp->data > item)
				break;
			tmp = tmp->next;
		}
		return list<N>::insert(pos, item);
	}
	/*
	bool replace(int pos, N item){
		N flag;
		if(!list<N>::retrieve(pos, flag))
			return false;
		list<N>::remove(pos);
		return insert(item);
	}
	*/
	bool replace(int pos, N item){
		N x;
		if (!list<N>::retrieve(pos, x))
			return false;
		node <N>* tmp = new node <N>(item);
		if (tmp == NULL)
			return false;
		node <N>* prev, *follow;
		if (pos > 0){
			prev = list<N>::setPos(pos - 1);
			follow = prev->next;
		}
		else
			follow = list<N>::head;
		if(prev->data < item && follow->data > item){
			tmp->next = follow;
			if (pos > 0)
				prev->next = tmp;
			else
				list<N>::head = tmp;
			list<N>::currentSize++;
			return true;
		}
		return false;
	}
};

template <class N>
void print(list <N> &l){
	N item;
	for (int i = 0; i < l.size(); i++){
		l.retrieve(i, item);
		cout << item << "\t";
	}
	cout << endl;
}

template <class N>
void printo(orderedList <N> &l){
	N item;
	for (int i = 0; i < l.size(); i++){
		l.retrieve(i, item);
		cout << item << "\t";
	}
	cout << endl;
}

int sum(list <int> &L, int pos = 0){
	int x;
	if(L.retrieve(pos, x))
		return x+sum(L, pos+1);
	return 0;
}

bool closest(list <int> &L){
	if (L.size() <= 1) 
		return false;
	bool flag = true;
	int item1, item2, sub;
	int tmp1, tmp2, tmpSub;
	for (int i = 0; i < L.size(); i++){
		L.retrieve(i, tmp1);
		for (int j = 0; j < L.size(); j++){
			if (i == j)
				continue;
			L.retrieve(j, tmp2);
			tmpSub = tmp1 - tmp2;
			if (tmpSub < 0)
				tmpSub *= -1;
			if (!flag){
				if (tmpSub < sub){
					sub = tmpSub;
					item1 = tmp1;
					item2 = tmp2;
				}
			}
			else{
				sub = tmpSub;
				item1 = tmp1;
				item2 = tmp2;
				flag = false;
			}
		}
	}
	cout << item1 << "\t" << item2 << endl;
	return true;
}

template <class N>
void revList(list <N> &L){
	int i = 0, j = L.size() - 1;
	N i1, i2, tmp;
	while (i != j){
		L.retrieve(i, i1);
		L.retrieve(j, i2);
		L.replace(i, i2);
		L.replace(j, i1);
		i++;
		j--;
	}
}

int search(list<int> &L, int x, int i = 0){
	int tmp;
	if (!L.retrieve(i, tmp))
		return -1;
	if (tmp == x)
		return i;
	return search(L, x, ++i);	
}

template <class T>
bool InsertAt(node<T>* head, T x, T item){
	if (head == NULL)
		return false;
	node <T>* tmp = head;
	while(tmp != NULL){
		if (tmp->data == x){
			node <T>* i = new node<T>(item);
			i->next = tmp->next;
			tmp->next = i;
			return true;
		}
		tmp = tmp->next;
	}
	return false;
}

int main(){
// 	list <int> L1;
// 	L1.insert(L1.size(), 20);
// 	L1.insert(L1.size(), 31);
// 	L1.insert(L1.size(), 10);
// 	print(L1);
	/*
	orderedList<int> ol;
	ol.insert(20);
	int x;
	ol.retrieve(0, x);
	cout << x << endl;
	ol.insert(10);
	print(ol);
	cout << ol.replace(0, 5) << endl;
	ol.retrieve(0,x);
	cout << x << endl;
	*/
// 	cout << sum(L1) << endl;
// 	closest(L1);
// 	revList(L1);
// 	print(L1);
	return 0;
}
