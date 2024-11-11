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


    //声明属性 undoQueue <- 记录文本区历史记录
    Q_PROPERTY(std::queue<std::string>* undoQueue MEMBER m_undoQueue READ undoQueue WRITE setUndoQueue NOTIFY undoUpdated)

    // READ FUNCTION for undoQueue
    std::queue<std::string>* undoQueue();
    std::string undoLast();


    // READ FUNCTION for m_undoTimes
    int undoTimes();


signals:
    // SIGNAL FUNCTION for undoQueue
    void undoUpdated(std::queue<std::string>* updatedUndoQueue);


public slots:
    // WRITE FUNCTION for undoQueue
    void setUndoQueue(std::queue<std::string>* newUndoQueue);
    void pushToUndo(std::string newText);


    // WRITE FUNCTION for private m_undoTimes
    void setUndoTimes(int newTimes = 5);


    // 更新文本区状态的槽函数
    void updateTextEditor();

    // void checkTextChanged();


private:
    // MEMBER VARIABLE for undoQueue
    std::queue<std::string>* m_undoQueue;

    // 撤回次数
    int m_undoTimes = 5;
};

#endif // MYTEXTEDITOR_H
