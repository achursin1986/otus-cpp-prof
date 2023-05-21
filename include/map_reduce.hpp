#pragma once 
#include <sstream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <future>
#include <algorithm>


typedef std::pair<std::ifstream::pos_type, std::ifstream::pos_type> FR;
static std::vector<FR> Ranges;
static std::unordered_map<int,std::vector<std::string>> Strings;
static std::unordered_multimap<char,int> Shuffle;  


void Split(char* filename, int size) {
      std::filesystem::path p{filename};
      char c;
      int index{};
      std::ifstream::pos_type threshold = std::filesystem::file_size(p) / size;
      std::ifstream file(filename, std::ios::binary);
      #ifdef DEBUG
      std::cout << "Threshold: " << threshold << std::endl;
      #endif
      std::ifstream::pos_type start{},end{threshold};
      for ( int i =0; i<size; i++) {
              file.clear();
              file.seekg(end);
              // peek gets next so is a good match to tellg 
              while( !file.eof() && file.peek() != '\n') {
                           file.ignore(1);
                           
              }
              end = file.tellg();
              if ( start >= 0 && start != std::filesystem::file_size(p)-1 && start != std::filesystem::file_size(p)) { 
                          if ( end < 0 ) end = std::filesystem::file_size(p)-1; 
                          Ranges.push_back(std::make_pair(start,end));
                          file.ignore(1);
                          start = file.tellg(); 
                          end = start + threshold;
               } else break;
      }

       for ( auto k: Ranges ) {
               std::string temp;
               std::vector<std::string>temp_vec;
               #ifdef DEBUG
               std::cout << k.first << " " << k.second << std::endl;
               #endif
               std::ifstream file(filename, std::ios::binary);
               file.seekg(k.first);
               Strings[index] = temp_vec;
               while ( std::getline(file,temp) ) {
                      Strings[index].emplace_back(std::move(temp));
                      if ( file.tellg() >= k.second ) break;
               }
               index++;
      }
      

}


void Map(int size, int curr_index) {
         std::vector<std::future<std::unordered_map<char,int>>> Results;

         for ( int i=0; i<size; i++) {
              Results.push_back(std::async(std::launch::async,[size,curr_index,i](){ 
                  std::vector<char> temp;
                  std::unordered_map<char,int> result;
                  for ( auto k: Strings[i] ) {
                            if ( k.size() >= curr_index ) temp.push_back(k[curr_index-1]);
                  }
                  std::sort(temp.begin(),temp.end());
                  if ( temp.empty() ) return result; 
                  char comp = temp[0];
                  result[temp[0]]++;
                  for (int i=1; i<temp.size(); i++) {
                    if ( temp[i] == comp ) result[temp[i]]++;
                    else { comp = temp[i]; result[temp[i]]++; }      

                  }
                  return result; 
             }));
         }


         for ( int i=0; i<size; i++) {
               for (auto k: Results[i].get() ) {
                  #ifdef DEBUG
                  std::cout << k.first << " " << k.second << std::endl;
                  std::cout << "-----" << std::endl;
                  #endif
                  if ( !k.first || !k.second ) continue;  
                  Shuffle.insert(std::pair<char,int>(k.first,k.second));
               }
               
         }

}


bool Reduce (int size) { 
        int step =  Shuffle.size() / size;
        if ( ! step ) { step =  Shuffle.size(); size=1;};
        std::vector<std::future<bool>> Results;
        for ( int i=0; i<size; i++) {
             Results.push_back(std::async(std::launch::async,[i,step](){
                    auto Iterator = Shuffle.begin();
                    for ( int l=0; l<= i*step; l++) Iterator++;
                    if ( i == 0 ) Iterator = Shuffle.begin();
                    for ( int j=0; j<step; j++) {
                         if ( Iterator == Shuffle.end() ) break;
                         if ( Shuffle.count((*Iterator).first) > 1 || (*Iterator).second > 1 ) return false;
                         Iterator++;
                    }      
                    return true; 
             }));
       }

       for ( int i=0; i<size; i++) {
            if ( ! Results[i].get() ) return false;  

       }
       return true;    

} 






