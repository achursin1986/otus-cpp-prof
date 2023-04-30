#pragma once
#include<string>
#include<vector>
#include <chrono>
#include "common.hpp"
#include <fstream>
#include <sstream>
#include "threadpool.hpp"



void print(std::vector<std::string> commands, std::time_t current_time){
    my::File_writer.Add_task([commands,current_time](){
                 std::stringstream ss;
                 ss << std::this_thread::get_id();
                 std::string filename = "bulk" + std::to_string(current_time) + "_" + ss.str() + ".log";           
                 std::ofstream output_file(filename, std::ios_base::app);
                 output_file << "bulk: ";
                 for (int i =0; i<commands.size(); i++ ) {
                 output_file << commands[i];
                 if ( i != commands.size() -1 )  {
                         output_file << ",";
                  } else {
                         output_file << "\n";
                  }
                 }
                 output_file.close();                 

               });

    my::Console_writer.Add_task([commands,current_time](){ 
                std::cout << "bulk: ";
               for (int i =0; i<commands.size(); i++ ) {
                 std::cout << commands[i];
                 if ( i != commands.size() -1 )  {
                         std::cout << ",";
                  } else {
                         std::cout << "\n";
                  }
               }

           }); 

};




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

      data() = default;
      ~data() {  
              // save leftovers on disconnect         
              if ( ! commands.empty() ) save();

      }

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
        print(commands,current_time);
        drain(); 
      };


    private:
      std::time_t current_time;
      std::vector<std::string> commands;


};


