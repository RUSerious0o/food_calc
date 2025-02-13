#ifndef CONSUMEDFOODITEMEVENTFILTER_H
#define CONSUMEDFOODITEMEVENTFILTER_H

#include <QObject>

#include <QEvent>
#include <QDebug>

class ConsumedFoodItemEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit ConsumedFoodItemEventFilter(QObject *parent = nullptr);

signals:
    void removeRequested();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // CONSUMEDFOODITEMEVENTFILTER_H
