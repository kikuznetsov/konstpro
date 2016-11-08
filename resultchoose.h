#ifndef RESULTCHOOSE_H
#define RESULTCHOOSE_H

#include <Wt/WDateTime>
using namespace Wt;

enum Datatype
    {surface_rec, pressure_meters,
     pressure_mmhg, temperature};

class Result{
private:

    WDateTime begTime;
    WDateTime endTime;
    Datatype dataType;
    int idExp;

public:
    Result(){
        idExp = 0;
        begTime = WDateTime::currentDateTime();
        endTime = WDateTime::currentDateTime();
    }
    Result(int selItem, int id, WDateTime& beg, WDateTime& end){
        idExp = id;
        begTime = beg;
        endTime = end;
        if(selItem==1)
            dataType = pressure_meters;
        else if(selItem==2)
            dataType = pressure_mmhg;
        else if(selItem==3)
            dataType = temperature;
        else
            dataType = surface_rec;
    }
    Datatype getType() const{
        return dataType;
    }
    int getId() const{
        return idExp;
    }
    WDateTime getBegTime() const{
        return begTime;
    }
    WDateTime getEndTime() const{
        return endTime;
    }
};

#endif // RESULTCHOOSE_H
