#ifndef FITSET_H
#define FITSET_H

#include <string>
#include "workout.h"

using namespace std;

/* Class invariants:
 * The FitSet has a name and classification that does not change.
 * A FitSet is invalid if the reps or weight performed are set more than once.
 * A FitSet is complete once performed weight and reps have been entered at least once.
 */

class fitSet : public workout {

    private: 
        //instructor input, does not change after constructor
        string classification = "";
        unsigned int weight = -1;
        unsigned int targetReps = -1;

        bool repsChanged = false;
        bool weightChanged = false;

        //client input
        unsigned int performedReps = -1;
        unsigned int performedWeight = -1;

    public:
        //Preconditions: None
        //Postconditions: name, classification, weight, and targetReps have been entered.
        fitSet();
        fitSet(string, string, int, int);
        string getClassification() const;
        int getWeight() const;
        int getTargetReps() const;
        int getPerformedReps() const;
        int getPerformedWeight() const;

        //Preconditions: performedReps has been entered
        //Postconditions: None
        double percentOfGoal() const override;
        //Preconditions: performedReps and performedWeight have been entered
        //Postconditions: None
        double score() const override;
        //Preconditions: none, however, assumes weight has been entered because date of completion
        //is entered in this function
        //Postconditions: Validity may have changed, date is recorded
        void setPerformedReps(int);
        //Preconditions: None
        //Postconditions: Validity may have changed
        void setPerformedWeight(int);
        //Preconditions: None
        //Postconditions: complete may or may not be true
        bool isComplete() const override;
        string getType() const override;
        workout* clone() const override;
        //Postconditions: target metrics will be increased by int.
        workout* operator+=(const int) override;
        //Postconditions: target metrics will be decreased by int.
        workout* operator-=(const int) override;
};

/* Implementation invariants: 
 * Class does not control for the chance that negative values are entered by user.
 * Operator overloads do not control for chance that goal metrics become negative because of user.
 * Bools repsChanged and weightChanged are only used internally to track validity.
 * performedWeight added so client can change the weight if different than instructed (affects validity).
 * performedReps and performedWeight will still be set per request regardless of validity.
 * Completed means reps and weight have each been entered by the user.
 * The date is set when the performedReps is recorded, which is meant to be set after performedWeight.
 * Constructor assumes valid input.
 */

 #endif