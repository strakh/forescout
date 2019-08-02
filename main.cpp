#include <iostream>
#include "TaskManager.h"

class MyPeriodicTask: public PeriodicTask {
public:
    explicit MyPeriodicTask(int interval): PeriodicTask(interval) {};
    void run() override {
        std::cout << "running my task every: " << getInterval() << " sec" << std:: endl;
    }
};

int main() {
    auto taskManager = TaskManager();
    auto task1 = std::make_shared<MyPeriodicTask>(2);
    auto task2 = std::make_shared<MyPeriodicTask>(5);
    auto task3 = std::make_shared<MyPeriodicTask>(3);
    taskManager.addTask(task1);
    taskManager.addTask(task2);
    taskManager.addTask(task3);
    for (auto i = 0; i < 5; i+=2) {
        taskManager.onNewTime(i);
    }
    taskManager.onNewTime(6);
    taskManager.onNewTime(6);
    taskManager.onNewTime(5);
    taskManager.onNewTime(10);
    taskManager.onNewTime(8);
    return 0;
}