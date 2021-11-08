//
// Created by himep on 11/8/2021.
//

#include <cmath>
#include <QRandomGenerator>
#include <QOpenGLWidget>
#include "PlottingWidget.h"


PlottingWidget::PlottingWidget(QWidget *pParent /*= nullptr*/)
        : QChartView(pParent), m_bMiddleButtonPressed(false), m_oPrePos(0, 0) {
    setRubberBand(QChartView::RectangleRubberBand);
    auto *pLineServies = new QtCharts::QLineSeries();
    for (int i = 0; i < 100; ++i) {
        pLineServies->append(i, qrand() % 10);
    }
    this->chart()->addSeries(pLineServies);
    this->chart()->createDefaultAxes();
}

PlottingWidget::PlottingWidget(QChart *chart, QWidget *parent) : QChartView(chart, parent), m_isTouching(false),
                                                                 m_bMiddleButtonPressed(false), m_oPrePos(0, 0) {
    setRubberBand(QChartView::RectangleRubberBand);
}

PlottingWidget::~PlottingWidget() = default;

bool PlottingWidget::viewportEvent(QEvent *event) {
    if (event->type() == QEvent::TouchBegin) {
        // By default touch events are converted to mouse events. So
        // after this event we will get a mouse event also but we want
        // to handle touch events as gestures only. So we need this safeguard
        // to block mouse events that are actually generated from touch.
        m_isTouching = true;

        // Turn off animations when handling gestures they
        // will only slow us down.
        chart()->setAnimationOptions(QChart::NoAnimation);
    }
    return QChartView::viewportEvent(event);
}

void PlottingWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Plus:
            chart()->zoomIn();
        break;
        case Qt::Key_Minus:
            chart()->zoomOut();
        break;
        case Qt::Key_Left:
            chart()->scroll(-10, 0);
        break;
        case Qt::Key_Right:
            chart()->scroll(10, 0);
        break;
        case Qt::Key_Up:
            chart()->scroll(0, 10);
        break;
        case Qt::Key_Down:
            chart()->scroll(0, -10);
        break;
        case Qt::Key_F:
            chart()->zoomReset();
        chart()->resetTransform();
        chart()->adjustSize();
        chart()->setMinimumSize(800, 800);
        default:
            QGraphicsView::keyPressEvent(event);
            break;
    }
}

void PlottingWidget::mouseMoveEvent(QMouseEvent *pEvent) {
    if (m_isTouching && !m_bMiddleButtonPressed)
        return;
    if (m_bMiddleButtonPressed) {
        QPoint oDeltaPos = pEvent->pos() - m_oPrePos;
        this->chart()->scroll(-oDeltaPos.x(), oDeltaPos.y());
        m_oPrePos = pEvent->pos();
    }
    QChartView::mouseMoveEvent(pEvent);
}

void PlottingWidget::mousePressEvent(QMouseEvent *pEvent) {
    if (m_isTouching && m_bMiddleButtonPressed)
        return;
    if (pEvent->button() == Qt::MiddleButton) {
        m_bMiddleButtonPressed = true;
        m_oPrePos = pEvent->pos();
        setCursor(Qt::OpenHandCursor);
    }
    QChartView::mousePressEvent(pEvent);
}

void PlottingWidget::mouseReleaseEvent(QMouseEvent *pEvent) {
    if (m_isTouching && !m_bMiddleButtonPressed)
        m_isTouching = false;
    if (pEvent->button() == Qt::MiddleButton) {
        m_bMiddleButtonPressed = false;
        setCursor(Qt::ArrowCursor);
    }
    chart()->setAnimationOptions(QChart::SeriesAnimations);
    QChartView::mouseReleaseEvent(pEvent);
}

void PlottingWidget::wheelEvent(QWheelEvent *pEvent) {
    qreal rVal = std::pow(0.999, pEvent->delta());

    QRectF oPlotAreaRect = this->chart()->plotArea();
    QPointF oCenterPoint = oPlotAreaRect.center();

    oPlotAreaRect.setWidth(oPlotAreaRect.width() * rVal);

    oPlotAreaRect.setHeight(oPlotAreaRect.height() * rVal);

    QPointF oNewCenterPoint(2 * oCenterPoint - pEvent->position() - (oCenterPoint - pEvent->position()) / rVal);

    oPlotAreaRect.moveCenter(oNewCenterPoint);

    this->chart()->zoomIn(oPlotAreaRect);

    QChartView::wheelEvent(pEvent);
}

QPixmap PlottingWidget::toPixmap() {
    QPixmap p = this->grab();
    auto *glWidget = this->findChild<QOpenGLWidget *>();
    if (glWidget) {
        QPainter painter(&p);
        QPoint d = glWidget->mapToGlobal(QPoint()) - this->mapToGlobal(QPoint());
        painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
        painter.drawImage(d, glWidget->grabFramebuffer());
        painter.end();
    }
    return p;
}

