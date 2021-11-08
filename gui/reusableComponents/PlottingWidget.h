//
// Created by himep on 11/8/2021.
//

#ifndef TESTINGNOFORMS_PLOTTINGWIDGET_H
#define TESTINGNOFORMS_PLOTTINGWIDGET_H

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

class PlottingWidget : public QtCharts::QChartView {
Q_OBJECT
public:
    explicit PlottingWidget(QWidget *pParent = nullptr);

    explicit PlottingWidget(QChart *chart, QWidget *pParent = nullptr);;

    ~PlottingWidget() override;

    QPixmap toPixmap();

protected:
    void mouseMoveEvent(QMouseEvent *pEvent) override;

    void mousePressEvent(QMouseEvent *pEvent) override;

    void mouseReleaseEvent(QMouseEvent *pEvent) override;

    void wheelEvent(QWheelEvent *pEvent) override;

    bool viewportEvent(QEvent *event);

    void keyPressEvent(QKeyEvent *event);

private:
    bool m_bMiddleButtonPressed;
    bool m_isTouching;
    QPoint m_oPrePos;
};


#endif //TESTINGNOFORMS_PLOTTINGWIDGET_H
