#include "playscene.h"
#include<QDebug>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QLabel>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>
//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int levelNum)
{
    this->levelIndex=levelNum;

    //设置固定大小
    setFixedSize(320,588);

    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    setWindowTitle("翻金币场景");

    //退出按钮实现
    QMenuBar *bar=menuBar();
    QMenu *startMenu=bar->addMenu("开始");
    QAction *quitAction=startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //设置返回按钮音效
    QSound *backSound=new QSound(":/res/BackButtonSound.wav",this);

    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    connect(backBtn,&MyPushButton::clicked,[=](){
        backSound->play();     //播放返回按钮音效
        QTimer::singleShot(200,this,[=]()->char *{
             emit this->gameSceneBack();
        });
    });

    //显示当前关卡数
    QLabel *label=new QLabel;
    label->setParent(this);
    label->setGeometry(30,this->height()-50,120,50);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str1=QString("Level:%1").arg(this->levelIndex);
    label->setFont(font);
    label->setText(str1);

    if(this->levelIndex<=10)
    {
        game(4);
    }
    else if(this->levelIndex>10&&this->levelIndex<=15)
    {
        game(5);
    }
    else
    {
        game(6);
    }





}

void PlayScene::game(int panelSize)
{
    //设置硬币翻转音效
    QSound *flipSound=new QSound(":/res/ConFlipSound.wav",this);
    //设置游戏胜利音效
    QSound *winSound=new QSound(":/res/LevelWinSound.wav",this);

    this->gameArray=new int*[panelSize];
    for(int i=0;i<panelSize;i++)
    {
        this->gameArray[i]=new int[panelSize];
    }
    coinBtn=new MyCoin**[panelSize];
    for(int i=0;i<panelSize;i++)
    {
        coinBtn[i]=new MyCoin*[panelSize];
    }

    //从dataConfig配置文件中初始化gameArray数组
    dataConfig config;
    for(int i=0;i<panelSize;i++)
    {
        for(int j=0;j<panelSize;j++)
        {
            this->gameArray[i][j]=(*(config.mData.find(levelIndex))).at(i).at(j);
            this->checkSum=this->checkSum+gameArray[i][j];
        }
    }

    //设置胜利时显示的图片
        QLabel *winLabel=new QLabel;
        QPixmap winPix;
        winPix.load(":/res/LevelCompletedDialogBg.png");
        winLabel->setGeometry(0,0,winPix.width(),winPix.height());
        winLabel->setPixmap(winPix);
        winLabel->setParent(this);
        winLabel->move((this->width()-winPix.width())*0.5,-winPix.height());

    //显示硬币背景图片
    QPixmap pix=QPixmap(":/res/BoardNode.png");
    for(int i=0;i<panelSize;i++)
    {
        for(int j=0;j<panelSize;j++)
        {
            QLabel *label=new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setParent(this);
            label->setPixmap(pix);
            label->move((this->width()-label->width()*panelSize)*0.5+i*label->width(),200+j*label->height());

            //创建硬币
            QString str=gameArray[i][j]==1?":/res/Coin0001.png":":/res/Coin0008.png";
            MyCoin *coin=new MyCoin(str);
            coin->setParent(this);
            coin->move((label->width()-coin->width())*0.5+(this->width()-label->width()*panelSize)*0.5+i*label->width(),(label->height()-coin->height())*0.5+200+j*label->height());

            coin->posX=i;
            coin->posY=j;
            coin->flag=this->gameArray[i][j];  //1正面(金币)  0反面(银币)
            coinBtn[i][j]=coin;
            connect(coin,&QPushButton::clicked,[=]()
            {
                flipSound->play();    //播放硬币翻转音效

                //按下一个硬币后立即禁用所有硬币(防止快速按下导致bug)
                for(int i=0;i<panelSize;i++)
                {
                    for(int j=0;j<panelSize;j++)
                    {
                        coinBtn[i][j]->isWin=true;
                    }
                }
                coin->changeFlag();
                this->gameArray[i][j] = this->gameArray[i][j]==0?1:0;
                this->checkSum+=(this->gameArray[i][j]==0?-1:1);
                QTimer::singleShot(300,this,[=](){
                    //上方硬币翻转
                    if(coin->posY-1>=0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1]=this->gameArray[coin->posX][coin->posY-1]==0?1:0;
                        this->checkSum+=(this->gameArray[coin->posX][coin->posY-1]==0?-1:1);
                    }
                    //下方硬币翻转
                    if(coin->posY+1<=panelSize-1)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1]=this->gameArray[coin->posX][coin->posY+1]==0?1:0;
                        this->checkSum+=(this->gameArray[coin->posX][coin->posY+1]==0?-1:1);
                    }
                    //左方硬币翻转
                    if(coin->posX-1>=0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY]=this->gameArray[coin->posX-1][coin->posY]==0?1:0;
                        this->checkSum+=(this->gameArray[coin->posX-1][coin->posY]==0?-1:1);
                    }
                    //右方硬币翻转
                    if(coin->posX+1<=panelSize-1)
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY]=this->gameArray[coin->posX+1][coin->posY]==0?1:0;
                        this->checkSum+=(this->gameArray[coin->posX+1][coin->posY]==0?-1:1);
                    }

                    //待一次硬币点击操作后(上下左右所有要翻转的硬币都翻转完毕)立即解锁所有硬币
                    for(int i=0;i<panelSize;i++)
                    {
                        for(int j=0;j<panelSize;j++)
                        {
                            coinBtn[i][j]->isWin=false;
                        }
                    }

                    //判断是否胜利(胜利瞬间禁用所有按钮)
                    if(this->checkSum==panelSize*panelSize)
                    {
                        winSound->play();   //播放游戏胜利音效
                        for(int i=0;i<panelSize;i++)
                        {
                            for(int j=0;j<panelSize;j++)
                            {
                                coinBtn[i][j]->isWin=true;
                            }
                        }

                        //游戏胜利提示
                        QPropertyAnimation *animation=new QPropertyAnimation(winLabel,"geometry");
                        animation->setDuration(1000);
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                    }
                });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}

PlayScene::~PlayScene()
{
    if(this->levelIndex<=10)
    {
        for(int i=0;i<4;i++)
        {
            delete[] coinBtn[i];
        }
        delete[] coinBtn;
        for(int i=0;i<4;i++)
        {
            delete[] gameArray[i];
        }
        delete[] gameArray;
    }
    else if(this->levelIndex>10&&this->levelIndex<=15)
    {
        for(int i=0;i<5;i++)
        {
            delete[] coinBtn[i];
        }
        delete[] coinBtn;
        for(int i=0;i<5;i++)
        {
            delete[] gameArray[i];
        }
        delete[] gameArray;
    }
    else
    {
        for(int i=0;i<6;i++)
        {
            delete[] coinBtn[i];
        }
        delete[] coinBtn;
        for(int i=0;i<6;i++)
        {
            delete[] gameArray[i];
        }
        delete[] gameArray;
    }
}
