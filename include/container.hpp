#pragma once
#include <memory>

template <typename T>
struct Data1 {
	T value;
	struct Data1<T>* next;
};

template <typename T, class A = std::allocator<struct Data1<T>>>
class L1_Node {
    public:
	L1_Node(int value) {
		// Head = new struct Data1<T>;
		Head = Allocator.allocate(1);
		Head->value = value;
		Head->next = NULL;
		Tail = Head;
	}
	~L1_Node() {
		struct Data1<T>*Temp, *Before {};
		Temp = Head;
		  while (Temp) {
			Before = Temp;
			Temp = Temp->next;
			//delete Before;
                        if ( Before != Head ) {
			Allocator.deallocate(Before, 1);
                        }
		}
                Allocator.deallocate(Head, 1);
	}

	void Print();
	void Push_back(T value);

	int Size() {
		struct Data1<T>* Temp;
		int size{};
		Temp = Head;
		while (Temp) {
			size++;
			Temp = Temp->next;
		}
		return size;
	}

	T& operator[](int index) {
		struct Data1<T>* Temp;
		Temp = Head;
		int size{};
		while (Temp) {
			if (size == index - 1) {
				return Temp->value;
			}
			size++;
			Temp = Temp->next;
		}

		return Temp->value;
	}

    private:
	struct Data1<T>* Head {};
	struct Data1<T>* Tail {};
	A Allocator;
};

template <typename T, class A>
void L1_Node<T, A>::Push_back(T value) {
	struct Data1<T>* New;
	// New = new Data1<T>;
	New = Allocator.allocate(1);
	New->value = value;
	New->next = NULL;
	Tail->next = New;
	Tail = New;
}

template <typename T, class A>
void L1_Node<T, A>::Print() {
	struct Data1<T>* Temp;
	Temp = Head;
	while (Temp) {
		std::cout << Temp->value << " ";
		Temp = Temp->next;
	}
	std::cout << std::endl;
}

