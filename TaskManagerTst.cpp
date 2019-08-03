//
// Created by Stepan Rakhimov on 2019-08-02.
//

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "TaskManager.h"

BOOST_AUTO_TEST_SUITE(TaskManagerSuite)

    class DefinedPeriodicTask: public PeriodicTask {
    public:
        explicit DefinedPeriodicTask(int interval): PeriodicTask(interval) {};
        void run() override {
            std::cout << "running task every: " << getInterval() << " sec" << std:: endl;
            ++runCounter;
        }
        int runCounter = 0;
    };

    BOOST_AUTO_TEST_CASE(testCreate) {
        BOOST_CHECK_NO_THROW(TaskManager());
    }

    BOOST_AUTO_TEST_CASE(testAddTask) {
        auto manager = std::make_unique<TaskManager>();
        auto task = std::make_shared<DefinedPeriodicTask>(60);
        manager->addTask(task);
        BOOST_CHECK_EQUAL(manager->countTasks(), 1);
        BOOST_CHECK_EQUAL(task->runCounter, 0);
    }

    BOOST_AUTO_TEST_CASE(testTimestampExternallyUpdated) {
        auto manager = std::make_unique<TaskManager>();
        auto now = std::chrono::system_clock::now();
        BOOST_CHECK_EQUAL(manager->getLastTimestamp(), 0);
        manager->onNewTime(std::chrono::system_clock::to_time_t(now));
        BOOST_CHECK_EQUAL(manager->getLastTimestamp(), std::chrono::system_clock::to_time_t(now));
    }

    BOOST_AUTO_TEST_CASE(testTimeJitter) {
        auto manager = std::make_unique<TaskManager>();
        manager->onNewTime(-100);
        BOOST_CHECK_EQUAL(manager->getLastTimestamp(), 0);
        manager->onNewTime(256);
        BOOST_CHECK_EQUAL(manager->getLastTimestamp(), 256);
        manager->onNewTime(250);
        BOOST_CHECK_EQUAL(manager->getLastTimestamp(), 256);
    }

    BOOST_AUTO_TEST_CASE(testTaskTimestampInit) {
        auto manager = std::make_unique<TaskManager>();
        auto task = std::make_shared<DefinedPeriodicTask>(2);
        manager->addTask(task);
        manager->onNewTime(1);
        BOOST_CHECK_EQUAL(task->getTimestamp(), 3);
    }

    BOOST_AUTO_TEST_CASE(testPeriodicalTaskExecution) {
        auto manager = std::make_unique<TaskManager>();
        auto task = std::make_shared<DefinedPeriodicTask>(2);
        manager->addTask(task);
        manager->onNewTime(0);
        BOOST_CHECK_EQUAL(task->runCounter, 0);
        manager->onNewTime(2);
        BOOST_CHECK_EQUAL(task->runCounter, 1);
        BOOST_CHECK_EQUAL(task->getTimestamp(), 4);
    }

    BOOST_AUTO_TEST_CASE(testMultipleTasksExecution) {
#define CHECK_RUN_COUNTERS(t1, t2, t3) \
        BOOST_CHECK_EQUAL(task1->runCounter, t1); \
        BOOST_CHECK_EQUAL(task2->runCounter, t2); \
        BOOST_CHECK_EQUAL(task3->runCounter, t3)

        auto manager = std::make_unique<TaskManager>();
        auto task1 = std::make_shared<DefinedPeriodicTask>(2);
        auto task2 = std::make_shared<DefinedPeriodicTask>(3);
        auto task3 = std::make_shared<DefinedPeriodicTask>(5);
        manager->addTask(task1);
        manager->addTask(task3);
        manager->addTask(task2);
        BOOST_CHECK_EQUAL(manager->countTasks(), 3);
        manager->onNewTime(0);
        CHECK_RUN_COUNTERS(0, 0, 0);
        manager->onNewTime(1);
        CHECK_RUN_COUNTERS(0, 0, 0);
        manager->onNewTime(2);
        CHECK_RUN_COUNTERS(1, 0, 0);
        manager->onNewTime(3);
        CHECK_RUN_COUNTERS(1, 1, 0);
        manager->onNewTime(4);
        CHECK_RUN_COUNTERS(2, 1, 0);
        manager->onNewTime(5);
        CHECK_RUN_COUNTERS(2, 1, 1);
        manager->onNewTime(6);
        CHECK_RUN_COUNTERS(3, 2, 1);
        manager->onNewTime(7);
        CHECK_RUN_COUNTERS(3, 2, 1);
        manager->onNewTime(8);
        CHECK_RUN_COUNTERS(4, 2, 1);
        manager->onNewTime(9);
        CHECK_RUN_COUNTERS(4, 3, 1);
        manager->onNewTime(10);
        CHECK_RUN_COUNTERS(5, 3, 2);
    }

    BOOST_AUTO_TEST_CASE(testTasksExecutionJumpingTime) {
        auto manager = std::make_unique<TaskManager>();
        auto task1 = std::make_shared<DefinedPeriodicTask>(2);
        auto task2 = std::make_shared<DefinedPeriodicTask>(3);
        manager->addTask(task2);
        manager->addTask(task1);
        manager->onNewTime(10);
        BOOST_CHECK_EQUAL(task1->runCounter, 0);
        BOOST_CHECK_EQUAL(task2->runCounter, 0);
        manager->onNewTime(20);
        BOOST_CHECK_EQUAL(task1->runCounter, 5);
        BOOST_CHECK_EQUAL(task2->runCounter, 3);
    }

BOOST_AUTO_TEST_SUITE_END()