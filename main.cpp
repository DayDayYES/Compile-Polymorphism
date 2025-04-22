#include <chrono>
#include <iostream>
#include "Logger.h"
#include "TaskManger.h"
#include "Command.h"
#include <unordered_map>
#include <functional>
#include <variant>

int main() {
    TaskManger taskManger;
    // 1. 虚基类
    // std::unordered_map<std::string, std::unique_ptr<CommandBase>> commands;
    // commands["add"] = std::make_unique<AddCommand>(taskManger);
    // commands["delete"] = std::make_unique<DeleteCommand>(taskManger);
    // commands["list"] = std::make_unique<ListCommand>(taskManger);
    // commands["update"] = std::make_unique<UpdateCommand>(taskManger);

    //2. 类型擦除
    // std::unordered_map<std::string, std::function<void(const std::string&)>> commands;
    // auto add_command = std::make_shared<AddCommand>(taskManger);
    // auto delete_command = std::make_shared<DeleteCommand>(taskManger);
    // auto list_command = std::make_shared<ListCommand>(taskManger);
    // auto update_command = std::make_shared<UpdateCommand>(taskManger);
    // commands["add"] = [add_command](const std::string& args) {
    //     add_command->execute(args);
    // };
    // commands["delete"] = [delete_command](const std::string& args) {
    //     delete_command->execute(args);
    // };
    // commands["list"] = [list_command](const std::string& args) {
    //     list_command->execute(args);
    // };
    // commands["update"] = [update_command](const std::string& args) {
    //     update_command->execute(args);
    // };

    //3. std::variant
    // using CommandVector = std::variant<
    //     std::unique_ptr<AddCommand>,
    //     std::unique_ptr<DeleteCommand>,
    //     std::unique_ptr<ListCommand>,
    //     std::unique_ptr<UpdateCommand>
    // >;
    // std::unordered_map<std::string, CommandVector> commands;
    // commands["add"] = std::make_unique<AddCommand>(taskManger);
    // commands["delete"] = std::make_unique<DeleteCommand>(taskManger);
    // commands["list"] = std::make_unique<ListCommand>(taskManger);
    // commands["update"] = std::make_unique<UpdateCommand>(taskManger);

    //4.
    std::unordered_map<std::string, CommandWrapper> commands;
    commands.emplace("add", AddCommand(taskManger));
    commands.emplace("delete", DeleteCommand(taskManger));
    commands.emplace("list", ListCommand(taskManger));
    commands.emplace("update", UpdateCommand(taskManger));


    std::cout << "Welcome to the Task Manager!" << std::endl;
    std::cout << "Available commands: add, delete, list, update" << std::endl;
    std::string input;
    while (true) {
        std::cout << "\n>";
        std::getline(std::cin, input);
        if (input.empty()) {
            continue;
        }
        size_t spacePos = input.find(' ');
        std::string command = input.substr(0, spacePos);
        std::string args;
        if (spacePos != std::string::npos) {
            args = input.substr(spacePos + 1);
        }

        if (command == "exit") {
            std::cout << "Bye!" << std::endl;
            break;
        }

        auto it = commands.find(command);
        if (it != commands.end()) {
            // std::visit([&args](auto&& cmdPtr) {
            //     cmdPtr->execute(args);
            // }, it->second);
            it->second.execute(args);
        }else {
            std::cout << "Unknown command: " << command << std::endl;
        }
    }
    return 0;
}