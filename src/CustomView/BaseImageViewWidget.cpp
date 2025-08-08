#include "BaseImageViewWidget.h"

#include <QGridLayout>
#include <QGraphicsView>
#include <QResizeEvent>
#include <QGraphicsPixmapItem>

#include "BaseImageItem.h"
#include "Viewer.h"

template<class T>
BaseImageViewWidget<T>::BaseImageViewWidget(QWidget *parent)
    : QWidget(parent)
{
    initUi();
    initLayout();
    initParamSet();
    initBindSlots();
}

template<class T>
void BaseImageViewWidget<T>::clearItems() noexcept
{
    auto items = m_Scene->items();
    for (auto item : items) {
        m_Scene->removeItem(item);
    }
    if constexpr (std::is_same_v<std::remove_reference_t<decltype(m_MainItem)>, QPixmap>){
        QPixmap pixmap;
        m_MainItem = pixmap;
    } else if constexpr (std::is_base_of_v<QGraphicsItem, std::remove_reference_t<decltype(m_MainItem)>>){
        m_MainItem.clearData();
    }
}

template<class T>
void BaseImageViewWidget<T>::updateShowImage(const QPixmap &pixmap) noexcept
{
    if constexpr (std::is_same_v<std::remove_reference_t<decltype(m_MainItem)>, QPixmap>){
        m_MainItem = pixmap;
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(m_MainItem);
        m_Scene->addItem(item);
    } else if constexpr (std::is_base_of_v<QGraphicsItem, std::remove_reference_t<decltype(m_MainItem)>>){
        m_MainItem.updateImg(pixmap);
        m_Scene->addItem(&m_MainItem);
    }
    m_Scene->update();
}

template<class T>
void BaseImageViewWidget<T>::resizeEvent(QResizeEvent *event)
{
    int width = event->size().width();
    int height = event->size().height();
    if constexpr (std::is_same_v<std::remove_reference_t<decltype(m_MainItem)>, QPixmap>) {
        if(m_Scene->items().size()) {
            auto scaleW = (double)width / m_Scene->items().at(0)->boundingRect().width();
            auto scaleH = (double)height / m_Scene->items().at(0)->boundingRect().height();
            auto lowerScale = scaleW > scaleH ? scaleH : scaleW;
            auto diffX = (width - m_MainItem.width() * lowerScale) / 2;
            auto diffY = (height - m_MainItem.height() * lowerScale) / 2;
            m_Scene->items().at(0)->setPos(-(width / 2) + diffX, -(height / 2) + diffY);
            m_Scene->items().at(0)->setScale(lowerScale);
        }
    } else if constexpr (std::is_base_of_v<QGraphicsItem, std::remove_reference_t<decltype(m_MainItem)>>) {
        auto scaleW = (double)width / m_MainItem.image().width();
        auto scaleH = (double)height / m_MainItem.image().height();
        auto lowerScale = scaleW > scaleH ? scaleH : scaleW;
        m_MainItem.resetItemData(lowerScale);
        m_MainItem.setScale(lowerScale);
        m_MainItem.setPos(0, 0);
    }
    m_Scene->setSceneRect(QRectF(-width / 2, -height / 2, width, height));
}

template<class T>
void BaseImageViewWidget<T>::initUi() noexcept
{
    m_Scene = new QGraphicsScene(this);
    m_View = new Viewer(this);
    m_View->setScene(m_Scene);
}
template<class T>
void BaseImageViewWidget<T>::initLayout() noexcept
{
    m_Obj = new QGridLayout(this);
    m_Obj->setContentsMargins(0, 0, 0, 0);

    m_Obj->addWidget(m_View);
}
template<class T>
void BaseImageViewWidget<T>::initParamSet() noexcept
{

}
template<class T>
void BaseImageViewWidget<T>::initBindSlots() noexcept
{

}
