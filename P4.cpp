/**
 * @file P4.cpp
 * @author Nga Hoang 
 * @version 2
 * @date 2022-05-20
 * PURPOSE: 
 * -  Using collection of distinct objects 
 * -  Test move semantic using STL vector
 * -  Demonstrating shared_ptr, unique_ptr
 * -  Use STL vector to store heap allocated inFest
 * -  Demonstrating pass - by - value
 * PROCESSING:
 * - Process the purpose above
 * - Additionally, test comparision operators of collection of inFests and gridFleas 
 * - Test various mode changes of inFests and gridFleas through arithmetic operators
 * - look below to see how I precessing 
 * OUTPUT:
 * - Please run the code to see the output. Thank you 
 * - Each test will be conducted in its own section. 
 */

#include <iostream>
#include "inFest.h"
#include  <math.h>
#include  <memory>
#include "time.h"
#include <vector>
using namespace  std;

const int BOUND_INFEST = 20;
const int BOUND_VALUES = 150;
const int BOUND_VECTOR = 5;
inFest generateInfest();
void testHeapInfest(unique_ptr<inFest> ptr);
vector<unique_ptr<gridFlea>> generateVectorGridGlea();
gridFlea generategridFlea();
unique_ptr<inFest> generateHeapInfest();
unique_ptr<gridFlea> generateHeapGridflea();
vector<unique_ptr<inFest>> generateVectorinFest();
void testArithOpInfest(vector<unique_ptr<inFest>>& arr);
gridFlea generategridFlea();
void testComparisionOpInfest(vector<unique_ptr<inFest>> &arr);
void testStackGridFlea(gridFlea obj);
void testHeapGridFlea(unique_ptr<gridFlea> ptr);
void testArithOpGridFlea(vector<unique_ptr<gridFlea>>& arr);
void testComparisionOpGridFlea(vector<unique_ptr<gridFlea>> &arr);
void testShared(shared_ptr<inFest> ptr1, shared_ptr<gridFlea> ptr2);
void testStackInfest(inFest obj);

int main(int argc, char** argv) {
    srand(time(nullptr));

    cout << "Demonstrating ownership transfer of unique_ptr... \nOnce onwership's relinquished, expect unique_ptr == nullptr" << endl;
    unique_ptr<gridFlea> gridPtr_1(generateHeapGridflea());
    cout << "Address of initial gridFlea: " << gridPtr_1.get() << endl;
    cout << "Transferring ownership..." << endl;
    testHeapGridFlea(move(gridPtr_1));
    cout << "Ownership's lost, gridFlear ptr is nullptr: " << (gridPtr_1 == nullptr ? "TRUE" : "FALSE") << endl;
    unique_ptr<inFest> inFest_ptr1(generateHeapInfest());
    cout << "Address of initial inFest: " << inFest_ptr1.get() << endl;
    cout << "Transferring ownership..." << endl;
    testHeapInfest(move(inFest_ptr1));
    cout << "Ownership's lost, inFest ptr is nullptr: " << (inFest_ptr1 == nullptr ? "TRUE" : "FALSE") << endl;
   
    cout << "====================================" << endl;
    cout << "Demonstrating pass-by-value. \nExpect address of copy to be different from intial" << endl;
    gridFlea gridObj_1(generategridFlea()); // move semantic invoked
    cout << "Address of inital gridFlea: " << &gridObj_1 << endl;
    cout << "Passing-by-value..." << endl;
    testStackGridFlea(gridObj_1);
    inFest inFestObj_1(generateInfest()); // move semantic invoked
    cout << "Address of inital inFest: " << &inFestObj_1 << endl;
    cout << "Passing-by-value..." << endl;
    testStackInfest(inFestObj_1);

    cout << "====================================" << endl;
    cout << "Demonstrating move semantics using STL vector. \nEach object invokes move semantics when inserted (see implenentation)" << endl;
    vector<inFest> inFest_vec;
    for (int i = 0; i < BOUND_VECTOR; i++) inFest_vec.push_back(generateInfest());

    cout << "====================================" << endl;
    cout << "Demonstrating shared ownership through shared_ptr... \nOwnership is shared, hence expect shared_ptr != nullptr" << endl;
    shared_ptr<gridFlea> gridPtr_2(generateHeapGridflea());
    shared_ptr<inFest> inFest_ptr2(generateHeapInfest());
    cout << "Address of initial gridFlea: " << gridPtr_2.get() << endl;
    cout << "Address of initial inFest: " << inFest_ptr2.get() << endl;
    cout << "Sharing ownership..." << endl;
    testShared(inFest_ptr2, gridPtr_2);
    cout << "Ownership's retained, gridFlear ptr is nullptr: " << (gridPtr_2 == nullptr ? "TRUE" : "FALSE") << endl;
    cout << "Ownership's retained, gridFlear ptr is nullptr: " << (inFest_ptr2 == nullptr ? "TRUE" : "FALSE") << endl;

    cout << "====================================" << endl;
    vector<unique_ptr<gridFlea>> gridVector(generateVectorGridGlea());
    vector<unique_ptr<inFest>> inFestVector(generateVectorinFest());
    testComparisionOpGridFlea(gridVector);
    testArithOpGridFlea(gridVector);
    //testArithOpGridFlea(gridVector);
    testComparisionOpInfest(inFestVector);
    testArithOpInfest(inFestVector);
    
}

