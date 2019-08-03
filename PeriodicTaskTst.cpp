//
// Created by Stepan Rakhimov on 2019-08-02.
//

#define BOOST_TEST_MODULE forescout test

#include <boost/test/included/unit_test.hpp>
#include "PeriodicTask.h"

namespace forescout {
    BOOST_AUTO_TEST_SUITE(PeriodicTaskSuite)

        class TestPeriodicTask : public PeriodicTask<void> {
        public:
            explicit TestPeriodicTask(std::time_t interval) : PeriodicTask(interval) {};

            void run() override {};
        };

        class ContextPeriodicTask : public PeriodicTask<int> {
        public:
            explicit ContextPeriodicTask(std::time_t interval, const std::shared_ptr<int>& context) : PeriodicTask(
                    interval, context) {};

            void run() override {
                contextReadByRun = true;
                *getContext() = 333;
            };
            bool contextReadByRun = false;
        };


        BOOST_AUTO_TEST_CASE(testCreate) {
            BOOST_CHECK_NO_THROW(TestPeriodicTask(2));
        }

        BOOST_AUTO_TEST_CASE(testGetInterval) {
            auto task = std::make_unique<TestPeriodicTask>(5);
            BOOST_CHECK_EQUAL(task->getInterval(), 5);
        }

        BOOST_AUTO_TEST_CASE(testGetTimestamp) {
            auto task = std::make_unique<TestPeriodicTask>(5);
            BOOST_CHECK_EQUAL(task->getTimestamp(), 0);
        }

        BOOST_AUTO_TEST_CASE(testCreateWithContext) {
            BOOST_CHECK_NO_THROW(ContextPeriodicTask(3, std::make_shared<int>(300)));
        }

        BOOST_AUTO_TEST_CASE(testGetContext) {
            auto task = std::make_unique<ContextPeriodicTask>(3, std::make_shared<int>(500));
            BOOST_CHECK_EQUAL(task->getContext().operator*(), 500);
        }

        BOOST_AUTO_TEST_CASE(testRunAccessContext) {
            auto task = std::make_unique<ContextPeriodicTask>(3, std::make_shared<int>(1000));
            task->run();
            BOOST_CHECK_EQUAL(task->contextReadByRun, true);
        }

        BOOST_AUTO_TEST_CASE(testRunWritesContext) {
            auto task = std::make_unique<ContextPeriodicTask>(3, std::make_shared<int>(1000));
            task->run();
            BOOST_CHECK_EQUAL(*task->getContext(), 333);
        }

    BOOST_AUTO_TEST_SUITE_END()
}
