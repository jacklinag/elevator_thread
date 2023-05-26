# elevator_thread
The header file elevator.h includes three classes, which are building, elevator and person.
  Class person can be viewes as a request from a persoom a start_floor to end_floor.
  Class elevator include a private int data member, current_floor, which is the current floor elevator at. It aslo has a setter, getter and a display_floor() to print the current_floor in format of "[current_floor]".
  Class Building contains a vector<Elevator*> to record the elevator of building, and a newElevator(Elevator*) to new a elevator for scalibility. Building can add one/multi request by user's input, If the input contain a request number larger than elevator nums of building, 
the extra request should be waiting for the formmer request complete. I setup a critical section design by using vector<bool> _using and int request_num to force extra request waiting. 
  Every valid reuqest creates a thread to make a building b call the function Elevatorperson(). Elevateperson() contains three steps:
  1. select a elevator* tmp in _elist with it's idx returned.
  2. set tmp to start floor
  3. set tmp to end floor 
  
 Note:
  If a certain elevator is being used, _using[idx] is set to true and CANNOT be selected by other request! if all elements of _using is true, then the request is blocking outside the _elsit.
  If request contains invalid inputs that the thread is created to cerr a error message. Elevatorperson() would not be called.
  I tried to ues a mutex lock in library but failed. Just not knowing how to lock the different shared datas in a class::vector<Elevator*>. the problem is i dont want to lock the whole list cuz avalible elevator should be selected!
  So i finally decided to design the entry and exit section in 
  1. building::selectElevator()
  2. CmdFunc() which thread execute.
 
