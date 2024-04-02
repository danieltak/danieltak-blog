---
title: "Logging"
date: '2024-02-16T20:11:32-03:00'
# weight: 1
# aliases: ["/first"]
tags: ["Singleton", "DesignPattern"]
categorias: ["C++", "Qt", "Linux", "Windows"]
author: "danieltak"
# author: ["Me", "You"] # multiple authors
showToc: true
TocOpen: false
draft: false
hidemeta: false
comments: false
description: "Logs de Erros"
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
    image: images/logging/log-file.jpg
    alt: "Imagem de storyset no Freepik" # alt text
    caption: "fonte: https://br.freepik.com/vetores-gratis/adicionar-ilustracao-do-conceito-de-arquivos_5568817.htm" # display caption under cover
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

**Um log de erros** é um arquivo de texto que registra a **cronologia de eventos** que ocorrem em um sistema operacional, aplicativo ou serviço. Esses registros são essenciais para **monitoramento**, **auditoria**, **segurança** e **correção de problemas**. Desde o momento em que o sistema operacional é iniciado, os primeiros logs começam a ser gravados, registrando informações como data, horário, carregamento do kernel e possíveis erros ou ações excepcionais executadas. Os logs de erro são valiosos para desenvolvedores e administradores, pois fornecem insights sobre falhas e exceções durante a execução de programas, permitindo a identificação e resolução de problemas.

Em resumo, o **log de erros** é uma ferramenta fundamental para **solucionar bugs**, **melhorar a estabilidade** e **otimizar o desempenho** de sistemas e aplicativos. Ele armazena informações sobre erros, exceções e falhas, permitindo que os profissionais de suporte identifiquem e corrijam problemas, garantindo um funcionamento mais confiável e seguro.

## Qt

No Qt, o [QtLogging][1] pode ser usado, em que um Message Handler precisa ser programado e o logger instalado na aplicação usando o `qInstallMessageHandler()`, antes do objeto de `QApplication` ser criado.

Após a instalação de um handler, as macros `qInfo()`, `qDebug()`, `qWarning()`, `qCritical()` e `qFatal()` podem ser usadas para enviar mensagens para o logger.

Um [Exemplo Logger no Qt][2] pode ser visto no repositório do github e o código será visto a seguir:

```cpp
#include "mainwindow.h"

#include <iostream>

#include <QApplication>
#include <QDate>
#include <QDebug>
#include <QFile>

void logMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString message = qFormatLogMessage(type, context, msg);
    QString fileBase = qApp->applicationDirPath() + "/";
    QString fileName = fileBase + QString( "log" + QDate::currentDate().toString("yyyyMMdd") + ".txt" );

    QHash<QtMsgType, QString> msgLevelHash({{QtDebugMsg, "Debug"}, {QtInfoMsg, "Info"}, {QtWarningMsg, "Warning"}, {QtCriticalMsg, "Critical"}, {QtFatalMsg, "Fatal"}});


    QFile outputFile( fileName );
    if ( outputFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text) ){
        QTextStream textStream( &outputFile );
        QString printMessage;
        QString logLevelName = msgLevelHash[type];

        printMessage = QString("%1 %2: %3 (%4:%5, %6)")
                           .arg( logLevelName,
                                QDateTime::currentDateTime().toString("hh:mm:ss"),
                                message,
                                QString( context.file ),
                                QString::number( context.line ),
                                QString( context.function ) );

        textStream << printMessage << Qt::endl;
        std::cout << printMessage.toStdString() << std::endl;
        outputFile.close();

        if( type == QtFatalMsg )
            abort();
    }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler( logMessageOutput );

    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
```

Um arquivo de log é criado com a data de hoje no mesmo diretório do executável, o handler `logMessageOutput` que cria o arquivo, se múltiplas aplicações ou threads escreverem no mesmo arquivo, um semáforo deverá ser criado.

A função `qFormatLogMessage()` é chamada para gerar a string com os dados do log de erro, posteriormente algumas informações são adicionadas ao log de erros e escritas no arquivo usando o `QTextStream`. A mensagem também é escrita no terminal com o `std::cout`.

Utilizando as MACROS da seguinte maneira:

```
qInfo() << "qInfo" << Qt::endl;

qWarning() << "qWarning" << Qt::endl;;

qCritical() << "qCritical" << Qt::endl;;

//qFatal() << "qFatal" << Qt::endl;;

qDebug() << "qDebug" << Qt::endl;;
```

O resultado do log é o seguinte:

```
Info 18:57:36: qInfo 
 (C:/exemplos/LoggingQt/mainwindow.cpp:10, MainWindow::MainWindow(QWidget*))
Warning 18:57:36: qWarning 
 (C:/exemplos/LoggingQt/mainwindow.cpp:12, MainWindow::MainWindow(QWidget*))
Critical 18:57:36: qCritical 
 (C:/exemplos/LoggingQt/mainwindow.cpp:14, MainWindow::MainWindow(QWidget*))
Debug 18:57:36: qDebug 
 (C:/exemplos/LoggingQt/mainwindow.cpp:18, MainWindow::MainWindow(QWidget*))
```

Perceba que recebemos o arquivo em que a macro foi chamada e a linha de código, com o timestamp e o nome da classe, essas informações são muito úteis para identificar possíveis problemas ou dar suporte remotamente ao usuário.

Se a linha de código contendo a Macro `qFatal()` for descomentada, o código é abortado com a função `abort()`.

## Logger Genérico



## Referência

- [QtLogging][1]

[1]: https://doc.qt.io/qt-6/qtlogging.html

- [Exemplo Logger no Qt][2]

[2]: https://github.com/danieltak/danieltak-blog/blob/master/exemplos/LoggingQt