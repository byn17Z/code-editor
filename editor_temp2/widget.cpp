#include "widget.h"
#include "mytexteditor.h"
#include "djumpwindow.h"
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QLineEdit>
#include <QTextEdit>
#include <QTextBrowser>
#include <QStatusBar>
#include <QFileDialog>
#include <QCoreApplication>
#include <QIODevice>
#include <QFile>
#include <QMessageBox>
#include <QLabel>


//CONSTRUCTOR
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    // set window
    this->setFixedSize(900, 600);
    this->setWindowTitle("Editor");




    // set tool bar
    QMenuBar* myBar = new QMenuBar(this);

        QMenu* menuFile = new QMenu("File", this);
        myBar->addMenu(menuFile);

            QAction* actNew = new QAction("New", this);
            menuFile->addAction(actNew);
            connect(actNew, &QAction::triggered, this, &Widget::newSlot);

            QAction* actOpen = new QAction("Open", this);
            menuFile->addAction(actOpen);
            connect(actOpen, &QAction::triggered, this, &Widget::openSlot);

            QAction* actSave = new QAction("Save", this);
            menuFile->addAction(actSave);
            connect(actSave, &QAction::triggered, this, &Widget::saveSlot);

            QAction* actSaveAs = new QAction("Save As", this);
            menuFile->addAction(actSaveAs);
            connect(actSaveAs, &QAction::triggered, this, &Widget::saveAsSlot);

            QAction* actClose = new QAction("Close", this);
            menuFile->addAction(actClose);
            connect(actClose, &QAction::triggered, this, &Widget::closeSlot);


        QMenu* menuEdit = new QMenu("Edit", myBar);
        myBar->addMenu(menuEdit);

        QMenu* menuDebug = new QMenu("Debug", myBar);
        myBar->addMenu(menuDebug);

            QAction* actDebug = new QAction("Debug", this);
            menuDebug->addAction(actDebug);
            connect(actDebug, &QAction::triggered, this, &Widget::debugSlot);


            QAction* actDNext = new QAction("Next", this);
            menuDebug->addAction(actDNext);
            connect(actDNext, &QAction::triggered, this, &Widget::dNextSlot);

            QAction* actDPre = new QAction("Previous", this);
            menuDebug->addAction(actDPre);
            connect(actDPre, &QAction::triggered, this, &Widget::dPreSlot);

            QAction* actDJump = new QAction("Jump", this);
            menuDebug->addAction(actDJump);
            // connect(actDJump, &QAction::triggered, this, &Widget::dJumpSlot);

            QAction* actDTmn = new QAction("Terminate", this);
            menuDebug->addAction(actDTmn);
            connect(actDTmn, &QAction::triggered, this, &Widget::dTmnSlot);

        QMenu* menuCompile = new QMenu("Compile", myBar);
        myBar->addMenu(menuCompile);


    QPushButton* btnRefresh = new QPushButton("Refresh", this);
    btnRefresh->move(450, 0);


    // set edit area
    // MyTextEditor *textEditor = new MyTextEditor(this);
    this->m_myEditor = new MyTextEditor(this);

    connect(btnRefresh, &QAbstractButton::pressed, this->m_myEditor, &MyTextEditor::refreshEditor);


    //TEST
    // std::string strHtml = "<span style=\"color: red;\">Edit Area</span>";
    // QString qstrHtml = QString::fromStdString(strHtml);
    // textEditor->QTextEdit::setHtml(qstrHtml);
    // connect(textEditor, &QTextEdit::textChanged, this, &Widget::setisCFileSaved);


    // set terminal bar
    QTextBrowser* term = new QTextBrowser(this);
    term->resize(800, 160);
    term->move(50, 420);
    this->m_myTerminal = term;


    // set status bar
    QStatusBar* statusBar = new QStatusBar(this);
    statusBar->move(0, 575);
    statusBar->resize(900, 20);
    statusBar->show();
    statusBar->showMessage("Ready", 1000);


    // this->m_dJumpWin = new DJumpWindow(this);
    // this->m_dJumpWin->hide();

}




//QPROPEERTY myEditor
//READ - myEditor
// MyTextEditor* Widget::myEditor()
// {
//     return this->m_myEditor;
// }


// //WRITE - myEditor
// void Widget::setEditor(MyTextEditor* textEditor)
// {
//     this->m_myEditor = textEditor;
// }


//SIGNAL - myEditor
// void Widget::myEditorChanged() {}




//QPROPEERTY cFilePath
// //READ - cFilePath
// QString Widget::cFilePath()
// {
//     return this->m_cFilePath;
// }


// //WRITE - cFilePath
// void Widget::setcFilePath(QString path)
// {
//     this->m_cFilePath = path;
// }


//SIGNAL - cFilePath
// void cFilePathChanged() {}


// //QPROPEERTY isCFileSaved
// //READ - isCFileSaved
// bool Widget::isCFileSaved()
// {
//     return this->m_isCFileSaved;
// }


// //WRITE - isCFileSaved
// void Widget::setisCFileSaved()
// {
//     qDebug() << this->m_isCFileSaved;
//     this->m_isCFileSaved = 0;
// }


