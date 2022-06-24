#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QString>
#include <QPushButton>
#include <QPixmap>
#include <QDebug>
#include <QLineEdit>
#include <QButtonGroup>
#include <QRadioButton>
#include <QTime>
#include <QCloseEvent>
#include <QMediaPlaylist>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->initialMain();
    this->initialAbrupty();
    this->initialResultWindow();
    this->initialStartWindow();
    sw.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialMain()
{
    //对局窗口标题、图标、属性、大小初始化
    //两个消息窗口属性初始化
    this->setWindowTitle("Four in line: Battle v1080");
    this->setWindowIcon(QIcon(":/icon/mario.ico"));
    this->setAttribute(Qt::WA_QuitOnClose,false);
    this->setFixedSize(800,600);
    this->abruptLog.setAttribute(Qt::WA_QuitOnClose,false);
    this->resultLog.setAttribute(Qt::WA_QuitOnClose,false);

    //棋子四种样式初始化
    whiteCrystal = new QPixmap(":/pieces/white_crystal.jpg");
    blueCrystal = new QPixmap(":/pieces/blue_crystal.jpg");
    filmCult = new QPixmap(":/pieces/film_cult.jpg");
    vision = new QPixmap(":/pieces/vision.jpg");

    //箭头控件的地址初始化
    playerPointer1 = this->findChild<QLabel*>(QString("player1turn"));
    playerPointer2 = this->findChild<QLabel*>(QString("player2turn"));

    //准备大厅中显示玩家1和玩家2所选棋子的控件的地址初始化
    playerIcon1 = this->sw.findChild<QLabel*>(QString("pieceSample_1"));
    playerIcon2 = this->sw.findChild<QLabel*>(QString("pieceSample_2"));

    //对局中显示玩家1和玩家2所选棋子的控件的地址初始化
    battleIcon1 = this->ui->playerIcon_1;
    battleIcon2 = this->ui->playerIcon_2;

    //对局中显示玩家1和玩家2所取名称的控件的地址初始化
    battleName1 = this->ui->playerName_1;
    battleName2 = this->ui->playerName_2;

    //玩家1和玩家2的单选按钮分组容器初始化
    playerIconGroup1 = new QButtonGroup(this);
    playerIconGroup2 = new QButtonGroup(this);

    //单选按钮控件的地址的初始化
    radio1 = this->sw.findChild<QRadioButton*>(QString("radioButton_0"));
    radio2 = this->sw.findChild<QRadioButton*>(QString("radioButton_1"));
    radio3 = this->sw.findChild<QRadioButton*>(QString("radioButton_2"));
    radio4 = this->sw.findChild<QRadioButton*>(QString("radioButton_3"));

    //将单选按钮分组
    playerIconGroup1->addButton(radio1);
    playerIconGroup1->addButton(radio2);
    playerIconGroup2->addButton(radio3);
    playerIconGroup2->addButton(radio4);

    //准备大厅玩家1和玩家2名称输入框的地址初始化
    text1 = this->sw.findChild<QLineEdit*>(QString("lineEdit_1"));
    text2 = this->sw.findChild<QLineEdit*>(QString("lineEdit_2"));

    //音效文件初始化
    keyboard = new QSoundEffect(this);
    keyboard->setSource(QUrl::fromLocalFile(":/vfx/effects/player1_turn_remind_1.wav"));
    keyboard->setVolume(0.75f);
    star = new QSoundEffect(this);
    star->setSource(QUrl::fromLocalFile(":/vfx/effects/player1_turn_remind_2.wav"));
    star->setVolume(0.75f);
    piano = new QSoundEffect(this);
    piano->setSource(QUrl::fromLocalFile(":/vfx/effects/player2_turn_remind_1.wav"));
    piano->setVolume(0.75f);
    drum = new QSoundEffect(this);
    drum->setSource(QUrl::fromLocalFile(":/vfx/effects/player2_turn_remind_2.wav"));
    drum->setVolume(0.75f);
    start = new QSoundEffect(this);
    start->setSource(QUrl::fromLocalFile(":/vfx/effects/battle_start_btn.wav"));
    start->setVolume(0.75f);
    success = new QSoundEffect(this);
    success->setSource(QUrl::fromLocalFile(":/vfx/effects/battle_success.wav"));
    success->setVolume(0.75f);
    abrupt = new QSoundEffect(this);
    abrupt->setSource(QUrl::fromLocalFile(":/vfx/effects/battle_abrupt.wav"));
    abrupt->setVolume(0.75f);

    //玩家1和玩家2的回合音效选择初始化
    vfxPlayer1 = keyboard;
    vfxPlayer2 = piano;

    //玩家1和玩家2音效选择下拉菜单地址初始化
    vfx1Box = this->sw.findChild<QComboBox*>(QString("vfx1ComboBox"));
    vfx2Box = this->sw.findChild<QComboBox*>(QString("vfx2ComboBox"));
    connect(vfx1Box,QOverload<int>::of(&QComboBox::activated),this,[=](int i){this->forVfxComboBoxSolution(1,i);});
    connect(vfx2Box,QOverload<int>::of(&QComboBox::activated),this,[=](int i){this->forVfxComboBoxSolution(2,i);});

    //音效试听按钮初始化
    vfx1ViewBtn = this->sw.findChild<QPushButton*>(QString("vfx1ViewButton"));
    connect(this->vfx1ViewBtn,&QPushButton::clicked,this,[=](){this->vfxPlayer1->play();});
    vfx2ViewBtn = this->sw.findChild<QPushButton*>(QString("vfx2ViewButton"));
    connect(this->vfx2ViewBtn,&QPushButton::clicked,this,[=](){this->vfxPlayer2->play();});

    //对局背景音乐初始化
    QMediaPlaylist* list1 = new QMediaPlaylist(this);
    list1->addMedia(QUrl("qrc:/music/bgm/Beautiful Ruin.mp3"));
    list1->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    ruin = new QMediaPlayer(this);
    ruin->setPlaylist(list1);
    ruin->setVolume(25);
    QMediaPlaylist* list2 = new QMediaPlaylist(this);
    list2->addMedia(QUrl("qrc:/music/bgm/Lost In Epizode.mp3"));
    list2->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    lost = new QMediaPlayer(this);
    lost->setPlaylist(list2);
    lost->setVolume(25);
    QMediaPlaylist* list3 = new QMediaPlaylist(this);
    list3->addMedia(QUrl("qrc:/music/bgm/Theme.mp3"));
    list3->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    theme = new QMediaPlayer(this);
    theme->setPlaylist(list3);
    theme->setVolume(25);
    QMediaPlaylist* list4 = new QMediaPlaylist(this);
    list4->addMedia(QUrl("qrc:/music/bgm/Untrodden Morn.mp3"));
    list4->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    morn = new QMediaPlayer(this);
    morn->setPlaylist(list4);
    morn->setVolume(25);
    QMediaPlaylist* list5 = new QMediaPlaylist(this);
    list5->addMedia(QUrl("qrc:/music/bgm/Wonderful world.mp3"));
    list5->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    world = new QMediaPlayer(this);
    world->setPlaylist(list5);
    world->setVolume(25);
    QMediaPlaylist* list6 = new QMediaPlaylist(this);
    list6->addMedia(QUrl("qrc:/music/bgm/Beautiful Ruin View.mp3"));
    ruinView = new QMediaPlayer(this);
    ruinView->setPlaylist(list6);
    ruinView->setVolume(25);
    QMediaPlaylist* list7 = new QMediaPlaylist(this);
    list7->addMedia(QUrl("qrc:/music/bgm/Lost In Epizode View.mp3"));
    lostView = new QMediaPlayer(this);
    lostView->setPlaylist(list7);
    lostView->setVolume(25);
    QMediaPlaylist* list8 = new QMediaPlaylist(this);
    list8->addMedia(QUrl("qrc:/music/bgm/Theme View.mp3"));
    themeView= new QMediaPlayer(this);
    themeView->setPlaylist(list8);
    themeView->setVolume(25);
    QMediaPlaylist* list9 = new QMediaPlaylist(this);
    list9->addMedia(QUrl("qrc:/music/bgm/Untrodden Morn View.mp3"));
    mornView = new QMediaPlayer(this);
    mornView->setPlaylist(list9);
    mornView->setVolume(25);
    QMediaPlaylist* list10 = new QMediaPlaylist(this);
    list10->addMedia(QUrl("qrc:/music/bgm/Wonderful world View.mp3"));
    worldView = new QMediaPlayer(this);
    worldView->setPlaylist(list10);
    worldView->setVolume(25);

    //对局背景音乐选择初始化
    bgm = ruin;
    bgmView = ruinView;

    //准备大厅对局背景音乐选择下拉菜单初始化
    bgmBox = this->sw.findChild<QComboBox*>(QString("bgmComboBox"));
    connect(bgmBox,QOverload<int>::of(&QComboBox::activated),this,[=](int i){this->forBgmComboBoxSolution(i);});

    //描述文本初始化
    musicText[0] = new QString("作曲：高田雅史\n来自：高速动作推理游戏《弹丸论破2》\n发布日期：2012年8月21日");
    musicText[1] = new QString("作曲：马海平\n来自：个人专辑《遗落边境》\n发布日期：2020年6月16日");
    musicText[2] = new QString("作曲：植松伸夫（2022年重混、1988年原曲）\n来自：2DRPG游戏《最终幻想II》\n发布日期：2022年3月17日");
    musicText[3] = new QString("作曲：SilentRoom\n来自：第二个人专辑《In My Heart》\n发布日期：2022年4月24日");
    musicText[4] = new QString("作曲：高田雅史\n来自：JRPG游戏《数码宝贝物语：网络侦探》\n发布日期：2015年5月29日");

    //背景音乐描述标签初始化
    bgmInfo = this->sw.findChild<QLabel*>(QString("bgmInfo"));
    bgmInfo->setText(*this->musicText[0]);

    //准备大厅对局背景音乐试听按钮
    bgmViewBtn = this->sw.findChild<QPushButton*>(QString("bgmViewButton"));
    connect(bgmViewBtn,&QPushButton::clicked,this,[=](){bgmView->play();});

    //指针数组初始化，下棋按钮按下的信号绑定对应处理函数
    for(int i=0;i<7;i++)
    {
        insert[i] = this->findChild<QPushButton*>(QString("pushButton_%1").arg(i));
        connect(insert[i],&QPushButton::clicked,this,[=](){forInsertButtonSolution(i);});
    }

    //准备大厅单选按钮绑定对应处理函数
    for(int i=0;i<4;i++)
    {
        QRadioButton* temp = this->sw.findChild<QRadioButton*>(QString("radioButton_%1").arg(i));
        connect(temp,&QRadioButton::clicked,this,[=](){forRadioSolution(i);});
    }

    //准备大厅“战斗开始”按钮绑定处理函数
    {
        QPushButton* temp = this->sw.findChild<QPushButton*>(QString("pushButton"));
        connect(temp,&QPushButton::clicked,this,[=](){battleStart();});
    }

    radio1->setChecked(true);radio1->clicked();
    radio3->setChecked(true);radio3->clicked();
}

