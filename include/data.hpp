#pragma once
#include<string>
#include<vector>
#include <chrono>
#include "common.hpp"
#include <fstream>


void print(std::ostream &os1, std::ostream &os2, const std::string &str)
{
    os1 << str;
    os2 << str;
}




class data: public ops {
     

    public:

      void event(const struct command& input) { 
          append(input.data);
      };
      void event(const struct save&) {
          save();
      };
      void event(const struct drain&) {
          drain();
      };


      void append(std::string command) {
            if ( commands.empty() ) {
               current_time = std::time(nullptr);
            }

            commands.push_back(command);

      };
      void drain() {
            commands.clear();

      };
      void save() {
        std::string filename = "bulk" + std::to_string(current_time) + ".log";
        std::ofstream output_file(filename);
        print(output_file,std::cout, "bulk: ");
        for (int i =0; i<commands.size(); i++ ) {
             print(output_file,std::cout, commands[i]);
             if ( i != commands.size() -1 )  {
                   print(output_file,std::cout, ",");
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
