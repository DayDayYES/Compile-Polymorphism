//
// Created by 24124 on 2025-04-22.
//

#include "TaskManger.h"
#include <iostream>
#include "Logger.h"

TaskManger::TaskManger() :nextId(1){
    loadTasks();
}

void TaskManger::addTask(const std::string &description, int priority, const std::string &date) {
    Task task;
    task.id = nextId++;
    task.description = description;
    task.priority = priority;
    task.dueDate = date;
    tasks.push_back(task);
    saveTasks();
    Logger::getInstance().log("Task added: " + task.toString());
}

void TaskManger::removeTask(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& t) {
        return t.id == id;
    });
    if (it != tasks.end()) {
        tasks.erase(it);
        Logger::getInstance().log("Task removed: " + it->toString());
        saveTasks();
    }else {
        std::cerr << "Task not found" << std::endl;
    }
}

void TaskManger::updateTask(int id, const std::string &description, int priority, const std::string &date) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& t) {
        return t.id == id;
    });
    if (it != tasks.end()) {
        it->description = description;
        it->priority = priority;
        it->dueDate = date;
        Logger::getInstance().log("Task updated: " + it->toString());
        saveTasks();
    }else {
        std::cerr << "Task not found" << std::endl;
    }
}

void TaskManger::listTasks(int sortOption) const {
    std::vector<Task> sortedTasks = tasks;
    switch (sortOption) {
        case 1:
            std::sort(sortedTasks.begin(), sortedTasks.end(), compareByPriority);
            break;
        case 2:
            std::sort(sortedTasks.begin(), sortedTasks.end(), compareByDueDate);
            break;
        default:
            break;
    }

    for (const auto &it : sortedTasks) {
        std::cout << it.toString() << std::endl;
    }
}

void TaskManger::loadTasks() {
    std::ifstream inFile("tasks.txt");
    if (!inFile.is_open()) {
        Logger::getInstance().log("Failed to open tasks file for loading");
        return;
    }
    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        Task task;
        char delimiter;
        iss >> task.id >> delimiter;
        std::getline(iss, task.description, ',');
        iss >> task.priority >> delimiter;
        iss >> task.dueDate;
        tasks.push_back(task);
        if (task.id >= nextId) {
            nextId = task.id + 1;
        }
    }
    inFile.close();
    Logger::getInstance().log("Tasks loaded successfully");
}

void TaskManger::saveTasks() const {
    std::ofstream outFile("tasks.txt");
    if (!outFile.is_open()) {
        Logger::getInstance().log("Failed to open tasks file for saving");
        return;
    }
    for (const auto &it : tasks) {
        outFile << it.id << " " << it.description << "," << it.priority << " " << it.dueDate << std::endl;
    }
    outFile.close();
    Logger::getInstance().log("Tasks saved successfully");
}

bool TaskManger::compareByPriority(const Task &a, const Task &b) {
    return a.priority < b.priority;
}

bool TaskManger::compareByDueDate(const Task &a, const Task &b) {
    return a.dueDate < b.dueDate;
}
