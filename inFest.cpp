/* Nga Hoang - May 14 2022
    Implementation Invariants:
  - The inFest will encapsulated a fixed number of gridFlea objects.
  - An array of provided distinct gridFlea objects are given to a inFest object.
  - Each gridFlea object stay in diferent (X,Y) positions.
  - gridFlea subobject makes movement when inFest is in active mode. 
  - Comparisons are designed such that logically opposite operators must result in negations of each other
  - Comparisons account for the cardinality of the object in its evaluation of the predicate - such
  that the "best fit" of the predicate is determined.
  - Arithmetic operations are designed to expand such cardinality.
  
*/

#include "inFest.h"
#include <iostream>
using namespace std;
inFest::inFest(int startX[], int startY[], int numObjs): numGridFleas(numObjs)
{   
    if  ( numObjs  <  0 ){
        throw "number of objects can't be  negative";
    }
    gridFleaObjs = new gridFlea[numGridFleas];
    for( int i = 0 ; i < numGridFleas; i++){
        gridFleaObjs[i] = gridFlea(startX[i],startY[i]);
        
        
    }
    active = true;

}
inFest::inFest(const inFest& orig){
    copy(orig);
}

/* PreCondition: The inFest must be "active" for moving
   PostCondition: The inFest may become  inactive
*/
int inFest::move(int p){
    
    int count = 0 ; 
    if(!active) return -1;

    for(int  i = 0 ; i < numGridFleas; i++){
        if(gridFleaObjs[i].activeStatus()){
            gridFleaObjs[i].move(p);
            count++;
        }    
    }
    
    if (count  >=  numGridFleas /2) {
        active  = !active;
    }
    

    return count;
    

}
/* PreCondition: The inFest must be "active" for selecting min value
*/
int inFest::minQ(){
    if(!active){
        throw " The inFest is not active ";
    }
    
    int min = gridFleaObjs[0].value();
    for( int i = 0 ; i < numGridFleas;i++){
        if(gridFleaObjs[i].value() < min){
            min = gridFleaObjs[i].value();            
        }
    }
    
    
    return min; 

}
/* PreCondition: The gridFlea must be "active" for selecting max value
*/
int inFest::maxQ(){
    if(!active){
        throw " The inFest is not active ";
    }
    int max = 0;
    for ( int i = 0 ; i < numGridFleas;i++){
        if(gridFleaObjs[i].value() > max){
            max = gridFleaObjs[i].value();            
        }
    }
    return max;
    
}



inFest::inFest(inFest&& orig) noexcept{
    gridFleaObjs      = orig.gridFleaObjs;
    numGridFleas      = orig.numGridFleas;
    active             = orig.active;

    orig.gridFleaObjs = nullptr;
    orig.active       = false;
    orig.numGridFleas = 0;
}
inFest& inFest::operator=(const inFest& orig){
    if(this == &orig){
        return *this;
    }
    delete[] gridFleaObjs;
    copy(orig);
    return *this;

}

inFest& inFest::operator=(inFest&& orig) noexcept{
    if (this == &orig) return *this;

    swap(numGridFleas, orig.numGridFleas);
    swap(active, orig.active);
    swap(gridFleaObjs, orig.gridFleaObjs);

    return *this;
}

inFest::~inFest(){
    delete [] gridFleaObjs;
}
void inFest::copy(const inFest& orig){
    
    gridFleaObjs = new gridFlea[orig.numGridFleas];
    for( int i = 0 ; i < orig.numGridFleas; i++){
        gridFleaObjs[i] = orig.gridFleaObjs[i];
    }
    numGridFleas = orig.numGridFleas;
    active = orig.active;

}
bool inFest::operator>(const inFest& obj){
    if(numGridFleas == obj.numGridFleas){
        int count_1 = 0 ; 
        int count_2 = 0;
        for( int i = 0 ; i< numGridFleas;i++){
            if(gridFleaObjs[i] > obj.gridFleaObjs[i])
                count_1++;            
            else
                count_2++;
            
        }
        return count_1 > count_2;

    }
    
    return numGridFleas > obj.numGridFleas;

}
bool inFest::operator<(const inFest& obj){
    if(numGridFleas == obj.numGridFleas){
        int count_1 = 0 ; 
        int count_2 = 0;
        for( int i = 0 ; i< numGridFleas;i++){
            if(gridFleaObjs[i] < obj.gridFleaObjs[i])
                count_1++;            
            else
                count_2++;            
        }
        return count_1 > count_2;

    }
    
    return numGridFleas < obj.numGridFleas;
}
bool inFest::operator==(const inFest& obj){
    if(numGridFleas !=  obj.numGridFleas) {
        return false;
    }
    for(int i = 0 ; i < numGridFleas;i++){
        if(gridFleaObjs[i] !=  obj.gridFleaObjs[i]){
            return false;
        }
    }
    return true;
}
bool inFest::operator!=(const inFest& obj){
    return !(*this == obj);
}
bool inFest::operator>=(const inFest& obj){
    return !(*this < obj);
    
}
bool inFest::operator<=(const inFest& obj){
    return !(*this > obj);


}
bool inFest::isActive(){
    return active;
}
//PreCondition: The inFest is active
//PostCondition:The inFest's size is changed and  the amount of gridFlea in inFest is increased    
inFest inFest::operator+(const inFest& obj){
    inFest clone = *this;
    if(!active) return clone;
    int size = clone.numGridFleas + obj.numGridFleas;
    gridFlea* temp = new gridFlea[size]; 
    int j = 0;
    for( int i = 0 ; i  < clone.numGridFleas;i++){
        temp[j] = clone.gridFleaObjs[i];
        j++;
    }
    for( int i = 0 ; i  < obj.numGridFleas;i++){
        temp[j] = obj.gridFleaObjs[i];
        j++;
    }
    delete[] clone.gridFleaObjs;
    clone.gridFleaObjs = temp;
    clone.numGridFleas = size;
    return clone;

}
//PreCondition: The inFest is active
//PostCondition:The inFest's size is changed and  the amount of gridFlea in inFest is increased 
inFest& inFest::operator+=(const inFest& obj){
    if(!active) return *this;
    *this = *this + obj;
    return *this;
}
//PreCondition: The inFest is active
//PostCondition:The inFest's size is changed and  the amount of gridFlea in inFest is increased      
inFest inFest::operator+(const gridFlea& obj){
    inFest clone = *this;
    if(!active) return clone;
    gridFlea* temp = new gridFlea[numGridFleas + 1];
    for(int i = 0 ; i< numGridFleas;i++){
        temp[i] = gridFleaObjs[i];
    }
    temp[numGridFleas] = obj;
    delete[] clone.gridFleaObjs;
    clone.gridFleaObjs = temp;
    clone.numGridFleas +=1;
    
    return  clone;
}
//PreCondition: The inFest is active
//PostCondition:The inFest's size is changed and  the amount of gridFlea in inFest is increased     
inFest& inFest::operator+=(const gridFlea& obj){
    if (!active) return *this;
    *this = *this + obj;
    return *this;
}
inFest operator+( gridFlea& gridObj, inFest& obj){
    return  obj + gridObj;
}