#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QObject>
#include "qtsqlmanager.h"

//#include <QtSql/QSqlDatabase>
//#include <QtSql/QSqlQuery>
//#include <QtSql/QSqlRecord>
//#include <QtSql/QSqlError>
//#include <QtSql/QSql>

#include <QTimer>
#include <QTime>
#include <chrono>
#include <QMediaPlayer>

class Countdown : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList time READ time NOTIFY timeChanged)
    Q_PROPERTY(bool isActive READ isActive NOTIFY isActiveChanged)
    Q_PROPERTY(bool isStarted READ isStarted NOTIFY isStartedChanged)
    Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY timerFinished)
    Q_PROPERTY(QString melodyName READ melodyName WRITE setMelodyName NOTIFY melodyNameChanged)
    Q_PROPERTY(QStringList melodyNames READ melodyNames CONSTANT)

public:
    Countdown(QObject *parent = nullptr);

    QStringList time() const;

    bool isPlaying() const; // true if melody plays
    bool isActive() const;
    bool isStarted() const;
    QString melodyName() const;
    void setMelodyName(QString name);
    QStringList melodyNames();

    Q_INVOKABLE void reset();
    Q_INVOKABLE void startOrPause(const QStringList hrMinSecList);
    Q_INVOKABLE void stopMelody();

signals:
    void timeChanged();
    void timerFinished(bool isFinished);
    void isActiveChanged(bool isActive);
    void isStartedChanged(bool isStarted);
    void melodyNameChanged(QString name);

private slots:
    void changeTime();

private:
    QTimer* m_timer;
    QTime m_time;
    bool m_isActive = false;
    bool m_isStarted = false;
    bool m_isPlaying = false;
    QMediaPlayer* m_player;
    QtSQLManager m_sqlitemanager;

    void setIsPlaying(bool isFinished);
    void setIsStarted(bool isStarted);
    void setIsActive(bool isActive);
    void setTime(QTime time);

    QTime convertFromStrListToTime(const QStringList hrMinSecList);
    void finishTimerWithMelody();
    QString pathToMusic() const;
};

#endif // COUNTDOWN_H
