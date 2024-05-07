#include "countdown.h"
#include <QDebug>
#include <QCoreApplication>

Countdown::Countdown(QObject *parent)
    : QObject(parent)
{
    m_timer = new QTimer(this);
    m_player = new QMediaPlayer(this);
    QObject::connect(m_timer, &QTimer::timeout, this, &Countdown::changeTime);
    QObject::connect(m_player, &QMediaPlayer::durationChanged, this, [&](qint64 dur) {
        qDebug() << "Duration " << dur;
    });

    QObject::connect(m_player, &QMediaPlayer::stateChanged, this, [&]( QMediaPlayer::State state) {
        qDebug() << "State Changed " << state;
        setIsPlaying(false);
    });
}

void Countdown::changeTime()
{
    setTime(m_time.addSecs(-1));

    if (m_time <= QTime(0,0,0))
    {
        finishTimerWithMelody();
        reset();
    }
}

QStringList Countdown::time() const
{
    QString timeHour = QString::asprintf("%02d", m_time.hour());
    QString timeMinute = QString::asprintf("%02d", m_time.minute());
    QString timeSecond = QString::asprintf("%02d", m_time.second());
    return { timeHour, timeMinute, timeSecond };
}

void Countdown::setTime(const QTime newTime)
{
    if (newTime == m_time)
        return;
    m_time = newTime;
    emit timeChanged();
}

bool Countdown::isPlaying() const
{
    return m_isPlaying;
}

void Countdown::setIsPlaying(bool isFinished)
{
    if (isFinished == m_isPlaying)
        return;
    m_isPlaying = isFinished;
    qDebug() << "isFinished is " << m_isPlaying;
    emit timerFinished(isFinished);
}

QString Countdown::pathToMusic() const {
    auto pathStr = QCoreApplication::applicationDirPath();
    int pos = pathStr.lastIndexOf(QChar('/'));
    return pathStr.left(pos) + "/Timer/music/";
}

void Countdown::finishTimerWithMelody()
{
    std::map<QString,QString> namesMap {
        {"drums 1", "rhythmical_drums1"},
        {"drums 2", "rhythmical_drums2"},
        {"fretless bass", "anxious_fretless_bass"},
        {"piano 1", "piano"},
        {"piano 2", "piano2"},
        {"piano 3", "piano3"},
        {"piano 4", "piano4"},
        {"piano 5", "piano5"},
        {"synthesizer", "piano_synth"},
        {"electrosound 1", "electronic_sound2"},
        {"electrosound 2", "electronic_sound3"},
        {"electrosound 3", "electronic_sound4"},
        {"electrosound 4", "electronic_sound6"},
        {"electrosound 5", "anxious_violin"},
        {"lullaby", "bottle_sound"},
        {"seagulls and foghorn", "seagulls_and_foghorn"},
        {"wobble", "wobble"},
        {"sleigh bells", "sleigh_bells"}
    };
    QString mName = melodyName();
    QString fileName = namesMap[mName];
    m_player->setMedia(QUrl::fromLocalFile(pathToMusic() + fileName + ".mp3"));
    m_player->setVolume(50);
    m_player->play();
    setIsPlaying(true);
    reset();
}

bool Countdown::isStarted() const
{
    return m_isStarted;
}

void Countdown::setIsStarted(bool isStarted)
{
    if (m_isStarted == isStarted)
        return;
    m_isStarted = isStarted;
    emit isStartedChanged(m_isStarted);
}

bool Countdown::isActive() const
{
    return m_isActive;
}

// Starts or stops timer
void Countdown::setIsActive(bool isActive)
{
    if (isActive == m_isActive)
        return;
    m_isActive = isActive;
    emit isActiveChanged(isActive);
}

QString Countdown::melodyName() const
{
    return m_sqlitemanager.selectedMelody();
}

void Countdown::setMelodyName(QString name)
{
    if (name == m_sqlitemanager.selectedMelody())
        return;
    m_sqlitemanager.updateSelectedMelody(name);
    emit melodyNameChanged(name);
}

QStringList Countdown::melodyNames()
{
    return m_sqlitemanager.melodies();
}

QTime Countdown::convertFromStrListToTime(const QStringList hrMinSecList)
{
    int hr = hrMinSecList[0].toInt();
    int min = hrMinSecList[1].toInt();
    int sec = hrMinSecList[2].toInt();
    QTime newTime = QTime(hr,min,sec);
    return newTime;
}

void Countdown::startOrPause(const QStringList hrMinSecList)
{
    if (!m_isStarted)
    {
        setTime(convertFromStrListToTime(hrMinSecList));
        setIsStarted(true);
    }

    setIsActive(!m_isActive);
    m_isActive ? m_timer->start(1000) : m_timer->stop();
}

void Countdown::reset()
{
    setIsActive(false);
    setIsStarted(false);
    m_timer->stop();
    m_time.setHMS(0,0,0);
    emit timeChanged();
}

void Countdown::stopMelody()
{
    m_player->stop();
}
