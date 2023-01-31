#pragma once

#include <memory>

#include "allocator.hpp"

/* Serial container implementation, element index starts with 1 */

template <typename T, class A = std::allocator<T>>
class S_Node {
    public:
	struct Iterator {
		Iterator() : CurrentNode() {}

		Iterator(const T* Node) : CurrentNode(Node) {}

		Iterator& operator=(T* Node) {
			this->CurrentNode = Node;
			return *this;
		}
		Iterator& operator++() {
			if (CurrentNode) {
				CurrentNode++;
			}
			return *this;
		}
		Iterator operator++(int) {
			Iterator iterator = *this;
			++*this;
			return iterator;
		}
		bool operator!=(const Iterator& iterator) { return CurrentNode != iterator.CurrentNode; }

		int operator*() { return *CurrentNode; }

	    private:
		const T* CurrentNode;
	};

	S_Node(int size) : capacity(size), free(size) {
		// array = new T[size];
		array = Allocator.allocate(capacity);
	}
	~S_Node() {
		// delete []array;
		Allocator.deallocate(array, capacity);
	}
	void Insert(int pos, const T& value);

	void Print();

	void Erase(int pos);

	void Push_back(T value);

	int Size() { return capacity - free; }

	T& operator[](int index) {
		if (index <= 0 || index > capacity - free) {
			std::cout << "Out of boundary access attempt, 1st element" << std::endl;
			std::exit(1);
		}
		return array[index - 1];
	}
	T& operator[](int index) const {
		if (index <= 0 || index > capacity - free) {
			std::cout << "Out of boundary access attempt, 1st element" << std::endl;
			std::exit(1);
		}
		return array[index - 1];
	}

	Iterator begin() { return Iterator(array); }
	Iterator end() { return Iterator(array + capacity - free); }

    private:
	// service funcs
	T* Expand05(T* array);
	void Shift(T* array, int pos);

	int capacity = 0;
	int free = 0;
	T* array;
	A Allocator;
};

template <typename T, class A>
T* S_Node<T, A>::Expand05(T* array) {
	// T* temp = new T[capacity + capacity/2];
	T* temp = Allocator.allocate(capacity + capacity / 2);
	for (int i = 0; i < capacity; i++) {
		temp[i] = array[i];
	}
	free = capacity / 2;
	capacity = capacity + capacity / 2;
	// delete[] array;
	Allocator.deallocate(array, 2*capacity / 3);
	return temp;
}

template <typename T, class A>
void S_Node<T, A>::Shift(T* array, int pos) {
	if (pos <= 0 || pos > capacity - free) {
		std::cout << "Out of boundary access attempt" << std::endl;
		return;
	}
	for (int i = capacity - 1; i >= pos; i--) {
		array[i] = array[i - 1];
	}
}

template <typename T, class A>
void S_Node<T, A>::Push_back(T value) {
	if (!free) {
		array = Expand05(array);
		array[capacity - free] = value;
		free--;

	} else {
		array[capacity - free] = value;
		free--;
	}
}

template <typename T, class A>
void S_Node<T, A>::Erase(int pos) {
	if (pos <= 0 || pos > capacity - free) {
		std::cout << "Out of boundary access attempt" << std::endl;
		return;
	}
	for (int i = pos - 1; i < capacity - 1; i++) {
		array[i] = array[i + 1];
	}
	free++;
}

template <typename T, class A>
void S_Node<T, A>::Print() {
	for (int i = 0; i < capacity - free; i++) {
		if (i == capacity - 1) {
			std::cout << array[i];
			break;
		}
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

