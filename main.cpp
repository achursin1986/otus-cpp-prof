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
    Controller controller(model, view);
    model.RegisterDataChangeHandlers(&controller);
    /* GUI thread using view 
      gets data from GUI and calls methods of Model through Controller 
      controller.model.LoadData
      invokes controller -> OnLoad()

      controller.model.SaveData
      no need to update

      controller.model.NewData
      invokes controller -> OnLoad()

      controller.model.AddLine(x1, y1, x2, y2, id)
      invokes controller -> OnLoad()
      
      controller.model.RemoveLast
      invokes controller -> OnLoad();
    */
    return 0;
}
