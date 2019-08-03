//
// Created by strakh on 31-07-19.
//

#include <iostream>
#include <future>
#include "TaskManager.h"

void TaskManager::onNewTime(const std::time_t& external) {
    std::cout << external << " seconds passed" << std::endl;
    std::lock_guard<std::mutex> guard(tasksLock);
    if (external >= current) {
        if (!tasks.empty()) {
            while (tasks.top()->getTimestamp() <= external) {
                auto task = tasks.top();
                if (task->getTimestamp() != 0 ) {
                    auto future = std::async(std::launch::async, [t = task]() { t->run(); });
                    std::cout << "run & updated task with interval " << task->getInterval() << " to ts "
                              << task->getTimestamp() + task->getInterval() << std::endl;
                } else {
                    std::cout << "updated task with interval " << task->getInterval() << " to ts " << external + task->getInterval()
                              << std::endl;
                }
                task->updateTimestamp(task->getTimestamp() == 0 ? external : task->getTimestamp());
                tasks.pop();
                tasks.emplace(task);
            }
        }
        if (external > current) { current = external; }
    }
}

void TaskManager::addTask(const PeriodicTaskPtr& task) {
    std::lock_guard<std::mutex> guard(tasksLock);
    tasks.emplace(task);
}

//void TaskManager::removeTask(const PeriodicTaskPtr& task) {
//    std::lock_guard<std::mutex> guard(tasksLock);
//    tasks.remove(task);
//}
//
//void TaskManager::updateTaskInterval(const PeriodicTaskPtr& task, int interval) {
//    std::lock_guard<std::mutex> guard(tasksLock);
//    auto old = task->getInterval();
//    task->updateInterval(interval);
//    task->updateTimestamp(task->getTimestamp() - old);
//    tasks.update();
//}