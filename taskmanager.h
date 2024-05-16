#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QObject>
#include "database.h"

enum class TaskStatus
{
    Unknown,
    Completed,
    InCompleted,
    WorkingOn,
};

class TaskManager : public QObject
{
    Q_OBJECT
    DataBase m_db;
    QSqlQuery* m_query;
    QString m_queryStr;

public:
    explicit TaskManager(QObject *parent = nullptr);
    ~TaskManager();
    bool createTask(QString text);
    bool removeTask(qint8 id);
    bool updateTask(qint8 id, QString text, TaskStatus status=TaskStatus::Unknown);
    QString printTaskList();
signals:
};

#endif // TASKMANAGER_H
