#pragma once 


struct command {
    command() = delete;
    command(std::string&& _data): data(std::move(_data)){};
    std::string data;

};

struct save { };

struct drain{ };


class ops { 

     public:
       virtual void event(const struct command&){};
       virtual void event(const struct save&){};
       virtual void event(const struct drain&){};       

       virtual ~ops(){};
};
