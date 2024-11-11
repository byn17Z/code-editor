
#include "mytexteditor.h"
#include <string>
#include <iostream>

MyTextEditor::MyTextEditor(QWidget *parent)
    :QTextEdit(parent)
{
    this->resize(800, 350);
    this->move(50, 50);


    std::queue<std::string> myUndoQueue;
    this->m_undoQueue = & myUndoQueue;

    // 输入文本 -> 触发slot: updateTextEditor
    // connect(this, &QTextEdit::textChanged, this, &myTextEditor::updateTextEditor);


}




// READ FUNCTION for private m_undoTimes
int MyTextEditor::undoTimes() {
    return this->m_undoTimes;
}

// WRITE FUNCTION for private m_undoTimes
void MyTextEditor::setUndoTimes(int newTimes) {
    this->m_undoTimes = newTimes;
}




// READ FUNCTION for undoQueue
std::queue<std::string>* MyTextEditor::undoQueue() {
    return this->m_undoQueue;
}

std::string MyTextEditor::undoLast() {
    return this->m_undoQueue->back();
}


// WRITE FUNCTION for undoQueue
void MyTextEditor::setUndoQueue(std::queue<std::string>* newUndoQueue) {
    this->m_undoQueue = newUndoQueue;
}

void MyTextEditor::pushToUndo(std::string newText) {
    std::queue<std::string>* myQueue = this->m_undoQueue;
    myQueue->push(newText);
    if (myQueue->size() > this->m_undoTimes) {
        myQueue->pop();
    }
}


// SIGNAL FUNCTION for undoQueue
// void myTextEditor::undoUpdated(std::queue<std::string>* updatedUndoQueue) {}




// 更新文本区状态的槽函数
// 用户每次输入文本时 触发槽函数slot: updateTextEditor以：
// 1、用QTextEdit::toHtml记录当前文本并更新至newText (O)
// 2、保存newText至undoStack
// 3、将qstrText转换为c++string (O)，处理（词法分析，高亮），生成html并储存至qstrHtml
// 4、用QTextEdit::setHtml更新展示文本
// !!!issues!!!
void MyTextEditor::updateTextEditor() {
    QString newText = this->QTextEdit::toPlainText();
    std::string strText = newText.QString::toStdString();
    this->QTextEdit::clear();
    // std::cout << strText;
    // this->QTextEdit::setHtml(newText);

    // if (strText == this->undoLast()) {return;}
    // else {
    //     // this->MyTextEditor::pushToUndo(strText);
    //     this->QTextEdit::clear();
    //     // this->QTextEdit::setPlainText(newText);
    // }
}


// void myTextEditor::checkTextChanged() {
//     std::cout << "text changed\n";
// }

MyTextEditor::~MyTextEditor() {}
