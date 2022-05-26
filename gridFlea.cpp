
/* Nga Hoang -May 20 -2022
    Implementation Invariants: 
    - GridFlea moves inside of the grid's size.
    - A gridFlea starts at (0,0)
    - The active state of a gridFlea will be evaluated to false if the number of
    moves exceeds the size of the grid.
    - The active status will change back to true if the gridFlea is revive or reset.
    - Reviving an active gridFlea will permanently deactivate it. The gridFlea can not
    be revived or reset after permanent deactivation.
    - while moving, if in energetic mode the gridFlea object will move p squares, otherwise moves 1 square 
    (must smaller than size of grid.)
    - gridFlea object will not in object mode after some number of moves smaller than SIZE /2
    - Comparisons are designed such that logically opposite operators must result in negations of each other
    - Arithmetic operations are designed such that int + gridFlear == gridFlea + int in addition to the
    considerations for valid state changes
  ........
*/
#include "gridFlea.h"
gridFlea::gridFlea(){
    initial(initialX,initialY);
    isActive = false;
    permanentlyDeactivated = true;

}
gridFlea::gridFlea(int x, int  y){
    initial(x,y);
}
void gridFlea::initial(int startX, int startY){
    x = startX;
    y = startY;
    energetic = true;
    change = 0;
    moveCount = 0;
    countJump  = 0;
    isActive = true;
    permanentlyDeactivated = false;
    initialX = startX;
    initialY = startY;
}
bool gridFlea::activeStatus(){
    return isActive;
}
/* PreCondition: the gridFlea must be "active"
   PostCondition: the gridFlea is inactive 

*/
bool gridFlea::move(int p){
    if (!isActive)
    {
        return false;
    }
    
    if (energetic)
    {
        if (x - p >= 0 )
        {
            x -= p;
        }
        else if ( y -p >=0){
              y -=p;
        }
        else if (x + p< SIZE )
        {
            if( x + p > SIZE /2){

                energetic = false;
            }
             x +=p;
        }
        else if (y + p < SIZE){
            if ( y + p > SIZE / 2){
                energetic = false;

            }
            y +=p;
        }
        else
        {   

            countJump++;
            
            if ( x + p > z + SIZE  || y + p > z + SIZE || countJump >= 1 ){
                isActive = false;
                return false;
            }
            
        }
                
        moveCount += p;
        checkMoveCount();
        change +=p;
        reward -=p;
        energetic = false;
                
    }
    else
    {   
        if (x - 1 >= 0)
        {
            x--;
        }
        else if (y - 1 >= 0)
        {
            y--;
        }
        else if (x + 1 < SIZE)
         {
             if ( x  + 1 >  SIZE/2){
                 energetic = false;
             }
            x++;
            
         }
         else if (y + 1 < SIZE)
         {
             if ( y + 1 > SIZE / 2){
                 energetic = false;
             }
             y++;
             
         }
         else
         {
            countJump++;
            
            if ( x + p > z + SIZE  || y + p > z + SIZE || countJump >= 1 ){
                isActive = false;
                return false;
            }
        }
        
        moveCount++;
        checkMoveCount();
        change++;
        reward--;
        
        
        
    }
    return true;

}
int gridFlea::value(){
    change = (initialX - this->x) + (initialY - this->y);
    return reward * SIZE * change;
    
}
gridFlea& gridFlea::operator=(const gridFlea& obj) {
    x = obj.x;
    countJump = obj.countJump; 
    y = obj.y;
    initialX = obj.initialX;
    initialY = obj.initialY;
    isActive = obj.isActive;
    change = obj.change;
    reward = obj.reward;
    moveCount = obj.moveCount;
    energetic = obj.energetic;
    permanentlyDeactivated = obj.permanentlyDeactivated;
    return *this;
}
void gridFlea::checkMoveCount(){
    
    isActive  = moveCount <= SIZE;
}       
bool gridFlea::isEnergetic(){
    return energetic;
}
/*PreCondition: The gridFlea is active
  PostCondition: The gridFlea is  deactivated
 */
void gridFlea::revive(){
   isActive = true;
}
/* PreCondition: The gridFlea may be inactive
   PostCondition: Set gridFlea to its original position.
*/
bool gridFlea::reset(int startX, int startY){
    if(permanentlyDeactivated){
        return false;
    }
    initial(startX,startY);
    return true;

}
void gridFlea::permanentlyDeactivate(){
    isActive =false;
    permanentlyDeactivated = true; 
}
bool gridFlea::operator==(const gridFlea& obj)const  {
    return x == obj.x && y == obj.y;
}
bool gridFlea::operator!=(const gridFlea& obj )const{
    return !(*this == obj);
}
bool gridFlea::operator<(const gridFlea& obj)const{
    return x < obj.x && y < obj.y;
}
bool gridFlea::operator>(const gridFlea& obj) const{
    return  x > obj.x && y  >  obj.y;
}
bool gridFlea::operator<=(const gridFlea& obj)const{
    return !(*this > obj);
}
bool gridFlea::operator>=(const gridFlea& obj)const{
    return !(*this < obj);
}

//PreCondition: gridFlea is in active
gridFlea gridFlea::operator+(int increment) {
    gridFlea temp = *this; 
    
    temp.move(increment);

    return temp;
}
//PreCondition: gridFlea is in active
gridFlea gridFlea::operator+(const gridFlea& obj){

    gridFlea clone = *this; 
    if (!isActive) return clone;

    clone.x += obj.x;
    clone.y += obj.y;
    if( clone.x >= SIZE || clone.y >= SIZE || clone.x < 0 || clone.y < 0){
        clone = *this; // no changes
        clone.isActive = false;
        
    }
    return clone;
}
//PreCondition: gridFlea is in active
//PreCondition: gridFlea's values are changed and can become inactive     
gridFlea& gridFlea::operator+=(const gridFlea&obj){
    if (!isActive) return *this;
    *this =  *this + obj;
    return *this;

}
//PreCondition: gridFlea is in active
//PreCondition: gridFlea's values are changed and can become inactive      
gridFlea& gridFlea::operator+=(int increment){
    if (!isActive) return *this;

    *this = *this + increment;
    return *this ;
}
//PreCondition: gridFlea is in active
//PreCondition: gridFlea's values are changed
gridFlea& gridFlea::operator++(){ // ++a -> pre
    if (!isActive) return *this;

    return *this += 1;
}
// a++ - post
//PreCondition: gridFlea is in active
//PreCondition: gridFlea's values are changed
gridFlea gridFlea::operator++(int dummy) {
    
    gridFlea clone = *this ;
    if (!isActive) return clone;

    *this += 1;
    return clone;
}


gridFlea operator+(int increment, gridFlea& obj){

    return obj + increment;
}