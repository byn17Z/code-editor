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
# include <QProcess>


//CONSTRUCTOR
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    // set window
    this->setFixedSize(900, 600);
    this->setWindowTitle("Editor");



    // set edit area
    // MyTextEditor *textEditor = new MyTextEditor(this);
    this->m_myEditor = new MyTextEditor(this);



    // set tool bar
    QMenuBar* myBar = new QMenuBar(this);

        QMenu* menuFile = new QMenu("File", this);
        myBar->addMenu(menuFile);

            QAction* actNew = new QAction("New", this);
            menuFile->addAction(actNew);
            connect(actNew, &QAction::triggered, this, &Widget::newSlot);
            connect(this, &Widget::sendIsDebuggerOff, actNew, &QAction::setEnabled);

            QAction* actOpen = new QAction("Open", this);
            menuFile->addAction(actOpen);
            connect(actOpen, &QAction::triggered, this, &Widget::openSlot);
            connect(this, &Widget::sendIsDebuggerOff, actOpen, &QAction::setEnabled);

            QAction* actSave = new QAction("Save", this);
            menuFile->addAction(actSave);
            connect(actSave, &QAction::triggered, this, &Widget::saveSlot);
            connect(this, &Widget::sendIsDebuggerOff, actSave, &QAction::setEnabled);

            QAction* actSaveAs = new QAction("Save As", this);
            menuFile->addAction(actSaveAs);
            connect(actSaveAs, &QAction::triggered, this, &Widget::saveAsSlot);
            connect(this, &Widget::sendIsDebuggerOff, actSaveAs, &QAction::setEnabled);

            QAction* actClose = new QAction("Close", this);
            menuFile->addAction(actClose);
            connect(actClose, &QAction::triggered, this, &Widget::closeSlot);
            connect(this, &Widget::sendIsDebuggerOff, actClose, &QAction::setEnabled);


        QMenu* menuEdit = new QMenu("Edit", myBar);
        myBar->addMenu(menuEdit);

            QAction* actUndo = new QAction("Undo", this);
            menuEdit->addAction(actUndo);
            connect(actUndo, &QAction::triggered, this->m_myEditor, &MyTextEditor::undo);
            connect(this, &Widget::sendIsDebuggerOff, actUndo, &QAction::setEnabled);

            QAction* actRedo = new QAction("Redo", this);
            menuEdit->addAction(actRedo);
            connect(actRedo, &QAction::triggered, this->m_myEditor, &MyTextEditor::redo);
            connect(this, &Widget::sendIsDebuggerOff, actRedo, &QAction::setEnabled);


        QMenu* menuDebug = new QMenu("Debug", myBar);
        myBar->addMenu(menuDebug);

            QAction* actDebug = new QAction("Debug", this);
            menuDebug->addAction(actDebug);
            connect(actDebug, &QAction::triggered, this, &Widget::debugSlot);
            connect(this, &Widget::sendIsDebuggerOff, actDebug, &QAction::setEnabled);
            connect(this, &Widget::sendIsDebuggerOn, actDebug, &QAction::setEnabled);

            QAction* actDNext = new QAction("Next", this);
            menuDebug->addAction(actDNext);
            actDNext->QAction::setEnabled(0);
            connect(actDNext, &QAction::triggered, this, &Widget::dNextSlot);
            connect(this, &Widget::sendIsDebuggerOn, actDNext, &QAction::setEnabled);

            QAction* actDPre = new QAction("Previous", this);
            menuDebug->addAction(actDPre);
            actDPre->QAction::setEnabled(0);
            connect(actDPre, &QAction::triggered, this, &Widget::dPreSlot);
            connect(this, &Widget::sendIsDebuggerOn, actDPre, &QAction::setEnabled);

            QAction* actDJump = new QAction("Jump to...", this);
            menuDebug->addAction(actDJump);
            actDJump->QAction::setEnabled(0);
            connect(actDJump, &QAction::triggered, this, &Widget::dJumpSlot);
            connect(this, &Widget::sendIsDebuggerOn, actDJump, &QAction::setEnabled);

            QAction* actDTmn = new QAction("Terminate", this);
            menuDebug->addAction(actDTmn);
            actDTmn->QAction::setEnabled(0);
            connect(actDTmn, &QAction::triggered, this, &Widget::dTmnSlot);
            connect(this, &Widget::sendIsDebuggerOn, actDTmn, &QAction::setEnabled);

        QMenu* menuCompile = new QMenu("Compile", myBar);
        myBar->addMenu(menuCompile);

            QAction* actCompile = new QAction("Compile", this);
            menuCompile->addAction(actCompile);
            // connect(actCompile, &QAction::triggered, this, &Widget::compileSlot);
            connect(this, &Widget::sendIsDebuggerOff, actCompile, &QAction::setEnabled);

            QAction* actRun = new QAction("Run", this);
            menuCompile->addAction(actRun);
            // connect(actRun, &QAction::triggered, this, &Widget::runSlot);
            connect(this, &Widget::sendIsDebuggerOff, actRun, &QAction::setEnabled);


    QPushButton* btnRefresh = new QPushButton("Refresh", this);
    btnRefresh->move(450, 0);

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

}




