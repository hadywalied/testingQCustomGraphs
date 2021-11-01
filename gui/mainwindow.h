#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QListView>
#include <QSplitter>
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow();

private:
    void setupUI();
    void setCentralPlottingArea();
    void setLeftDockPlottingList();
    void setRightDockPlottingSettings();

signals:

};

#endif // MAINWINDOW_H
