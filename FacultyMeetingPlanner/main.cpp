//
//  main.cpp
//  FacultyMeetingPlanner
//
//  Created by Jose Pagan on 3/26/17.
//  Copyright © 2017 Jose Pagan. All rights reserved.
//



/*
 Program: Fusion Meeting Planner
 Data: March 20, 2017
 Description:  Plans faculty meetings for the teachers of each student, based on the following:
 - One meeting per student with all the teachers of that student.
 - 30 minute meeting timeslots, up to [4] meetings per timeslot, [14] timeslots per day.
 - Minimize conflicts (when a teacher has to attend more than one meeting in a given time slot).
 - Students are assigned to timeslots on a first come first serve basis based on their order in the Student List.
 - If student has conflict with next available timeslot, he is assigned to the next available timeslot.
 - If student has conflict with all available timeslots, he is assigned to first timeslot with least number of conflicts.
 - Student List may be sorted in: (i) original order, (ii) sorted by non ascending number of teachers of the student,
 -   (iii) sorted by total number of students of the teachers for the student, or (iv) any combination
 -   of (i), (ii) and (iii).
 */





#include "Schedule.h"
#define Verbosity 0

int main() {
    int maxTimeSlots = 14;
    int maxSlotSize = 4;
    
    try {
        Schedule aSchedule(maxTimeSlots, maxSlotSize);   // create a meeting schedule with 14 time slots.
        aSchedule.help();
#if(Verbosity)
        aSchedule.print();
#endif
        aSchedule.menu();
        
        // With Verbosity, the level of tracing and error messaging increases.
    }
    catch (int e)
    {
        cout << "An exception occurred. Exception Nr. " << e << '\n';
    }
    return 0;
}


