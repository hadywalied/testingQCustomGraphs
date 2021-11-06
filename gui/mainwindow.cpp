#include "mainwindow.h"
#include <gui/reusableComponents/qcustomplot.h>
#include <gui/reusableComponents/ListView.h>
#include <gui/reusableComponents/flowlayout.h>


MainWindow::MainWindow() {
    setupUI();
}

void MainWindow::setupUI() {
    resize(1200, 800);
    set_toolbar_top();
    setLeftDockPlottingList();
    setRightDockPlottingSettings();
    setCentralPlottingArea();
    show();
}

void MainWindow::setCentralPlottingArea() {
//    gridLayout = new QGridLayout;

    customPlot = new QCustomPlot();

    addPlot("Plotting 1", {1, 2, 3, 4, 5, 6}, {2, 3, 4, 5, 6, 8}, true);
    addPlot("Plotting 2", {1, 2, 3, 4, 5, 6}, {2, 5, 4, 8, 6, 1}, false);

//    gridLayout->addWidget(customPlot);
//    QWidget *widget = new QWidget;
//    widget->setLayout(gridLayout);
    setCentralWidget(customPlot);
}

void MainWindow::setLeftDockPlottingList() {
    QDockWidget *dock;
    dock = new QDockWidget(tr("Plots"), this);


    dock->setAllowedAreas(Qt::LeftDockWidgetArea);

    QAction *action = dock->toggleViewAction();
    action->setText("Plots");
    toolbar->addAction(action);


    list_view = new ListView();
    dock->setWidget(list_view);

    addDockWidget(Qt::LeftDockWidgetArea, dock);

    connect(list_view, SIGNAL(itemClicked(QListWidgetItem * )), SLOT(onListItemSelected()));
}

void MainWindow::setRightDockPlottingSettings() {
    auto *dock = new QDockWidget(tr("Settings"), this);

    dock->setAllowedAreas(Qt::RightDockWidgetArea);

    QAction *action = dock->toggleViewAction();
    action->setText("Settings");
    toolbar->addAction(action);

    auto *widget = new QWidget();
    auto *layout = new QVBoxLayout();

    auto w = new QWidget();
    auto flowLayout = new FlowLayout();
    QPushButton *qButton = new QPushButton("Item Number 1");
    QPushButton *wButton = new QPushButton("Item Number 2");

    flowLayout->addWidget(qButton);
    flowLayout->addWidget(wButton);

    w->setLayout(flowLayout);
    layout->addWidget(w);

    QPushButton *pButton = new QPushButton("Plot");
    layout->addWidget(pButton);
    connect(pButton, SIGNAL(clicked()), SLOT(onPlotButtonClicked()));

    QPushButton *aButton = new QPushButton("Append");
    layout->addWidget(aButton);
    connect(aButton, SIGNAL(clicked()), SLOT(onAppendButtonClicked()));

    widget->setLayout(layout);

    dock->setWidget(widget);


    addDockWidget(Qt::RightDockWidgetArea, dock);
}

void MainWindow::set_toolbar_top() {
    toolbar = new QToolBar(this);

    toolbar->setFloatable(false);
    toolbar->setMovable(false);

    addToolBar(Qt::TopToolBarArea, toolbar);

}

void MainWindow::onPlotButtonClicked() {
    addPlot("newPlot", {1, 2, 3, 4, 5, 6, 7, 8}, {10, 120, 30, 40, 50, 60, 70, 80}, std::rand() % 2);
}

void MainWindow::addPlot(const QString &title, const QVector<double> &xdata,
                         const QVector<double> &ydata, bool linePlot) {
    customPlot->clearGraphs();
    customPlot->addGraph();
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    int r = std::rand() % 155 + 100;
    int g = std::rand() % 155 + 100;
    int b = std::rand() % 155 + 100;
    QColor color(r, g, b, 255);
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    customPlot->graph()->setPen(QPen(color, 2));
    customPlot->graph()->setName(title);
    customPlot->graph()->setScatterStyle(QCPScatterStyle::ssCircle);
    if (linePlot)
        customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    else
        customPlot->graph()->setLineStyle(QCPGraph::lsNone);

    customPlot->xAxis->setLabel("X");
    customPlot->yAxis->setLabel("Y");
    customPlot->xAxis->setRange(-6000, 100);
    customPlot->yAxis->setRange(-6000, 8000);

    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                QCP::iSelectLegend | QCP::iSelectPlottables);

    customPlot->axisRect()->setupFullAxesBox();

    QFont legendFont = font();
    legendFont.setPointSize(10);

    customPlot->legend->setVisible(false);
    customPlot->legend->setFont(legendFont);
    customPlot->legend->setSelectedFont(legendFont);
    customPlot->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items
