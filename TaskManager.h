//
// Created by strakh on 31-07-19.
//

#ifndef FORESCOUT_TASKMANAGER_H
#define FORESCOUT_TASKMANAGER_H

#include <ctime>
#include <vector>
#include "PeriodicTask.h"

class TaskManager {

public:
    void onNewTime(const std::time_t& external);
    void addTask(const std::shared_ptr<PeriodicTask>& task);


private:
    std::time_t current = 0;
    std::vector<std::shared_ptr<PeriodicTask>> tasks;

};


#endif //FORESCOUT_TASKMANAGER_H
