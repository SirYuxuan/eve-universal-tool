#include "application.h"
#include <qlist.h>
#include <qaction.h>
#include <qmap.h>
#include <http.h>
/**
 * 构造函数拿到系统操作对象
 * @brief Application::Application
 * @param ui
 * @param main
 */
Application::Application(Ui::MainWindow *ui,QMainWindow *main): QObject(main)
{
    this->ui = ui;
    this->main = main;
    this->config = new ToolConfig(main);
    this->lpCore = new LpCore(ui,main);
}

/**
 * 初始化整个系统
 * @brief Application::init
 * @param ui
 */
void Application::init()
{

    // 隐藏主Tab的表头
    hideMainTabTitle();

    QMap<QString,int> *tabMapping = new QMap<QString,int>;
    tabMapping->insert("lpAction",0);
    tabMapping->insert("starAction",1);
    tabMapping->insert("aboutAction",2);

    // 绑定主Tab切换效果
    foreach(QAction *action,main->findChildren<QAction *>(QRegularExpression(".*Action.*")))
    {
        connect(action,&QAction::triggered,main,[=](){
            ui->tabMain->setCurrentIndex(tabMapping->find(action->objectName()).value());
            cancelOtherActionActivat(action);
        });
    }

    // 加载LP的公司树
    this->config->buildLpTreeModel(ui->lpTree);
    // 构建LP查询结果表格的表头
    ui->treeWidget->setSortingEnabled(true);
    ui->treeWidget->setHeaderLabels(QStringList()<< "物品名" << "数量" << "LP成本"<<"ISK成本"<<"材料成本"<<"收入"<<"利润"<<"日交易量"<<"出货指数"<<"LP比例");

    // 显示状态栏

    QLabel *hd = new QLabel(main);
    hd->setFrameStyle(QFrame::Box|QFrame::Sunken);
    hd->setText("<a href='http://www.hd-eve.com'>欧服军团：混沌仲裁者招新</a>");
    hd->setOpenExternalLinks(true);
    ui->statusbar->addPermanentWidget(hd);






}
/**
 * 隐藏主Tab容器的表头
 * @brief hideMainTabTitle
 */
void Application::hideMainTabTitle()
{
    ui->tabMain->tabBar()->hide();
}
/**
 * 取消其他Action的激活效果
 * @brief cancelOtherActionActivat
 * @param action
 */
void Application::cancelOtherActionActivat(QAction *pAction)
{

    foreach(QAction *action,main->findChildren<QAction *>(QRegularExpression(".*Action")))
    {
        if(action->objectName() != "" && action->objectName() != pAction->objectName())
        {
            action->setChecked(false);
        }
    }

}
