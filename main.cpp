#include "elevator.h"
#include <iostream>
#include <string>
#include <thread>
#include <sys/wait.h>
#include <queue>
#include <mutex>
#include <unistd.h>
using namespace std;

Building* b = new Building(10);

void cmdFunc(int i, int x,int y){

    if(x>10 || x<0 || y>10 || y<0){
        cerr<< "person ["<<i<<"] has invalid input!!"<<endl;
        return;
    }
    else if(x==y){
        cerr<<"you are already at end floor!"<<endl;
        return;
    }
    else{
        b->requset_nums+=1;
        Person* a = new Person(x,y);
        b->Elevateperson(a);
        delete a;
        b->requset_nums-=1;
        return;
    }
    cout<<"?"<<endl;
}

int main(){
    Elevator* elevator1 = new Elevator(0);
    Elevator* elevator2 = new Elevator(0);
    b->NewElevator(elevator1);
    b->NewElevator(elevator2);
    
    while(true){
        cout<< "input e for elevate , s for check elevators' status"<<endl;
        string str;
        cin >> str;
        if(str.size()!=1){
            cerr<< "error command!! plz reinput again"<<endl;
        }
        else if(str[0]=='e'){
            cout<< "how many people are requeset elevators?"<<endl;
            int n;
            cin >> n;
            vector<int> _liststart(n), _listend(n);
            vector<thread> _t(n);
            for(int i=0; i<n; i++){
                printf("which floor is the person[%d] at?\n",i);
                cin>>_liststart[i];
                printf("which floor is the person[%d] leaving?\n",i);
                cin>>_listend[i];
                
                thread t1(cmdFunc,i,_liststart[i],_listend[i]);
                t1.detach();            
            }
            
            
        }
        else if(str[0]=='s'){
            b->printstatus();
        }
        else{
            cerr<<"error command!! plz reinput again"<<endl;
        }
            
    }
    delete elevator1;
    delete elevator2;
    delete b;
    return 0;
}