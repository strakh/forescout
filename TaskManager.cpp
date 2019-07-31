//
// Created by strakh on 31-07-19.
//

#include "TaskManager.h"

void TaskManager::onNewTime(const std::time_t& external) {
    if (external > current) {
        current = external;
        tasks.front().get()->run();
    }
}

void TaskManager::addTask(const std::shared_ptr<PeriodicTask>& task) {
    tasks.emplace_back(task);
}