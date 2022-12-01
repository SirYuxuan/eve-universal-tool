#ifndef HTTP_H
#define HTTP_H
#include <QNetworkAccessManager>

class Http : public QObject
{
    Q_OBJECT
public:
    explicit Http(QObject *parent = nullptr);
    static QString get(QString strUrl);
    static QByteArray getPic(QString strUrl);
private:



signals:

};

#endif // HTTP_H
