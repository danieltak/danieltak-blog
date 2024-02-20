#ifndef MYSINGLETON_H
#define MYSINGLETON_H

#include <QObject>
#include <QString>
#include <QtQml/qqml.h>
#include "singleton.h"

class MySingleton : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString helloWorld READ helloWorld WRITE helloWorld NOTIFY helloWorldChanged )
    Q_PROPERTY( QString loremIpsum READ loremIpsum WRITE loremIpsum NOTIFY loremIpsumChanged )
    Q_PROPERTY( bool changeTextColor READ changeTextColor WRITE changeTextColor NOTIFY textColorChanged )
    QML_NAMED_ELEMENT(MySingleton)
    QML_SINGLETON

protected:
    QString helloWorld() const;
    void helloWorld( QString newString );

    QString loremIpsum() const;
    void loremIpsum( QString newString );

    bool changeTextColor() const;
    void changeTextColor( bool newValue );
private:
    explicit MySingleton(QObject *parent = nullptr);
public:
    SINGLETON(MySingleton)
    static MySingleton *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine){return getInstance();}

public:
    QString m_helloWorld;
    QString m_loremIpsum;
    bool m_changeTextColor;

signals:
    void helloWorldChanged();
    void loremIpsumChanged();
    void textColorChanged();
};

#endif // MYSINGLETON_H
