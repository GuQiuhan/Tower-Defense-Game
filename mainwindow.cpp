#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMovie>
#include "monster.h"
#include <iostream>
#include <QTimer>
#include <QPushButton>
#include <QMessageBox>
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QDebug>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new CustomScene(this)),
    gamecontroller(new GameController(*scene,this))//游戏控制器，创建即游戏开始
{
    ui->setupUi(this);
    scene->setController(gamecontroller);
    InitBackground();//初始化背景
    InitListWidget();//初始化塔防栏
    createActions();//增加菜单栏
    createMenus();

    test();//！测试路线，发行时删除！


    setAcceptDrops(true);		//设置：接受拖放
    ui->listWidget->setAcceptDrops(false);//list控件不支持drag，所以松开鼠标时icon不会移位

}

void MainWindow::InitBackground()
{
    //左上角标签
    ui->lineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset;color: rgb(128, 0, 2)");
    ui->lineEdit_2->setStyleSheet("background:transparent;border-width:0;border-style:outset;color: rgb(128, 0, 2)");
    QFont font;
    font.setFamily("Trattatello");
    font.setPixelSize(20);
    font.setBold(true);
    ui->lineEdit->setFont(font);
    ui->lineEdit_2->setFont(font);
    ui->lineEdit->setText("Your Blood Now: 100/100");
    QString s="Round: ";
    s+=QString::number(gamecontroller->getRound());
    ui->lineEdit_2->setText(s);
    //场景
    scene->setSceneRect(0, 0, 900, 550);//设置坐标系，此时坐标（0，0）在窗口左上角
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setStyleSheet("background: transparent");
    //一定要设置透明背景！将label置于底层，这样子scene里的item才可以露出来，底下的background也可以看见

    //添加背景到scene
    //由于背景是gif,所以使用scene->addWidget
    QLabel* label=new QLabel(this);
    label->setGeometry(0,0,910,560);
    QMovie *movie = new QMovie(":/image/map2.gif");
    label->setMovie(movie);// 在标签中添加动画
    label->setScaledContents(true);
    label->lower();//一定要这句代码置于底层！否则看不见view
    movie->start();
    // 将label添加到场景中
    //labelProxy= scene->addWidget(label);//scene->addWidget返回一个代理


}


void MainWindow::InitListWidget()
{
    ui->listWidget->setViewMode(QListView::IconMode);
    ui->listWidget->setFlow(QListView::TopToBottom);
    ui->listWidget->setIconSize(QSize(100,70));//设置icon大小
    //ui->listWidget->setGridSize(QSize(50, 20));
    QFont font;
    font.setFamily("American Typewriter");
    font.setPixelSize(10);
    font.setBold(true);
    QListWidgetItem *item1 = new QListWidgetItem(QIcon(":/image/MoonTower.jpg"), "MoonTower");
    item1->setFont(font);
    //item1->setBackground(QColor(204,204,204));
    QListWidgetItem *item2 = new QListWidgetItem(QIcon(":/image/tower4_v1.jpg"), "GunTower1");
    item2->setFont(font);
    QListWidgetItem *item3 = new QListWidgetItem(QIcon(":/image/tower4_v2.jpg"), "GunTower3");
    item3->setFont(font);
    QListWidgetItem *item4 = new QListWidgetItem(QIcon(":/image/tower5_v1.jpg"), "GunTower2");
    item4->setFont(font);
    QListWidgetItem *item5 = new QListWidgetItem(QIcon(":/image/tower5_v2.jpg"), "GunTower4");
    item5->setFont(font);

    ui->listWidget->setDragEnabled(true);
    ui->listWidget->addItem(item2);
    ui->listWidget->addItem(item4);
    ui->listWidget->addItem(item3);
    ui->listWidget->addItem(item5);
    ui->listWidget->addItem(item1);

}
MainWindow::~MainWindow()//释放内存
{
    //labelProxy=NULL;
    //delete labelProxy;//这里删除会导致程序崩溃吗？
    delete scene;
    delete ui;
}

void MainWindow::test()
{
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::black);
    //第一条路
    scene->addLine(330,0,330,100);
    scene->addLine(330,100,300,125);
    scene->addLine(300,125,160,125);
    scene->addLine(160,125,110,175);
    scene->addLine(110,175,110,430);
    scene->addLine(110,430,160,480);
    scene->addLine(160,480,300,480);
    scene->addLine(300,480,340,450);
    scene->addLine(340,450,480,450);
    scene->addLine(480,450,530,475);
    scene->addLine(530,475,910,475);
    //(330,0)
    //(330,100)
    //(300,125)
    //(160,125)
    //(110,175)
    //(110,430)
    //(160,480)
    //(300,480)
    //(340,450)
    //(480,450)
    //(530,475)
    //(910,475)

    //第二条路
    scene->addLine(860,0,860,260);
    scene->addLine(860,260,825,305);
    scene->addLine(825,305,700,305);
    scene->addLine(700,305,650,340);
    scene->addLine(650,340,650,475);
    scene->addLine(650,475,910,475);
    //(860,0)
    //(860,260)
    //(825,305)
    //(700,305)
    //(650,340)
    //(650,475)
    //(910,475)



}

void MainWindow::createActions() //菜单栏
{
    newGameAction = new QAction(tr("&New Game"), this);
    newGameAction->setShortcuts(QKeySequence::New);
    newGameAction->setStatusTip(tr("Start a new game"));
    connect(newGameAction, &QAction::triggered, this, &MainWindow::newGame);

    exitAction = new QAction(tr("&Exit"), this);
    //exitAction->setVisible(true);
    //exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the game"));
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    pauseAction = new QAction(tr("&Pause"), this);
    pauseAction->setStatusTip(tr("Pause..."));
    connect(pauseAction, &QAction::triggered, gamecontroller, &GameController::pause);

    resumeAction = new QAction(tr("&Resume"), this);
    resumeAction->setStatusTip(tr("Resume..."));
    resumeAction->setEnabled(false);
    gamecontroller->setResumeAction(resumeAction);
    connect(resumeAction, &QAction::triggered, gamecontroller, &GameController::resume);

    gameHelpAction = new QAction(tr("Game &Help"), this);
    gameHelpAction->setShortcut(tr("Ctrl+H"));
    gameHelpAction->setStatusTip(tr("Help on this game"));
    connect(gameHelpAction, &QAction::triggered, this, &MainWindow::gameHelp);

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the application's about box"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction, &QAction::triggered, qApp, QApplication::aboutQt);
}

void MainWindow::createMenus()
{
    //注意，由于macOS的特性，这里的QAction不会按照代码加入的逻辑排列
    QMenu *options = menuBar()->addMenu(tr("&Options"));
    //options->addAction(aboutAction);
    options->addAction(newGameAction);
    options->addSeparator();
    options->addAction(pauseAction);
    options->addAction(resumeAction);
    options->addSeparator();
    options->addAction(exitAction);

    QMenu *help = menuBar()->addMenu(tr("&Help"));
    help->addAction(gameHelpAction);
    help->addAction(aboutAction);
    help->addAction(aboutQtAction);
}


void MainWindow::newGame()
{
    QTimer::singleShot(0, gamecontroller, SLOT(gameOver()));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About this Game"), tr("<h2>Doggy Game</h2>"
        "<p>Copyright &copy; GuQiuhan."
        "<p>This game is a small Qt application written by GuQiuhan. Hope you like it ~"));
}

void MainWindow::gameHelp()
{
    QMessageBox::about(this, tr("Game Help"), tr("Learn it by yourself hahaha ~"
        "<p>Space - pause & resume"));
}




