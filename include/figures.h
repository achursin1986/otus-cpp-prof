#pragma once

#include <list>
#include <memory>


class Shape {

    public:
      Shape() {};

};

class Line: public Shape  {
   public:
    typedef std::list<std::pair<int,int>> Line_type;

    Line(int x1, int y1, int x2, int y2) {

         line.push_back(std::make_pair(x1,y1));
         line.push_back(std::make_pair(x2,y2));
    }

     Line_type* Get() {
           return &line;
    }

    private:
       Line_type line;
};


class Document {
    public:

       typedef std::list<std::unique_ptr<Line>> Lines;
       Document() {};
       void Add_Line(int x1,int y1,int x2,int y2) {
          figures.push_back(std::make_unique<Line>(Line(x1,y1,x2,y2))); 
          
       };
       void Remove_Last() {
          figures.pop_back();

       };
       Lines* Get() {
          return &figures;
       }

    private:
     Lines figures;
};
