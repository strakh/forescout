//
// Created by strakh on 31-07-19.
//

#include "TaskManager.h"

void TaskManager::onNewTime(const std::time_t& external) {
    if (external > current) {
        current = external;
    }
}