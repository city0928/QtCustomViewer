#pragma once

#include <QGraphicsItem>
#include <QWidget>

#include "BaseImageItem.h"

class QGridLayout;
class Viewer;

template<class T>
class BaseImageViewWidget : public QWidget
{
    static_assert(std::is_base_of<QPixmap, T>::value or std::is_base_of<QGraphicsItem, T>::value, "T must inherit from QPixmap or QGraphicsItem");
public:
    BaseImageViewWidget(QWidget *parent = nullptr);

    void clearItems() noexcept;
    void updateShowImage(const QPixmap& pixmap) noexcept;

protected:
    virtual void resizeEvent(QResizeEvent *event);

private:
    void initUi() noexcept;
    void initLayout() noexcept;
    void initParamSet() noexcept;
    void initBindSlots() noexcept;

private:
    T m_MainItem;
    QGridLayout* m_Obj{nullptr};
    QGraphicsScene *m_Scene{nullptr};
    Viewer* m_View{nullptr};
};

template class BaseImageViewWidget<QPixmap>;
template class BaseImageViewWidget<BaseImageItem>;

