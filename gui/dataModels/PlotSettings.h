//
// Created by himep on 11/1/2021.
//

#ifndef TESTINGNOFORMS_PLOTSETTINGS_H

#include <QObject>
#include <utility>

#define TESTINGNOFORMS_PLOTSETTINGS_H


class PlotSettings {


public:
    PlotSettings();

    PlotSettings(QString lut, QString temp, QString corner, QString xAxis,
                 QString yAxis, QString l, QString vgsVar, QString vgsVal,
                 QString vds, QString vsb, QString scaleAdjustmentVar,
                 QString scaleAdjustmentVal) : lut(std::move(lut)), Temp(std::move(temp)),
                                               Corner(std::move(corner)),
                                               x_Axis(std::move(xAxis)), y_Axis(std::move(yAxis)), L(std::move(l)),
                                               VGS_var(std::move(vgsVar)),
                                               VGS_val(std::move(vgsVal)), VDS(std::move(vds)), VSB(std::move(vsb)),
                                               scaleAdjustment_var(std::move(scaleAdjustmentVar)),
                                               scaleAdjustment_val(std::move(scaleAdjustmentVal)) {}

public:
    QString lut;
    QString Temp;
    QString Corner;
    QString x_Axis;
    QString y_Axis;
    QString L;
    QString VGS_var;
    QString VGS_val;
    QString VDS;
    QString VSB;
    QString scaleAdjustment_var;
    QString scaleAdjustment_val;
};

Q_DECLARE_METATYPE(PlotSettings);


#endif //TESTINGNOFORMS_PLOTSETTINGS_H
