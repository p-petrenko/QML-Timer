#include "qtsqlmanager.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include <QtSql>

#include <QCoreApplication>
#include <QDebug>

QtSQLManager::QtSQLManager(QObject *parent)
    : QObject(parent)
{
    m_db = createDb();

    if (!m_db.open()) {
        qDebug() << "error in open db:" << m_db.lastError().text();
    } else {
        m_sqlQuery = new QSqlQuery(m_db);
        createTable();
        fillDb(melodies());
    }
}

QString QtSQLManager::pathToDb() const {
    auto pathStr = QCoreApplication::applicationDirPath();
    int pos = pathStr.lastIndexOf(QChar('/'));
    QString nameOfDb = "/Timer/melodiesTableDb";
    return pathStr.left(pos) + nameOfDb;
}

// создается один раз при инициализации и не меняется
const QStringList QtSQLManager::melodies()
{
    return {
        "drums 1",
        "drums 2",
        "fretless bass",
        "piano 1",
        "piano 2",
        "piano 3",
        "piano 4",
        "piano 5",
        "synthesizer",
        "electrosound 1",
        "electrosound 2",
        "electrosound 3",
        "electrosound 4",
        "electrosound 5",
        "lullaby",
        "seagulls and foghorn",
        "wobble",
        "sleigh bells"
    };
}

QSqlDatabase QtSQLManager::createDb() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(pathToDb());
    return db;
}

void QtSQLManager::createTable() {
    if (!m_sqlQuery->exec("CREATE TABLE IF NOT EXISTS melodiesTable(MelodyName, isSelected)")) {
        qDebug() << "error in table creation:" << m_sqlQuery->lastError().text();
    }
}

void QtSQLManager::fillDb(QStringList names) {
    // check if table is already filled
    readTableData();

    m_sqlQuery->last(); // Retrieves the last record in the result
    int currentIndex = m_sqlQuery->at();

    if (currentIndex < 0) {
        // Positional binding for adding multiple rows
        m_sqlQuery->prepare("INSERT INTO melodiesTable VALUES (?, ?)");
        for (int i = 0; i < names.count(); i++) {
            m_sqlQuery->addBindValue(names[i]);

            // set initially first melody as selected
            m_sqlQuery->addBindValue((i == 0) ? 1 : 0);

            if (!m_sqlQuery->exec()) {
                qDebug() << "error in fill db:" << m_sqlQuery->lastError().text();
            }
        }
        qDebug() << m_db;

        if (!m_db.commit()) {
            qDebug() << "error in db commit:" << m_db.lastError().text();
        }
    }
}

void QtSQLManager::readTableData() const {

    if (m_sqlQuery->exec("SELECT * FROM melodiesTable")) {
        qDebug() << "Query success";

        // Print all values
        while ( m_sqlQuery->next()) {
            QString name =  m_sqlQuery->value(0).toString();
            QString name2 =  m_sqlQuery->value(1).toString();
        }
    } else {
        qDebug() << "error in select:" << m_sqlQuery->lastError().text();
    }
}

// --- PUBLIC METHODS ---

// возвращает название выбранной мелодии таймера
QString QtSQLManager::selectedMelody() const {
    int currIndex = m_sqlQuery->at();
    qDebug() << "Current index in Select Meleody: " << currIndex;

    if (!m_sqlQuery) {
        qDebug() << "SQL query is empty";
        return NULL;
    } else {
        m_sqlQuery->exec("SELECT MelodyName FROM melodiesTable WHERE isSelected = 1");
        m_sqlQuery->next();
        QString name = m_sqlQuery->value(0).toString();
        qDebug() << "Selected name is " << name;
        return name;
    }
}

// устанавливает isSelected на новую выбранную мелодию
void QtSQLManager::updateSelectedMelody(QString name) {

    // clear previous isSelected
    if (!m_sqlQuery->exec("UPDATE melodiesTable SET isSelected = 0 WHERE isSelected = 1")) {
        qDebug() << "error in select:" << m_sqlQuery->lastError().text();
    }

    // use positional binding
    m_sqlQuery->prepare("UPDATE melodiesTable SET isSelected = 1 WHERE MelodyName = ?");
    // bind parameter for line above
    m_sqlQuery->addBindValue(name);
    if (!m_sqlQuery->exec()) {
        qDebug() << "error in select:" << m_sqlQuery->lastError().text();
    }
}





