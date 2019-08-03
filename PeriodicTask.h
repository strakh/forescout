//
// Created by strakh on 31-07-19.
//

#ifndef FORESCOUT_PERIODICTASK_H
#define FORESCOUT_PERIODICTASK_H


#include <stdatomic.h>
#include <ctime>

namespace forescout {
    class PeriodicTaskBase {

    public:
        explicit PeriodicTaskBase(std::time_t interval) : interval_sec(interval), timestamp(0L) {};

        virtual ~PeriodicTaskBase() = default;

        std::time_t getInterval() const { return interval_sec; }

        std::time_t getTimestamp() const { return timestamp; }

    private:
        virtual void run() = 0;

        void updateTimestamp(std::time_t current) {
            timestamp = current + getInterval();
        }

        void updateInterval(std::time_t interval) {
            interval_sec = interval;
        }

        std::atomic<time_t> interval_sec;
        std::atomic<time_t> timestamp;

        friend class TaskManager;
    };

    template<typename T>
    class PeriodicTask : public PeriodicTaskBase {

    public:
        explicit PeriodicTask(std::time_t interval) : PeriodicTaskBase(interval) {};

        PeriodicTask(std::time_t interval, const std::shared_ptr<T> &context) : PeriodicTaskBase(interval),
                                                                                context(context) {};

        virtual ~PeriodicTask() = default;

        const auto &getContext() const { return context; }

    private:
        std::shared_ptr<T> context;

        friend class TaskManager;
    };
}
#endif //FORESCOUT_PERIODICTASK_H