void MainWindow::initialAbrupty()
{
    abruptLog.setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    abruptLog.setWindowFlag(Qt::WindowCloseButtonHint,false);
    QPushButton* btn1 = this->abruptLog.findChild<QPushButton*>(QString("pushButton"));
    connect(btn1,&QPushButton::clicked,&this->abruptLog,[=](){
        this->clearBoard();
        this->showStartWindow();
        sw.show();
        abruptLog.close();
    });
}

void MainWindow::initialResultWindow()
{
    resultLog.setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    resultLog.setWindowFlag(Qt::WindowCloseButtonHint,false);
    QPushButton* btn1 = this->resultLog.findChild<QPushButton*>(QString("pushButton"));
    connect(btn1,&QPushButton::clicked,&this->resultLog,[=](){
        this->clearBoard();
        this->showStartWindow();
        sw.show();
        this->hide();
        resultLog.close();
    });
}

void MainWindow::initialStartWindow()
{
    //准备大厅窗口标题、图标、大小初始化
    //关闭最大最小化
    //显示准备大厅
    //默认设置初始化等
    sw.setWindowTitle("Four in line: Setup v1080 ");
    sw.setWindowIcon(QIcon(":/icon/mario.ico"));
    sw.setFixedSize(360,480);
    sw.setWindowFlag(Qt::WindowMinMaxButtonsHint,false);
    this->showStartWindow();
    this->playerIcon1->setPixmap(*this->whiteCrystal);
    this->playerIcon2->setPixmap(*this->blueCrystal);
}

