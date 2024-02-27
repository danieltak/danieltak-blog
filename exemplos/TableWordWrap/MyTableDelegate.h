#ifndef MYTABLEDELEGATE_H
#define MYTABLEDELEGATE_H

#include <QPainter>
#include <QStyledItemDelegate>

class MyTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MyTableDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    virtual QSize sizeHint(const QStyleOptionViewItem &option,
                           const QModelIndex &index) const override;

signals:
};

#endif // MYTABLEDELEGATE_H
