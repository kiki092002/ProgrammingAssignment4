/* Nga Hoang - May 14 2022
    Class Invariants:
    - Calling move() will return True if the gridFlea object successfully moves, otherwise return false
    - Calling revive() will return True if the gridFlea object successfull revives, otherwise return false
    - Calling reset() will return True if the gridFlea object successfull revives, otherwise return false
    -gridFlea must be initialized with x, y, size (x, y is position)
    - if object is out of bound( Size/2 ) -> the object will not in energetic mode 
    - GridFlea becomes inactive if it moves out of bound more than ONCE.
    - revive() makes gridFlea become active.
    - Comparisons shall result in the evaluation of x and y values according to integer comparisons
    - Addition with an integer x shall result in a move(x) operation in which internal states may change 
    according to invariants of move()
    - Addition with a gridFlear o shall result in the addition of o.x and o.y to this.x and this.y only in 
    the event that the object remains in bound
    - In such cases that additions with another gridFlea result in invalid states, the value return shall 
    be inactive with no additional state changes
    - Assignment additions replace *this with the results of additions
    - Arithmetic operators require that the object is active. Else, an unchanged copy/reference shall
    be returned
    
   Interface Invariants: 
    - A gridFlea object is not usable when inactive. The object becomes
    inactive when the number of moves exceeds the size of the grid.
    -
    - A gridFlea object can be reactivated if and only if it is inactive but
      not permanently inactive. Hence, if the gridFlea is permanently deactivated, it can never become active again
    - gridFlea stay in the previous position if the current position it need to move is out of bound
    - when x, y, size become encapsulated in a gridflea, the initial state of the gridflea 
    is set to active. The number of move is set to 0
    - gridFlea supports comparison with other gridFleas
    - gridFlea supports addition and assignment addition with both gridFleas and integers as well as pre/post-incrementation
    
*/

#ifndef GRIDFLEA_H
#define GRIDFLEA_H

class gridFlea{
    private:
        
        int x;
        int countJump; 
        const int z = 20;
        int y;
        int initialX = 0 ;
        int initialY = 0;
        bool isActive;
        int change;
        const static int SIZE = 200; // size of grid - bound
        int reward = 5;
        int moveCount;
        bool energetic;
        bool permanentlyDeactivated;
        void checkMoveCount();
        void initial(int startX, int startY);
        
        
        
    public:
        
        gridFlea();
        gridFlea(int x, int y);
        /* PreCondition: The gridFlea may be inactive
        PostCondition: Set gridFlea to its original position.
        */
        bool reset(int startX, int startY);
        /*PreCondition: The gridFlea is active
        PostCondition: The gridFlea is  deactivated
        */
        void revive();
        /* PreCondition: the gridFlea must be "active"
           PostCondition: the gridFlea can become inactive 

        */
        bool move(int p);
        bool activeStatus();
        bool isEnergetic();

        /*
        PostCondition: The gridFlea is permenantly deactivated
        */
        void permanentlyDeactivate();
       
        gridFlea& operator=(const gridFlea&);
        
        int value();
        bool operator==(const gridFlea& obj)const;
        bool operator!=(const gridFlea&obj) const;
        bool operator<(const gridFlea& obj) const;
        bool operator>(const gridFlea& obj) const ;
        bool operator<=(const  gridFlea& obj) const;
        bool operator>=(const gridFlea& obj) const;

        //PreCondition: gridFlea is in active
        gridFlea operator+(const gridFlea& obj);
        //PreCondition: gridFlea is in active
        gridFlea operator+(int increment);
        //PreCondition: gridFlea is in active
        //PreCondition: gridFlea's values are changed and can become inactive
        gridFlea& operator+=(int increment);
        //PreCondition: gridFlea is in active
        //PreCondition: gridFlea's values are changed and can become inactive
        gridFlea&  operator+=(const gridFlea& obj);
        //PreCondition: gridFlea is in active
        //PreCondition: gridFlea's values are changed
        gridFlea&  operator++();
        //PreCondition: gridFlea is in active
        //PreCondition: gridFlea's values are changed
        gridFlea operator++(int dummy);                                
        
        


};
extern gridFlea operator+(int increment, gridFlea& obj);

#endif

