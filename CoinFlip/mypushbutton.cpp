#include "mypushbutton.h"
#include<QDebug>
#include<QPropertyAnimation>

//MyPushButton::MyPushButton(QWidget *parent) : QWidget(parent)
//{

//}

MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;
    QPixmap pix;
    bool ret=pix.load(normalImg);
    if(!ret)
    {
        qDebug()<<normalImg<<"图片加载失败";
        return;
    }
    //设置按钮固定大小
    this->setFixedSize(pix.width(),pix.height());   //pix.width(),pix.height()均是保留背景后的尺寸

    //设置不规则样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(QIcon(pix));   //QPixmap对象不保留背景

    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));

}

void MyPushButton::zoom1()
{
    //创建动态对象
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");

    //设置动画时间间隔
    animation->setDuration(200);

    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    connect(animation, &QPropertyAnimation::finished, animation, &QObject::deleteLater);

    //执行动画
    animation->start();

//  delete animation;
}

void MyPushButton::zoom2()
{
    //创建动态对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");

    //设置动画时间间隔
    animation->setDuration(200);

    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    connect(animation, &QPropertyAnimation::finished, animation, &QObject::deleteLater);

    //执行动画
    animation->start();

//  delete animation;
}

void MyPushButton::mousePressEvent(QMouseEvent *event)
{
    if(this->pressImgPath!="")
    {
        QPixmap pix;
        bool ret=pix.load(pressImgPath);
        if(!ret)
        {
            qDebug()<<pressImgPath<<"图片加载失败";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(QIcon(pix));
        this->setIconSize(QSize(pix.width(),pix.height()));
//        return;
    }
    return QPushButton::mousePressEvent(event);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(this->pressImgPath!="")
    {
        QPixmap pix;
        bool ret=pix.load(normalImgPath);
        if(!ret)
        {
            qDebug()<<normalImgPath<<"图片加载失败";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(QIcon(pix));
        this->setIconSize(QSize(pix.width(),pix.height()));
//        return;
    }
    return QPushButton::mouseReleaseEvent(event);
}

void MyPushButton::keyPressEvent(QKeyEvent *event)
{
    return;
}

