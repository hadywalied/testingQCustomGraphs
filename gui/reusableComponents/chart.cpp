
#include "chart.h"
#include <QtWidgets/QGesture>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
        : QChart(QChart::ChartTypeCartesian, parent, wFlags) {
    // Seems that QGraphicsView (QChartView) does not grab gestures.
    // They can only be grabbed here in the QGraphicsWidget (QChart).
    grabGesture(Qt::PanGesture);
    grabGesture(Qt::PinchGesture);
}

Chart::~Chart() = default;

bool Chart::sceneEvent(QEvent *event) {
    if (event->type() == QEvent::Gesture)
        return gestureEvent(dynamic_cast<QGestureEvent *>(event));
    return QChart::event(event);
}

bool Chart::gestureEvent(QGestureEvent *event) {
    if (QGesture *gesture = event->gesture(Qt::PanGesture)) {
        auto *pan = dynamic_cast<QPanGesture *>(gesture);
        QChart::scroll(-(pan->delta().x()), pan->delta().y());
    }

    if (QGesture *gesture = event->gesture(Qt::PinchGesture)) {
        auto *pinch = dynamic_cast<QPinchGesture *>(gesture);
        if (pinch->changeFlags() & QPinchGesture::ScaleFactorChanged)
            QChart::zoom(pinch->scaleFactor());
    }

    return true;
}
