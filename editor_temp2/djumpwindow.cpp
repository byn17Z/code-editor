#include "djumpwindow.h"
#include <QLabel>
#include <QPushButton>
#include <string>
#include <string.h>


DJumpWindow::DJumpWindow(QWidget *parent)
    : QDialog(parent)
{
    this->setWindowTitle("Jump to Specific Line");
    this->setFixedSize(400, 200);

    QLabel* promptLabel = new QLabel(this);
    promptLabel->setText("Jump to line: ");
    promptLabel->move(100, 40);

    QLineEdit* inputLine = new QLineEdit(this);
    inputLine->resize(80, 40);
    inputLine->move(200, 40);
    this->m_inputLine = inputLine;

    QPushButton* btnConfirm = new QPushButton("Confirm", this);
    btnConfirm->move(70, 160);
    connect(btnConfirm, &QPushButton::pressed, this, &DJumpWindow::getInput);

    QPushButton* btnCancel = new QPushButton("Cancel", this);
    btnCancel->move(270, 160);
    connect(btnCancel, &QPushButton::pressed, this, &DJumpWindow::cancelWindow);


    QTextBrowser* infoBrowser = new QTextBrowser(this);
    infoBrowser->resize(320, 40);
    infoBrowser->move(40, 100);
    infoBrowser->setPlainText("Please input a line number to jump to.");
    this->m_infoBrowser = infoBrowser;

    // this->hide();

}


DJumpWindow::~DJumpWindow() {}


void DJumpWindow::getInput()
{
    const char* userInput = this->m_inputLine->text().toStdString().c_str();
    for (int i = 0; i < std::strlen(userInput); i++) {
        if (! std::isdigit(userInput[i])) {
            this->m_infoBrowser->setPlainText("Invalid input. Please input an integer!");
            this->m_inputLine->clear();
            return;
        }
    }
    int lineNum = std::atoi(userInput);
    // 发一个信号（传递lineNum）
    emit sendLineNum(lineNum);
    this->~DJumpWindow();

}


void DJumpWindow::cancelWindow()
{
    this->~DJumpWindow();
}
