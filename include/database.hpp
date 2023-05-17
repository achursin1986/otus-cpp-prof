#pragma once
#include <sqlite3.h>

#include <iostream>
#include <string>

namespace my {

std::string Create_Table(std::string&& name);
std::string Insert_Into(std::string&& table, int id, std::string&& value);
std::string Truncate_DB(std::string&& table);
std::string Intersection_DB();
std::string Symmetric_Diff_DB();

int callback(void* data, int argc, char** argv, char** azColName);

/*
class callback_ftr{
       public:
          callback_ftr() = default;
          static int callback (void* data, int argc, char** argv, char** azColName) {
                     std::cout << "arg count:" << argc;
                     for (int idx = 0; idx < argc; idx++) {
                              printf("%s |  %s",azColName[idx], argv[idx]);
                     } 
                     return ((callback_ftr*)data)->callback_aux(argc,argv,azColName);

          }
          std::string get_data(sqlite3* db, std::string& db_name) {
               int rc{};
               char* zErrMsg = nullptr;
               rc = sqlite3_open(db_name.c_str(), &db);
               if (rc) { throw std::runtime_error("Error opening/creating database file, code " + std::to_string(rc)); sqlite3_free(zErrMsg);}
               std::string output;
               //rc = sqlite3_exec(db, Intersection_DB().c_str(), callback, 0, &zErrMsg);
               rc = sqlite3_exec(db, "select * from A;", callback, 0, &zErrMsg);
               if (rc) { throw std::runtime_error("Error getting output, code " + std::to_string(rc)); sqlite3_free(zErrMsg);}
               std::string err(zErrMsg ? zErrMsg:"");
               sqlite3_close(db);
               if ( err == "" ) return output;
               else return "ERR "+err+"\n";

          }

       private:
         int callback_aux(int argc, char** argv, char** azColName){
                 // get output saved
                 //for (int idx = 0; idx < argc; idx++) {
                        //output += std::string(azColName[idx])+ " | " + std::string(argv[idx]) +"\n";
                   //     printf("%s |  %s",azColName[idx], argv[idx]);
                 //}
                 return 0;
          }


};
*/
class Database {
    public:
	static Database* GetDatabase(std::string&& name);
        static std::string Insert(std::string&& table, int id, std::string&& value);  
        static std::string Truncate(std::string&& table);
        static std::string Intersection();
        static std::string Symmetric_Difference(); 

    private:
	Database(std::string&& name);
	Database(Database& other) = delete;
	void operator=(const Database& other) = delete;

	static sqlite3* db;
	static Database* db_ptr;
        static std::string db_name;
};

}  // namespace my

