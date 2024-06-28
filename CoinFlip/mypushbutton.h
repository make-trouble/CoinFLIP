#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include<QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//  explicit MyPushButton(QWidget *parent = nullptr);

    //构造函数 参数1 正常显示的图片路径   参数2 按下后显示的图片路径
    MyPushButton(QString normalImg,QString pressImg="");
    QString normalImgPath;
    QString pressImgPath;
    void zoom1();   //start按钮向下跳
    void zoom2();   //start按钮向上跳
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
signals:

};

#endif // MYPUSHBUTTON_H

