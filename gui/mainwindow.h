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
#include <gui/reusableComponents/flowlayout.h>

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow();

    QToolBar *toolbar{};
    QCustomPlot *currentCustomPlot;
//    QGridLayout *gridLayout;
    FlowLayout *flowlayout;
    ListView *list_view;
    PlotData currentPlotData;
    PlotSettings currentPlotSettings;
    QVector<QWidget *> widgetList{};
    QScrollArea *scroll;

private:
    void setupUI();

    void setCentralPlottingArea();

    void setLeftDockPlottingList();

    void setRightDockPlottingSettings();

    void addPlot(const QString &title, const QVector<double> &xdata, const QVector<double> &ydata, bool linePlot);

    void appendPlot(const QString &title, const QVector<double> &xdata, const QVector<double> &ydata, bool linePlot);

    void set_toolbar_top();

    void dynamicWidgetSizeAdjusting();

    void addFlowWidget(QWidget *customPlot);

public slots:

    void onPlotButtonClicked();

    void onAppendButtonClicked();

    void onListItemSelected();

    void ShowContextMenu(const QPoint &pos) const;

    void menu_addNewPlot();

    void menu_appendToCurrentPlot();


};

#endif // MAINWINDOW_H
