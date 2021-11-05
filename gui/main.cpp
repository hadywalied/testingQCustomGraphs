#include "mainwindow.h"

#include <QStringListModel>

#include <QApplication>
#include <QComboBox>
#include <QListView>
#include <QSplitter>

int main(int argc, char *argv[]) {
  QApplication app{argc, argv};
  MainWindow *window = new MainWindow();
  return app.exec();
}

//
//#include <QtGui>
//#include <QVBoxLayout>
//#include <QPushButton>
//#include <QListWidgetItem>
//#include <QListWidget>
//#include <QLabel>
//#include <QApplication>
//
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//
//    QWidget window;
//
//    QLabel* title = new QLabel("Custom widgets on a QListWidget");
//    title->setAlignment(Qt::AlignHCenter);
//
//    QListWidget* list = new QListWidget;
//    list->addItem("foo");
//
//    QListWidgetItem* item;
//    item = new QListWidgetItem(list);
//    list->addItem(item);
//    QPushButton* button = new QPushButton("hey");
//    item->setSizeHint(button->minimumSizeHint());
//    list->setItemWidget(item, button);
//
//    list->addItem("bar");
//
//    QVBoxLayout* layout = new QVBoxLayout(&window);
//    layout->addWidget(title);
//    layout->addWidget(list);
//    window.setLayout(layout);
//
//    window.show();
//
//    return a.exec();
//}