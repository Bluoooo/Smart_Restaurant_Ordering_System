#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <QMap>

class TimerManager : public QObject {
    Q_OBJECT

public:
    explicit TimerManager(QObject *parent = nullptr);
    ~TimerManager();

    void startTimer(int tableId);
    void stopTimer(int tableId);
    QString getElapsedTime(int tableId) const;

signals:
    void timerUpdated(int tableId, const QString &time);

private:
    QMap<int, QTimer *> timers;           // 每张桌子的计时器
    QMap<int, QElapsedTimer *> timeData; // 用于记录启动时间
};

#endif // TIMERMANAGER_H
