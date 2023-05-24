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

	//static sqlite3* db;
	static Database* db_ptr;
        static std::string db_name;
};

}  // namespace my

