#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    sched.resize(avail.size());
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, 0);
}

bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, size_t day){
    if(day == sched.size()){
      return true;
    }
    
    for(size_t w = 0; w < avail[day].size(); w++){
       sched[day].push_back(w);
      if(isValid(w, maxShifts, day, sched) && avail[day][w]){
        bool status = scheduleHelper(avail,dailyNeed,maxShifts, sched, day+1);
        if(status){
          return true;
        }
      }
     
      sched[day].pop_back();
    }

  return false;
 }

bool isValid(size_t worker, size_t maxShifts, size_t day, const DailySchedule& sched){
  size_t shiftsTaken = 0;
  for(size_t day = 0; day < sched.size(); day++){ 
      for(size_t worker = 0; worker < sched[day].size(); worker++){
        if(sched[day][worker] == worker){
          shiftsTaken++;
        }

    } 
  }

  return  shiftsTaken <= maxShifts ;

}


