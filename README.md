# Workout Session Creation and Tracking Project

### Background
I made this project in Object-Oriented Programming 
with Professor Timothy Spinney at Seattle University.

#### Classes
There are different types of exercises:
- a **fitset**: any kind of weighted or body exercise 
with sets and reps would classify
- a **hiit**: an exercise with specific active and rest 
time as well as sets
- a **triworkout**: an exercise of swimming, running, 
or cycling

These are all a subtype of the **workout** class, the 
**workout** class itself is pretty unimportant.

You can create an empty session of workouts using 
the **sessionLog** class. 
Someone can then perform these workouts and the 
intended use is for the creator of the session would
then assess the quality of the session performed via
stats provided. 

Restrictions and rules for performing a session are
in the invariants on the files.

#### Other
I then created several operator overloads that can
be used to simplify the creation and performance of
sessions.