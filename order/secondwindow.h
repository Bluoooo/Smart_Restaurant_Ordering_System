#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QInputDialog>
#include <QButtonGroup>
#include <QMap>
#include <QTimer>
#include <QTime>

class SecondWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

signals:
    void switchToMainWindow(int tableId); // 跳转到 MainWindow 的信号

private:
    QPushButton *table_buttons[25]; // 桌子按钮
    int customerNumbers[25]; // 存储每个桌子输入的人数
    std::string serverIds[25];
    QLabel *information_label;      // 右侧 Order Information
    QLabel *information_title;      // 右侧标题
    QGridLayout *layout;            // 按钮布局
    QWidget *centralWidget;         // 中心部件

    void setupUI();
    void setupConnections();

    QTimer *timers[25];             // 每个桌子对应一个计时器
    QTime elapsedTimes[25];         // 存储每个桌子的计时时间

};

#endif // SECONDWINDOW_H
