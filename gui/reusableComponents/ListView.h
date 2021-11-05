//
// Created by himep on 11/3/2021.
//

#ifndef TESTINGNOFORMS_LISTVIEW_H
#include <QListWidget>
#include <gui/dataModels/PlotSettings.h>
#include <gui/dataModels/PlotData.h>

#define TESTINGNOFORMS_LISTVIEW_H


class ListView : public QListWidget{
Q_OBJECT

public:
    explicit ListView(QWidget *parent = nullptr);
    void addPlotItem(const QPixmap &pixmap,  QString plotTitle, PlotSettings Settings, PlotData data);

};


#endif //TESTINGNOFORMS_LISTVIEW_H
