#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextBrowser>
#include "mytexteditor.h"
#include "mydebugger.h"
#include "djumpwindow.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    // //QPROPEERTY myEditor
    // Q_PROPERTY(MyTextEditor* myEditor MEMBER m_myEditor READ myEditor WRITE setEditor NOTIFY myEditorChanged)

    // //QPROPEERTY cFilePath
    // Q_PROPERTY(QString cFilePath MEMBER m_cFilePath READ cFilePath WRITE setcFilePath NOTIFY cFilePathChanged)

    // //QPROPEERTY cFilePath
    // Q_PROPERTY(QString isCFileSaved MEMBER m_isCFileSaved READ isCFileSaved WRITE setisCFileSaved NOTIFY isCFileSavedChanged)


    // //READ - myEditor
    // MyTextEditor* myEditor();

    // //READ - cFilePath
    // QString cFilePath();

    // //READ - isCFileSaved
    // bool isCFileSaved();

    // READ - myDebugger
    MyDebugger* myDebugger();


public slots:

    // //WRITE - myEditor
    // void setEditor(MyTextEditor* textEditor);

    // //WRITE - cFilePath
    // void setcFilePath(QString path);

    // //WRITE - isCFileSaved
    // void setisCFileSaved();


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


signals:

    // //SIGNAL - myEditor
    // void myEditorChanged();

    // //SIGNAL - cFilePath
    // void cFilePathChanged();

    // //SIGNAL - isCFileSaved
    // void isCFileSavedChanged();

private:

    MyTextEditor* m_myEditor;

    QTextBrowser* m_myTerminal;

    MyDebugger* m_myDebugger = NULL;

    // DJumpWindow* m_dJumpWin;

    bool m_isDebuggerOn = 0;

    QString m_cFilePath = "";

    bool m_saveSuccess = 1;

    // bool m_isCFileSaved = 1;

};

#endif // WIDGET_H
