#ifndef HIIT_H
#define HIIT_H

#include <string>
#include "workout.h"

using namespace std;

/* Class invariants:
 * The HIIT has a name that does not change.
 * A HIIT is invalid if the time, rest or reps performed are set more than once.
 * HIIT is completed once performed time, rest, and reps have been recorded at least once.
 */

class hiit : public workout {

    private: 
        //instructor input, does not change after constructor
        double repGoal = -1.0;
        double timeGoal = -1.0;
        double restGoal = -1.0;

        bool repsChanged = false;
        bool timeChanged = false;
        bool restChanged = false;

        //client input
        double performedTime = -1.0;
        double performedRest = -1.0;
        double performedReps = -1.0;

    public: 
        hiit();
        //Preconditions: None
        //Postconditions: name, repGoal, timeGoal, and restGoal have been entered.
        hiit(string, double, double, double);
        double getRepGoal() const;
        double getTimeGoal() const;
        double getRestGoal() const;
        double getPerformedTime() const;
        double getPerformedRest() const;
        double getPerformedReps() const;
        //Preconditions: performedTime, performedRest, and performedReps have been entered
        //Postconditions: None
        double percentOfGoal() const override;
        //Preconditions: performedTime, performedRest, and performedReps have been entered
        //Postconditions: None
        double score() const override;
        //Preconditions: None
        //Postconditions: Validity may have changed
        void setPerformedTime(double);
        //Preconditions: None
        //Postconditions: Validity may have changed
        void setPerformedRest(double);
        //Preconditions: none, however, assumes performed times have been entered because date of completion
        //is recorded in this function
        //Postconditions: Validity may have changed, date is recorded
        void setPerformedReps(double);
        //Preconditions: None
        //Postconditions: None
        bool isComplete() const override;
        string getType() const override;
        workout* clone() const override;
        //Postconditions: target metrics will be increased by int.
        workout* operator+=(const int) override;
        //Postconditions: target metrics will be decreased by int.
        workout* operator-=(const int) override;
};

/* Implementation invariants:
 * The program does not control for the chance that a user enters invalid values for all time or rep variables (negative values are invalid).
 * Operator overloads do not control for chance that goal metrics become negative because of user.
 * Bools timeChanged, restChanged, and repsChanged are only used internally to track validity.
 * performedTime, performedRest, performedReps will still be set per request regardless of validity.
 * The date is set when the performedReps are recorded, which is meant to be set after performed time and rest.
 * All time variables are meant to be in seconds.
 */

 #endif