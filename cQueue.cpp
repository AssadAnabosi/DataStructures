#include <iostream>
using namespace std;
const int maxSize = 100;

template <class Q>
class queue{
	Q Queue[maxSize];
	unsigned int currentSize, frontIndex, rearIndex;
	public:
	queue(){
		currentSize = 0;
		frontIndex = 0;
		rearIndex = 0;
	}
	bool empty(){
		if(currentSize == 0)
			return 1;
		return 0;
	}
	
	bool full(){
		if(currentSize == maxSize)
			return 1;
		return 0;		
	}
	
	int size(){
		return currentSize;
	}
	
	Q front(){
		return Queue[frontIndex];
	}
	
	Q rear(){
		if (rearIndex == 0 || rearIndex == maxSize - 1){
			return Queue[rearIndex];
		}
		else
			return Queue[rearIndex-1];
	}
	
	void push(Q item){
		if (!full()){
			Queue[rearIndex] = item;
			if (rearIndex + 1 < maxSize)
				rearIndex++;
			else{
				if (currentSize + 1 == maxSize)
					rearIndex = maxSize - 1;
				else
					rearIndex = 0;
			}
			currentSize++;
		}
		else
			cout << "Full Queue" << endl;
	}
	void pop(){
		if (currentSize != 0){
			if (full())
				rearIndex = 0;
			if (frontIndex + 1 < maxSize)
				frontIndex++;
			else
				frontIndex = 0;
			currentSize--;
		}
	}
	void print(){
		if (empty())
			cout << "Empty Queue" << endl;
		else{
			int tmp = currentSize;
			int tmpIndex = frontIndex;
			while(tmp){
				cout << tmpIndex << "\t" << Queue[tmpIndex] << endl;
				if (tmpIndex + 1 < maxSize)
					tmpIndex++;
				else
					tmpIndex = 0;
				tmp--;
			}	
		}
	}
};

int main(){
	// system("color a");
	// queue <int> e;
	
	// e.print();
	
	// e.push(10);
	// e.push(20);
	// e.push(30);
	// e.print();
	// cout << "S = " << e.size() << endl;
	// cout << "E = " << e.empty() << endl;
	// cout << "F = " << e.full() << endl;
	// cout << "Front: " << e.front() << ", Rear: " << e.rear() << endl;
	
	// cout << "^^^^^^^^^^^ 10, 20, 30 ^^^^^^^^^^^" << endl;

	// e.pop();
	// e.print();
	// cout << "S = " << e.size() << endl;
	// cout << "E = " << e.empty() << endl;
	// cout << "F = " << e.full() << endl;
	// cout << "Front: " << e.front() << ", Rear: " << e.rear() << endl;
	
	// cout << "^^^^^^^^^^^ popped ^^^^^^^^^^^" << endl;

	// e.push(40);
	// e.print();
	// cout << "S = " << e.size() << endl;
	// cout << "E = " << e.empty() << endl;
	// cout << "F = " << e.full() << endl;
	// cout << "Front: " << e.front() << ", Rear: " << e.rear() << endl;
	
	// cout << "^^^^^^^^^^^ pushed ^^^^^^^^^^^" << endl;
	// e.push(50);
	// return 0;
}