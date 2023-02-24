#pragma once
#include "model.h"
#include "view.h"

class Controller: public Callback {
    public:
        Controller(const Model &model, const View &view) {
          this->SetModel(model);
          this->SetView(view);
        }
        void SetModel(const Model &model) {
            this->model = model;
        }
        void SetView(const View &view) {
            this->view = view;
        }


        void OnLoad() {
            this->view.Render();
        }
        void callback() {
            this->OnLoad();
        }
    private:
        Model model;
        View view;
};
