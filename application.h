#ifndef APPLICATION_H
#define APPLICATION_H

#include "ui_mainwindow.h"
#include "util.h"
#include "toolconfig.h"
#include "lpcore.h"
#include "loadingwidget.h"


class Application: QObject
{
public:
    LpCore *lpCore;
    Application(Ui::MainWindow *ui,QMainWindow *main);
    /**
     * 初始化系统
     * @brief init
     */
    void init();
    /**
     * 取消其他Action的激活效果
     * @brief cancelOtherActionActivat
     * @param action
     */
    void cancelOtherActionActivat(QAction *action);
    /**
     * 隐藏主Tab容器的表头
     * @brief hideMainTabTitle
     */
    void hideMainTabTitle();


private:
    Ui::MainWindow *ui;
    QMainWindow *main;
    ToolConfig *config;


};

#endif // APPLICATION_H
