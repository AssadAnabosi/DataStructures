#include <iostream>
using namespace std;

template <class D>
class node {
public:
	D data;
	node <D>* back, * next;

	node() {
		next = back = NULL;
	}
	node(D item) {
		data = item;
		next = back = NULL;
	}
};

template <class D>
class list {
protected:
	node <D>* head;
	int currentSize;
	int currentPos;
	node<D>* setPos(int pos) {
		if (pos < currentPos) {
			for (; pos != currentPos && head->back != NULL; currentPos--)
				head = head->back;
		}
		else if (pos > currentPos) {
			for (; pos != currentPos && head->next != NULL; currentPos++)
				head = head->next;
		}
		return head;
	}
public:
	list() {
		head = NULL;
		currentSize = 0;
		currentPos = 0;
	}
	list(list <D>& L) {
		head = NULL;
		currentSize = 0;
		currentPos = 0;
		D tmp;
		for (int i = 0; i < L.size(); i++) {
			L.retrieve(i, tmp);
			insert(this->currentSize, tmp);
		}
	}
	bool empty() {
		return (currentSize == 0);
	}
	int size() {
		return currentSize;
	}
	bool insert(int pos, D item) {
		if (pos < 0 || pos > currentSize)
			return false;
		node <D>* tmp = new node <D>(item);
		if (tmp == NULL)
			return false;
		if (pos != currentPos)
			setPos(pos);
		if (currentSize == 0)
			head = tmp;
		else if (pos == 0) {
			head->back = tmp;
			tmp->next = head;
		}
		else if (pos == currentSize) {
			head->next = tmp;
			tmp->back = head;
			currentPos++;
		}
		else {
			tmp->back = head->back;
			tmp->next = head;
			head->back->next = tmp;
			head->back = tmp;
		}
		head = tmp;
		currentSize++;
		return true;
	}
	bool remove(int pos) {
		if (pos < 0 || pos >= currentSize)
			return false;
		node<D>* tmp = setPos(pos);
		if (pos == currentSize - 1 && pos != 0) {
			head->back->next = NULL;
			head = head->back;
			currentPos--;
		}
		else if (pos == 0 && currentSize > 1) {
			head->next->back = NULL;
			head = head->next;
		}
		else if (pos >= 1) {
			head = head->back;
			head->next = tmp->next;
			currentPos--;
		}
		else if (pos < currentSize - 1) {
			head = head->next;
			head->back = tmp->back;
			currentPos++;
		}
		currentSize--;
		delete tmp;
		return true;
	}
	bool retrieve(int pos, D& item) {
		if (pos < 0 || pos >= currentSize)
			return false;
		setPos(pos);
		item = head->data;
		return true;
	}
	bool replace(int pos, D item) {
		if (pos < 0 || pos >= currentSize)
			return false;
		setPos(pos);
		head->data = item;
		return true;
	}
	int search(D item) {
		D tmp;
		for (int i = 0; i < currentSize; i++) {
			retrieve(i, tmp);
			if (tmp == item)
				return i;
		}
		return -1;
	}
	void sort() {
		int min;
		D tmpMin, tmpJ, tmp;
		for (int i = 0; i < currentSize - 1; i++) {
			min = i;
			for (int j = i + 1; j < currentSize; j++) {
				retrieve(j, tmpJ);
				retrieve(min, tmpMin);
				if (tmpJ < tmpMin)
					min = j;
				retrieve(i, tmp);
				replace(i, tmpMin);
				replace(min, tmp);
			}
		}
	}
	void destroy() {
		while (remove(0));
	}
	void operator=(list <D>& L) {
		this->destroy();
		if (L.empty())
			return;
		D tmp;
		for (int i = 0; i < L.size(); i++) {
			L.retrieve(i, tmp);
			insert(this->currentSize, tmp);
		}
	}
	~list() {
		destroy();
	}
};
template <class D>
class orderedList :public list<D> {
public:
	bool insert(D item) {
		if (list<D>::empty()) {
			return list<D>::insert(0, item);
		}
		if (list<D>::head->data > item) {
			while (list<D>::head->data > item && list<D>::head->back != NULL && list<D>::head->back->data > item) {
				list<D>::setPos(list<D>::currentPos - 1);
			}
		}
		else if (list<D>::head->data < item) {
			while (list<D>::head->data > item && list<D>::head->next != NULL) {
				list<D>::setPos(list<D>::currentPos + 1);
			}
			if (list<D>::head->data < item && list<D>::head->next == NULL) {
				return list<D>::insert(list<D>::currentSize, item);
			}
		}
		return list<D>::insert(list<D>::currentPos, item);
	}
	bool replace(int pos, D item) {
		D x;
		if (!list<D>::retrieve(pos, x))
			return false;
		list<D>::setPos(pos);
		if (pos == 0) {
			if (list<D>::head->next->data < item)
				return false;
			list<D>::head->data = item;
		}
		else if (pos == list<D>::currentSize - 1) {
			if (list<D>::head->back->data > item)
				return false;
			list<D>::head->data = item;
		}
		else {
			if (list<D>::head->back->data < item && list<D>::head->next->data > item)
				list<D>::head->data = item;
			else
				return false;
		}
		return true;
	}
	int search(D item) {
		D tmp;
		int L = 0, R = list<D>::currentSize - 1, mid;
		while (L <= R) {
			mid = (L + R) / 2;
			list<D>::retrieve(mid, tmp);
			if (tmp == item)
				return mid;
			if (tmp > item)
				R = mid - 1;
			else
				L = mid + 1;
		}
		return -1;
	}
};

