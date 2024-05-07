#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>

class Stopwatch : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString time READ time NOTIFY timeChanged)
    Q_PROPERTY(bool isActive READ isActive WRITE setIsActive NOTIFY isActiveChanged)
    Q_PROPERTY(bool isStarted READ isStarted NOTIFY isStartedChanged)
public:
    explicit Stopwatch(QObject *parent = nullptr);

    QString time() const;

    bool isActive() const;
    void setIsActive(bool isActive);

    bool isStarted() const;

    Q_INVOKABLE void reset();

signals:
    void timeChanged();
    void isActiveChanged(bool isActive);
    void isStartedChanged(bool isStarted);

private slots:
    void addMilliSeconds();

private:
    int m_milliseconds;
    QString m_time;
    bool m_isActive = false;
    bool m_isStarted = false;
    QTimer* m_timer;

    void startTimer();
    void setTime(const QString& newTime);
    void setIsStarted(bool isStarted);
};

#endif
