//
// Created by strakh on 31-07-19.
//

#ifndef FORESCOUT_PERIODICTASK_H
#define FORESCOUT_PERIODICTASK_H


#include <stdatomic.h>
#include <ctime>

class PeriodicTaskBase {

public:
    explicit PeriodicTaskBase(int interval): interval_sec(interval), timestamp(0) {};
    virtual ~PeriodicTaskBase() = default;
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

    friend class TaskManager;
};

template<typename T>
class PeriodicTask: public PeriodicTaskBase {

public:
    explicit PeriodicTask(int interval): PeriodicTaskBase(interval) {};
    PeriodicTask(int interval, const std::shared_ptr<T>& context): PeriodicTaskBase(interval), context(context) {};
    virtual ~PeriodicTask() = default;
    const auto& getContext() const { return context; }

private:
    std::shared_ptr<T> context;
    friend class TaskManager;
};
#endif //FORESCOUT_PERIODICTASK_H