void MainWindow::initialBattleName()
{
    if(text1->text() != "" && text1->text() == text2->text())
    {
        this->getBattleName1()->setText(text1->text()+"(1)");
        this->getBattleName2()->setText(text2->text()+"(2)");
    }
    else
    {
        if(text1->text() == "")
        {
            this->getBattleName1()->setText("玩家一");
        }
        else
        {
            this->getBattleName1()->setText(text1->text());
        }
        if(text2->text() == "")
        {
            this->getBattleName2()->setText("玩家二");
        }
        else
        {
            this->getBattleName2()->setText(text2->text());
        }
    }
}

void MainWindow::forRadioSolution(int i)
{
    switch (i)
    {
        case 0:
        this->piecePlayer1 = this->whiteCrystal;
        this->getPlayerIcon1()->setPixmap(*this->whiteCrystal);
        this->getBattleIcon1()->setPixmap(*this->whiteCrystal);break;
        case 1:
        this->piecePlayer1 = this->filmCult;
        this->getPlayerIcon1()->setPixmap(*this->filmCult);
        this->getBattleIcon1()->setPixmap(*this->filmCult);break;
        case 2:
        this->piecePlayer2 = this->blueCrystal;
        this->getPlayerIcon2()->setPixmap(*this->blueCrystal);
        this->getBattleIcon2()->setPixmap(*this->blueCrystal);break;
        case 3:
        this->piecePlayer2 = this->vision;
        this->getPlayerIcon2()->setPixmap(*this->vision);
        this->getBattleIcon2()->setPixmap(*this->vision);break;
    }
}

