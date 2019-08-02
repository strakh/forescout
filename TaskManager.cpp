//
// Created by strakh on 31-07-19.
//

#include <iostream>
#include "TaskManager.h"

void TaskManager::onNewTime(const std::time_t& external) {
    std::cout << external << " seconds passed" << std::endl;
    if (current == 0) {
        // init
        while (tasks.top()->getTimestamp() == 0) {
            auto task = tasks.top();
            task->updateTimestamp(external);
            tasks.pop();
            tasks.emplace(task);
            std::cout << "updated task with interval " << task->getInterval() << " to ts " << task->getTimestamp() << std::endl;
        }
    }
    if (external > current) {
        while (tasks.top()->getTimestamp() <= external) {
            auto task = tasks.top();
            task->run();
            task->updateTimestamp(task->getTimestamp());
            tasks.pop();
            tasks.emplace(task);
            std::cout << "run & updated task with interval " << task->getInterval() << " to ts " << task->getTimestamp() << std::endl;
        }
        current = external;
    }
}

void TaskManager::addTask(const PeriodicTaskPtr& task) {
    tasks.emplace(task);
}