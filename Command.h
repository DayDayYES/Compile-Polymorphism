//
// Created by 24124 on 2025-04-22.
//

#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include <iostream>
#include <memory>

// class CommandBase {
// public:
//     virtual void execute(const std::string& args) = 0;
// };


template<typename Derived>
class Command {
public:
    void execute(const std::string& args) {
        static_cast<Derived*>(this)->executeImpl(args);
    }
};

#include "Logger.h"
#include "TaskManger.h"
class AddCommand: public Command<AddCommand> {
public:
    AddCommand(TaskManger& manger):taskManger(manger){}
    void executeImpl(const std::string& args) {
        size_t pos1 = args.find(',');
        size_t pos2 = args.find(',', pos1 + 1);
        if (pos1 == std::string::npos || pos2 == std::string::npos) {
            //Logger::getInstance().log("Invalid arguments for add command");
            std::cout << "Invalid arguments for add command, please use: add <description>, <priority>, <dueDate>" << std::endl;
            return;
        }
        std::string description = args.substr(0, pos1);
        int priority = std::stoi(args.substr(pos1+1, pos2-pos1-1));
        std::string dueDate = args.substr(pos2+1);
        taskManger.addTask(description, priority, dueDate);
        std::cout << "successfully added task" << std::endl;
    }
private:
    TaskManger& taskManger;
};

class DeleteCommand: public Command<DeleteCommand> {
public:
    DeleteCommand(TaskManger& manger):taskManger(manger){}
    void executeImpl(const std::string& args) {
        try {
            size_t pos;
            int id = std::stoi(args, &pos);
            if (!pos == args.length()) {
                //Logger::getInstance().log("Invalid arguments for delete command");
                std::cout << "Invalid arguments for delete command, please use: delete <id>" << std::endl;
                return;
            }
            taskManger.removeTask(id);
            Logger::getInstance().log("successfully deleted task");
        }catch (const std::invalid_argument& e) {
            Logger::getInstance().log("Invalid arguments for delete command");
            return;
        }catch (const std::out_of_range& e) {
            Logger::getInstance().log("Invalid arguments for delete command");
            return;
        }
    }
private:
    TaskManger& taskManger;
};

class ListCommand: public Command<ListCommand> {
public:
    ListCommand(TaskManger& manger): taskManger(manger){}
    void executeImpl(const std::string& args) {
        try {
            int sortOption = 0;
            if (!args.empty()) {
                sortOption = std::stoi(args);
            }


            taskManger.listTasks(sortOption);
        }catch (const std::out_of_range){
            Logger::getInstance().log("Invalid arguments for list command");
            return;
        }catch (const std::invalid_argument& e) {
            Logger::getInstance().log("Invalid arguments for list command");
            return;
        }
    }
private:
    TaskManger& taskManger;
};

class UpdateCommand: public Command<UpdateCommand> {
public:
    UpdateCommand(TaskManger& manger):taskManger(manger){}
    void executeImpl(const std::string& args) {
        try {
            size_t pos1 = args.find(',');
            size_t pos2 = args.find(',', pos1 + 1);
            size_t pos3 = args.find(',', pos2+1);
            if (pos1 == std::string::npos || pos2 == std::string::npos || pos3 == std::string::npos) {
                //Logger::getInstance().log("Invalid arguments for update command");
                std::cout << "Invalid arguments for update command, please use: update <id>, <description>, <priority>, <dueDate>" << std::endl;
                return;
            }
            int id = std::stoi(args.substr(0, pos1));
            std::string newDestription = args.substr(pos1+1, pos2-pos1-1);
            int priority = std::stoi(args.substr(pos2+1, pos3-pos2-1));
            std::string dueDate = args.substr(pos3+1);
            taskManger.updateTask(id, newDestription, priority, dueDate);
        }catch (const std::invalid_argument& e) {
            Logger::getInstance().log("Invalid arguments for update command");
            return;
        }catch (const std::out_of_range& e) {
            Logger::getInstance().log("Invalid arguments for update command");
            return;
        }
    }
private:
    TaskManger& taskManger;
};


class CommandWrapper {
    struct Concept {
        virtual void execute(const std::string& args) = 0;
    };

    template<typename T>
    struct Model: Concept{
        T command;
        Model(T cmd):command(std::move(cmd)){}
        void execute(const std::string &args) {
            command.execute(args);
        }
    };
public:
    template<typename T>
    CommandWrapper(T cmd):impl(std::make_unique<Model<T>>(std::move(cmd))) {}
    void execute(const std::string &args) {
        impl->execute(args);
    }

private:
    std::unique_ptr<Concept> impl;
};


#endif //COMMAND_H
