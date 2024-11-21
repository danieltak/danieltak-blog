#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void myLogFunc( QString qStr, const char* cFile = __FILE__ , const int cLine = __LINE__ );

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