//ACTION SLOTS


//MENU :File
//actNew 新建文件
void Widget::newSlot()
{
    // if (this->m_isDebuggerOn == 1) {
    //     qDebug() << "not available: debugger on";
    //     return;
    // }

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

    // if (m_isDebuggerOn == 1) {
    //     qDebug() << "debugger restart";
    //     this->m_myTerminal->clear();
    //     this->m_myTerminal->setPlainText(this->m_cFilePath);
    // }
    // this->m_isDebuggerOn = 1;
    emit sendIsDebuggerOn(1);
    emit sendIsDebuggerOff(0);

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
    // if (m_isDebuggerOn == 0) {
    //     qDebug() << "invalid \"next\" action";
    //     return;
    // }

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
void Widget::recvLineNumJump(int a)
{
    bool isJumpSuccess = this->m_myDebugger->jump(a);
    if (isJumpSuccess) {
        this->updateDebuggerInfo();
    }
    else {
        this->m_myTerminal->append("invalid jump");
    }
}

void Widget::dJumpSlot()
{
    this->m_myEditor->setReadOnly(1);

    DJumpWindow* dJumpWin = new DJumpWindow(this);
    connect(dJumpWin, &DJumpWindow::sendLineNum, this, &Widget::recvLineNumJump);
    qDebug() << "after connect DJumpWin";
    dJumpWin->exec();
    qDebug() << "after exec DJumpWin";
}


//actDTmn
void Widget::dTmnSlot()
{
    // if (m_isDebuggerOn == 0) {
    //     qDebug() << "invalid \"Terminate\" action";
    //     return;
    // }

    this->m_myDebugger->User::~User();
    this->m_myDebugger = NULL;
    if (this->m_myDebugger == NULL) {
        qDebug() << "clear debugger success";
    }
    this->m_myTerminal->clear();
    this->m_myTerminal->setPlainText(this->m_cFilePath);

    // this->m_isDebuggerOn = 0;
    emit sendIsDebuggerOn(0);
    emit sendIsDebuggerOff(1);
    qDebug() << "debugger off";
    this->m_myEditor->setReadOnly(0);
}




// Menu: Compile
// actCompile
void Widget::compileSlot()
{
    if (this->m_exePath.isEmpty()) {
        // prompt用户选择生成可执行文件的路径
        QString fileName = QFileDialog::getSaveFileName(
            this,
            "choose a path for executable",
            QCoreApplication::applicationFilePath());

        if (fileName.isEmpty()) {return;}
        else {
            qDebug() << "create executable in: " << fileName;
            this->m_exePath = fileName;

            // call compiler
            ////////////////
        }
    }
    else {
        // call compiler
        ////////////////
    }
}
void Widget::runSlot() {}


//DECONSTRUCTOR
Widget::~Widget()
{
    this->closeSlot();
}



