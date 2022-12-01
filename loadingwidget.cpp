#include "loadingwidget.h"


LoadingWidget::LoadingWidget(QWidget *parent):QDialog(parent)
{

    label = new QLabel(this);
    this->setFixedSize(85,81);
    setAttribute(Qt::WA_TranslucentBackground);
    //setWindowOpacity(0.5);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setModal(true);
    this->setContentsMargins(0,0,0,0);
    label->setContentsMargins(0,0,0,0);
    movie = new QMovie(":/loading.gif");
    label->setMovie(movie);
    movie->start();
}
LoadingWidget::~LoadingWidget()
{
    if(label != NULL)
    {
        delete label;
        label = NULL;
    }
    if(movie != NULL)
    {
        delete movie;
        movie = NULL;
    }
}
