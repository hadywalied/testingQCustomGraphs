//
// Created by himep on 11/1/2021.
//

#ifndef TESTINGNOFORMS_PLOTDATA_H

#include <QObject>
#include <utility>
#include <QColor>

#define TESTINGNOFORMS_PLOTDATA_H


class PlotData {


public:
    PlotData();

    PlotData(const QVector<QVector<double>> &xdataList, const QVector<QVector<double>> &ydataList,
             const QVector<bool> &linePlot, const QVector<QColor> &color, const QVector<QString> &plotTitle);

    QVector<QVector<double>> xdataList, ydataList;
    QVector<bool> linePlot;
    QVector<QColor> color;
    QVector<QString> plotTitle;
};

Q_DECLARE_METATYPE(PlotData);


#endif //TESTINGNOFORMS_PLOTDATA_H
