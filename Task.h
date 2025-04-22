//
// Created by 24124 on 2025-04-22.
//

#ifndef TASK_H
#define TASK_H
#include <string>
#include <iostream>
#include <sstream>

class Task {
public:
    int id;
    std::string description;
    int priority;
    std::string dueDate;

    std::string toString() const {
        std::ostringstream oss;
        oss << "Task: " << id
        << ", Description: " << description
        << ", Priority: " << priority
        << ", Due Date: " << dueDate;
        return oss.str();
    }

};



#endif //TASK_H
