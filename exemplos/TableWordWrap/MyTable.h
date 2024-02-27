#ifndef MYTABLE_H
#define MYTABLE_H

#include <QTableWidget>

class MyTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit MyTable(QWidget *parent = nullptr);

    QString GetRandomString() const;

    void PopulateDummyTable();

signals:
};

#endif // MYTABLE_H
