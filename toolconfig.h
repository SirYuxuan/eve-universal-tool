#ifndef TOOLCONFIG_H
#define TOOLCONFIG_H
#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include "http.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QStandardItemModel>
#include <QTreeView>
#include <QTableView>

/**
 * 系统配置
 * @brief The ToolConfig class
 */
class ToolConfig: QObject
{
public:
    ToolConfig(QMainWindow *main);
    ~ToolConfig();
    void init();
    /**
     * 加载EVE-LP的网络数据
     * @brief loadLpData
     */
    void loadLpData();
    /**
     * 构建LP树需要的数据
     * @brief buildLpTreeModel
     * @return
     */
    void buildLpTreeModel(QTreeView *tree);
    /**
     * 构建LP查询结果表格的表头
     * @brief buildLpSearchTableHeaderModel
     * @return
     */
    void buildLpSearchTableHeaderModel(QTableView *table);

private:
    QSqlDatabase db;
    QMainWindow *main;
};

#endif