void MainWindow::forInsertButtonSolution(int column)
{
    int x = column;
    int y = pieceCount[column];
    this->inputPiece(x,y);
    this->columnFullDetect(column);
    bool isOver, isTie;
    isOver = this->judgeWinner(x,y);
    isTie = this->judgeTie();
    if(isOver || isTie)
    {
        if(isOver)
        {
            this->winner = this->getCurrentTurn();
        }
        if(isTie)
        {
            this->winner = 0;
        }
        this->showResultWindow();
        return;
    }
    this->continueBattle();
}

void MainWindow::forVfxComboBoxSolution(int boxId, int i)
{
    if(boxId == 1)
    {
        switch(i)
        {
            case 0:
            this->vfxPlayer1 = this->keyboard;break;
            case 1:
            this->vfxPlayer1 = this->star;break;
        }
    }
    else if(boxId == 2)
    {
        switch(i)
        {
            case 0:
            this->vfxPlayer2 = this->piano;break;
            case 1:
            this->vfxPlayer2 = this->drum;break;
        }
    }
}

void MainWindow::forBgmComboBoxSolution(int i)
{
    switch(i)
    {
    case 0:
        this->bgm = this->ruin;this->bgmView = this->ruinView;bgmInfo->setText(*this->musicText[0]);break;
    case 1:
        this->bgm = this->lost;this->bgmView = this->lostView;bgmInfo->setText(*this->musicText[1]);break;
    case 2:
        this->bgm = this->theme;this->bgmView = this->themeView;bgmInfo->setText(*this->musicText[2]);break;
    case 3:
        this->bgm = this->morn;this->bgmView = this->mornView;bgmInfo->setText(*this->musicText[3]);break;
    case 4:
        this->bgm = this->world;this->bgmView = this->worldView;bgmInfo->setText(*this->musicText[4]);break;
    }
}

