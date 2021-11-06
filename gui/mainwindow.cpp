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

    currentCustomPlot = new QCustomPlot();
    currentCustomPlot->setMinimumSize(400, 400);
    currentCustomPlot->setMaximumSize(800, 800);
    currentCustomPlot->setSizeIncrement(100, 100);
    QSizePolicy policy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    currentCustomPlot->setSizePolicy(policy);

    scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setCentralWidget(scroll);

    flowlayout = new FlowLayout();
    centerWidget = new QWidget;
    centerWidget->setLayout(flowlayout);
    scroll->setWidget(centerWidget);

    addPlot("Plotting 1", {1, 2, 3, 4, 5, 6}, {2, 3, 4, 5, 6, 8}, true);
    addPlot("Plotting 2", {1, 2, 3, 4, 5, 6}, {2, 5, 4, 8, 6, 1}, false);

    addFlowWidget(currentCustomPlot);

//    setCentralWidget(currentCustomPlot);
}

void MainWindow::addFlowWidget(QWidget *w) {
    widgetList.push_back(w);
//    for(auto w : widgetList){
//        flowlayout->removeWidget(w);
//    }
    flowlayout->addWidget(w);
    dynamicWidgetSizeAdjusting();
}

void MainWindow::dynamicWidgetSizeAdjusting() {
    if (widgetList.size() < 2) {
        scroll->setWidget(widgetList[0]);
    } else if (widgetList.size() < 4) {
        for (auto w1 : widgetList) {
            w1->setMinimumSize(400, 400);
        }
        scroll->setWidget(centerWidget);
//        setCentralWidget(scroll);
    } else {
        for (auto w1 : widgetList) {
            w1->setMinimumSize(200, 200);
        }
        scroll->setWidget(centerWidget);
//        setCentralWidget(scroll);
    }
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
    list_view->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(list_view, SIGNAL(itemClicked(QListWidgetItem * )), SLOT(onListItemSelected()));
    connect(list_view, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(ShowContextMenu(QPoint)));
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
    currentCustomPlot->clearGraphs();
    currentCustomPlot->addGraph();
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    int r = std::rand() % 155 + 100;
    int g = std::rand() % 155 + 100;
    int b = std::rand() % 155 + 100;
    QColor color(r, g, b, 255);
    currentCustomPlot->graph()->setLineStyle(QCPGraph::lsLine);
    currentCustomPlot->graph()->setPen(QPen(color, 2));
    currentCustomPlot->graph()->setName(title);
    currentCustomPlot->graph()->setScatterStyle(QCPScatterStyle::ssCircle);
    if (linePlot)
        currentCustomPlot->graph()->setLineStyle(QCPGraph::lsLine);
    else
        currentCustomPlot->graph()->setLineStyle(QCPGraph::lsNone);

    currentCustomPlot->xAxis->setLabel("X");
    currentCustomPlot->yAxis->setLabel("Y");
    currentCustomPlot->xAxis->setRange(-6000, 100);
    currentCustomPlot->yAxis->setRange(-6000, 8000);

    currentCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                       QCP::iSelectLegend | QCP::iSelectPlottables);

    currentCustomPlot->axisRect()->setupFullAxesBox();

    QFont legendFont = font();
    legendFont.setPointSize(10);

    currentCustomPlot->legend->setVisible(false);
    currentCustomPlot->legend->setFont(legendFont);
    currentCustomPlot->legend->setSelectedFont(legendFont);
    currentCustomPlot->legend->setSelectableParts(
            QCPLegend::spItems); // legend box shall not be selectable, only legend items
// show legend with slightly transparent background brush:
    currentCustomPlot->legend->setBrush(QColor(255, 255, 255, 150));
    currentCustomPlot->graph()->setData(xdata, ydata);

    currentCustomPlot->rescaleAxes();
    currentCustomPlot->replot();
    currentCustomPlot->update();

    auto data = currentCustomPlot->toPixmap(400, 400);
    auto pix = QPixmap(data);

    auto settings = new PlotSettings();

    currentPlotSettings = *settings;

    auto pData = new PlotData(QVector<QVector<double>>{xdata}, QVector<QVector<double>>{ydata},
                              QVector<bool>{linePlot},
                              QVector<QColor>{color}, QVector<QString>{title});

    currentPlotData = *pData;

    list_view->addPlotItem(pix, title, *settings, *pData);

    currentCustomPlot->legend->setVisible(true);
    currentCustomPlot->rescaleAxes();
    currentCustomPlot->replot();
    currentCustomPlot->update();
}

