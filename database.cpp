#include <database.hpp>
#include <exception>

namespace my {

std::string Create_Table(std::string&& name) {
	return "CREATE TABLE IF NOT EXISTS " + name +
	       " ("
	       "ID INT PRIMARY KEY     NOT NULL,"
	       "NAME           TEXT    NOT NULL);";
};

std::string Insert_Into(std::string&& table, int id, std::string&& value) {
        return "INSERT INTO " + table + " VALUES(" + std::to_string(id) +", " + "'" + value + "'" +");";
};

std::string Truncate_DB(std::string&& table) {
        return "DELETE from " + table + ";";

};

std::string Intersection_DB() {
       return "SELECT * FROM A WHERE id IN (SELECT id FROM A INTERSECT SELECT id FROM B)"
              " UNION ALL "
              "SELECT * FROM B WHERE id IN (SELECT id FROM A INTERSECT SELECT id FROM B);";

};

std::string Symmetric_Diff_DB() {
       return "SELECT t.id,t.name"
              " FROM"
                   " A t "
               "LEFT OUTER JOIN"
                   " B l "
               "ON t.id = l.id"
               " WHERE "
               "l.id IS NULL"
               " UNION ALL "
               "SELECT t.id,t.name"
              " FROM"
                   " B t "
               "LEFT OUTER JOIN"
                   " A l "
               "ON t.id = l.id"
               " WHERE "
               "l.id IS NULL";

};

int callback(void* NotUsed, int argc, char** argv, char** azColName) { 
for (int idx = 0; idx < argc; idx++) {
                              printf("%s |  %s",azColName[idx], argv[idx]);
}


return 0; 
}

Database::Database(std::string&& name) {
	int rc{};
	char* zErrMsg = nullptr;
        sqlite3* db = nullptr;
        rc = sqlite3_config(SQLITE_CONFIG_MULTITHREAD);
        if (rc) { throw std::runtime_error("Error setting sql params, code " + std::to_string(rc)); sqlite3_free(zErrMsg);}
	rc = sqlite3_open(name.c_str(), &db); 
	if (rc) { throw std::runtime_error("Error opening/creating database file, code " + std::to_string(rc)); sqlite3_free(zErrMsg);}
        db_name = name;
	rc = sqlite3_exec(db, Create_Table("A").c_str(), callback, 0, &zErrMsg); 
	if (rc) { throw std::runtime_error("Error checking/creating table A, code " + std::to_string(rc)); sqlite3_free(zErrMsg);}
	rc = sqlite3_exec(db, Create_Table("B").c_str(), callback, 0, &zErrMsg);
	if (rc) { throw std::runtime_error("Error checking/creating table B, code " + std::to_string(rc)); sqlite3_free(zErrMsg);}
        sqlite3_close(db);
}

Database* Database::GetDatabase(std::string&& name) {
	if (db_ptr == nullptr) {
		db_ptr = new Database(std::move(name));
	}
	return db_ptr;
}

std::string Database::Insert(std::string&& name, int id, std::string&& value) {
        int rc{};
        char* zErrMsg = nullptr;
        sqlite3* db = nullptr;
        rc = sqlite3_open(db_name.c_str(), &db);
        if (rc) { throw std::runtime_error("Error opening/creating database file, code " + std::to_string(rc)); sqlite3_free(zErrMsg);}
        rc = sqlite3_exec(db, Insert_Into(std::move(name),id,std::move(value)).c_str(), callback, 0, &zErrMsg);
        if (rc) {
               std::string err(zErrMsg ? zErrMsg:"");
               sqlite3_free(zErrMsg);
               sqlite3_close(db);
               if ( err == "" ) return err;
               else return "ERR "+err+"\n";
        }
        sqlite3_close(db);
        return "OK\n";
        
}

std::string Database::Truncate(std::string&& name) {
         int rc{};
         char* zErrMsg = nullptr;
         sqlite3* db = nullptr;
         rc = sqlite3_open(db_name.c_str(), &db);
         if (rc) { throw std::runtime_error("Error opening/creating database file, code " + std::to_string(rc)); sqlite3_free(zErrMsg);}
         rc = sqlite3_exec(db, Truncate_DB(std::move(name)).c_str(), callback, 0, &zErrMsg);
        if (rc) {
               std::string err(zErrMsg ? zErrMsg:"");
               sqlite3_free(zErrMsg);
               if ( err == "" ) return err;
               else return "ERR "+err+"\n";
        }
        sqlite3_close(db);
        return "OK\n";

}

std::string Database::Intersection() {
         int rc{};
         char* zErrMsg = nullptr;
         sqlite3* db = nullptr;
         rc = sqlite3_open(db_name.c_str(), &db);
         if (rc) { throw std::runtime_error("Error opening/creating database file, code " + std::to_string(rc)); sqlite3_free(zErrMsg);}
         std::string output;
         sqlite3_stmt *response;
         sqlite3_prepare(db, Intersection_DB().c_str(), -1, &response, NULL);
         if ( rc ) {
                 std::string err(zErrMsg ? zErrMsg:"");
                 sqlite3_free(zErrMsg);
                 if ( err == "" ) return err;
                 else return "ERR "+err+"\n";
         }
         while (sqlite3_step(response) == SQLITE_ROW) {
              output += std::string((char*)sqlite3_column_text(response, 0))+"|" + std::string((char*)sqlite3_column_text(response, 1))  + '\n';
         } 
         sqlite3_close(db);
         return output+"OK\n";
        
}       

std::string Database::Symmetric_Difference() {
        int rc{};
         char* zErrMsg = nullptr;
         sqlite3* db = nullptr;
         rc = sqlite3_open(db_name.c_str(), &db);
         if (rc) { throw std::runtime_error("Error opening/creating database file, code " + std::to_string(rc)); sqlite3_free(zErrMsg);}
         std::string output;
         //rc = sqlite3_exec(db, Symmetric_Diff_DB().c_str(), callback, 0, &zErrMsg);
         sqlite3_stmt *response;
         rc = sqlite3_prepare(db, Symmetric_Diff_DB().c_str(), -1, &response, NULL);
         if ( rc ) {
                 std::string err(zErrMsg ? zErrMsg:"");
                 sqlite3_free(zErrMsg);
                 if ( err == "" ) return err;
                 else return "ERR "+err+"\n";
         }
         while (sqlite3_step(response) == SQLITE_ROW) {
              output += std::string((char*)sqlite3_column_text(response, 0))  +"|" + std::string((char*)sqlite3_column_text(response, 1))+ '\n';
         }
         sqlite3_close(db);
         return output+"OK\n"; 
}


//sqlite3* Database::db = nullptr;
Database* Database::db_ptr = nullptr;
std::string Database::db_name = "";

}  // namespace my