void MainWindow::inputPiece(int x, int y)
{
    this->pieceMap[y][x] = this->getCurrentTurn();
    if(this->pieceCount[x] < 6)
    {
        this->pieceCount[x]++;
    }
    QLabel* piece = this->findChild<QLabel*>(QString("piece_%1%2").arg(y).arg(x));
    if(this->getCurrentTurn() == 1)
    {
        piece->setPixmap(*piecePlayer1);
    }
    else if(this->getCurrentTurn() == 2)
    {
        piece->setPixmap(*piecePlayer2);
    }
}

void MainWindow::showCurrentTurnPointer()
{
    int turn = this->getCurrentTurn();
    if(turn == 1)
    {
        this->vfxPlayer1->play();
        this->playerPointer1->show();
        this->playerPointer2->hide();
    }
    else if(turn == 2)
    {
        this->vfxPlayer2->play();
        this->playerPointer1->hide();
        this->playerPointer2->show();
    }
}

void MainWindow::showAbrupty()
{
    this->bgm->stop();
    for(int i=0;i<7;i++) insert[i]->setEnabled(true);
    this->abrupt->play();
    this->abruptLog.exec();
}

void MainWindow::showResultWindow()
{
    this->bgm->stop();
    this->chooseWinner();
    for(int i=0;i<7;i++) insert[i]->setEnabled(true);
    this->success->play();
    this->resultLog.exec();
}

void MainWindow::showStartWindow()
{
    memset(this->pieceCount,0,sizeof(this->pieceCount));
    memset(this->pieceMap,0,sizeof(this->pieceMap));
    this->playerPointer1->hide();
    this->playerPointer2->hide();
    this->setCurrentTurn(0);
    this->setPiecePlayer1(this->whiteCrystal);
    this->setPiecePlayer2(this->blueCrystal);
}

void MainWindow::battleStart()
{
    this->start->play();
    this->chooseFirstHand();
    this->showCurrentTurnPointer();
    this->initialBattleName();
    this->show();
    this->bgm->play();
    sw.hide();
}

void MainWindow::chooseFirstHand()
{
    QTime randtime;
    randtime = QTime::currentTime();
    qsrand(randtime.msec()+randtime.second()*1000);
    this->setCurrentTurn((qrand() % 2)+1);
}

void MainWindow::chooseWinner()
{
    QLabel* winMsg = this->resultLog.findChild<QLabel*>(QString("label_2"));
    switch (this->winner)
    {
        case 0:
        winMsg->setText(QString("平局!"));
        break;
        case 1:
        winMsg->setText(QString("胜者为%1!").arg(this->getBattleName1()->text()));
        break;
        case 2:
        winMsg->setText(QString("胜者为%1!").arg(this->getBattleName2()->text()));
        break;
    }
}

