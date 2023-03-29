#ifndef TRIWORKOUT_H
#define TRIWORKOUT_H

#include <string>
#include "workout.h"

using namespace std;

/* Class invariants:
 * The TriWorkout has a name that does not change.
 * A TriWorkout is invalid if the time or distance performed are set more than once.
 * TriWorkout is completed once performed time and distance have been recorded at least once.
 */

class triWorkout : public workout {

    private: 
        //instructor input, does not change after constructor
        double timeGoal = -1.0;
        double distanceGoal = -1.0;

        bool timeChanged = false;
        bool distanceChanged = false;

        //client input
        double performedTime = -1.0;
        double performedDistance = -1.0;

    public:
        triWorkout();
        //Preconditions: None
        //Postconditions: name, timeGoal, and distanceGoal have been entered.
        triWorkout(string, double, double);
        double getTimeGoal() const;
        double getDistanceGoal() const;
        double getPerformedTime() const;
        double getPerformedDistance() const;
        //Preconditions: performedTime and performedDistance have been entered
        //Postconditions: None
        double pace() const;
        //Preconditions: performedTime and performedDistance have been entered
        //Postconditions: None
        double percentOfGoal() const override;
        //Preconditions: performedTime and performedDistance have been entered
        //Postconditions: None
        double score() const override;
        //Preconditions: none, however, assumes distance has been entered because date of completion
        //is recorded in this function
        //Postconditions: Validity may have changed, date is recorded
        void setPerformedTime(double);
        //Preconditions: None
        //Postconditions: Validity may have changed
        void setPerformedDistance(double);
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
 * The program does not control for the chance that a user enters invalid values for all time or distance variables (negative values are invalid).
 * Operator overloads do not control for chance that goal metrics become negative because of user.
 * Bools timeChanged and distanceChanged are only used internally to track validity.
 * performedTime and performedDistance will still be set per request regardless of validity.
 * The date is set when the performedTime is recorded, which is meant to be set after performedDistance.
 * For running, the intended units are minutes and miles.
 * For cycling, the intended units are hours and miles.
 * For swimming, the intended units are seconds and yards.
 * The unit for Pace in swimming context is seconds per 100 yards. The constructor takes the raw yard number done (in the hundreds), 
 * and later the Pace function divides the raw number by 100 for unit conversion.
 * Constructor only accepts "running, cycling, swimming" as names, all lower case and no extra spaces.
 * PercentOfGoal is calculated in a way so that for running and swimming: as your pace becomes slower (higher value), percentOfGoal becomes less,
 * and for cycling: percentOfGoal becomes higher as your pace increases.
 */

 #endif