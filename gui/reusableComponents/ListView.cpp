//
// Created by himep on 11/3/2021.
//

#include <QPointer>
#include "ListView.h"

ListView::ListView(QWidget *parent) : QListWidget(parent) {
    setViewMode(QListView::ListMode);
    setResizeMode(ResizeMode::Adjust);
    setIconSize(QSize(100, 100));
    setSpacing(10);
}

void ListView::addPlotItem(const QPixmap &pixmap, QString plotTitle, PlotSettings Settings, PlotData data) {
    auto *pieceItem = new QListWidgetItem(this);

    QVariant variant_settings;
    variant_settings.setValue(Settings);
    QVariant variant_data;
    variant_data.setValue(data);

    pieceItem->setIcon(QIcon(pixmap));
    pieceItem->setText(plotTitle);
    pieceItem->setData(Qt::UserRole, QVariant(pixmap));
    pieceItem->setData(Qt::UserRole + 1, plotTitle);
    pieceItem->setData(Qt::UserRole + 2, variant_settings);
    pieceItem->setData(Qt::UserRole + 3, variant_data);
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}
