
#include "mytexteditor.h"
#include "Lexical/Lexical.h"
#include <string>
#include <QTextCursor>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>

MyTextEditor::MyTextEditor(QWidget *parent)
    : QTextEdit(parent)
{
    this->resize(800, 350);
    this->move(50, 50);

    std::deque<QString> undoDeque{};
    this->m_undoDeque = undoDeque;
    std::deque<QString> redoDeque{};
    this->m_redoDeque = redoDeque;

    // 输入文本 -> 触发refreshTextEditor
    connect(this, &QTextEdit::textChanged, this, &MyTextEditor::refreshEditor);


}



// 堆撤回
void MyTextEditor::pushUndo(QString qstr)
{
    if (this->m_undoDeque.size() == this->m_undoTimes) {
        this->m_undoDeque.pop_front();
        this->m_undoDeque.push_back(qstr);
        return;
    }   // 控制容量

    this->m_undoDeque.push_back(qstr);
}



// 堆重做
void MyTextEditor::pushRedo(QString qstr)
{
    if (this->m_redoDeque.size() == this->m_undoTimes) {
        this->m_redoDeque.pop_front();
        this->m_redoDeque.push_back(qstr);
        return;
    }   // 控制容量

    this->m_redoDeque.push_back(qstr);
}



// 撤回
void MyTextEditor::undo()
{
    this->QTextEdit::setReadOnly(1);
    this->m_isUndoRedoWork = 1;

    if (!this->m_undoDeque.empty()) {
        // qDebug() << "undo start";

        // 堆重做：当前文本
        this->pushRedo(this->QTextEdit::toPlainText());

        // 展示：撤回后的文本
        this->QTextEdit::setPlainText(this->m_undoDeque.back());

        // 回溯
        this->m_undoDeque.pop_back();

        // qDebug() << "undo end" << "\n";
    }

    this->m_isUndoRedoWork = 0;
    this->QTextEdit::setReadOnly(0);
}



// 重做
void MyTextEditor::redo()
{
    this->QTextEdit::setReadOnly(1);
    this->m_isUndoRedoWork = 1;

    if (!this->m_redoDeque.empty()) {
        // qDebug() << "redo start";

        // 堆撤回：当前文本
        this->pushUndo(this->QTextEdit::toPlainText());

        // 展示：重做后的文本
        this->QTextEdit::setPlainText(this->m_redoDeque.back());

        // 回溯
        this->m_redoDeque.pop_back();

        // qDebug() << "redo end" << "\n";
    }

    this->m_isUndoRedoWork = 0;
    this->QTextEdit::setReadOnly(0);
}



// 清空
void MyTextEditor::editorClear()
{
    this->clear();
    this->m_undoDeque.clear();
    this->m_redoDeque.clear();
}




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
    qDebug() << "new text: " << newText << "\n";
    // newText.append("->HelloWorld");  // test
    // qDebug() << "after get";    // test
    // qDebug() << newText;    // test
    // newText.append("->HelloWorld"); // test

    // 若用户改变内容
    if (this->m_undoDeque.empty() || newText != this->m_cText){
        // this->QTextEdit::clear();

        // qDebug() << "before reset undo/redo";  // test
        // qDebug() << "old text: " << this->m_cText;

        if (!this->m_isUndoRedoWork) {
            this->pushUndo(this->m_cText);    // 更新undoDeque
            this->m_redoDeque.clear();  // 清空redoDeque
        }

        this->m_cText = newText;
        // qDebug() << "new text: " << this->m_cText;
        // qDebug() << "after reset undo/redo";   // test

        // HIGHLIGHTING
        if (this->m_isHLon)
            {
            qDebug() << "Highlight";
            QString tempPath = QCoreApplication::applicationDirPath();
                tempPath.append("\\tempFile.cpp");
                QFile tempFile(tempPath);
                tempFile.open(QIODeviceBase::WriteOnly);
                QTextStream out(&tempFile);
                out << newText;
                tempFile.close();

                string strText = HL::highlightHTML(tempPath.QString::toStdString());   // 转换为string (html form)
                newText = QString::fromStdString(strText);
                qDebug() << "new text html: " << newText << "\n";
            }

        // // debug highlighting
        // QString testPath = QCoreApplication::applicationDirPath();
        // testPath.append("\\testFile.cpp");
        // QFile testFile(testPath);
        // testFile.open(QIODeviceBase::WriteOnly);
        // QTextStream testOutput(&testFile);
        // testOutput << newText;
        // testFile.close();

        // qDebug() << "html printed on the editor: " << this->toHtml() << "\n";
        // qDebug() << "plain text printed on the editor: " << this->toPlainText() << "\n";

        // 记录光标位置
        QTextCursor cursor = this->textCursor();
        int cursorPos = cursor.position();
        // qDebug() << "current cursor position: " << cursorPos;

        // 展示更新后的文本
        // qDebug() << "before set";   // test
        // this->QTextEdit::setHtml(newText);
        this->QTextEdit::setText(newText);
        // qDebug() << "after set";    // test
        // qDebug() << "new text: " << newText;    // test

        // 还原光标位置
        cursor.setPosition(cursorPos);
        this->setTextCursor(cursor);
        // qDebug() << "reset cursor: " << this->textCursor().position();
    }

    // 若没有改变内容则跳过 -> 跳出setPlainText函数引发的循环
    else {
        // qDebug() << ":no change";   // test
    }

    this->QTextEdit::setReadOnly(0);


    // newText.QString::toStdString();
    // std::string strType = typeid(newText).name();
    // QString typeName = QString::fromStdString(strType);
    // qDebug() << typeName;
}



void MyTextEditor::switchHL()
{
    if (this->m_isHLon == 0) {
        this->m_isHLon = 1;
    } else {
        this->m_isHLon = 0;
    }
    qDebug() << this->m_isHLon;
}



MyTextEditor::~MyTextEditor() {}
