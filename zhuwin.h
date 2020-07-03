#ifndef ZHUWIN_H
#define ZHUWIN_H

#include <QMainWindow>
#include <QPushButton>
#include "model.h"
namespace Ui {
class zhuwin;
}


struct incobutton:QPushButton{
public:
    incobutton(QWidget *parent=Q_NULLPTR):
        QPushButton(parent),
        xid(-1),
        yid(-1)
    {}
    int xid;
    int yid;
};

class zhuwin : public QMainWindow
{
    Q_OBJECT

public:
    explicit zhuwin(int flag,QWidget *parent = 0);
    ~zhuwin();
    virtual bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::zhuwin *ui;
    model *game;
    incobutton *but[allsize];
    QTimer *time;
    incobutton *pre,*now;
    bool linking;
    int flag;
public:
    void initgame(int flag);

private slots:
    void onIconButtonPressed(); // icon点击到响应
    void gameTimerEvent(); // 游戏计时回调
    void handleLinkEffect(); // 实现连接效果
    //void on_hintBtn_clicked(); // 提示按钮
    //void on_robot_btn_clicked(); // 机器人自动刷
    //void createGameWithLevel(); // 选中难度开始
    void on_reset_clicked();
    void on_tishi_clicked();
};



#endif // ZHUWIN_H
