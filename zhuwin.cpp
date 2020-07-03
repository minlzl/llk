
#include "ui_zhuwin.h"

#include <QDebug>
#include <QAction>
#include <QMessageBox>
#include <QPainter>
#include <QLine>
#include <QTimer>
#include <QString>
#include <QSize>
#include "zhuwin.h"
const int ksize=36;
const int topmargin=70;
const int leftmargin=50;

const QString kIconReleasedStyle = "";
const QString kIconClickedStyle = "background-color: rgba(255, 255, 12, 161)";
const QString kIconHintStyle = "background-color: rgba(255, 0, 0, 255)";

const int totaltime=10*60*1000;
const int kGameTimerInterval = 300;
const int timedelay=100;

zhuwin::zhuwin(int flag,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::zhuwin)
{
    ui->setupUi(this);
    pre=NULL;
    now=NULL;
    this->flag=flag;
    ui->centralwidget->installEventFilter(this);
    initgame(flag);
}

zhuwin::~zhuwin()
{
    if(game)
        delete game;
    delete ui;
}
void zhuwin::initgame(int flag)
{
    game=new model();
    game->gamestart();
    QString a=QString::number(game->score,10);
    ui->score->setText(a);
    for(int i=0;i<allsize;i++)
    {
        but[i]=new incobutton(this);
        but[i]->setGeometry(leftmargin+(i%maxcol)*ksize,topmargin+(i/maxcol)*ksize,ksize,ksize);
        but[i]->xid=i/maxcol;
        but[i]->yid=i%maxcol;
        but[i]->show();
        if(game->getmap()[i])
        {
            QPixmap map;
            QString str;
            str.sprintf(":/image/%d.png",game->getmap()[i]);
            map.load(str);
            QIcon icon(map);
            but[i]->setIcon(icon);
            but[i]->setIconSize(QSize(ksize,ksize));
            connect(but[i],SIGNAL(pressed()),this,SLOT(onIconButtonPressed()));
        }
        else
        {
            but[i]->hide();
        }
    }
    if(flag==2)
    {
        ui->timebar->setMaximum(totaltime);
        ui->timebar->setMinimum(0);
        ui->timebar->setValue(totaltime);
    }
    else if(flag==1)
    {
        ui->timebar->setMaximum(totaltime*100);
        ui->timebar->setMinimum(0);
        ui->timebar->setValue(totaltime*100);
        ui->timebar->hide();
        ui->label->hide();
    }
    time = new QTimer(this);
    connect(time, SIGNAL(timeout()), this, SLOT(gameTimerEvent()));
    time->start(300);
    this->linking=false;
}
void zhuwin::onIconButtonPressed()
{
    now = dynamic_cast<incobutton *>(sender());
    if(!pre)
    {
        now->setStyleSheet(kIconClickedStyle);
        pre=now;
    }
    else
    {
        if(pre!=now)
        {
            now->setStyleSheet(kIconClickedStyle);
            if(game->iscanline(pre->xid,pre->yid,now->xid,now->yid))
            {
                linking=true;
                update();
                QTimer::singleShot(timedelay,this,SLOT(handleLinkEffect()));
                 if (game->isfozened())
                      QMessageBox::information(this, "oops", "dead game");
                 if (game->iswin())
                      QMessageBox::information(this, "great", "you win");
            }
            else
            {
                pre->setStyleSheet(kIconReleasedStyle);
                now->setStyleSheet(kIconReleasedStyle);
                pre=NULL;
                now=NULL;
            }
        }
        else if(pre==now)
        {
            pre->setStyleSheet(kIconReleasedStyle);
            now->setStyleSheet(kIconReleasedStyle);
            pre=NULL;
            now=NULL;
        }
    }
}

void zhuwin::handleLinkEffect()
{
    game->points.clear();
    pre->hide();
    now->hide();
    pre=NULL;
    now=NULL;
    update();
    linking=false;
}


bool zhuwin::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type()==QEvent::Paint)
    {
        QString a=QString::number(game->score,10);
        ui->score->setText(a);
        QPainter paint(ui->centralwidget);
        QColor color(rand()%255,rand()%255,rand()%255);
        QPen pen;
        pen.setColor(color);
        pen.setWidth(5);
        paint.setPen(pen);

        QString str;
        for(int i=0;i<int(game->points.size())-1;i++)
        {
            point p1=game->points[i];
            point p2=game->points[i+1];
            QPoint put1;
            QPoint put2;
            put1=but[p1.x*maxcol+p1.y]->pos();
            put2=but[p2.x*maxcol+p2.y]->pos();

            QPoint pos1(put1.x() + ksize / 2, put1.y() + ksize / 2);
            QPoint pos2(put2.x() + ksize / 2, put2.y() + ksize / 2);

            paint.drawLine(pos1, pos2);
        }
        return true;
    }
    else
    {
        return QMainWindow::eventFilter(watched, event);
    }
}

void zhuwin::gameTimerEvent()
{
    if(ui->timebar->value()==0)
    {
        time->stop();
        QMessageBox::information(this,"gameover","play again");
        this->initgame(flag);
    }
    else
    {
        ui->timebar->setValue(ui->timebar->value()-kGameTimerInterval);
    }
}









void zhuwin::on_reset_clicked()
{
    game->gamereset();
    for(int i=0;i<allsize;i++)
    {
        if(game->getmap()[i])
        {
            QPixmap map;
            QString str;
            str.sprintf(":/image/%d.png",game->getmap()[i]);
            map.load(str);
            QIcon icon(map);
            but[i]->setIcon(icon);
            but[i]->setIconSize(QSize(ksize,ksize));
        }
        else
        {
            but[i]->hide();
        }
    }
    game->isfozened();
}







void zhuwin::on_tishi_clicked()
{
    game->isfozened();
    for(int i=0;i<4;i++)
    {
        if(game->gethit()[i]==-1)
        {
            return ;
        }
    }
    int x1=game->gethit()[0];
    int y1=game->gethit()[1];
    int x2=game->gethit()[2];
    int y2=game->gethit()[3];
    incobutton *but1=but[x1*maxcol+y1];
    incobutton *but2=but[x2*maxcol+y2];

    but1->setStyleSheet(kIconHintStyle);
    but2->setStyleSheet(kIconHintStyle);
}









