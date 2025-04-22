//
// Created by 24124 on 2025-04-22.
//

#ifndef TASKMANGER_H
#define TASKMANGER_H
#include "Task.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>


class TaskManger {
public:
    TaskManger();
    void addTask(const std::string& description, int priority, const std::string& date);
    void removeTask(int id);
    void updateTask(int id, const std::string& description, int priority, const std::string& date);
    void listTasks(int sortOption) const;
    void loadTasks();
    void saveTasks() const;
private:
    std::vector<Task> tasks;
    int nextId;
    static bool compareByPriority(const Task& a, const Task& b);
    static bool compareByDueDate(const Task& a, const Task& b);
};



#endif //TASKMANGER_H
