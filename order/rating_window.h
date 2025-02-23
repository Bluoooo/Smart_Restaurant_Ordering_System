#ifndef RATING_WINDOW_H
#define RATING_WINDOW_H//Honorable Work by Ziqi ZHAO, 122090793


#include <QWidget>
#include <QLabel>//Honorable Work by Ziqi ZHAO, 122090793
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>//Honorable Work by Ziqi ZHAO, 122090793
#include <QMessageBox>
#include <QIcon>
#include <QString>//Honorable Work by Ziqi ZHAO, 122090793

class RatingWindow : public QWidget {//Honorable Work by Ziqi ZHAO, 122090793
    Q_OBJECT

public:
    explicit RatingWindow(std::string waiterid, QWidget *parent = nullptr);//Honorable Work by Ziqi ZHAO, 122090793

private slots:
    void submitRating(int score);
//Honorable Work by Ziqi ZHAO, 122090793
private:
    std::string waiterid;//Honorable Work by Ziqi ZHAO, 122090793
    QString buttonStyle = "font-size: 14px; padding: 10px; margin: 5px;";  // 按钮样式
};

#endif // RATING_WINDOW_H//Honorable Work by Ziqi ZHAO, 122090793
