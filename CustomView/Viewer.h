#pragma once

#include <QWidget>
#include <QGraphicsView>

class Viewer : public QGraphicsView
{
    Q_OBJECT

public:
    Viewer(QWidget *parent = nullptr);
    ~Viewer();
};
