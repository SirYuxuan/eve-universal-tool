#include "http.h"
#include <qdebug.h>
#include <QNetworkReply>
#include <QEventLoop>
#include <QMessageBox>
#include <QtNetwork/QSslConfiguration>
#include <QtNetwork/QSslSocket>
#include <QPixmap>
#include "loadingwidget.h"
Http::Http(QObject *parent) : QObject(parent)
{

}
/**
 * HttpGet请求
 * @brief Http::get
 * @param strUrl
 * @return
 */
QString Http::get(QString strUrl)
{
    LoadingWidget * loading = new LoadingWidget;
    loading->show();
    QNetworkAccessManager manager;
    const QUrl url = QUrl::fromUserInput(strUrl);
    assert(url.isValid());

    QNetworkRequest qnr(url);

    QNetworkReply* reply = manager.get(qnr);

    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);

    QByteArray replyData = reply->readAll();
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QVariant redirectAttr = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply->error() || 300 == statusCode  || !redirectAttr.isNull())
    {
        replyData.clear();
        loading->close();
        reply->deleteLater();
        reply = nullptr;
        delete loading;
        loading = NULL;
        return QString("网络连接错误,").append(QString::number(statusCode));
    }

    reply->deleteLater();
    reply = nullptr;
    loading->close();
    delete loading;
    loading = NULL;
    return QString(replyData);

}
/**
 * HttpGet请求获取网络图片
 * @brief Http::get
 * @param strUrl
 * @return
 */
QByteArray Http::getPic(QString strUrl)
{

    QNetworkAccessManager manager;
    const QUrl url = QUrl::fromUserInput(strUrl);
    assert(url.isValid());

    QNetworkRequest qnr(url);

    QNetworkReply* reply = manager.get(qnr);

    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);

    QByteArray replyData = reply->readAll();
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QVariant redirectAttr = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply->error() || 300 == statusCode  || !redirectAttr.isNull())
    {
        replyData.clear();
        return NULL;
    }
    return replyData;


}
