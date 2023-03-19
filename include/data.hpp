#pragma once
#include<string>
#include<vector>
#include <chrono>
#include "common.hpp"
#include <fstream>

class data: public ops {
     

    public:

      void event(struct command input) { 
          append(input.data);
      };
      void event(struct save) {
          save();
      };
      void event(struct drain) {
          drain();
      };


      void append(std::string& command) {
            if ( !commands.size() ) {
               current_time = std::time(0);
            }

            commands.push_back(command);

      };
      void drain() {
            commands.clear();

      };
      void save() {
        std::string filename = "bulk" + std::to_string(current_time) + ".log";
        std::ofstream output_file(filename);
        output_file << "bulk: ";
        std::cout << "bulk: ";
        for (int i =0; i<commands.size(); i++ ) {
             output_file << commands[i];
             std::cout << commands[i];
             if ( i != commands.size() -1 )  {
                  output_file << ",";
                   std::cout << ",";
             } else {
                    output_file << "\n";
                   std::cout << std::endl;
             }  
        } 
        output_file.close();
        drain(); 
      };


    private:
      std::time_t current_time;
      std::vector<std::string> commands;


};
