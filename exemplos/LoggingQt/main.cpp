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
