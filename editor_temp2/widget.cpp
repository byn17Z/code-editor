#include "widget.h"
#include <QPushButton>
#include <QLine>
#include <QTextEdit>
#include <QStatusBar>
#include <QFrame>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // this->resize(900, 600);
    this->setFixedSize(900, 600);
    this->setWindowTitle("Editor");

    QPushButton* btnFile = new QPushButton("File", this);
    btnFile->move(0, 0);

    QPushButton* btnSave = new QPushButton("Save", this);
    btnSave->move(75, 0);

    QPushButton* btnEdit = new QPushButton("Edit", this);
    btnEdit->move(150, 0);

    QPushButton* btnDebug = new QPushButton("Debug", this);
    btnDebug->move(225, 0);

    QPushButton* btnCompile = new QPushButton("Compile", this);
    btnCompile->move(300, 0);

    QPushButton* btnRun = new QPushButton("Run", this);
    btnRun->move(375, 0);

    QTextEdit* textEditor = new QTextEdit(this);
    textEditor->resize(790, 300);
    textEditor->move(50, 50);

    // QFrame* tFrame = new QFrame(this);
    // tFrame->resize(900, 175);
    // tFrame->move(0, 400);
    // tFrame->setLineWidth(5);
    // tFrame->setFrameStyle(QFrame::HLine | QFrame::Plain);

    QStatusBar* statusBar = new QStatusBar(this);
    statusBar->move(0, 550);
    statusBar->resize(900, 50);
    statusBar->show();
}

Widget::~Widget() {}
