#include <iostream>
#include <map>

#include "allocator.hpp"
#include "utils.hpp"
#include "serial_container.hpp"



int main() {
        std::map<int, int> map;
	std::map<int, int, std::less<int>, MyAllocator<int,10>> map_test;
        S_Node<int> cont(10);
        S_Node<int,MyAllocator<int,10>> cont_test(10); 
	for (int i = 0; i < 10; ++i) {
		map_test.insert({i, factorial(i)});
                map.insert({i, factorial(i)});
               // if ( i ) {
                     cont.Push_back(i);
                     cont_test.Push_back(i);
               // }
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


        std::cout << "Custom container custom allocator - remove 3rd element:" << std::endl;
        cont_test.Erase(3);
        cont_test.Print();
        cont_test.Push_back(101);
        cont_test.Push_back(111);
        std::cout << "Custom container custom allocator - push 2 new elements with expanding:" << std::endl;
        cont_test.Print();
        std::cout << "Size of above is: " << cont_test.Size() << std::endl;
        
        std::cout << "One more time same thing but using iterator: " << std::endl;
        for (auto i = cont_test.begin(), end = cont_test.end(); i != end; ++i) {
               std::cout << *i << " ";
        }
        std::cout << std::endl;
        return 0;


}
