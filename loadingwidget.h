#ifndef LOADINGWIDGET_H
#define LOADINGWIDGET_H
#include <QDialog>
#include <QWidget>
#include "ui_mainwindow.h"
#include <QMovie>

class LoadingWidget : public QDialog
{
public:
    explicit LoadingWidget(QWidget *parent = 0);
    ~LoadingWidget();
private:
   QMovie *movie;
   QLabel *label;
};

#endif // LOADINGWIDGET_H