template <class D>
bool print(list <D>& l) {
	if (l.empty())
		return false;
	D item;
	for (int i = 0; i < l.size(); i++) {
		l.retrieve(i, item);
		cout << item << "\t";
	}
	cout << endl;
	return true;
}
template <class D>
bool printv(list <D> l) {
	if (l.empty())
		return false;
	D item;
	for (int i = 0; i < l.size(); i++) {
		l.retrieve(i, item);
		cout << item << "\t";
	}
	cout << endl;
	return true;
}

int main() {

	// list <int> L1;
	// cout << "L1 Created" << endl;
	// L1.insert(L1.size(), 20);
	// L1.insert(L1.size(), 30);
	// L1.insert(L1.size(), 10);
	// L1.insert(0, 25);
	// L1.insert(1, 30);
	// L1.insert(0, 40);
	// L1.insert(2, 5);
	// L1.insert(L1.size(), 330);
	// L1.insert(L1.size(), 220);
	// print(L1);
	// list <int> L2 = L1;
	// cout << "lsit <int> L2 = L1" << endl;
	// print(L2);
	// L1.replace(0, 0);
	// cout << "replace pos 0 with val 0: " << endl;
	// print(L1);
	// cout << "L2 = L1" << endl;
	// L2 = L1;
	// print(L2);
	// cout << "printing L1 using copy const. : " << endl;
	// printv(L1);
	// printv(L1);
	// L2.sort();
	// cout << "Sorting L2" << endl;
	// print(L2);
	// cout << "orderedList<int> L3" << endl;
	// orderedList<int> L3;
	// L3.insert(5);
	// L3.insert(0);
	// L3.insert(2);
	// L3.insert(8);
	// L3.insert(7);
	// L3.insert(1);
	// L3.insert(9);
	// print(L3);
	// cout << "orderedList<int> L4 = L3" << endl;
	// orderedList<int> L4 = L3;
	// print(L4);
	// cout << "L3.replace(0, -1)" << endl;
	// L3.replace(0, -1);
	// print(L3);
	// cout << "L4 = L3" << endl;
	// L4 = L3;
	// print(L4);
	// cout << "L4.destroy()" << endl;
	// L4.destroy();
	// cout << "L4.empty() = " << L4.empty() << endl;
	// return 0;
}
