#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QListView>
#include <QSplitter>
#include <gui/reusableComponents/qcustomplot.h>
#include <gui/reusableComponents/ListView.h>

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow();

    QToolBar *toolbar{};
    QCustomPlot *customPlot;
//    QGridLayout *gridLayout;
    ListView *list_view;
    PlotData currentPlotData;
    PlotSettings currentPlotSettings;

private:
    void setupUI();

    void setCentralPlottingArea();

    void setLeftDockPlottingList();

    void setRightDockPlottingSettings();

    void addPlot(const QString& title, const QVector<double>& xdata, const QVector<double>& ydata, bool linePlot);
    void appendPlot(const QString& title, const QVector<double>& xdata, const QVector<double>& ydata, bool linePlot);

    void set_toolbar_top();

public slots:
    void onPlotButtonClicked();
    void onAppendButtonClicked();
    void onListItemSelected();
};

#endif // MAINWINDOW_H
