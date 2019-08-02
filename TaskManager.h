//
// Created by strakh on 31-07-19.
//

#ifndef FORESCOUT_TASKMANAGER_H
#define FORESCOUT_TASKMANAGER_H

#include <ctime>
#include <queue>
#include "PeriodicTask.h"

using PeriodicTaskPtr = std::shared_ptr<PeriodicTask>;

struct CmpPeriodicTaskPrts
{
    bool operator()(const PeriodicTaskPtr& lhs, const PeriodicTaskPtr& rhs) const
    {
        return lhs->getTimestamp() > rhs->getTimestamp();
    }
};

class TaskManager {

public:
    void onNewTime(const std::time_t& external);
    void addTask(const PeriodicTaskPtr& task);
//    void updateTaskInterval(const PeriodicTaskPtr& task, int interval);
//    void removeTask(const PeriodicTaskPtr& task);
    std::time_t getLastTimestamp() const { return current; }
    size_t countTasks() const { return tasks.size(); }


private:
    std::time_t current = 0;
    std::priority_queue<PeriodicTaskPtr, std::vector<PeriodicTaskPtr>, CmpPeriodicTaskPrts> tasks;

};


#endif //FORESCOUT_TASKMANAGER_H
