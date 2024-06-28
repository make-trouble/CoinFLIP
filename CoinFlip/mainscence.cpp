#include "mainscence.h"
#include "ui_mainscence.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QSound>
MainScence::MainScence(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScence)
{
    ui->setupUi(this);

    //设置固定大小
    setFixedSize(320,588);

    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    setWindowTitle("翻金币主场景");

    //退出按钮实现
    connect(ui->actionquit,&QAction::triggered,[=]()
    {
        this->close();
    });

    //设置游戏开始音效
    QSound *startSound=new QSound(":/res/TapButtonSound.wav",this);

    MyPushButton *startBtn=new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    choosescene=new ChooseLevelScene;

    connect(startBtn,&MyPushButton::clicked,[=]()
    {
        startSound->play();   //播放游戏开始音效
        startBtn->zoom1();
        startBtn->zoom2();
        QTimer::singleShot(500,this,[=]()->char *{
            choosescene->setGeometry(this->geometry());   //设置选择关卡场景的位置
            this->hide();
            choosescene->show();
        });
    });

    //监听选择关卡的back按钮的信号
    connect(choosescene,&ChooseLevelScene::chooseSceneBack,[=](){
        this->setGeometry(choosescene->geometry());   //设置从选择关卡场景返回主场景后的位置
        choosescene->hide();
        this->show();
    });
}

void MainScence::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}

MainScence::~MainScence()
{
    delete ui;
}



