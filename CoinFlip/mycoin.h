#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyCoin(QWidget *parent = nullptr);

      //参数代表传入的是金币路径还是银币路径
      MyCoin(QString btnImg);

      //硬币属性
      int posX;    //x坐标
      int posY;    //y坐标
      bool flag;   //正反标志
      QTimer *timer;  //定时器，翻转特效
      int min=1;
      int max=8;
      void changeFlag();   //实现硬币翻转
      bool isAnimation=false;    //判断翻转特效是否完成标志，防止因快速点击导致的前次翻转未完成时后次翻转开启
      void mousePressEvent(QMouseEvent *event);
      bool isWin=false;
      void keyPressEvent(QKeyEvent *event);
signals:

};

#endif // MYCOIN_H

