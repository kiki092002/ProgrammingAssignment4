/* Nga Hoang 
  * Date May 14 -2022 
  Class Invariants:
   - Each inFest must contain a number of gridFlea objects, each of
   which is distinct, having their own uniquely privided encapsulated (X,Y).
   - The number of gridFlea can vary between inFest objects, as the cardinality is not constant.
   - Throw exception if minQ() and maxQ() is not active
   - The inFest will become inactive upon a call to move() in which over half the encapsulated 
   gridFleas are inactive
   - Calling min() and max() will respectively return the minimum and maximum acquired fron a value()
    call across all gridFlea subobjects.
   - Size of X and Y is same and equal to number of gridFlea subobjects that a inFest current holds
   - Conmparisons with other inFests shall count the numbers of encapsulated gridFlea which fit the 
   provided predicate between the compared objects.
   - The object with the higher count is determined to fit such predicates. If this object fits the 
   predicate, the comparison is TRUE.
   - If the cardinality of compared objects differ, cardinality alone will determine the predicate
   - Additions of any type shall expand the encapsulated collection of gridFleas to include either 
   the new gridFlea or copies of the encapsulated gridFleas in the other inFest
   - Assignment additions replace *this with the results of additions
    - Arithmetic operators require that the object is active. Else, an unchanged copy/reference shall
    be returned
  Interface Invariants:
   - The a inFest must be active to ensure max and min are selected; otherwise,
   return throw message " the inFest is not active"
   - move() will return number of gridFlea objects successfully moved.
   - If called while inactive, move() will return -1 to signal failure
   -Client must construct the Cluster with an interger array of X axis, Y axis, and number of gridFLea objects
  
   - Since all objects moving at the same time, at inital they have the same min max and gradually have a 
   diffenrent values depends on the given bound ( SIZE /2)
   - Comparisons with other inFest are supported
   - inFest supports addition and assignment addition with both gridFleas and other inFests
   


*/
#include "gridFlea.h"
#ifndef INFEST_H
#define INFEST_H
class inFest{
    private:
        gridFlea* gridFleaObjs;
        int numGridFleas;
        void copy(const inFest& orig);
        bool active;
        
    public:
        
        inFest(int StartX[], int startY[], int numObjs);
        inFest(const inFest& orig);
        inFest(inFest&& orig) noexcept;
        inFest& operator=(const inFest& orig);
        inFest& operator=(inFest&& orig) noexcept;
        bool  operator>(const inFest& obj) ;
        bool operator<(const inFest& obj);
        bool operator==(const inFest& obj);
        bool operator!=(const inFest&  obj);
        bool operator>=(const inFest& obj);
        bool operator<=(const inFest& obj);
        //PreCondition: The inFest is active
        //PostCondition: The inFest's size is changed and  the amount of gridFlea in inFest is increased
        inFest operator+(const inFest& obj);
        //PreCondition: The inFest is active
        //PostCondition: The inFest's size is changed and  the amount of gridFlea in inFest is increased
        inFest& operator+=(const inFest& obj);
        //PreCondition: The inFest is active
        //PostCondition:The inFest's size is changed and  the amount of gridFlea in inFest is increased
        inFest operator+(const gridFlea&obj);
        //PreCondition: The inFest is active
        //PostCondition:The inFest's size is changed and  the amount of gridFlea in inFest is increased
        inFest& operator+=(const gridFlea& obj);

        /* PreCondition: The inFest must be "active" for moving
           PostCondition: The inFest may become  inactive
        */
        int move(int p);
        /* PreCondition: The inFest must be "active" for selecting min value
        */
        int minQ();
        /* PreCondition: The gridFlea must be "active" for selecting max value
        */
        int maxQ();
        ~inFest();
        bool isActive();


};
extern inFest operator+( gridFlea& gridObj, inFest& obj);

#endif


