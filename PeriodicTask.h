//
// Created by strakh on 31-07-19.
//

#ifndef FORESCOUT_PERIODICTASK_H
#define FORESCOUT_PERIODICTASK_H


#include <stdatomic.h>

class PeriodicTask {

public:
    explicit PeriodicTask(int interval): interval_sec(interval) {};
    void UpdateInterval(int interval) {
        interval_sec = interval;
    }
    virtual void run() = 0;
private:
    atomic_int interval_sec;
    // context
};


#endif //FORESCOUT_PERIODICTASK_H