bool MainWindow::judgeWinner(int x, int y)
{
    int targetPiece = this->getCurrentTurn();
    //horizontal
    {
        int sequence = 0;
        for(int i= 0;i < 7;i++)
        {
            if(this->pieceMap[y][i] == targetPiece) sequence++;
            else sequence = 0;
            if(sequence == 4) return true;
        }
    }
    //vertical
    {
        int sequence = 0;
        for(int i = 0;i < 6;i++)
        {
            if(this->pieceMap[i][x] == targetPiece) sequence++;
            else sequence = 0;
            if(sequence == 4) return true;
        }
    }
    //diagnal
    {
        int sequence = 0;
        if(y >= x)
        {
            int start_y = y - x;
            for(int i = 0;start_y < 6;i++,start_y++)
            {
                if(this->pieceMap[start_y][i] == targetPiece) sequence++;
                else sequence = 0;
                if(sequence == 4) return true;
            }
        }
        else
        {
            int start_x = x - y;
            for(int i = 0;start_x < 7;i++,start_x++)
            {
                if(this->pieceMap[i][start_x] == targetPiece) sequence++;
                else sequence = 0;
                if(sequence == 4) return true;
            }
        }
    }
    //anti-diagnal
    {
        int sequence = 0;
        if(x + y > 2)
        {
            int start_y = x + y;
            int i = 0;
            if(start_y > 5)
            {
                start_y = 5 , i = x + y - start_y;
                for(;i < 7;i++,start_y--)
                {
                    if(this->pieceMap[start_y][i] == targetPiece) sequence++;
                    else sequence = 0;
                    if(sequence == 4) return true;
                }
            }
            else
            {
                for(;start_y > -1;i++,start_y--)
                {
                    if(this->pieceMap[start_y][i] == targetPiece) sequence++;
                    else sequence = 0;
                    if(sequence == 4) return true;
                }
            }

        }
    }
    return false;
}

bool MainWindow::judgeTie()
{
    for(int i=0;i<7;i++)
    {
        if(this->pieceCount[i] != 6)
        {
             return false;
        }
    }
    return true;
}

void MainWindow::columnFullDetect(int column)
{
    if(this->pieceCount[column] == 6)
    {
        this->insert[column]->setDisabled(true);
    }
}

void MainWindow::continueBattle()
{
    if(this->getCurrentTurn() == 1)
    {
        this->setCurrentTurn(2);
    }
    else if(this->getCurrentTurn() == 2)
    {
        this->setCurrentTurn(1);
    }
    this->showCurrentTurnPointer();
}

void MainWindow::clearBoard()
{
    for(int i=0;i<6;i++)
    {
        QLabel* temp = nullptr;
        for(int j=0;j<7;j++)
        {
            temp = this->findChild<QLabel*>(QString("piece_%1%2").arg(i).arg(j));
            temp->setPixmap(QPixmap());
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    this->hide();
    this->showAbrupty();
    this->showStartWindow();
    event->ignore();
    sw.show();
}

int MainWindow::getCurrentTurn() const
{
    return currentTurn;
}

void MainWindow::setCurrentTurn(int value)
{
    currentTurn = value;
}

QPixmap *MainWindow::getPiecePlayer1() const
{
    return piecePlayer1;
}

void MainWindow::setPiecePlayer1(QPixmap *value)
{
    piecePlayer1 = value;
}

QPixmap *MainWindow::getPiecePlayer2() const
{
    return piecePlayer2;
}

QLabel *MainWindow::getBattleIcon1() const
{
    return battleIcon1;
}

void MainWindow::setBattleIcon1(QLabel *value)
{
    battleIcon1 = value;
}

QLabel *MainWindow::getBattleIcon2() const
{
    return battleIcon2;
}

QLabel *MainWindow::getBattleName1() const
{
    return battleName1;
}

void MainWindow::setBattleName1(QLabel *value)
{
    battleName1 = value;
}

QLabel *MainWindow::getBattleName2() const
{
    return battleName2;
}

QLabel *MainWindow::getPlayerIcon1() const
{
    return playerIcon1;
}

void MainWindow::setPlayerIcon1(QLabel *value)
{
    playerIcon1 = value;
}

QLabel *MainWindow::getPlayerIcon2() const
{
    return playerIcon2;
}

void MainWindow::setPlayerIcon2(QLabel *value)
{
    playerIcon2 = value;
}

void MainWindow::setBattleName2(QLabel *value)
{
    battleName2 = value;
}

void MainWindow::setBattleIcon2(QLabel *value)
{
    battleIcon2 = value;
}

void MainWindow::setPiecePlayer2(QPixmap *value)
{
    piecePlayer2 = value;
}
