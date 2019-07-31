//
// Created by strakh on 31-07-19.
//

#ifndef FORESCOUT_TASKMANAGER_H
#define FORESCOUT_TASKMANAGER_H

#include <ctime>
#include <queue>
#include "PeriodicTask.h"

class TaskManager {

public:
    void onNewTime(const std::time_t& external);
    void addTask(PeriodicTask task); // todo: return shared_ptr


private:
    std::time_t current = 0;
    std::priority_queue<PeriodicTask> tasks; // todo: shared_ptr

};


#endif //FORESCOUT_TASKMANAGER_H
