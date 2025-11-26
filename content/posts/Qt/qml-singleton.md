---
title: "QML Singleton"
date: '2024-02-16T20:11:32-03:00'
# weight: 1
# aliases: ["/first"]
tags: ["Singleton", "DesignPattern"]
categorias: ["C++", "QML", "Snippet"]
author: "danieltak"
# author: ["Me", "You"] # multiple authors
showToc: true
TocOpen: false
draft: false
hidemeta: false
comments: false
description: "Instância única"

disableShare: false
disableHLJS: false
hideSummary: false
searchHidden: false
ShowReadingTime: false
ShowBreadCrumbs: true
ShowPostNavLinks: true
ShowWordCount: true
ShowRssButtonInSectionTermList: true
UseHugoToc: true
cover:
    image: images/qml-singleton/singleton.png
    alt: "https://refactoring.guru/images/patterns/content/singleton/singleton.png" # alt text
    caption: "fonte: https://refactoring.guru/" # display caption under cover
    relative: false # when using page bundles set this to true
    hidden: false # only hide on current single page
    hiddenInSingle: false
    responsiveImages: true
editPost:
    URL: "https://github.com/danieltak/danieltak-blog/blob/master/content"
    Text: "Sugerir Alterações" # edit text
    appendFilePath: true # to append file path to Edit link
---

## Introdução

No QML muitas vezes é necessário o acesso global à variáveis e funções, isso pode ser alcançado com um padrão de projeto [Singleton][1].

Um exemplo é a configuração global de um software, que além de ser acessado por qualquer janela, deve também salvar os dados de configuração em algum arquivo.

>O Singleton é um padrão de projeto criacional que permite a você garantir que uma classe tenha apenas uma instância, enquanto provê um ponto de acesso global para essa instância.

## Singleton

O [Refactoring.guru][1] diz o seguinte:

O padrão Singleton resolve dois problemas de uma só vez, violando o princípio de responsabilidade única:

1. **Garantir que uma classe tenha apenas uma única instância.** Por que alguém iria querer controlar quantas instâncias uma classe tem? A razão mais comum para isso é para controlar o acesso a algum recurso compartilhado, por exemplo, uma base de dados ou um arquivo.

Funciona assim: imagine que você criou um objeto, mas depois de um tempo você decidiu criar um novo. Ao invés de receber um objeto fresco, você obterá um que já foi criado.

Observe que esse comportamento é impossível implementar com um construtor regular uma vez que uma chamada do construtor deve sempre retornar um novo objeto por design.

2. **Fornece um ponto de acesso global para aquela instância.** Se lembra daquelas variáveis globais que você (tá bom, eu) usou para guardar alguns objetos essenciais? Embora sejam muito úteis, elas também são muito inseguras uma vez que qualquer código pode potencialmente sobrescrever os conteúdos daquelas variáveis e quebrar a aplicação.

Assim como uma variável global, o padrão Singleton permite que você acesse algum objeto de qualquer lugar no programa. Contudo, ele também protege aquela instância de ser sobrescrita por outro código.

Há outro lado para esse problema: você não quer que o código que resolve o problema #1 fique espalhado por todo seu programa. É muito melhor tê-lo dentro de uma classe, especialmente se o resto do seu código já depende dela.

## CMake

Muitos tutoriais antigos dizem para alterar o qmldir, mas no Qt6, o qmldir é gerado automaticamente, portanto, uma das maneiras é declarar que uma classe QML é singleton no CMake.

`set_source_files_properties(MyTheme.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)`

E no cabeçalho da classe `pragma Singleton`

Um [Example Singleton1][2] pode ser visto no github, em que a classe QML `MySingleton` é criada com as seguintes propriedades:

```cpp
property string helloWorld:
property string loremIpsum:
property bool changeTextColor:
```

E o seguinte código é usado para um teste numa janela:

```cpp
import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    color: "#888888"
    title: qsTr( MySingleton.helloWorld )

    Text{
        id: myText
        width: parent.width

        font.pixelSize: 22
        color: MySingleton.changeTextColor ? "red" : "blue"
        text: MySingleton.loremIpsum
        wrapMode: Text.WrapAnywhere
    }

    Button{
        id: myButton
        anchors.top: myText.bottom

        width: parent.width / 4
        text: "Trocar Cor"

        onClicked: {
            MySingleton.changeTextColor = !MySingleton.changeTextColor;
        }

    }

}
```

![Result Singleton1](/posts/images/qml-singleton/Singleton1.gif)

## Classe C++

Muitas vezes o QML é limitado e é necessário criar classes em C++.

Para criar um singleton numa classe C++, vamos criar um header chamado `singleton.h`, com templates e thread-safe. Utilizando como base o projeto do [FluentUI][4].

