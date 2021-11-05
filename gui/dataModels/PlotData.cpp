//
// Created by himep on 11/1/2021.
//

#include "PlotData.h"

PlotData::PlotData() = default;

PlotData::PlotData(const QVector<QVector<double>> &xdataList, const QVector<QVector<double>> &ydataList,
                   const QVector<bool> &linePlot, const QVector<QColor> &color, const QVector<QString> &plotTitle)
        : xdataList(xdataList), ydataList(ydataList), linePlot(linePlot), color(color), plotTitle(plotTitle) {}
