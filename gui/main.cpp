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
