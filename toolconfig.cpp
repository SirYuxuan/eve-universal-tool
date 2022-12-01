#include "toolconfig.h"

ToolConfig::ToolConfig(QMainWindow *main):QObject(main)
{
    this->main = main;
    const QString DBPWD = "yuxuaneve2012";
    const QString DBFILE = "./Database.eve";

    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setPassword(DBPWD);

    this->db.setDatabaseName(DBFILE);

    if(!this->db.open())
    {
        QMessageBox::critical(main,"提示","无法打开核心配置文件，程序无法正常运行");
        exit(-1);
    }
    // 创建核心表
    if(!this->db.tables().contains("config"))
    {
        // 首次启动项目，创建各种数据表，缓存数据等
        QSqlQuery query;
        if(!query.exec("CREATE TABLE 'config' ('id' INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,'label' TEXT,'value' TEXT);"))
        {
            QMessageBox::critical(main,"提示",QString("程序异常，无法创建核心配置文件,").append(query.lastError().text()));
            exit(-1);
        }
        query.exec("CREATE TABLE 'lp_power' ('power' TEXT,'power_en' TEXT,'power_id' INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT);");
        query.exec("CREATE TABLE 'lp_company' ('company' TEXT,'company_en' TEXT,'company_id' INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,'power_id' INTEGER);");
        loadLpData();

    }





}
/**
 * 加载EVE-LP的网络数据
 * @brief loadLpData
 */
void ToolConfig::loadLpData()
{
    QString result = Http::get("https://eve-lp.com/api/common/factionList");
    QJsonParseError parseErr;
    QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8(),&parseErr);

    if(parseErr.error != QJsonParseError::NoError)
    {
        QMessageBox::critical(main,"提示",QString("程序异常，无法解析忠诚点数据"));
    }

    QJsonArray jsonArr = doc.array();
    for(int i = 0;i < jsonArr.size();i++)
    {
        QJsonValue val = jsonArr.at(i);
        QJsonObject power = val.toObject();
        QJsonArray corpArr = power.value("corporationList").toArray();
        // 打印势力
        int factionId = power["factionId"].toInt();
        QString factionName = power["factionName"].toString();
        QString factionNameZh = power["factionNameZh"].toString();
        QSqlQuery query;
        query.prepare("insert into lp_power values(?,?,?)");
        query.addBindValue(factionNameZh);
        query.addBindValue(factionName);
        query.addBindValue(factionId);
        query.exec();
        for(int j = 0;j < corpArr.size();j++)
        {
            QJsonObject corp = corpArr.at(j).toObject();
            int corpId = corp["corpId"].toInt();
            QString corpName = corp["corpName"].toString();
            QString corpNameZh = corp["corpNameZh"].toString();
            QSqlQuery query;
            query.prepare("insert into lp_company values(?,?,?,?)");
            query.addBindValue(corpNameZh);
            query.addBindValue(corpName);
            query.addBindValue(corpId);
            query.addBindValue(factionId);
            query.exec();
        }
    }

}
/**
 * 构建LP树需要的数据
 * @brief buildLpTreeModel
 * @return
 */
void ToolConfig::buildLpTreeModel(QTreeView *tree)
{
    QStandardItemModel *model = new QStandardItemModel(tree);
    QSqlQuery query;
    query.exec("select * from lp_power");
    while(query.next())
    {
        QString power = query.value(0).toString();
        QString powerEn = query.value(1).toString();
        int powerId = query.value(2).toInt();
        QStandardItem *item=new QStandardItem(power);
        QJsonObject obj;
        obj.insert("id",powerId);
        obj.insert("end",false);
        QVariant var;
        var.setValue(obj);
        item->setData(var);
        item->setToolTip(powerEn);
        item->setIcon(QIcon(QString(":/corp/").append(QString::number(powerId)).append(".png")));
        model->appendRow(item);
        QSqlQuery corpQuery;
        corpQuery.prepare("select * from lp_company where power_id = ?");
        corpQuery.addBindValue(powerId);
        corpQuery.exec();
        while(corpQuery.next())
        {
            QString corpName = corpQuery.value(0).toString();
            QString corpNameEn = corpQuery.value(1).toString();
            int corpId = corpQuery.value(2).toInt();
            QStandardItem *corpItem = new QStandardItem(corpName);
            QJsonObject objCorp;
            objCorp.insert("id",corpId);
            objCorp.insert("end",true);
            QVariant varCorp;
            varCorp.setValue(objCorp);
            corpItem->setData(varCorp);
            corpItem->setToolTip(corpNameEn);
            corpItem->setIcon(QIcon(QString(":/corp/").append(QString::number(corpId)).append(".png")));
            item->appendRow(corpItem);
        }
    }
    tree->setHeaderHidden(true);
    tree->setModel(model);


}
/**
 * 构建LP查询结果表格的表头
 * @brief buildLpSearchTableHeaderModel
 * @return
 */
void ToolConfig::buildLpSearchTableHeaderModel(QTableView *table)
{
    QStandardItemModel *model = new QStandardItemModel;
    table->setModel(model);
    table->setSortingEnabled(true);
    model->setColumnCount(10);
    model->setHeaderData(0,Qt::Horizontal,"物品名");
    model->setHeaderData(1,Qt::Horizontal,"数量");
    model->setHeaderData(2,Qt::Horizontal,"LP成本");
    model->setHeaderData(3,Qt::Horizontal,"ISK成本");
    model->setHeaderData(4,Qt::Horizontal,"材料成本");
    model->setHeaderData(5,Qt::Horizontal,"收入");
    model->setHeaderData(6,Qt::Horizontal,"利润");
    model->setHeaderData(7,Qt::Horizontal,"日交易量");
    model->setHeaderData(8,Qt::Horizontal,"出货指数");
    model->setHeaderData(9,Qt::Horizontal,"LP比例");

}
ToolConfig::~ToolConfig()
{

}