// //SIGNAL - isCFileSaved
// // void Widget::isCFileSavedChanged() {}


// READ - m_myDebugger
MyDebugger* Widget::myDebugger()
{
    return this->m_myDebugger;
}




//ACTION SLOTS


//MENU :File
//actNew 新建文件
void Widget::newSlot()
{
    if (this->m_isDebuggerOn == 1) {
        qDebug() << "not available: debugger on";
        return;
    }

    // prompt用户选择新建路径
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "new",
        QCoreApplication::applicationFilePath());

    if (fileName.isEmpty()) {return;}

    else {
        qDebug() << fileName;

        // 关闭当前文件
        this->Widget::closeSlot();

        // 储存新建文件的路径为当前路径，供保存时使用
        this->m_cFilePath = fileName;
        this->m_myTerminal->setPlainText(fileName);

        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        file.close();
    }

    // this->m_isCFileSaved = 0;
}


//actOpen 打开文件
void Widget::openSlot()
{
    if (this->m_isDebuggerOn == 1) {
        qDebug() << "not available: debugger on";
        return;
    }

    // prompt用户选择文件
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "open",
        QCoreApplication::applicationFilePath(),
        "*.cpp");

    if (fileName.isEmpty()) {return;}

    else {
        qDebug() << fileName;

        // 关闭当前文件
        this->Widget::closeSlot();

        // 储存打开文件的路径为当前路径，供保存时使用
        this->m_cFilePath = fileName;
        this->m_myTerminal->setPlainText(fileName);

        // 从当前路径载入文件内容
        QFile file(fileName);
        file.open(QIODevice::ReadOnly);
        QByteArray openContent = file.readAll();
        this->m_myEditor->setPlainText(openContent);
        file.close();

        // this->m_isCFileSaved = 0;
    }
}


//actSave 保存文件
void Widget::saveSlot()
{
    if (this->m_isDebuggerOn == 1) {
        qDebug() << "not available: debugger on";
        return;
    }

    // 未打开或创建文件时，跳转save as
    if (this->m_cFilePath.isEmpty()) {this->Widget::saveAsSlot();}

    else {
        qDebug() << this->m_cFilePath;

        // 保存文件到当前路径
        QFile file(this->m_cFilePath);
        file.open(QIODevice::WriteOnly);
        QByteArray saveContent = this->m_myEditor->toPlainText().QString::toUtf8();
        file.write(saveContent);

        // this->m_saveSuccess = 1;

        // this->m_isCFileSaved = 1;
    }
}


//actSaveAs 另存为
void Widget::saveAsSlot()
{
    if (this->m_isDebuggerOn == 1) {
        qDebug() << "not available: debugger on";
        return;
    }

    // prompt用户选择保存路径
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "save as...",
        QCoreApplication::applicationFilePath());

    if (fileName.isEmpty()) {
        // 用户有主动关闭/取消另存为窗口、未选择路径的可能性
        // 在actClose关闭文件的过程中，保存是否完成涉及actClose是否继续的判断
        this->m_saveSuccess = 0;
        return;
    }

    else {
        qDebug() << fileName;

        // 保存文件到选择的路径
        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        QByteArray saveContent = this->m_myEditor->toPlainText().QString::toUtf8();
        file.write(saveContent);

        // 如果用户还没有打开或创建过文件，则储存选择另存为的路径作为当前路径
        if (this->m_cFilePath.isEmpty()) {
            this->m_cFilePath = fileName;
            this->m_myTerminal->setPlainText(fileName);
        }

        // 保存成功
        this->m_saveSuccess = 1;

        // this->m_isCFileSaved = 1;
    }
}


//actClose 关闭文件并清空窗口
void Widget::closeSlot()
{
    if (this->m_isDebuggerOn == 1) {
        qDebug() << "not available: debugger on";
        return;
    }

    // 未打开文件且内容为空时，直接关闭（跳过）
    if (this->m_cFilePath.isEmpty()) {
        if (this->m_myEditor->toPlainText().isEmpty()) {
            this->m_myTerminal->clear();
            return;}
    }

    // 有打开文件 或 未打开文件但有内容 时，提示是否保存
    QMessageBox* msgBox = new QMessageBox(this);
        msgBox->setText("Warning");
        msgBox->setInformativeText("Do you want to save your changes");
        msgBox->setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox->setDefaultButton(QMessageBox::Save);

    int ret = msgBox->exec();

    switch (ret) {
    case QMessageBox::Save:
        // Save was clicked
        // 保存
        this->Widget::saveSlot();

        // 清空窗口（如果用户在跳转另存为后关闭了另存为窗口，未完成保存过程，则放弃清空）
        if (this->m_saveSuccess) {
            this->m_cFilePath = "";
            this->m_myEditor->clear();
            this->m_myTerminal->clear();
        }

        // this->m_isCFileSaved = 1;
        break;

    case QMessageBox::Discard:
        // Don't Save was clicked
        // 只清空不保存
        this->m_cFilePath = "";
        this->m_myEditor->clear();
        this->m_myTerminal->clear();
        // this->m_isCFileSaved = 1;
        break;

    case QMessageBox::Cancel:
        // Cancel was clicked
        break;

    default:
        // should never be reached
        break;

    }
}




