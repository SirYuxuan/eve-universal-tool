#include "lpcore.h"

LpCore::LpCore(Ui::MainWindow *ui,QMainWindow *main):QObject(main)
{
    this->ui = ui;
    this->main = main;
}

void LpCore::treeClick(QStandardItem *item)
{
    QJsonObject obj = item->data().toJsonObject();
    if(obj["end"].toBool())
    {
        QString url = "https://eve-lp.com/api/common/offerList?corpId=%1&region=10000002&offerOrderType=buy&requireOrderType=sell&scope=0.05&days=7&bluePrint=true&filter=true";
        QString result = Http::get(url.arg(obj["id"].toInt()));
        QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
        QJsonArray arr = doc.array();
        ui->treeWidget->clear();
        for(int i =0 ;i < arr.size() ; i++)
        {
            QJsonValue val = arr.at(i);
            QStringList strList;
            strList << val["typeNameZh"].toString();
            strList<< numberToStr(val["quantity"].toInt());
            strList<< numberToStr(val["lpCost"].toDouble());
            strList<< numberToStr(val["iskCost"].toDouble());
            strList<< numberToStr(val["sumCost"].toInt());
            strList<< numberToStr(val["sumGain"].toInt());
            strList<< numberToStr(val["sumProfit"].toInt());
            strList<< numberToStr(val["volume"].toInt());
            strList<< numberToStr(val["saleIndex"].toInt());
            strList<< numberToStr(val["unitProfit"].toInt());
            QTreeWidgetItem * item = new QTreeWidgetItem(strList);
            if(val["blueprintMaterialList"].isArray())
            {
                QJsonArray subArr = val["blueprintMaterialList"].toArray();

                for(int j = 0;j < subArr.size(); j++)
                {
                    QJsonValue subVal = subArr.at(j);
                    QStringList strList;
                    strList <<"蓝图材料"<<subVal["materialTypeNameZh"].toString()<<"数量"<<numberToStr(subVal["quantity"].toInt())<<"成本"<<numberToStr(subVal["price"].toInt());
                    QTreeWidgetItem * subItem = new QTreeWidgetItem(strList);
                    item->addChild(subItem);
                }

            }
            if(val["requireList"].isArray())
            {
                QJsonArray subArr = val["requireList"].toArray();

                for(int j = 0;j < subArr.size(); j++)
                {
                    QJsonValue subVal = subArr.at(j);
                    QTreeWidgetItem * subItem = new QTreeWidgetItem(QStringList()<<"兑换材料"<<subVal["typeNameZh"].toString()<<"数量"<<numberToStr(subVal["quantity"].toInt())<<"成本"<<numberToStr(subVal["price"].toInt()));
                    item->addChild(subItem);
                }


            }


            ui->treeWidget->addTopLevelItem(item);

        }

    }
}
//void LpCore::treeClick(QStandardItem *item)
//{
//    QJsonObject obj = item->data().toJsonObject();
//    if(obj["end"].toBool())
//    {
//        QString url = "https://eve-lp.com/api/common/offerList?corpId=%1&region=10000002&offerOrderType=buy&requireOrderType=sell&scope=0.05&days=7&bluePrint=true&filter=true";
//        QString result = Http::get(url.arg(obj["id"].toInt()));
//        QStandardItemModel *model= (QStandardItemModel *)this->ui->searchTable->model();

//        QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
//        QJsonArray arr = doc.array();
//        model->removeRows(0,model->rowCount());

//        for(int i =0 ;i < arr.size() ; i++)
//        {
//            QJsonValue val = arr.at(i);


//            //item->setIcon();

//            model->setItem(i,0, new QStandardItem(val["typeNameZh"].toString()));
//            model->setItem(i,1,new QStandardItem(numberToStr(val["quantity"].toInt())));
//            model->setItem(i,2,new QStandardItem(numberToStr(val["lpCost"].toDouble())));
//            model->setItem(i,3,new QStandardItem(numberToStr(val["iskCost"].toDouble())));
//            model->setItem(i,4,new QStandardItem(numberToStr(val["sumCost"].toInt())));
//            model->setItem(i,5,new QStandardItem(numberToStr(val["sumGain"].toInt())));
//            model->setItem(i,6,new QStandardItem(numberToStr(val["sumProfit"].toInt())));
//            model->setItem(i,7,new QStandardItem(numberToStr(val["volume"].toInt())));
//            model->setItem(i,8,new QStandardItem(numberToStr(val["saleIndex"].toInt())));
//            model->setItem(i,9,new QStandardItem(numberToStr(val["unitProfit"].toInt())));

//        }

//    }
//}
