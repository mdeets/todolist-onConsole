#include <QCoreApplication>
#include <iostream>
#include "taskmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TaskManager tm;

    std::string input;
    while (true)
    {
        std::cout << "Enter a command ('create', 'remove', 'update', 'print', or 'quit'): ";
        std::cin >> input;

        if (input == "quit")
        {
            break; // Exit the loop
        }
        else if (input == "create")
        {
            std::string taskName;
            std::cout << "Enter task name: ";
            std::cin >> taskName;
            tm.createTask(QString::fromStdString(taskName)); // Convert std::string to QString
        }
        else if (input == "remove")
        {
            int taskId;
            std::cout << "Enter task ID to remove: ";
            std::cin >> taskId;
            tm.removeTask(taskId);
        }
        else if (input == "update")
        {
            int taskId;
            std::string newTaskName;
            int taskStatus;
            std::cout << "Enter task ID to update: ";
            std::cin >> taskId;
            std::cout << "Enter new task name: ";
            std::cin >> newTaskName;
            std::cout << "Enter task status (0 for InProgress, 1 for Completed, 2 for InCompleted): ";
            std::cin >> taskStatus;
            tm.updateTask(taskId, QString::fromStdString(newTaskName), static_cast<TaskStatus>(taskStatus));
        }
        else if (input == "print")
        {
            tm.printTaskList();
        }
        else
        {
            std::cout << "Invalid command. Please try again." << std::endl;
        }
    }

    return a.exec();
}
