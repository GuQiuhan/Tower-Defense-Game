#ifndef GAMESTART_H
#define GAMESTART_H

#include <QDialog>
#include <QButtonGroup>

namespace Ui {
class GameStart;
}

class GameStart : public QDialog
{
    Q_OBJECT

public:
    explicit GameStart(QWidget *parent = nullptr);
    ~GameStart();

private slots:


    void on_start_clicked();

private:
    Ui::GameStart *ui;


};

#endif // GAMESTART_H
