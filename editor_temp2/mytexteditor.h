#ifndef MYTEXTEDITOR_H
#define MYTEXTEDITOR_H

#include <QObject>
#include <QWidget>
#include <QTextEdit>
#include <queue>
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

    void refreshEditor();




private:
    // MEMBER VARIABLE for undoQueue
    std::queue<QString> m_undoQueue;

    // 撤回次数
    int m_undoTimes = 5;
};

#endif // MYTEXTEDITOR_H
