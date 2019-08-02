//
// Created by Stepan Rakhimov on 2019-08-02.
//

#define BOOST_TEST_MODULE forescout test
#include <boost/test/included/unit_test.hpp>
#include "PeriodicTask.h"

BOOST_AUTO_TEST_SUITE(PeriodicTaskSuite)
    class TestPeriodicTask: public PeriodicTask {
    public:
        explicit TestPeriodicTask(int interval): PeriodicTask(interval) {};
        void run() override {};
    };


    BOOST_AUTO_TEST_CASE(testCreate) {
        auto task = TestPeriodicTask(5);
        BOOST_CHECK_NO_THROW(TestPeriodicTask(2));
    }

    BOOST_AUTO_TEST_CASE(testGetInterval) {
        auto task = TestPeriodicTask(5);
        BOOST_CHECK_EQUAL(task.getInterval(), 5);
    }

    BOOST_AUTO_TEST_CASE(testGetTimestamp) {
        auto task = TestPeriodicTask(5);
        BOOST_CHECK_EQUAL(task.getTimestamp(), 0);
    }

BOOST_AUTO_TEST_SUITE_END()