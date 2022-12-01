#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "application.h"
#include "http.h"
#include <QStandardItemModel>
#include <QJsonObject>
#include "lpcore.h"
#include <QString>
#include <QTreeWidgetItem>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Application *app = new Application(ui,this);
    app->init();
    this->app = app;


}

MainWindow::~MainWindow()
{
    delete ui;
    delete app;

}

/**
 * lp树点击事件
 * @brief MainWindow::on_lpTree_clicked
 * @param index
 */
void MainWindow::on_lpTree_clicked(const QModelIndex &index)
{
    QStandardItemModel * standardModel = (QStandardItemModel*)(index.model());
    app->lpCore->treeClick(standardModel->itemFromIndex(index));
}