// show legend with slightly transparent background brush:
    customPlot->legend->setBrush(QColor(255, 255, 255, 150));
    customPlot->graph()->setData(xdata, ydata);

    customPlot->rescaleAxes();
    customPlot->replot();
    customPlot->update();

    auto data = customPlot->toPixmap(400, 400);
    auto pix = QPixmap(data);

    auto settings = new PlotSettings();

    currentPlotSettings = *settings;

    auto pData = new PlotData(QVector<QVector<double>>{xdata}, QVector<QVector<double>>{ydata},
                              QVector<bool>{linePlot},
                              QVector<QColor>{color}, QVector<QString>{title});

    currentPlotData = *pData;

    list_view->addPlotItem(pix, title, *settings, *pData);

    customPlot->legend->setVisible(true);
    customPlot->rescaleAxes();
    customPlot->replot();
    customPlot->update();
}

void MainWindow::appendPlot(const QString &title, const QVector<double> &xdata, const QVector<double> &ydata,
                            bool linePlot) {
    customPlot->addGraph();
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    int r = std::rand() % 155 + 100;
    int g = std::rand() % 155 + 100;
    int b = std::rand() % 155 + 100;
    QColor color(r, g, b, 255);
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    customPlot->graph()->setPen(QPen(color, 2));
    customPlot->graph()->setName(title);
    customPlot->graph()->setScatterStyle(QCPScatterStyle::ssCircle);
    if (linePlot)
        customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    else
        customPlot->graph()->setLineStyle(QCPGraph::lsNone);

    customPlot->xAxis->setLabel("X");
    customPlot->yAxis->setLabel("Y");
    customPlot->xAxis->setRange(-6000, 100);
    customPlot->yAxis->setRange(-6000, 8000);

    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                QCP::iSelectLegend | QCP::iSelectPlottables);

    customPlot->axisRect()->setupFullAxesBox();

    QFont legendFont = font();
    legendFont.setPointSize(10);

    customPlot->legend->setVisible(false);
    customPlot->legend->setFont(legendFont);
    customPlot->legend->setSelectedFont(legendFont);
    customPlot->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items
// show legend with slightly transparent background brush:
    customPlot->legend->setBrush(QColor(255, 255, 255, 150));
    customPlot->graph()->setData(xdata, ydata);

    customPlot->rescaleAxes();
    customPlot->replot();
    customPlot->update();

    auto data = customPlot->toPixmap(400, 400);
    auto pix = QPixmap(data);

    auto settings = new PlotSettings(); //TODO: set the settings

    currentPlotData.xdataList.push_back(xdata);
    currentPlotData.ydataList.push_back(ydata);
    currentPlotData.linePlot.push_back(linePlot);
    currentPlotData.color.push_back(color);
    currentPlotData.plotTitle.push_back(title);


    auto pData = currentPlotData;

    list_view->addPlotItem(pix, title, *settings, pData);

    customPlot->legend->setVisible(true);
    customPlot->rescaleAxes();
    customPlot->replot();
    customPlot->update();
}

void MainWindow::onAppendButtonClicked() {
    appendPlot("Appended Plot", {2, 4, 6, 8, 10}, {10, 8, 6, 4, 2}, true);
}

void MainWindow::onListItemSelected() {
    auto item = list_view->currentItem();
    QVariant title = item->data(Qt::UserRole + 1);
    QVariant var_settings = item->data(Qt::UserRole + 2);
    QVariant var_data = item->data(Qt::UserRole + 3);

    auto data = var_data.value<PlotData>();
    auto settings = var_data.value<PlotSettings>();

    currentPlotData = data;
    currentPlotSettings = settings;
    customPlot->clearGraphs();

    for (int i = 0; i < data.linePlot.size(); ++i) {
        customPlot->addGraph();

        customPlot->graph()->setLineStyle(QCPGraph::lsLine);
        customPlot->graph()->setPen(QPen(data.color[i], 2));
        customPlot->graph()->setName(data.plotTitle[i]);
        customPlot->graph()->setScatterStyle(QCPScatterStyle::ssCircle);
        if (data.linePlot[i])
            customPlot->graph()->setLineStyle(QCPGraph::lsLine);
        else
            customPlot->graph()->setLineStyle(QCPGraph::lsNone);

        customPlot->xAxis->setLabel("X");
        customPlot->yAxis->setLabel("Y");
        customPlot->xAxis->setRange(-6000, 100);
        customPlot->yAxis->setRange(-6000, 8000);

        customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);

        customPlot->axisRect()->setupFullAxesBox();

        QFont legendFont = font();
        legendFont.setPointSize(10);

        customPlot->legend->setVisible(true);
        customPlot->legend->setFont(legendFont);
        customPlot->legend->setSelectedFont(legendFont);
        customPlot->legend->setSelectableParts(
                QCPLegend::spItems); // legend box shall not be selectable, only legend items
// show legend with slightly transparent background brush:
        customPlot->legend->setBrush(QColor(255, 255, 255, 150));
        customPlot->graph()->setData(data.xdataList[i], data.ydataList[i]);

        customPlot->rescaleAxes();
        customPlot->replot();
        customPlot->update();

    }

}

