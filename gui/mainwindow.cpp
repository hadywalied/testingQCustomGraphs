#include "mainwindow.h"
#include <gui/reusableComponents/qcustomplot.h>




MainWindow::MainWindow()
{
    setupUI();
}

void MainWindow::setupUI(){
    resize(1200,800);
    setCentralPlottingArea();
    setLeftDockPlottingList();
    setRightDockPlottingSettings();
    show();
}

void MainWindow::setCentralPlottingArea(){

    auto *customPlot = new QCustomPlot();

    customPlot->addGraph();
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    customPlot->xAxis->setLabel("X");
    customPlot->yAxis->setLabel("Y");
    customPlot->xAxis->setRange(-6000,100);
    customPlot->yAxis->setRange(-6000,8000);

    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                       QCP::iSelectLegend | QCP::iSelectPlottables);

    customPlot->axisRect()->setupFullAxesBox();
    customPlot->plotLayout()->insertRow(0);
    auto *title = new QCPTextElement( customPlot, "Plotting Area", QFont("sans", 17, QFont::Bold));
    customPlot->plotLayout()->addElement(0, 0, title);
    customPlot->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    customPlot->legend->setFont(legendFont);
    customPlot->legend->setSelectedFont(legendFont);
    customPlot->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items

    QVector<double> x = {1,2,3,4,5} , y = {2,4,6,1,2};

    customPlot->graph(0)->setData(x,y);

    customPlot->rescaleAxes();
    customPlot->replot();
    customPlot->update();

    customPlot->addGraph();
    customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssCircle);
    customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    QVector<double> x1 = {1,2,3,4,5} , y1 = {1,2,3,4,5};

    customPlot->graph(1)->setData(x1,y1);


    setCentralWidget(customPlot);
}

void MainWindow::setLeftDockPlottingList(){
    auto *dock = new QDockWidget(tr("Plots"),this);
    auto  *toolbar = new QToolBar(this);

    toolbar->setFloatable(false);
    toolbar->setMovable(false);


    addToolBar(Qt::LeftToolBarArea,toolbar);

    dock->setAllowedAreas(Qt::LeftDockWidgetArea);

    QAction *action = dock->toggleViewAction();
    action ->setText("Plots");
    toolbar->addAction(action);

    auto model = new QStringListModel{this};
    model->setStringList(QStringList{"Gandalf", "Aragorn", "Legolas", "Samwise Gamgee" ,"Gimli", "Bilbo Baggins", "Peregrin Took", "Boromir"});
    auto combo_box_view = new QComboBox();
    combo_box_view->setModel(model);

    auto list_view = new QListView();
    list_view->setModel(model);

    dock->setWidget(list_view);

    addDockWidget(Qt::LeftDockWidgetArea,dock);
}


void MainWindow::setRightDockPlottingSettings(){
    auto *dock = new QDockWidget(tr("Settings"),this);
    auto  *toolbar = new QToolBar(this);

    toolbar->setFloatable(false);
    toolbar->setMovable(false);


    addToolBar(Qt::RightToolBarArea,toolbar);

    dock->setAllowedAreas(Qt::RightDockWidgetArea);

    QAction *action = dock->toggleViewAction();
    action ->setText("Settings");
    toolbar->addAction(action);

    auto *widget = new QWidget();
    auto *layout = new QVBoxLayout();

    auto model = new QStringListModel{this};
    model->setStringList(QStringList{"Gandalf", "Aragorn", "Legolas", "Samwise Gamgee" ,"Gimli", "Bilbo Baggins", "Peregrin Took", "Boromir"});
    auto combo_box_view = new QComboBox();
    combo_box_view->setModel(model);

    auto list_view = new QListView();
    list_view->setModel(model);

    layout->addWidget(list_view);
    layout->addWidget(new QPushButton("Plot"));
    widget->setLayout(layout);

    dock->setWidget(widget);


    addDockWidget(Qt::RightDockWidgetArea,dock);
}
