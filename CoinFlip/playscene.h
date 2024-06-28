#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include"mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum);
    ~PlayScene();
    int levelIndex;
    void paintEvent(QPaintEvent *event);
    int** gameArray;
    MyCoin ***coinBtn;
    void game(int panelSize);
    int checkSum=0;   //校验盘面硬币flag之和是否为全金币状态
signals:
    void gameSceneBack();
};

#endif // PLAYSCENE_H
