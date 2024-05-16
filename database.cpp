#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent} , m_db(nullptr)
{

}

DataBase::~DataBase()
{
    m_db->close();
    delete m_db;
}

bool DataBase::init(const QString &path, const QString &fileName)
{
    bool result=false;
    m_db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));


    QString fullPath = path+"/"+fileName;
    m_db->setDatabaseName(fullPath);

    if(QFile::exists(fullPath))
    {
        // qInfo() << "databae exists..";
        if(m_db->open())
            result=true;
    }
    else
    {
        QDir dbDire(path);
        dbDire.mkpath(".");
        QFile dbFile(fullPath);
        if(m_db->open())
        {
            QSqlQuery createTable("CREATE TABLE tasks(t_id INTEGER PRIMARY KEY,t_text TEXT,t_status TEXT);");
            if(createTable.exec())
            {
                // qInfo() << "database creation successed.";
                result=true;
            }
            else
            {
                // qInfo() << "database creation exec failed." << createTable.lastError().text();
                result=true;
                /* i dont know what is wrong but when database dont exits these commands
                 * make db file then create table fine but this .exec() always return false so
                 * result=true would skip this issue.
                 */
            }

        }
        else
        {
            qInfo() << "m_db could not open database file.";
        }
    }
    return result;
}

QSqlDatabase *DataBase::getDatabase()
{
    return m_db;
}

