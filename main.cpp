#include <iostream>
#include "TaskManager.h"

class MyPeriodicTask: public PeriodicTask<std::string> {

public:
    explicit MyPeriodicTask(int interval): PeriodicTask(interval) {};
    MyPeriodicTask(int interval, const std::shared_ptr<std::string>& context): PeriodicTask(interval, context) {};
    void run() override {
        if (getContext() != nullptr) {
            std::cout << "running my task with context " << *getContext() << " every: " << getInterval() << " sec" << std:: endl;
        } else {
            std::cout << "running my task every: " << getInterval() << " sec" << std::endl;
        }
    }
};

int main() {
    auto taskManager = std::make_shared<TaskManager>();
    auto task1context = std::make_shared<std::string>("some data");
    auto task1 = std::make_shared<MyPeriodicTask>(2, task1context);
    auto task2 = std::make_shared<MyPeriodicTask>(5);
    auto task3 = std::make_shared<MyPeriodicTask>(3);
    taskManager->addTask(task1);
//    taskManager->addTask(task2);
//    taskManager->addTask(task3);
//    for (auto i = 0; i < 5; i+=2) {
//        taskManager->onNewTime(i);
//    }
    taskManager->onNewTime(2);
    taskManager->onNewTime(4);
    taskManager->updateTaskInterval(task1, 3);
    *task1context = std::string("new data");
    taskManager->onNewTime(6);
    taskManager->onNewTime(9);
//    taskManager->onNewTime(10);
//    taskManager->onNewTime(8);
    return 0;
}