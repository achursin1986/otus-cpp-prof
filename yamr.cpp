#include<iostream>
#include<map_reduce.hpp>
#include <filesystem>



int main(int argc, char* argv[]) {
       int i{1};
       if ( argc != 4 ) {
             std::cerr << "Usage: yamr <src> <mnum> <rnum>" << std::endl;
             return 1;
        }

        if ( std::atoi(argv[2]) <= 0 ||  std::atoi(argv[3]) <= 0) { 
             std::cerr << "nums can't be zero or minus" << std::endl;
             return 1;
        } 

       // Split, result is Strings ready for Map  
       Split(argv[1],std::atoi(argv[2]));
       #ifdef DEBUG
       for (auto k: Strings) {
           for ( auto m: k.second ) std::cout << m << " " ;
           std::cout << std::endl;
       }
       #endif  

 
       while ( true ) {

            // Map, result is Shuffle
            Map(Ranges.size(), i);             
            // Check result of Reduce, stop to report result
            if ( Reduce(std::atoi(argv[3])) ) break;
            Shuffle.clear();
            i++;
            if ( i > 345) { std::cout << "Bigger than the biggest email looks like, need to check input data" << std::endl; break; return 0;}
       }

       std::cout << "Minimum prefix length: " << i <<  std::endl;

return 0;

}



