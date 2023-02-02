#pragma once
#include <memory>
#include "allocator.hpp"

template <typename T>
struct Data1 {
	T value;
	struct Data1<T>* next;
};

template <typename T, unsigned int S, class A = std::allocator<struct Data1<T>>>
class L1_Node {
    public:
	struct Iterator {
		Iterator() : CurrentNode() {}

		Iterator(const Data1<T>* Node) : CurrentNode(Node) {}

		Iterator& operator=(Data1<T>* Node) {
			this->CurrentNode = Node;
			return *this;
		}
		Iterator& operator++() {
			if (CurrentNode) {
				CurrentNode = CurrentNode->next;
			}
			return *this;
		}
		Iterator operator++(int) {
			Iterator iterator = *this;
			++*this;
			return iterator;
		}
		bool operator!=(const Iterator& iterator) { return CurrentNode != iterator.CurrentNode; }

		int operator*() { return CurrentNode->value; }

	    private:
		const Data1<T>* CurrentNode;
	};

	L1_Node(int value) {
		Head = Allocator.allocate(1);
		Head->value = value;
		Head->next = NULL;
		Tail = Head;
                free = S - 1 ;
                s = S;
	}
	~L1_Node() {
		struct Data1<T>*Temp, *Before {};
		Temp = Head;
		while (Temp) {
			Before = Temp;
			Temp = Temp->next;
			if (Before != Head) {
				Allocator.deallocate(Before, 1);
			}
		}
		Allocator.deallocate(Head, 1);
	}

	void Print();
	void Push_back(T value);
	void Erase(int pos);

	const int Size() { return s; }
        template <unsigned int K, class B>
        // have a look here        
        L1_Node<T,S,A>& operator= (const L1_Node<T,K,B>& Other)  {
                                 struct Data1<T>* Temp{},*New{},*Temp1;
                                 if ( !Other.Head && !Other.Tail ) {
                                        std::exit(1);
                                 }
                                 Temp = Other.Head;//->next;
                                 Temp1 = Head;
                                 Head->value = Other.Head->value;

                                 while ( Temp1 ) {
                                      //New = Other.Allocator.allocate(1);
                                      //New->value = Temp->value;
                                      //New->next = NULL;
                                      //Temp1->next = New;
                                      Temp1->value = Temp->value;
                                      Temp1 = Temp1->next;
                                      Temp = Temp -> next;

                                 };

                                 //Tail = New;
                                 return *this;
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

    Iterator begin() { return Iterator(Head); }
    Iterator end()   { return Iterator(NULL); }
      struct Data1<T>* Head {};
      struct Data1<T>* Tail {};
      A Allocator;
      int s{};
      int free{};

    private:
      /*struct Data1<T>* Head {};
      struct Data1<T>* Tail {};
      A Allocator;
      int s{};
      int free{};*/
};


// Have a look here
template <typename T,unsigned int S, class A>
void L1_Node<T,S,A>::Push_back(T value) {
        free--;
        if ( ! free ) {
                s++;
        }
        if ( s > S ) {
            L1_Node<T, S+1, MyAllocator<Data1<T>, S+1>> temp(0);
            for (auto i = this->begin(), end = this->end(); i != end; ++i) {
               temp.Push_back(*i); 
            }
            *this = temp;                           

        }
         
	struct Data1<T>* New;
	New = Allocator.allocate(1);
	New->value = value;
	New->next = NULL;
	Tail->next = New;
	Tail = New;
}






template <typename T, unsigned int S, class A>
void L1_Node<T,S,A>::Print() {
        for (auto i = this->begin(), end = this->end(); i != end; ++i) {
               std::cout << *i << " ";
        }
	std::cout << std::endl;
}

template <typename T, unsigned int S, class A>
void L1_Node<T,S,A>::Erase(int pos) {
	struct Data1<T>*Temp, *After, *Before {};
	int i{};
	Temp = Head;
	while (Temp) {
		if (i == pos - 2) {
			Before = Temp;
		}
		After = Temp->next;
		if (i == pos - 1) {
			if (Before) {
				Before->next = After;
			} else {
				Head = After;
			}

			Allocator.deallocate(Temp, 1);
                        free++;
			return;
		}
		Temp = Temp->next;
		i++;
	}
}
