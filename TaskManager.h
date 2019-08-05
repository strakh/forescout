//
// Created by strakh on 31-07-19.
//

#ifndef FORESCOUT_TASKMANAGER_H
#define FORESCOUT_TASKMANAGER_H

#include <ctime>
#include <algorithm>
#include <queue>
#include <vector>
#include <mutex>
#include "PeriodicTask.h"

namespace forescout {
    template<
            class T,
            class Container = std::vector<T>,
            class Compare = std::less<typename Container::value_type>
    >
    class accessible_priority_queue : public std::priority_queue<T, Container, Compare> {
    public:
        void update() {
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
        }

        bool remove(const T& value) {
            auto it = std::find(this->c.begin(), this->c.end(), value);
            if (it != this->c.end()) {
                this->c.erase(it);
                std::make_heap(this->c.begin(), this->c.end(), this->comp);
                return true;
            } else {
                return false;
            }
        }
    };

    using PeriodicTaskPtr = std::shared_ptr<PeriodicTaskBase>;

    struct CmpPeriodicTaskPrts {
        bool operator()(const PeriodicTaskPtr& lhs, const PeriodicTaskPtr& rhs) const {
            return lhs->getTimestamp() > rhs->getTimestamp();
        }
    };

    class TaskManager {

    public:
        void onNewTime(const std::time_t& external);

        void addTask(const PeriodicTaskPtr& task);

        void updateTaskInterval(const PeriodicTaskPtr& task, const std::time_t& interval);

        void removeTask(const PeriodicTaskPtr& task);

        const std::time_t& getLastTimestamp() const { return current; }

        size_t countTasks() const;


    private:
        mutable std::mutex tasksLock;
        std::time_t current = 0;
        accessible_priority_queue<PeriodicTaskPtr, std::vector<PeriodicTaskPtr>, CmpPeriodicTaskPrts> tasks;
    };
}
#endif //FORESCOUT_TASKMANAGER_H
