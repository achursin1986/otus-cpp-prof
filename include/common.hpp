#pragma once 


struct command {
    command() = delete;
    command(std::string _data): data(_data){};
    std::string data;

};

struct save { };

struct drain{ };


class ops { 

     public:
       virtual void event(struct command){};
       virtual void event(struct save){};
       virtual void event(struct drain){};       

       virtual ~ops(){};
};
