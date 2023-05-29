#include "elevator.h"
#include <iostream>
#include <unistd.h>
#include <condition_variable>
using namespace std;

extern condition_variable cv;
extern mutex m;



int 
Elevator::getfloor()
{
    return current_floor;
}

void 
Elevator::display_floor()
{
    cout <<"[" << getfloor() << "]"<<flush;
}

void 
Elevator::move(int a)
{
    setfloor(a);
    display_floor();
}




void 
Elevator::setfloor(int a)
{   
    int t = current_floor;
    // display_floor();
    if(t - a < 0){
        for(int i=0; i<a-t; i++){
            sleep(1);
            current_floor += 1;
            // cout<<"\b\b\b", display_floor();
        }
    }
    else if(t - a > 0){
        for(int i=0; i<t-a; i++){
            sleep(1);
            current_floor -= 1;
            // cout<<"\b\b\b", display_floor();
            
        }
    }
    
}

pair<Elevator*,int>
Building::SeletElevator(Person* a)
{   
    int mindiff =  maxfloor+1;
    Elevator* ret;
    int idx;
    for(int i=0; i<_elist.size(); i++){
        if(_using[i]) continue;

        if(abs(_elist[i]->getfloor()-a->getstart()) < mindiff){
            mindiff = abs(_elist[i]->getfloor()-a->getstart());
            idx = i;
            ret = _elist[i];
        }
    }
    
    return {ret,idx};
}

void 
Building::NewElevator(Elevator* ne)
{   
    if(!ne){
        return;
    }
    // mutex nm;
    _elist.push_back(ne);
    _using.push_back(false);

}




int Building::getrequestnum()
{
    return requset_nums;
}

void Building::setrequestnum(int n)
{
    requset_nums = n;
}

void Building::Elevateperson(Person *a)
{   
    //p_i is for record the total valid request num.
    int p_i = Person::getcnt();

    // _allusing is a flag , return true if all the elevator is being used.
    // mutex.lock ==> then push this thread to waiting queue
    while(_allusing()){
        unique_lock<mutex> ul(m);
        cv.wait(ul);
    }

    //select a elevator
    auto [tmp , idx] = SeletElevator(a);
    while(_using[idx]){

    }

    _using[idx] = true;
    //moving to start floor
    tmp->setfloor(a->getstart());
    cout << endl << "elevator [" << idx << "] arrives start floor for valid request [" << p_i << "] !!" <<endl;

    //moving to end floor
    tmp->setfloor(a->getend());
    cout << endl << "elevator [" << idx << "] arrives end floor for valid request [" << p_i << "] !!" <<endl;
    _using[idx] = false;
    // any thread finishing the request will notify the thread in waiting queue.
    cv.notify_one();
}

void 
Building::printstatus()
{   
    
    for(int i=0; i<_elist.size(); i++){
        cout << "[" << _elist[i]->getfloor() << "]";
    }
    cout<<endl;
 
}

bool Building::_allusing()
{   
    for(int i=0; i<_using.size(); i++){
        if(!_using[i]) return false;
    }
    return true;
}

int 
Person::getstart()
{
    return _floor_start;
}

int 
Person::getend()
{
    return _floor_end;
}

int Person::getcnt()
{
    return p_cnt;
}
