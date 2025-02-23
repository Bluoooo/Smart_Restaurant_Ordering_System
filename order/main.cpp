#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QDateTime>
#include <array>
#include <string>
#include <QButtonGroup>
#include <QPalette>
#include <QFont>
#include <QGridLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <QTableWidget>
#include <QListWidget>
#include <QInputDialog>
#include <QTableWidget>
#include <QHeaderView>
#include <QList>
#include <QPair>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include "ui0.cpp"
#include "card.h"
#include "checkout_window.cpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    SecondWindow secondWindow;
    //secondWindow.show();
    //show_order_window(11);
    show_ui0();

    return app.exec();

  }
