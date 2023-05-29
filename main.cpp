#include "elevator.h"
#include <iostream>
#include <string>
#include <thread>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <condition_variable>
using namespace std;

Building* b = new Building(10);
condition_variable cv;
mutex m;
int Person::p_cnt = -1;

bool is_number(const string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void cmdFunc(int i, string s1, string s2){
    if(!is_number(s1)||!is_number(s2)){
        cerr<< "person ["<<i<<"] has invalid string input!!"<<endl;
    }else{
        int x = stoi(s1), y = stoi(s2);
        if(x>10 || x<0 || y>10 || y<0){
            cerr<< "person ["<<i<<"] has invalid int input!!"<<endl;
            return;
        }
        else if(x==y){
            cerr<<"you are already at end floor!"<<endl;
            return;
        }
        else{
            b->setrequestnum( b->getrequestnum()+1 );
            Person* a = new Person(x,y);
            b->Elevateperson(a);
            delete a;
            b->setrequestnum( b->getrequestnum()-1 );
            return;
        }
    }
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
            // while(true){
                cout<< "how many people are requeset elevators?"<<endl;
                string str2;
                int n;
                cin >> str2;
                // if(is_number(str2)){
                n = stoi(str2);
                vector<string> _liststart(n), _listend(n);
                for(int i=0; i<n; i++){
                    printf("which floor is the person[%d] at?\n",i);
                    cin>>_liststart[i];
                    printf("which floor is the person[%d] leaving?\n",i);
                    cin>>_listend[i];
                    
                    thread t1(cmdFunc,i,_liststart[i],_listend[i]);
                    t1.detach();      
                }
                // break;
                // }
                // else{
                //     cerr<<"wrong input! plz reinput a number!!"<<endl;
                // }
            // }
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
    return 0;
}