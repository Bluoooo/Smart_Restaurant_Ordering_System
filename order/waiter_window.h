// EmployeeQueryWindow.h//Honorable Work by Ziqi ZHAO, 122090793
#ifndef EMPLOYEEQUERYWINDOW_H
#define EMPLOYEEQUERYWINDOW_H

#include <QWidget>
#include <QPushButton>//Honorable Work by Ziqi ZHAO, 122090793
#include <QLineEdit>
#include <QTableWidget>
#include <QLabel>//Honorable Work by Ziqi ZHAO, 122090793

class EmployeeQueryWindow : public QWidget {//Honorable Work by Ziqi ZHAO, 122090793
    Q_OBJECT

public:
    EmployeeQueryWindow(QWidget *parent = nullptr);
    ~EmployeeQueryWindow();//Honorable Work by Ziqi ZHAO, 122090793

private:
    QPushButton *queryButton;
    QPushButton *backButton;
    QLineEdit *idInput;//Honorable Work by Ziqi ZHAO, 122090793
    QTableWidget *resultsTable;
};

#endif // EMPLOYEEQUERYWINDOW_H//Honorable Work by Ziqi ZHAO, 122090793
