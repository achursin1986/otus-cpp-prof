#include <iostream>

#include "allocator.hpp"
#include "container.hpp"

int main() {
	L1_Node<int, 10, MyAllocator<Data1<int>, 10>> cont_test(0);
	for (int i = 0; i < 10; ++i) {
		if (i) {
			cont_test.Push_back(i);
		}
	}
	cont_test.Print();

	std::cout << "Custom container custom allocator - remove 3rd element and add 101:" << std::endl;
	cont_test.Erase(3);
        cont_test.Push_back(101);
	cont_test.Print();
	/*cont_test.Push_back(101);
	cont_test.Push_back(111);
	std::cout << "Custom container custom allocator - push 2 new elements with expanding:" << std::endl; */
	//cont_test.Print();
	return 0;
}
