#ifndef GAMESTART_H
#define GAMESTART_H

#include <QDialog>
#include <QButtonGroup>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSound>
#include "load.h"

namespace Ui {
class GameStart;
}

class GameStart : public QDialog
{
    Q_OBJECT

public:
    explicit GameStart(QWidget *parent = nullptr);
    ~GameStart();
    bool eventFilter(QObject* watched, QEvent* event);
    void mousePressEvent(QMouseEvent *e) override;
    void start();
    void playMusic();
    void loading();//加一个加载窗口
    Load l;

private:
    Ui::GameStart *ui;
//    QMediaPlayer * player;
//    QMediaPlaylist * playlist;
    QSound *sound;//尝试得最终只能使用sound来进行播放
    QTimer* q;

//private slots:
//    void start();

};

#endif // GAMESTART_H
