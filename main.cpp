#include <iostream>
#include "TaskManager.h"

class MyPeriodicTask: public PeriodicTask {
public:
    MyPeriodicTask(int interval): PeriodicTask(interval) {};
    void run() override {
        std::cout << "running my task every: " << getInterval() << " sec" << std:: endl;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;

    auto taskManager = TaskManager();
    auto task1 = std::make_shared<MyPeriodicTask>(2);
    auto task2 = std::make_shared<MyPeriodicTask>(5);
    taskManager.addTask(task1);
    taskManager.addTask(task2);
    for (auto i = 0; i < 10; ++i) {
        taskManager.onNewTime(i);
    }
    return 0;
}