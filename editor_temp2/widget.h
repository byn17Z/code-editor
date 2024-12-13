#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextBrowser>
#include "mytexteditor.h"
#include "mydebugger.h"
#include "djumpwindow.h"
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
#include <QProcess>
#include <QFlags>
#include <QProcess>
#include <QFile>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    MyDebugger* myDebugger();


public slots:

    //ACTION SLOTS
    // menu: file
    void newSlot();
    void openSlot();
    void saveSlot();
    void saveAsSlot();
    void closeSlot();

    // menu: debug
    void updateDebuggerInfo();
    void debugSlot();
    void dNextSlot();
    void dPreSlot();
    void recvLineNumJump(int a);
    void dJumpSlot();
    void dTmnSlot();

    // menu: compile
    void compileSlot();
    void runSlot();


signals:
    void sendIsDebuggerOn(bool);
    void sendIsDebuggerOff(bool);
    void sendIsCompiled(bool);
    void sendStatus(const QString&, int);

private:

    MyTextEditor* m_myEditor;

    QTextBrowser* m_myTerminal;

    MyDebugger* m_myDebugger = NULL;

    // bool m_isDebuggerOn = 0;

    QString m_cFilePath = "";

    bool m_saveSuccess = 1;

    QString m_exePath = "";

};

#endif // WIDGET_H