//MENU: Debug
void Widget::updateDebuggerInfo()
{
    if (this->m_myDebugger == NULL) {return;}

    // 获取debuggeer数据
    qDebug() << "before show()";
    std::pair<VT, int> debugInfo = this->m_myDebugger->show();
    qDebug() << "after show()";
    VT varTable = debugInfo.first;

    std::string clineNumStr = "CurrentLineNum:    ";
    clineNumStr += std::to_string(debugInfo.second);
    QString clineNum = QString::fromStdString(clineNumStr);
    qDebug() << QString::fromStdString(clineNumStr);

    // 展示debugger数据
    this->m_myTerminal->append("Debugger>\n");
    this->m_myTerminal->append(clineNum);

    qDebug() << "VT size = " << varTable.table.size() << "\n";

    for (int i = 0; i < varTable.table.size(); i++) {
        // std::array<std::string,4> cVar = varTable.table[i];
        // std::string varScope = cVar[0];
        // std::string varType = cVar[1];
        // std::string varName = cVar[2];
        // std::string varVal = cVar[3];
        std::string strInfo = "";
        qDebug() << "print info preparation iter: " << i << "\n";
        std::array title = {"scope", "type", "name", "value"};
        for (int t = 0; t < 4; t++) {
            qDebug() << "t = " << t;
            qDebug() << "title: " << QString::fromStdString(title[t]);
            qDebug() << "before get content: strInfo = " << QString::fromStdString(strInfo);
            strInfo += varTable.table[i][t];
            qDebug() << "after get content: strInfo = " << QString::fromStdString(strInfo) <<"\n";
            strInfo += "    ";
        }
        qDebug() << "before print info";
        this->m_myTerminal->append(QString::fromStdString(strInfo));
        qDebug() << "after print info" << "\n";

    }
    this->m_myTerminal->append("\n");
}


//actDebug 启动debugger
void Widget::debugSlot()
{
    this->saveSlot();
    if (m_cFilePath.isEmpty()) {return;}

    this->m_myEditor->setReadOnly(1);

    if (m_isDebuggerOn == 1) {
        qDebug() << "debugger restart";
        this->m_myTerminal->clear();
        this->m_myTerminal->setPlainText(this->m_cFilePath);
    }
    this->m_isDebuggerOn = 1;

    qDebug() << "debugger start";
    qDebug() << "m_cFilePath: " << this->m_cFilePath;
    // std::string fileName = this->m_cFilePath.toStdString();
    qDebug() << "before create debugger";
    // if (this->m_myDebugger == NULL) {
    //     qDebug() << "m_myDebugger is NULL now";
    // }

    this->m_myDebugger = new MyDebugger(this->m_cFilePath.toStdString());

    qDebug() << "after create debugger";

    this->updateDebuggerInfo();

    // this->m_myEditor->setReadOnly(0);
}


//actDNext
void Widget::dNextSlot()
{
    if (m_isDebuggerOn == 0) {
        qDebug() << "invalid \"next\" action";
        return;
    }

    // this->m_myEditor->setReadOnly(1);
    qDebug() << "before next";
    bool isNextSuccess = this->m_myDebugger->next();
    qDebug() << "after next";

    if (isNextSuccess){
        this->updateDebuggerInfo();
    }
    else {
        this->m_myTerminal->append("last step of the program");
        return;
    }

}


//actDPre
void Widget::dPreSlot()
{
    if (m_isDebuggerOn == 0) {
        qDebug() << "invalid \"previous\" action";
        return;
    }

    // this->m_myEditor->setReadOnly(1);
    qDebug() << "before pre";
    bool isPreSuccess = this->m_myDebugger->previous();
    qDebug() << "after pre";

    if (isPreSuccess) {
        this->updateDebuggerInfo();
    }
    else {
        this->m_myTerminal->append("first step of the program");
    }
}


//actDJump
void Widget::dJumpSlot()
{
    if (m_isDebuggerOn == 0) {
        qDebug() << "invalid \"jump\" action";
        return;
    }

    // this->m_myEditor->setReadOnly(1);
    // this->m_dJumpWin->show();

    // DJumpWindow* dJumpWin = new DJumpWindow(this);
    // dJumWin->show();
}


//actDTmn
void Widget::dTmnSlot()
{
    if (m_isDebuggerOn == 0) {
        qDebug() << "invalid \"Terminate\" action";
        return;
    }

    this->m_myDebugger->User::~User();
    this->m_myDebugger = NULL;
    if (this->m_myDebugger == NULL) {
        qDebug() << "clear debugger success";
    }
    this->m_myTerminal->clear();
    this->m_myTerminal->setPlainText(this->m_cFilePath);

    this->m_isDebuggerOn = 0;
    qDebug() << "debugger off";
    this->m_myEditor->setReadOnly(0);
}


//DECONSTRUCTOR
Widget::~Widget()
{
    this->closeSlot();
}



