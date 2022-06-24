#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "startwindow.h"
#include "dialog.h"
#include "resultdialog.h"
#include <QMainWindow>
#include <QPixmap>
#include <QLabel>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLineEdit>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int getCurrentTurn() const;
    QPixmap *getPiecePlayer1() const;
    QPixmap *getPiecePlayer2() const;

    bool getIsInBattle() const;

    QLabel *getBattleIcon1() const;
    QLabel *getBattleIcon2() const;

    QLabel *getBattleName1() const;
    QLabel *getBattleName2() const;

    QLabel *getPlayerIcon1() const;
    QLabel *getPlayerIcon2() const;

private:
    //对局窗口UI
    Ui::MainWindow *ui;

    //开始窗口对象
    StartWindow sw;

    //异常关闭窗口
    Dialog abruptLog;

    //对局结算窗口
    ResultDialog resultLog;

    //计数每列有多少棋子的数组
    int pieceCount[7];

    //棋盘映射的二维数组，用于判断是否连成四子
    int pieceMap[6][7];

    //数字1表示轮到玩家1，数字2表示轮到玩家2
    int currentTurn;

    //结算是判断赢家是谁
    //0是平局，1是玩家1，2是玩家2
    int winner;

    //玩家1和玩家2的棋子图案地址
    QPixmap* piecePlayer1;
    QPixmap* piecePlayer2;

    //棋子四种样式的地址
    QPixmap* whiteCrystal;
    QPixmap* blueCrystal;
    QPixmap* filmCult;
    QPixmap* vision;

    //对局中指向轮到哪位玩家下棋的箭头控件的地址
    QLabel* playerPointer1;
    QLabel* playerPointer2;

    //准备大厅中显示玩家1和玩家2所选棋子的控件的地址
    QLabel* playerIcon1;
    QLabel* playerIcon2;

    //对局中显示玩家1和玩家2所选棋子的控件的地址
    QLabel* battleIcon1;
    QLabel* battleIcon2;

    //对局中显示玩家1和玩家2所取名称的控件的地址
    QLabel *battleName1, *battleName2;

    //准备大厅单选按钮逻辑分组用的容器，保证容器内的单选按钮互斥
    QButtonGroup  *playerIconGroup1, *playerIconGroup2;

    //准备大厅单选按钮的地址
    QRadioButton *radio1, *radio2, *radio3, *radio4;

    //准备大厅玩家1和玩家2名称输入框的地址
    QLineEdit *text1, *text2;

    //指针数组，存放了对局中在7列下棋按钮的地址
    QPushButton* insert[7];

    //不同音效初始化
    QSoundEffect *keyboard, *star, *piano, *drum, *start, *success, *abrupt;

    //玩家1和玩家2的回合音效选择
    QSoundEffect *vfxPlayer1, *vfxPlayer2;

    //准备大厅玩家1和玩家2音效选择下拉菜单地址
    QComboBox *vfx1Box, *vfx2Box;

    //准备大厅玩家1和玩家2音效试听按钮地址
    QPushButton *vfx1ViewBtn, *vfx2ViewBtn;

    //对局背景音乐列表
    QMediaPlayer *ruin, *lost, *theme, *morn, *world, *ruinView, *lostView, *themeView, *mornView, *worldView;

    //对局背景音乐选择
    QMediaPlayer *bgm, *bgmView;

    //准备大厅对局背景音乐选择下拉菜单地址
    QComboBox* bgmBox;

    //描述文本
    QString* musicText[5];

    //准备大厅对局背景音乐描述标签地址
    QLabel* bgmInfo;

    //准备大厅对局背景音乐试听按钮地址
    QPushButton* bgmViewBtn;

    void initialMain();

    void initialAbrupty();

    void initialResultWindow();

    void initialStartWindow();

    void initialBattleName();

    void forRadioSolution(int i);

    void forInsertButtonSolution(int colmun);

    void forVfxComboBoxSolution(int boxId, int i);

    void forBgmComboBoxSolution(int i);

    void inputPiece(int x, int y);

    void showCurrentTurnPointer();

    void showAbrupty();

    void showResultWindow();

    void showStartWindow();

    void battleStart();

    void chooseFirstHand();

    void chooseWinner();

    bool judgeWinner(int x, int y);

    bool judgeTie();

    void columnFullDetect(int column);

    void continueBattle();

    void clearBoard();

    void closeEvent(QCloseEvent *event);

    void setCurrentTurn(int value);
    void setPiecePlayer1(QPixmap *value);
    void setPiecePlayer2(QPixmap *value);
    void setBattleIcon1(QLabel *value);
    void setBattleIcon2(QLabel *value);
    void setBattleName1(QLabel *value);
    void setBattleName2(QLabel *value);
    void setPlayerIcon1(QLabel *value);
    void setPlayerIcon2(QLabel *value);

};
#endif // MAINWINDOW_H
