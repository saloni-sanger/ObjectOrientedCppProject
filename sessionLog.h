#ifndef SESSIONLOG_H
#define SESSIONLOG_H
#include <string>
#include <vector>
#include <iostream>
#include "workout.h"

using namespace std;

/* Class invariants:
 * Editting the SessionLog in any way is only allowed if workoutCompleted is false.
 * All workouts in log must be completed on the same day, or performed values will not be set by justDoIt().
 * There is no limit on how many workouts a SessionLog can have.
 */

class sessionLog {
    private:
    workout** log = nullptr;
    int numWorkouts = 0;
    bool workoutCompleted = false; //to limit function use of user

    bool enforceSameDate(int);
    bool checkCompletion();

    friend ostream& operator<<(ostream&, const sessionLog&); 
    friend istream& operator>>(istream&, sessionLog&);

    public:
    sessionLog();
    ~sessionLog();

    //Preconditions: re-adding the same workout object is not allowed. 
    //Postconditions: One workout may have been appended to log
    void addWorkout(workout*); 
    //Preconditions: Trust user that int is a valid exercise number for the sessionLog.
    //Postconditions: One workout may have been deleted to log
    void removeWorkout(unsigned int);
    //Preconditions: Trust user that int is a valid exercise number for the sessionLog,
    //all objects before exerciseNum have been completed, exercise is a FitSet
    //Postconditions: Values may have been set for workout's performed variables, workoutCompleted may have changed
    void justDoIt(int, int, int);
    //Preconditions: Trust user that int is a valid exercise number for the sessionLog,
    //all objects before exerciseNum have been completed, exercise is a triWorkout
    //Postconditions: Values may have been set for workout's performed variables, workoutCompleted may have changed
    void justDoIt(int, double, double);
    //Preconditions: Trust user that int is a valid exercise number for the sessionLog,
    //all objects before exerciseNum have been completed, exercise is a HIIT
    //Postconditions: Values may have been set for workout's performed variables, workoutCompleted may have changed
    void justDoIt(int, double, double, double);
    //Preconditions: Trust user that int is representative of how many workouts are in the vector.
    //Postconditions: Adds all workouts in vector to log.
    void buildSession(vector<workout*>, unsigned int); 
    //Preconditions: None
    //Postconditions: Current sessionLog will be overwritten with what is sent in
    void buildSession(sessionLog&);
    //Preconditions: None
    //Postconditions: None
    string shareSession(); //change to buildSession if doesn't compile

    //Preconditions: None
    //Postconditions: this sessionLog will be a deep copy of sessionLog sent in.
    sessionLog& operator= (const sessionLog&);
    //Preconditions: None
    //Postconditions: this sessionLog will be a deep copy of sessionLog sent in.
    sessionLog(const sessionLog&);

    sessionLog operator+(const sessionLog&) const;
    //Preconditions: re-adding the same workout object is not allowed. 
    //Postconditions: One workout may have been appended to log
    sessionLog& operator+=(workout*);
    
    //Postconditions: Each goal variable in every workout in sessionLog is increased by int
    sessionLog operator+(int) const;
    //Postconditions: Each goal variable in every workout in sessionLog is decreased by int
    sessionLog operator-(int) const;

    //Preconditions: Trust user that int is a valid exercise number for the sessionLog.
    //Postconditions: One workout may have been deleted to log
    sessionLog& operator-=(int);

    bool operator==(const sessionLog&) const;
    bool operator!=(const sessionLog&) const;
    bool operator<(const sessionLog&) const;
    bool operator>(const sessionLog&) const;
};

//Postconditions: sessionLog contents will be written to ostream object
ostream& operator<<(ostream&, const sessionLog&); 
//Postconditions: anything previously in the sessionLog will be deleted.
//the sessionLog will be constructed by reading the istream object.
istream& operator>>(istream&, sessionLog&);

/* Implementation Invariants:
* OPERATOR OVERLOADS:
* + and += used to add workout to log.
* - and -= used to omit a workout at specific index from log.
* == and != verify equality at every level except validity status and completionDate.
* < and > return comparison of numWorkouts values. 
* sessionLog + sessionLog returns sessionLog with combined workouts from this and the argument.
* sessionLog + and - int adjust each goal variable in every workout in sessionLog.

* workoutCompleted is used to limit function use of user.
* The program does not control for the chance that a user enters invalid values for all number variables (negative values are invalid).
* operator overloads do not control for chance that workout variables are made to be invalid negative values during run.
* workout is marked completed if each workout in the log returns true for function call isComplete().
* addWorkout() allows user to add one Workout entry to SessionLog, removeWorkout() removes one Workout.
* buildSession allows user to add several Workouts to a SessionLog.
* When an exerciseNum is entered, it is decremented to represent an array index.
* justDoIt has 3 implementations for the 3 different types of Workout.
* enforceSameDate ensures that if the user has completed a workout within log, all future workouts performed are on the same day. (the time can differ, the date cannot)
* shareSession provides all info needed to display the log.
* A workout object is only allowed to appear in one sessionLog, and only one time in that sessionLog. This is only enforced by contract. 
*/

#endif