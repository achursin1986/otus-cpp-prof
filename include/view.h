#pragma once
#include "model.h"
#include "common.h"

class View: public Callback {
    public:
        View(const Model &model) {
            this->model = model;
        }
        View() {}
        void SetModel(const Model &model) {
            this->model = model;
        }
        void Render() {
            // present data in GUI
        }
        /*void callback()
        {
             this->Render();
        }*/
        /* static void callback(void* obj) {
              View* ptr_this= reinterpret_cast<View*>(obj)
              ptr_this->Render();
         } */


    private:
        Model model;
};
