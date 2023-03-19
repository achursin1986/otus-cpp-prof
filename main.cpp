#include <iostream>
#include <string>
#include <chrono>
#include "data.hpp"
#include "parser.hpp"
#include "common.hpp"





int main() {

    int N;
    std::string input;

    std::cout << "Enter N" << std::endl;  
    std::cin >> N;

    data Data;
    parser Parser("{","}","cmd", N ,&Data);

    std::cout << "Start entering commands" << std::endl;

    while ( true ) {
           std::cin >> input;
           if ( std::cin.eof() ) { Parser.check("null"); break; }
           Parser.check(input);
            
   }

}