void MainWindow::appendPlot(const QString &title, const QVector<double> &xdata, const QVector<double> &ydata,
                            bool linePlot) {
    currentCustomPlot->addGraph();
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    int r = std::rand() % 155 + 100;
    int g = std::rand() % 155 + 100;
    int b = std::rand() % 155 + 100;
    QColor color(r, g, b, 255);
    currentCustomPlot->graph()->setLineStyle(QCPGraph::lsLine);
    currentCustomPlot->graph()->setPen(QPen(color, 2));
    currentCustomPlot->graph()->setName(title);
    currentCustomPlot->graph()->setScatterStyle(QCPScatterStyle::ssCircle);
    if (linePlot)
        currentCustomPlot->graph()->setLineStyle(QCPGraph::lsLine);
    else
        currentCustomPlot->graph()->setLineStyle(QCPGraph::lsNone);

    currentCustomPlot->xAxis->setLabel("X");
    currentCustomPlot->yAxis->setLabel("Y");
    currentCustomPlot->xAxis->setRange(-6000, 100);
    currentCustomPlot->yAxis->setRange(-6000, 8000);

    currentCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                       QCP::iSelectLegend | QCP::iSelectPlottables);

    currentCustomPlot->axisRect()->setupFullAxesBox();

    QFont legendFont = font();
    legendFont.setPointSize(10);

    currentCustomPlot->legend->setVisible(false);
    currentCustomPlot->legend->setFont(legendFont);
    currentCustomPlot->legend->setSelectedFont(legendFont);
    currentCustomPlot->legend->setSelectableParts(
            QCPLegend::spItems); // legend box shall not be selectable, only legend items
// show legend with slightly transparent background brush:
    currentCustomPlot->legend->setBrush(QColor(255, 255, 255, 150));
    currentCustomPlot->graph()->setData(xdata, ydata);

    currentCustomPlot->rescaleAxes();
    currentCustomPlot->replot();
    currentCustomPlot->update();

    auto data = currentCustomPlot->toPixmap(400, 400);
    auto pix = QPixmap(data);

    auto settings = new PlotSettings(); //TODO: set the settings

    currentPlotData.xdataList.push_back(xdata);
    currentPlotData.ydataList.push_back(ydata);
    currentPlotData.linePlot.push_back(linePlot);
    currentPlotData.color.push_back(color);
    currentPlotData.plotTitle.push_back(title);


    auto pData = currentPlotData;

    list_view->addPlotItem(pix, title, *settings, pData);

    currentCustomPlot->legend->setVisible(true);
    currentCustomPlot->rescaleAxes();
    currentCustomPlot->replot();
    currentCustomPlot->update();
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
    currentCustomPlot->clearGraphs();

    for (int i = 0; i < data.linePlot.size(); ++i) {
        currentCustomPlot->addGraph();

        currentCustomPlot->graph()->setLineStyle(QCPGraph::lsLine);
        currentCustomPlot->graph()->setPen(QPen(data.color[i], 2));
        currentCustomPlot->graph()->setName(data.plotTitle[i]);
        currentCustomPlot->graph()->setScatterStyle(QCPScatterStyle::ssCircle);
        if (data.linePlot[i])
            currentCustomPlot->graph()->setLineStyle(QCPGraph::lsLine);
        else
            currentCustomPlot->graph()->setLineStyle(QCPGraph::lsNone);

        currentCustomPlot->xAxis->setLabel("X");
        currentCustomPlot->yAxis->setLabel("Y");
        currentCustomPlot->xAxis->setRange(-6000, 100);
        currentCustomPlot->yAxis->setRange(-6000, 8000);

        currentCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                           QCP::iSelectLegend | QCP::iSelectPlottables);

        currentCustomPlot->axisRect()->setupFullAxesBox();

        QFont legendFont = font();
        legendFont.setPointSize(10);

        currentCustomPlot->legend->setVisible(true);
        currentCustomPlot->legend->setFont(legendFont);
        currentCustomPlot->legend->setSelectedFont(legendFont);
        currentCustomPlot->legend->setSelectableParts(
                QCPLegend::spItems); // legend box shall not be selectable, only legend items
// show legend with slightly transparent background brush:
        currentCustomPlot->legend->setBrush(QColor(255, 255, 255, 150));
        currentCustomPlot->graph()->setData(data.xdataList[i], data.ydataList[i]);

        currentCustomPlot->rescaleAxes();
        currentCustomPlot->replot();
        currentCustomPlot->update();

    }

}

void MainWindow::ShowContextMenu(const QPoint &pos) const // this is a slot
{
    // Handle global position
    QPoint globalPos = list_view->mapToGlobal(pos);

    // Create menu and insert some actions
    QMenu myMenu;
    myMenu.addAction("Add to New Plot", this, SLOT(menu_addNewPlot()));
    myMenu.addAction("Append to Current Plot", this, SLOT(menu_appendToCurrentPlot()));

    // Show context menu at handling position
    myMenu.exec(globalPos);
}

void MainWindow::menu_addNewPlot() {
    auto *w = new QCustomPlot();
    w->setMinimumSize(400, 400);
    addFlowWidget(w);
}


void MainWindow::menu_appendToCurrentPlot() {

}