//
// Created by strakh on 31-07-19.
//

#include <iostream>
#include <future>
#include "TaskManager.h"

void TaskManager::onNewTime(const std::time_t& external) {
    std::cout << external << " seconds passed" << std::endl;
    std::lock_guard<std::mutex> guard(tasksLock);
    if (current == 0) {
        // init
        if (!tasks.empty()) {
            while (tasks.top()->getTimestamp() == 0) {
                auto task = tasks.top();
                task->updateTimestamp(external);
                tasks.pop();
                tasks.emplace(task);
                std::cout << "updated task with interval " << task->getInterval() << " to ts " << task->getTimestamp()
                          << std::endl;
            }
        }
    }
    if (external > current) {
        if (!tasks.empty()) {
            while (tasks.top()->getTimestamp() <= external) {
                auto task = tasks.top();
                task->updateTimestamp(task->getTimestamp());
                tasks.pop();
                tasks.emplace(task);
                auto future = std::async(std::launch ::async, [t=task]() {t->run();});
                std::cout << "run & updated task with interval " << task->getInterval() << " to ts "
                          << task->getTimestamp() << std::endl;
            }
        }
        current = external;
    }
}

void TaskManager::addTask(const PeriodicTaskPtr& task) {
    std::lock_guard<std::mutex> guard(tasksLock);
    tasks.emplace(task);
}