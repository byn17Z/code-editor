
#include "mytexteditor.h"
#include <string>

MyTextEditor::MyTextEditor(QWidget *parent)
    : QTextEdit(parent)
{
    this->resize(800, 350);
    this->move(50, 50);



    this->m_undoQueue.push("");

    // 输入文本 -> 触发slot: updateTextEditor
    connect(this, &QTextEdit::textChanged, this, &MyTextEditor::refreshEditor);


}




// // READ FUNCTION for private m_undoTimes
// int MyTextEditor::undoTimes() {
//     return this->m_undoTimes;
// }

// // WRITE FUNCTION for private m_undoTimes
// void MyTextEditor::setUndoTimes(int newTimes) {
//     this->m_undoTimes = newTimes;
// }




// 更新文本区状态的槽函数
// 用户每次输入文本时 触发槽函数slot: refreshEditor以：
// 1、用QTextEdit::toPlainText记录当前文本并更新至newText (o)
// 2、将newText转换为c++string strText, 保存strText至undoQueue (o)
// 3、处理strText（词法分析，高亮），生成strHtml，转换为newHtml (!)
// 4、用QTextEdit::setHtml更新展示文本 (o)
void MyTextEditor::refreshEditor()
{
    this->QTextEdit::setReadOnly(1);

    // qDebug() << "before get";   // test
    QString newText = this->QTextEdit::toPlainText();
    // newText.append("->HelloWorld");  // test
    // qDebug() << "after get";    // test
    // qDebug() << newText;    // test
    // newText.append("->HelloWorld"); // test


    // 若没有改变内容则跳过 -> 跳出setPlainText函数引发的循环
    if (newText == this->m_undoQueue.back()) {
        // qDebug() << ":no change";   // test
    }
    // 若用户改变内容
    else{
        // this->QTextEdit::clear();

        // 更新undoQueue
        // qDebug() << "before push";  // test
        this->m_undoQueue.push(newText);
        // qDebug() << "after push";   // test
        if (this->m_undoQueue.size() > this->m_undoTimes) {
            this->m_undoQueue.pop();
        }   // 控制undoQueue容量

        std::string strText = newText.QString::toStdString();   // 转换为string供lexer/debugger使用

        // 展示更新后的文本
        // qDebug() << "before set";   // test
        this->QTextEdit::setPlainText(newText);
        // qDebug() << "after set";    // test
        // qDebug() << newText;    // test
    }

    this->QTextEdit::setReadOnly(0);


    // newText.QString::toStdString();
    // std::string strType = typeid(newText).name();
    // QString typeName = QString::fromStdString(strType);
    // qDebug() << typeName;
}




MyTextEditor::~MyTextEditor() {}