inFest generateInfest(){
    int numOfObjs  = rand()%BOUND_INFEST + 1;
    
    cout << "Generating inFest of size " << numOfObjs << endl;
    int X[numOfObjs];
    int Y[numOfObjs];
    for( int i = 0 ; i< numOfObjs;i++){
        X[i] = rand()%BOUND_VALUES;

    }
    for( int i = 0 ; i< numOfObjs;i++){
        Y[i] = rand()%BOUND_VALUES;

    }
    inFest obj(X,Y,numOfObjs);
    return obj;

}
gridFlea generategridFlea(){
    cout << "Generate random gridFlea" << endl;
    int X = rand() % BOUND_VALUES; 
    
    int Y = rand() % BOUND_VALUES; 
    cout << "X value: " << X << endl;
    cout << "Y value: " << Y << endl;
    gridFlea obj(X,Y);
    return obj;

}
unique_ptr<inFest> generateHeapInfest(){
    return unique_ptr<inFest>(new inFest(generateInfest()));
}
unique_ptr<gridFlea> generateHeapGridflea(){
    return unique_ptr<gridFlea>(new gridFlea(generategridFlea()));
}
void testStackInfest(inFest obj){
    cout << "Address of stack inFest: " << &obj << endl;
}
void testHeapInfest(unique_ptr<inFest> ptr){
    cout << "Address of heap inFest: " << ptr.get() << endl;
}
vector<unique_ptr<inFest>> generateVectorinFest(){
    vector<unique_ptr<inFest>> obj; 
    cout << "Generating vector of " << BOUND_VECTOR << " inFests" << endl;
    for(int i = 0 ; i< BOUND_VECTOR ; i++){
        obj.push_back(generateHeapInfest());
    }
    return obj;
}
void testComparisionOpInfest(vector<unique_ptr<inFest>>& arr){

    cout << "====================================" << endl;
    inFest obj1  = generateInfest();
    cout << "Testing comparision operator of inFEST" << endl;

    for( int i = 0 ; i < arr.size(); i++) { 
        cout << "Testing > operator: arr["<<i<<"] > obj1: " <<   (*arr[i] > obj1 ? "TRUE" : "FALSE") << endl;
        cout << "Testing < operator: arr["<<i<<"] < obj1: " <<   (*arr[i] < obj1 ? "TRUE" : "FALSE") << endl;
        cout << "Testing >= operator: arr["<<i<<"] >= obj1: " << (*arr[i] >= obj1 ? "TRUE" : "FALSE") << endl;
        cout << "Testing <= operator: arr["<<i<<"] <= obj1: " << (*arr[i] <= obj1 ? "TRUE" : "FALSE") << endl;
        cout << "Testing == operator: arr["<<i<<"] == obj1: " << (*arr[i] == obj1 ? "TRUE" : "FALSE") << endl;
        cout << "Testing != operator: arr["<<i<<"] != obj1: " << (*arr[i] != obj1 ? "TRUE" : "FALSE") << endl;
        cout << endl;
    }
}
void testStackGridFlea(gridFlea obj){
    cout << "Address of stack gridFlea: " << &obj << endl;
}
void testHeapGridFlea(unique_ptr<gridFlea> ptr){
    cout << "Address of heap gridFlea: " << ptr.get() << endl;
}
vector<unique_ptr<gridFlea>> generateVectorGridGlea(){
    vector<unique_ptr<gridFlea>> obj;
    cout << "Generating vector of " << BOUND_VECTOR << " gridFleas" << endl;
    for ( int i = 0 ; i < BOUND_VECTOR; i ++){
        obj.push_back(generateHeapGridflea());
    }
    return obj;
}

