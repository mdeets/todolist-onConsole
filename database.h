#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

//SQL include
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlError>

//include File and Directory option
#include <QFile>
#include <QDir>

#include <QDebug>



class DataBase : public QObject
{
    Q_OBJECT

    QSqlDatabase* m_db;

    bool isDbExists(const QString& path, const QString& fileName);

public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();
    bool init(const QString& path, const QString& fileName);
    bool exec(QSqlQuery& query);
    bool next(QSqlQuery& query);
    QSqlDatabase *getDatabase();

signals:
};

#endif // DATABASE_H
