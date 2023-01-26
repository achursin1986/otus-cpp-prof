#include <iostream>
#include <map>

#include "allocator.hpp"
#include "utils.hpp"
#include "container.hpp"



int main() {
        std::map<int, int> map;
	std::map<int, int, std::less<int>, MyAllocator<struct Data1<int>,10>> map_test;
        L1_Node<int> cont(0);
        L1_Node<int,MyAllocator<struct Data1<int>,10>> cont_test(0); 
	for (int i = 0; i < 10; ++i) {
		map_test.insert({i, factorial(i)});
                map.insert({i, factorial(i)});
                if ( i ) {
                     cont.Push_back(i);
                     cont_test.Push_back(i);
                }
	}
        std::cout << "Default map allocator:" << std::endl;
        for (const auto& v : map) {
                 std::cout << v.first << ' ' << v.second << ' ' << std::endl;
         }
        std::cout << std::endl;

        std::cout << "Custom map allocator:" << std::endl;
	 for (const auto& v : map_test) {
		 std::cout << v.first << ' ' << v.second << ' ' << std::endl;
	 }
	std::cout << std::endl; 

        std::cout << "Custom container default allocator:" << std::endl;
	cont.Print();
        std::cout << "Custom container custom allocator:" << std::endl;
        cont_test.Print();
        return 0;
}