Para ser thread-safe, a classe [QMutexLocker][5] foi utilizada, mas um [lock_guard][6] também poderia ser utilizado.

O exemplo completo pode ser visto no repositório [Example Singleton2][3].

>Lembrando se for utilizar o [lock_guard][6], veja a [guideline CP44][7]

### QMutexLocker

O [QMutexLocker][5] deve ser criado em uma função na qual um QMutex precisa ser bloqueado. O mutex é bloqueado quando o [QMutexLocker][5] é criado. Você pode desbloquear e bloquear novamente o mutex com `unlock()` e `relock()`. Se estiver bloqueado, o mutex será desbloqueado quando o [QMutexLocker][5] for destruído.

Por exemplo, a seguinte função bloqueia e desbloqueia um QMutex, tendo que garantir que um Deadlock não ocorra.

```cpp
int complexFunction(int flag)
{
    mutex.lock();

    int retVal = 0;

    switch (flag) {
    case 0:
    case 1:
        retVal = moreComplexFunction(flag);
        break;
    case 2:
        {
            int status = anotherFunction();
            if (status < 0) {
                mutex.unlock();
                return -2;
            }
            retVal = status + flag;
        }
        break;
    default:
        if (flag > 10) {
            mutex.unlock();
            return -1;
        }
        break;
    }

    mutex.unlock();
    return retVal;
}
```

O uso do QMutexLocker simplifica muito o código e o torna mais legível:

```cpp
int complexFunction(int flag)
{
    QMutexLocker locker(&mutex);

    int retVal = 0;

    switch (flag) {
    case 0:
    case 1:
        return moreComplexFunction(flag);
    case 2:
        {
            int status = anotherFunction();
            if (status < 0)
                return -2;
            retVal = status + flag;
        }
        break;
    default:
        if (flag > 10)
            return -1;
        break;
    }

    return retVal;
}
```

**Opinião:** Eu pessoalmente prefiro usar as funções do STL, como o [lock_guard][6]. Mas vou manter o uso do [QMutexLocker][5] para fins educacionais, pois há bastante material sobre o [lock_guard][6] na internet.

### Estanciador Singleton

A classe `singleton.h` pode ser criada com o `#define SINGLETON(Class)` para construir a classe com o template definido no header. 

```cpp
#ifndef SINGLETON_H
#define SINGLETON_H

#include <QMutex>

template <typename T>
class Singleton {
public:
    static T* getInstance();
    
private:
    Q_DISABLE_COPY_MOVE(Singleton)
};

template <typename T>
T* Singleton<T>::getInstance() {
    static QMutex mutex;
    QMutexLocker locker(&mutex);
    static T* instance = nullptr;
    if (instance == nullptr) {
        instance = new T();
    }
    return instance;
}

#define SINGLETON(Class)                        \
private:                                        \
    friend class Singleton<Class>;              \
    public:                                     \
    static Class* getInstance() {               \
        return Singleton<Class>::getInstance(); \
}

#define HIDE_CONSTRUCTOR(Class)         \
private:                                \
    Class() = default;                  \
    Class(const Class& other) = delete; \
    Q_DISABLE_COPY_MOVE(Class);

#endif // SINGLETON_H
```

### Classe Singleton

Criamos a classe `MySingleton`, adicionando as variáveis com a Macro Qt [Q_PROPERTY][8], `QML_NAMED_ELEMENT`, `QML_SINGLETON` e o instanciando o singleton com o `#define SINGLETON(Class)`.

O header fica da seguinte maneira:

```cpp
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
```

No cpp inicializamos os membros da classe no construtor e criamos as funções com overload de READ e WRITE da do [Q_PROPERTY][8], emitindo o sinal de "changed" que será notificado pelo sistema de eventos do Qt.

```cpp
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
```

## Referência

- [Singleton Design Pattern][1]

[1]: https://refactoring.guru/pt-br/design-patterns/singleton

- [Exemplo Singleton1][2]

[2]: https://github.com/danieltak/danieltak-blog/blob/master/exemplos/Singleton1

- [Exemplo Singleton2][3]

[3]: https://github.com/danieltak/danieltak-blog/blob/master/exemplos/Singleton2

- [FluentUI][4]

[4]: https://github.com/zhuzichu520/FluentUI

- [QMutexLocker][5]

[5]: https://doc.qt.io/qt-6/qmutexlocker.html

- [lock_guard][6]

[6]: https://en.cppreference.com/w/cpp/thread/lock_guard

- [CP.44: Remember to name your lock_guards and unique_locks][7]

[7]: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rconc-name

- [Q_PROPERTY][8]

[8]: https://doc.qt.io/qt-6/properties.html