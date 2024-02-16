---
title: "Maximizar e Minimizar Janelas Qt no X11"
date: '2024-02-11T23:11:32-03:00'
# weight: 1
# aliases: ["/first"]
tags: ["Qt", "Linux", "X11", "GUI"]
categorias: ["C++", "Qt", "Linux", "Snippet"]
author: "danieltak"
# author: ["Me", "You"] # multiple authors
showToc: true
TocOpen: false
draft: false
hidemeta: false
comments: false
description: "XIconifyWindow() e XMapWindow()"
disableHLJS: true # to disable highlightjs
disableShare: false
disableHLJS: false
hideSummary: false
searchHidden: false
ShowReadingTime: true
ShowBreadCrumbs: true
ShowPostNavLinks: true
ShowWordCount: true
ShowRssButtonInSectionTermList: true
UseHugoToc: true
cover:
    image: "<image path/url>" # image path/url
    alt: "<alt text>" # alt text
    caption: "<text>" # display caption under cover
    relative: false # when using page bundles set this to true
    hidden: true # only hide on current single page
editPost:
    URL: "https://github.com/danieltak/danieltak-blog/blob/master/content"
    Text: "Sugerir Alterações" # edit text
    appendFilePath: true # to append file path to Edit link
---

## Introdução

Este post explicará como fazer um snippet de uma aplicação no Qt, utilizando o C++ e a biblioteca do X11. O sistema operacional Linux deve utilizar o protocolo X11.

Me deparei com este problema, pois o sistema embarcado não possui barra de tarefas, portanto, não é possível minimizar e maximizar da maneira convencional e alguns *hotkeys bindings* foram utilizados para maximizar e minimizar a aplicação principal.

## O que é o X11?

Segundo a [wiki][1]:

>X Window System, X-Window, X11 ou simplesmente X é um software de sistema e um protocolo que fornece uma base para interfaces gráficas de usuário (com o conceito de janelas) e funcionalidade rica de dispositivos de entrada para redes de computadores. Ele cria uma camada de abstração de hardware onde o software é escrito para usar um conjunto generalizado de comandos, permitindo a independência de dispositivo e reutilização de programas em qualquer computador que implemente o X.
>X-Window é o toolkit e protocolo padrão para GUI nos sistemas Unix e assemelhados, como o Linux, mas existem versões para outros sistemas operacionais, como o Microsoft Windows e o Mac OS, por exemplo.

Atualmente este projeto é mantido pela [X.Org Foundation][2], mas um protocolo novo chamado [Wayland][3] está ganhando espaço e a maioria das novas distribuições Linux utilizam este protocolo ou um híbrido XWayland. Os softwares ainda estão se adaptando a esse novo protocolo e um caminho longo para a portabilidade completa, contudo, o [Wayland][3] é o protocolo do futuro e o X11 será descontinuado em algum momento.

Mas ainda a maior parte dos softwares ou sistemas operacionais ainda utilizam o X11, portanto, é bom entender um pouco dos dois, pois estamos num momento de transição.

## Aplicação Qt

Às vezes, as funções padrão do Qt não tratam adequadamente a janela, portanto, as bibliotecas do X11 são necessárias para lidar com isso.

Para adicionar ao projeto, a seguinte configuração deve ser adicionada no CMakeLists:

```
find_package(X11 REQUIRED)

include_directories(${X11_INCLUDE_DIR})
link_libraries(${X11_LIBRARIES})
```

Includes:

```cpp
#include <X11/Xlib.h>
```

Use `XIconifyWindow()` para minimizar a janela, no Qt6 o código a seguir:

```cpp
// If there is only one Window
MainWindow * win = (MainWindow *) qApp::activeWindow();
Display *display = nullptr;
xcb_connection_t *connection = nullptr;
bool bIsPlatformX11 = false;
if (auto *x11Application = qGuiApp->nativeInterface<QNativeInterface::QX11Application>())
{
    display = x11Application->display();
    connection = x11Application->connection();
    bIsPlatformX11 = true;
}
XIconifyWindow( display, win->winId(), 0);
```

Para Maximizar, deve dar um show na janela:

```cpp
// If there is only one Window
MainWindow * win = (MainWindow *) qApp::activeWindow();
Display *display = nullptr;
xcb_connection_t *connection = nullptr;
bool bIsPlatformX11 = false;
if (auto *x11Application = qGuiApp->nativeInterface<QNativeInterface::QX11Application>())
{
    display = x11Application->display();
    connection = x11Application->connection();
    bIsPlatformX11 = true;
}
// Show
XMapWindow( display, win->winId() );
// Hide
// XUnMapWindow( display, win->winId() );
```

## Referências

- [X Window System][1]

[1]: https://pt.wikipedia.org/wiki/X_Window_System

- [X.Org Foundation][2]

[2]: https://www.x.org/wiki/

- [Wayland][3]

[3]: https://wayland.freedesktop.org/