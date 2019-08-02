//
// Created by strakh on 31-07-19.
//

#ifndef FORESCOUT_PERIODICTASK_H
#define FORESCOUT_PERIODICTASK_H


#include <stdatomic.h>
#include <ctime>

class PeriodicTask {

public:
    explicit PeriodicTask(int interval): interval_sec(interval), timestamp(0) {};
    virtual ~PeriodicTask() = default;
    int getInterval() const { return interval_sec; }
    std::time_t getTimestamp() const { return timestamp; }

private:
    virtual void run() = 0;
    void updateTimestamp(std::time_t current) {
        timestamp = current + getInterval();
    }
    void updateInterval(int interval) {
        interval_sec = interval;
    }
    atomic_int interval_sec;
    atomic_int timestamp;
    // context

    friend class TaskManager;
};

#endif //FORESCOUT_PERIODICTASK_H
