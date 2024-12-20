#ifndef MYTEXTEDITOR_H
#define MYTEXTEDITOR_H

#include <QObject>
#include <QWidget>
#include <QTextEdit>
#include <queue>
#include <deque>
#include <string>

// 用户每次输入文本时 触发槽函数slot: updateTextEditor以：
// 1、保存qMyText至undoStack
// 2、用QTextEdit::toHtml记录当前文本并更新至qMyText
// 3、将qMyText转换为c++string，处理（词法分析，高亮），生成html并储存至qstrHtml
// 4、用QTextEdit::setHtml更新展示文本

class MyTextEditor: public QTextEdit
{
    Q_OBJECT
public:
    MyTextEditor(QWidget *parent = nullptr);
    ~MyTextEditor();




public slots:
    void pushUndo(QString qstr);
    void undo();

    void pushRedo(QString qstr);
    void redo();

    void editorClear();

    void switchHL();

    void refreshEditor();




private:
    std::deque<QString> m_undoDeque;
    std::deque<QString> m_redoDeque;

    QString m_cText = "";

    bool m_isUndoRedoWork = 0;

    // 撤回次数
    int m_undoTimes = 5;

    // 高亮功能
    bool m_isHLon = 0;
};

#endif // MYTEXTEDITOR_H
