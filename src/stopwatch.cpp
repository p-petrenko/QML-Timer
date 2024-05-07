#include "stopwatch.h"

#include <QDebug>
#include <QTimer>
#include <chrono>

#define ZERO_TIME "00:00,0"
#define TIMER_PERIOD 100

Stopwatch::Stopwatch(QObject *parent)
    : QObject(parent), m_milliseconds(0), m_time(ZERO_TIME)
{
    m_timer = new QTimer(this);
    QObject::connect(m_timer, &QTimer::timeout, this, &Stopwatch::addMilliSeconds);
}

void Stopwatch::addMilliSeconds()
{
    m_milliseconds += TIMER_PERIOD;
    int minutes = (m_milliseconds / 1000) / 60;
    int seconds = (m_milliseconds / 1000) % 60;
    int mlseconds = (m_milliseconds % 1000) / TIMER_PERIOD;

    const QString str = QString::asprintf("%02d:%02d,%01d", minutes, seconds, mlseconds);
    setTime(str);
    //qDebug() << m_milliseconds;
}

QString Stopwatch::time() const
{
    return m_time;
}

void Stopwatch::setTime(const QString& newTime)
{
    if (newTime == m_time)
        return;
    m_time = newTime;
    emit timeChanged();
}

bool Stopwatch::isActive() const
{
    return m_isActive;
}

// Starts or stops timer
void Stopwatch::setIsActive(bool isActive)
{
    if (isActive == m_isActive)
        return;
    m_isActive = isActive;
    isActive ? m_timer->start(TIMER_PERIOD) : m_timer->stop();

    if (!m_isStarted)
        setIsStarted(true);

    emit isActiveChanged(isActive);
}

bool Stopwatch::isStarted() const
{
    return m_isStarted;
}

void Stopwatch::setIsStarted(bool isStarted)
{
    if (isStarted == m_isStarted)
        return;
    m_isStarted = isStarted;
    emit isStartedChanged(isStarted);
}

void Stopwatch::reset()
{
    m_timer->stop();
    m_isActive = false;
    m_isStarted = false;
    m_time = ZERO_TIME;
    m_milliseconds = 0;
    emit timeChanged();
    emit isActiveChanged(m_isActive);
    emit isStartedChanged(m_isStarted);
}
