#include "elevator.h"
#include <iostream>
#include <unistd.h>
using namespace std;


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
    int mindiff =  maxfloor;
    Elevator* ret;
    int idx;
    for(int i=0; i<_elist.size(); i++){
        if(_using[i]) continue;

        if(abs(_elist[i]->getfloor()-a->getstart()) <= mindiff){
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

void 
Building::Elevateperson(Person* a)
{   
    int p_i = Person::getcnt();
    //select a elevator
    while(requset_nums>_elist.size()){
        
    }
    auto [tmp , idx] = SeletElevator(a);
    while(_using[idx]){

    }
    _using[idx] = true;
    //moving to start floor
    tmp->setfloor(a->getstart());
    cout << endl << "elevator [" << idx << "] arrives start floor for person[" << p_i << "] !!" <<endl;

    //moving to end floor
    tmp->setfloor(a->getend());
    cout << endl << "elevator [" << idx << "] arrives end floor for person[" << p_i << "] !!" <<endl;
    _using[idx] = false;
}

void 
Building::printstatus()
{   
    for(int i=0; i<_elist.size(); i++){
        cout << "[" << _elist[i]->getfloor() << "]";
    }
    cout<<endl;
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
