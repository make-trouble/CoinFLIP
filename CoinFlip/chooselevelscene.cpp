#include "chooselevelscene.h"
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QDebug>
#include<QLabel>
#include<QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //设置固定大小
    setFixedSize(320,588);

    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    setWindowTitle("选择关卡场景");

    //退出按钮实现
    QMenuBar *bar=menuBar();
    QMenu *startMenu=bar->addMenu("开始");
    QAction *quitAction=startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //设置选择关卡音效
    QSound *chooseSound=new QSound(":/res/TapButtonSound.wav",this);
    //设置返回按钮音效
    QSound *backSound=new QSound(":/res/BackButtonSound.wav",this);

    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    connect(backBtn,&MyPushButton::clicked,[=](){
        backSound->play();    //播放返回按钮音效
        QTimer::singleShot(200,this,[=]()->char *{
            emit this->chooseSceneBack();
        });
    });

    for(int i=0;i<20;i++)
    {
        MyPushButton *selectBtn=new MyPushButton(":/res/LevelIcon.png");
        selectBtn->setParent(this);
        selectBtn->move(25+i%4*70,130+i/4*70);

        //监听每个按钮的点击事件
        connect(selectBtn,&MyPushButton::clicked,[=](){
            chooseSound->play();   //播放选择关卡音效
            play=new PlayScene(i+1);
            play->setGeometry(this->geometry());   //设置翻金币场景的位置
            this->hide();
            play->show();

            //监听翻金币主场景的back按钮的信号
            connect(play,&PlayScene::gameSceneBack,[=](){
                this->setGeometry(play->geometry());   //设置从翻金币场景返回选择关卡场景的位置
                delete play;
                play=NULL;
                this->show();
            });
        });

        QLabel *label=new QLabel;
        label->setParent(this);
        label->setFixedSize(selectBtn->width(),selectBtn->height());
        label->setText(QString::number(i+1));
        label->move(25+i%4*70,130+i/4*70);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        //设置鼠标穿透(因为有标签遮盖了按钮)
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }

}

void ChooseLevelScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}

