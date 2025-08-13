#include "BaseImageViewWidget.h"

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGridLayout>
#include <QResizeEvent>

#include "BaseImageItem.h"
#include "Viewer.h"

template <class T>
BaseImageViewWidget<T>::BaseImageViewWidget(QWidget* parent)
    : QWidget(parent)
{
    initUi();
    initLayout();
    initParamSet();
    initBindSlots();
}

template <class T> void BaseImageViewWidget<T>::clearItems() noexcept
{
    auto items = m_Scene->items();
    for (auto item : items) {
        m_Scene->removeItem(item);
    }
}

template <class T> void BaseImageViewWidget<T>::setMainItem(T* mainItem) noexcept
{
    if constexpr (std::is_same_v<std::remove_pointer_t<decltype(mainItem)>, QGraphicsPixmapItem>) {
        if (mainItem) {
            mainItem->setData(0, "mainItem");
        }
        if (!m_Scene->items().size()) {
            m_Scene->clear();
        }
        m_Scene->addItem(mainItem);
        m_Scene->setSceneRect(
            QRectF(-mainItem->pixmap().width() / 2, -mainItem->pixmap().height() / 2, mainItem->pixmap().width(), mainItem->pixmap().height()));
    } else if constexpr (std::is_base_of_v<QGraphicsItem, std::remove_pointer_t<decltype(mainItem)>>) {
        if (mainItem) {
            mainItem->setData(0, "mainItem");
        }
        if (m_Scene) {
            m_Scene->addItem(mainItem);
            m_Scene->setSceneRect(
                QRectF(-mainItem->image().width() / 2, -mainItem->image().height() / 2, mainItem->image().width(), mainItem->image().height()));
            mainItem->setScale(viewShowItemMinScale());
        }
    }
    m_Scene->update();
}

template <class T> void BaseImageViewWidget<T>::resizeEvent(QResizeEvent* event)
{
    int width = event->size().width();
    int height = event->size().height();
    for (int i = 0; i < m_Scene->items().size(); ++i) {
        if ("mainItem" == m_Scene->items().at(i)->data(0).toString()) {
            auto item = m_Scene->items().at(i);
            // 尝试转成 QGraphicsPixmapItem
            if (auto pixmapPtr = dynamic_cast<QGraphicsPixmapItem*>(item)) {
                auto scaleW = static_cast<double>(width) / pixmapPtr->boundingRect().width();
                auto scaleH = static_cast<double>(height) / pixmapPtr->boundingRect().height();
                auto lowerScale = std::min(scaleW, scaleH);
                auto diffX = (width - pixmapPtr->pixmap().width() * lowerScale) / 2;
                auto diffY = (height - pixmapPtr->pixmap().height() * lowerScale) / 2;
                pixmapPtr->setPos(-(width / 2) + diffX, -(height / 2) + diffY);
                pixmapPtr->setScale(lowerScale);
            }
            // 尝试转成 BaseImageItem
            else if (auto customPtr = dynamic_cast<BaseImageItem*>(item)) {
                if (!customPtr->image().isNull()) {
                    auto scaleW = static_cast<double>(width) / customPtr->image().width();
                    auto scaleH = static_cast<double>(height) / customPtr->image().height();
                    auto lowerScale = std::min(scaleW, scaleH);
                    customPtr->resetItemData(lowerScale);
                    customPtr->setScale(lowerScale);
                    customPtr->setPos(0, 0);
                }
            }
            // 两个 dynamic_cast 都失败时
            else {
                qWarning() << "[mainItem] 类型不是 QGraphicsPixmapItem 也不是 BaseImageItem:{}" << static_cast<const void*>(item);
            }
            break;
        }
    }
    m_Scene->setSceneRect(QRectF(-width / 2, -height / 2, width, height));
}

template <class T> double BaseImageViewWidget<T>::viewShowItemMinScale() noexcept
{
    int width = this->geometry().width();
    int height = this->geometry().height();
    for (int i = 0; i < m_Scene->items().size(); ++i) {
        if ("mainItem" == m_Scene->items().at(i)->data(0).toString()) {
            if (auto pixmapPtr = static_cast<QGraphicsPixmapItem*>(m_Scene->items().at(i))) {
                auto scaleW = (double)width / pixmapPtr->boundingRect().width();
                auto scaleH = (double)height / pixmapPtr->boundingRect().height();
                auto lowerScale = std::min(scaleW, scaleH);
                return lowerScale;
            }
            if (auto customPtr = static_cast<BaseImageItem*>(m_Scene->items().at(i))) {
                auto scaleW = (double)width / customPtr->image().width();
                auto scaleH = (double)height / customPtr->image().height();
                auto lowerScale = std::min(scaleW, scaleH);
                return lowerScale;
            }
            break;
        }
    }
    return 1.0;
}

template <class T> void BaseImageViewWidget<T>::initUi() noexcept
{
    m_Scene = new QGraphicsScene(this);
    m_View = new Viewer(this);
    m_View->setScene(m_Scene);
}
template <class T> void BaseImageViewWidget<T>::initLayout() noexcept
{
    m_Obj = new QGridLayout(this);
    m_Obj->setContentsMargins(0, 0, 0, 0);
    m_Obj->addWidget(m_View);
}
template <class T> void BaseImageViewWidget<T>::initParamSet() noexcept {}
template <class T> void BaseImageViewWidget<T>::initBindSlots() noexcept {}
