#pragma once

#include <list>
#include <memory>


class Shape {

    public:
      Shape() {};
      int id;
     

};

class Line: public Shape  {
   public:
    typedef std::list<std::pair<int,int>> Line_type;

    Line(int x1, int y1, int x2, int y2,int id_) {

         line.push_back(std::make_pair(x1,y1));
         line.push_back(std::make_pair(x2,y2));
         id = id_;
    }

     Line_type* Get() {
           return &line;
    }

    private:
       Line_type line;
};


class Document {
    public:

       typedef std::list<std::unique_ptr<Shape>> Shapes;
       Document() {};
       void Add_Shape(std::unique_ptr<Shape> shape) {
          figures.push_back(std::move(shape));

       };
       
       void Remove_Last() {
          figures.pop_back();

       };
       void Remove_Id(int id) {

          Shapes::iterator range_begin = figures.begin();
          std::advance(range_begin,id - 1);
          figures.erase(range_begin,range_begin);

       };
       Shapes* Get() {
          return &figures;
       }

    private:
     Shapes figures;
};
