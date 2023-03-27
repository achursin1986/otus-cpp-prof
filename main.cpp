#include <iostream>
#include <string>
#include <chrono>
#include "data.hpp"
#include "parser.hpp"
#include "common.hpp"


static std::string zero = "null";


int main(int argc, char* argv[] ) {

    if ( argc != 2 ) {
           std::cout << "need 1 argument" << std::endl;
           return 1;

    }


    int N = std::atoi(argv[1]);
    std::string input;


    data Data;
    parser Parser("{","}","cmd", N ,&Data);

    //std::cout << "Start entering commands" << std::endl;

    while ( true ) {
           std::cin >> input;
           if ( std::cin.eof() ) { Parser.check(zero); break; }
           Parser.check(input);
            
   }

}
