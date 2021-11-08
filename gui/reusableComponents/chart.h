
#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>

QT_BEGIN_NAMESPACE
class QGestureEvent;
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Chart : public QChart
{
public:
    explicit Chart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = {});
    ~Chart() override;

protected:
    bool sceneEvent(QEvent *event) override;

private:
    bool gestureEvent(QGestureEvent *event);

private:

};

#endif // CHART_H
