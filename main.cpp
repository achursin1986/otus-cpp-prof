#include <iostream>
#include "view.h"
#include "model.h"
#include "controller.h"
#include "common.h"

// include graphics


/*void DataChange() {
  //std::cout << "Render" << std::endl;
  
}*/

int main() {
    Model model;
    View view(model);
    model.RegisterDataChangeHandlers(&view);
    Controller controller(model, view);
    /* GUI thread 
      gets data from GUI and calls methods of Model 
      LoadData
      controller.OnLoad()
      SaveData

      NewData
      controller.OnLoad()
      AddLine
      controller.OnLoad()
      RemoveLast
      controller.OnLoad();
    */
    return 0;
}
