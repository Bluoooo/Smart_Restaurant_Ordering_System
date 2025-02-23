#include "timermanager.h"

TimerManager::TimerManager(QObject *parent) : QObject(parent) {}

TimerManager::~TimerManager() {
    for (auto timer : timers) {
        timer->stop();
        delete timer;
    }
    for (auto elapsed : timeData) {
        delete elapsed;
    }
}

void TimerManager::startTimer(int tableId) {
    if (!timers.contains(tableId)) {
        timers[tableId] = new QTimer(this);
        timeData[tableId] = new QElapsedTimer();
        timeData[tableId]->start();

        connect(timers[tableId], &QTimer::timeout, [this, tableId]() {
            QString elapsedTime = getElapsedTime(tableId);
            emit timerUpdated(tableId, elapsedTime);
        });

        timers[tableId]->start(1000);
    }
}

void TimerManager::stopTimer(int tableId) {
    if (timers.contains(tableId)) {
        timers[tableId]->stop();
    }
}

QString TimerManager::getElapsedTime(int tableId) const {
    if (timeData.contains(tableId)) {
        qint64 elapsed = timeData[tableId]->elapsed();
        int hours = elapsed / (1000 * 60 * 60);
        int minutes = (elapsed / (1000 * 60)) % 60;
        int seconds = (elapsed / 1000) % 60;
        return QString("%1:%2:%3")
            .arg(hours, 2, 10, QChar('0'))
            .arg(minutes, 2, 10, QChar('0'))
            .arg(seconds, 2, 10, QChar('0'));
    }
    return "00:00:00";
}
