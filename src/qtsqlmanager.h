#ifndef QTSQLMANAGER_H
#define QTSQLMANAGER_H

#include <QObject>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include <QDebug>

class QtSQLManager: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList melodies READ melodies CONSTANT)

public:
    QtSQLManager(QObject *parent = nullptr);

    QString selectedMelody() const;
    const QStringList melodies();

    ~QtSQLManager()
    {
        qDebug() << "Destructor for db called";
        m_db.close();
    }

public slots:
    void updateSelectedMelody(QString name);

private:
    QSqlDatabase m_db;
    QSqlQuery* m_sqlQuery;

    QSqlDatabase createDb();
    void createTable();
    void readTableData() const;
    QString pathToDb() const;

    void fillDb(QStringList names);
};

#endif // QTSQLMANAGER_H
