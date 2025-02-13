#include "consumedFoodItemEventFilter.h"

ConsumedFoodItemEventFilter::ConsumedFoodItemEventFilter(QObject *parent) : QObject(parent)
{

}

bool ConsumedFoodItemEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonRelease) {
        emit removeRequested();
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}