void testComparisionOpGridFlea(vector<unique_ptr<gridFlea>>& arr){
    
    cout << "====================================" << endl;
    gridFlea obj1  = generategridFlea();
    cout << "Testing comparision operator of gridFlea" << endl;

    for( int i = 0 ; i < arr.size(); i++) { 
        cout << "Testing > operator: arr["<<i<<"] > obj1: " <<   (*arr[i] > obj1 ? "TRUE" : "FALSE") << endl;
        cout << "Testing < operator: arr["<<i<<"] < obj1: " <<   (*arr[i] < obj1 ? "TRUE" : "FALSE") << endl;
        cout << "Testing >= operator: arr["<<i<<"] >= obj1: " << (*arr[i] >= obj1 ? "TRUE" : "FALSE") << endl;
        cout << "Testing <= operator: arr["<<i<<"] <= obj1: " << (*arr[i] <= obj1 ? "TRUE" : "FALSE") << endl;
        cout << "Testing == operator: arr["<<i<<"] == obj1: " << (*arr[i] == obj1 ? "TRUE" : "FALSE") << endl;
        cout << "Testing != operator: arr["<<i<<"] != obj1: " << (*arr[i] != obj1 ? "TRUE" : "FALSE") << endl;
        cout << endl;
    }
    
    
}
void testArithOpInfest(vector<unique_ptr<inFest>>& arr){
    cout << "====================================" << endl;
    inFest inFestObj = generateInfest();
    gridFlea  gridFleaObj = generategridFlea();
    cout << "Testing Arithemtic ops of inFest" << endl;
    for( int i = 0 ; i < arr.size();i++){
        inFest temp1 = *arr[i]  + inFestObj;
        inFest temp2 = *arr[i] + gridFleaObj;
        int move = rand() % BOUND_VALUES + 1;
        
        cout << "(arr[" << i << "] + inFest).move(" << move << ") -> " << temp1.move(move) <<  " gridFleas moved successfully" << endl;
        cout << "(arr[" << i << "] + gridFlea).move(" << move << ")-> " << temp2.move(move) <<  " gridFleas moved successfully" << endl;
        cout << endl;
    }


}

void testArithOpGridFlea(vector<unique_ptr<gridFlea>>& arr){
    cout << "====================================" << endl;
    gridFlea obj = generategridFlea();
    int num = rand() % BOUND_VALUES + 1;

    cout << "Testing Arithemtic ops of gridFlea" << endl;
    for( int i = 0 ; i< arr.size() ; i++){
        gridFlea tmp1 = *arr[i] + num;
        gridFlea tmp2 = *arr[i] + obj;

        cout << "arr[" << i << "] + " << num << ", activeStatus(): " << ((*arr[i]).activeStatus() ? "TRUE" : "FALSE") << "->" << (tmp1.activeStatus()? "TRUE" : "FALSE") <<endl;
        cout << "arr[" << i << "] + gridFlea, activeStatus(): " << ((*arr[i]).activeStatus() ? "TRUE" : "FALSE") << "->" << (tmp2.activeStatus()? "TRUE" : "FALSE") <<endl;
        
        cout << "++arr[" << i << "], activeStatus(): " << ((*arr[i]).activeStatus() ? "TRUE" : "FALSE") << "->" << ((++(*arr[i])).activeStatus()? "TRUE" : "FALSE") <<endl;
        if (!(*arr[i]).activeStatus()) { // If implemented correct, will never be true
            cout << "Reviving obj..." << endl;
            (*arr[i]).revive();
        }
        cout << "arr[" << i << "]  += gridFlea, activeStatus(): " << ((*arr[i]).activeStatus() ? "TRUE" : "FALSE") << "->" << (((*arr[i])+=obj).activeStatus()? "TRUE" : "FALSE") << endl;
        cout << endl;
        (*arr[i]).revive();
    }
    cout << "Reviving all objs..." << endl;
}
void testShared(shared_ptr<inFest> ptr1, shared_ptr<gridFlea> ptr2){
    cout << "Address of inFest in function: " << ptr1.get() << endl;
    cout << "Address of gridFlea in function: " << ptr2.get() << endl;
}
