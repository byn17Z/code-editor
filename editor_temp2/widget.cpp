#include "widget.h"
#include "mytexteditor.h"
#include <QPushButton>
#include <QLine>
#include <QTextEdit>
#include <QTextBrowser>
#include <QStatusBar>
#include <QFrame>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // set window
    this->setFixedSize(900, 600);
    this->setWindowTitle("Editor");


    // set tool bar
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

    QPushButton* btnRefresh = new QPushButton("Refresh", this);
    btnRefresh->move(450, 0);



    // set edit area
    MyTextEditor *textEditor = new MyTextEditor(this);


    connect(btnFile, &QAbstractButton::pressed, textEditor, &QTextEdit::clear);
    connect(btnSave, &QAbstractButton::pressed, textEditor, &QTextEdit::clear);
    connect(btnEdit, &QAbstractButton::pressed, textEditor, &QTextEdit::clear);
    connect(btnDebug, &QAbstractButton::pressed, textEditor, &QTextEdit::clear);
    connect(btnCompile, &QAbstractButton::pressed, textEditor, &QTextEdit::clear);
    connect(btnRun, &QAbstractButton::pressed, textEditor, &QTextEdit::clear);
    connect(btnRefresh, &QAbstractButton::pressed, textEditor, &MyTextEditor::updateTextEditor);

    // std::string strHtml = "<span style=\"color: red;\">Edit Area</span>";
    // QString qstrHtml = QString::fromStdString(strHtml);
    // textEditor->QTextEdit::setHtml(qstrHtml);

    // connect(textEditor, &QTextEdit::textChanged, this, &Widget::setMyText);




    // set terminal bar
    QTextEdit* term = new QTextEdit(this);
    term->resize(800, 160);
    term->move(50, 420);


    // set status bar
    QStatusBar* statusBar = new QStatusBar(this);
    statusBar->move(0, 575);
    statusBar->resize(900, 20);
    statusBar->show();
    statusBar->showMessage("Ready", 1000);
}

Widget::~Widget() {}



