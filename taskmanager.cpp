#include "taskmanager.h"

TaskManager::TaskManager(QObject *parent)
    : QObject{parent}
{
    if(m_db.init("./database","taskManager.sqlite"))
    {
        m_query = new QSqlQuery((*m_db.getDatabase()));
    }
    else
        qInfo() << "failed to init database..";
}

TaskManager::~TaskManager()
{
    delete m_query;
}

bool TaskManager::createTask(QString text)
{
    m_queryStr = "INSERT INTO tasks (t_text,t_status) VALUES (:text,:status);";
    if (!m_query->prepare(m_queryStr))
    {
        qInfo() << "Failed to prepare query:" << m_query->lastError().text();
        return false;
    }
    m_query->bindValue(":text", text);
    m_query->bindValue(":status", QString::number(static_cast<int>(TaskStatus::InCompleted)));
    return m_query->exec();
}

bool TaskManager::removeTask(qint8 id)
{
    m_queryStr = "DELETE FROM tasks WHERE t_id=:id;";
    if (!m_query->prepare(m_queryStr))
    {
        qInfo() << "Failed to prepare query:" << m_query->lastError().text();
        return false;
    }
    m_query->bindValue(":id", id);
    return m_query->exec();
}

bool TaskManager::updateTask(qint8 id, QString text, TaskStatus status)
{
    m_queryStr = "UPDATE tasks SET t_text=:text, t_status=:status WHERE t_id=:id;";
    if (!m_query->prepare(m_queryStr))
    {
        qInfo() << "Failed to prepare query:" << m_query->lastError().text();
        return false;
    }
    m_query->bindValue(":id", id);
    m_query->bindValue(":text", text);
    m_query->bindValue(":status", QString::number(static_cast<int>(status)));
    return m_query->exec();
}

QString TaskManager::printTaskList()
{
    QString result = "Tasks are:";

    m_queryStr = "SELECT * FROM tasks;";
    if (!m_query->prepare(m_queryStr))
    {
        qInfo() << "Failed to prepare query:" << m_query->lastError().text();
    }
    if(m_query->exec())
    {
        QString result2;
        while(m_query->next())
        {
            result2.clear();
            result2 += m_query->value("t_id").toString();
            result2 += "    ";
            result2 += m_query->value("t_text").toString();
            result2 += "    ";

            QChar some(QString(m_query->value("t_status").toString()).at(0));
            switch (some.toLatin1())
            {
            case '0': result2 += "Unknown"; break;
            case '1': result2 += "Completed"; break;
            case '2': result2 += "InCompleted"; break;
            case '3': result2 += "WorkingOn"; break;
            default: result2 += "Invalid"; break;
            }


            result2 += "    ";
            qInfo() << result2;
        }
    }
    return result;
}
