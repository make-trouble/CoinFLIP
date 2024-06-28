#include "mycoin.h"
#include<QDebug>

//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}

MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret=pix.load(btnImg);
    if(!ret)
    {
        qDebug()<<btnImg<<"图片加载失败";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(QIcon(pix));
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器
    this->timer=new QTimer(this);

    connect(timer,&QTimer::timeout,[=]()
    {
        QPixmap pix;
        if(this->flag==1)
        {
            QString str=QString(":/res/Coin000%1.png").arg(++min);
            pix.load(str);
            if(this->min>=this->max)
            {
                this->min=1;
                this->flag=false;
                isAnimation=false;
                timer->stop();
            }
        }
        else
        {
            QString str=QString(":/res/Coin000%1.png").arg(--max);
            pix.load(str);
            if(this->max<=this->min)
            {
                this->max=8;
                this->flag=true;
                isAnimation=false;
                timer->stop();
            }
        }

        //设置按钮固定大小
        this->setFixedSize(pix.width(),pix.height());   //pix.width(),pix.height()均是保留背景后的尺寸

        //设置不规则样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(QIcon(pix));   //QPixmap对象不保留背景

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    });
}

void MyCoin::changeFlag()
{
    timer->start(30);
    isAnimation=true;
}

void MyCoin::mousePressEvent(QMouseEvent *event)
{
    if(isAnimation||this->isWin)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(event);
    }
//    if(this->timer->isActive())
//    {
//        return;
//    }
//    else
//    {
//        QPushButton::mousePressEvent(event);
//    }
}

void MyCoin::keyPressEvent(QKeyEvent *event)
{
    return;
}

