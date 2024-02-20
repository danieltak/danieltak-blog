#include "MySingleton.h"

MySingleton::MySingleton(QObject *parent)
    : QObject{parent},
    m_helloWorld("Hello World!"),
    m_loremIpsum("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec quis convallis sapien. In pharetra, urna quis ornare bibendum, neque lacus varius tortor, sed pretium nunc ante a metus. Fusce finibus semper urna, quis pharetra odio tincidunt feugiat. Quisque fermentum elementum velit auctor sagittis. Aenean ac aliquam diam. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam euismod iaculis massa, sed pretium eros cursus a. Aenean eu tortor sed augue maximus pharetra. Aliquam erat volutpat. Pellentesque malesuada nibh quam, eu consequat elit pretium vel."),
    m_changeTextColor(false)
{
}

QString MySingleton::helloWorld() const
{
    return m_helloWorld;
}

void MySingleton::helloWorld(QString newString)
{
    m_helloWorld = newString;

    emit helloWorldChanged();
}

QString MySingleton::loremIpsum() const
{
    return m_loremIpsum;
}

void MySingleton::loremIpsum(QString newString)
{
    m_loremIpsum = newString;

    emit loremIpsumChanged();
}

bool MySingleton::changeTextColor() const
{
    return m_changeTextColor;
}

void MySingleton::changeTextColor(bool newValue)
{
    m_changeTextColor = newValue;

    emit textColorChanged();
}
