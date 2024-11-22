#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdio.h>
#include "muParser.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void Lectura();
    int ROOTER(QVector<double> I);
    double Two(QVector<double>I,QVector<double>t);

private:
    Ui::MainWindow *ui;
    QVector<double>I,V,T;
};
#endif // MAINWINDOW_H
