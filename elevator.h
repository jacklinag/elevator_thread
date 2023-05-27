#include <vector>
#include <mutex>

using namespace std;
class Elevator;
class Building;
class Person;

class Elevator{
public:
    Elevator(){}
    Elevator(int x){
        current_floor = x;
    }

    int getfloor();
    void setfloor(int);
    void display_floor();
    void move(int);

private:
//the elevator at now:
    int current_floor;

};

class Person{
public:
    Person() = delete; 
    Person(int x,int y){
        _floor_start = x;
        _floor_end = y;
        ++p_cnt;
    }
    
    int getstart();
    int getend();
    static int getcnt();

private:
    int _floor_start;
    int _floor_end;
    static int p_cnt;
};


class Building{
public:

    Building() = delete;
    Building(int x){
        maxfloor = x;
        requset_nums = 0;
    }

    // member function
    pair<Elevator*,int> SeletElevator(Person*);
    void Setfloor(Person*);
    void NewElevator(Elevator*);
    void Elevateperson(Person*);
    void printstatus();

    // data member
    //Elevator* e1;
    //Elevator* e2;
    vector<Elevator*> _elist;
    vector<bool> _using;
    int maxfloor;
    int requset_nums;
};
