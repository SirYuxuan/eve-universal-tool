#ifndef LPCORE_H
#define LPCORE_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "http.h"
#include <QString>
#include "ui_mainwindow.h"
#include "util.h"


class LpCore:public QObject
{
public:
    LpCore(Ui::MainWindow *ui,QMainWindow *main);
    /**
     * lp公司树被点击
     * @brief treeClick
     */
    void treeClick(QStandardItem *item);
private:
    QMainWindow *main;
    Ui::MainWindow *ui;
};

#endif // LPCORE_H
