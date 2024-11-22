#include "djumpwindow.h"
#include <QLabel>
#include <QPushButton>
#include <string>
#include <string.h>


DJumpWindow::DJumpWindow(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("Jump to Specific Line");
    this->setFixedSize(200, 100);
    this->m_parent = parent;

    QLabel* promptLabel = new QLabel(this);
    promptLabel->setText("Jump to line: ");
    promptLabel->move(50, 20);

    QLineEdit* inputLine = new QLineEdit(this);
    inputLine->resize(40, 20);
    inputLine->move(100, 20);
    this->m_inputLine = inputLine;

    QPushButton* btnConfirm = new QPushButton(this);
    btnConfirm->move(80, 80);
    // connect(btnConfirm, &QPushButton::pressed, this, &DJumpWindow::getInput);
    QPushButton* btnCancel = new QPushButton(this);
    btnCancel->move(140, 80);


    QTextBrowser* infoBrowser = new QTextBrowser(this);
    infoBrowser->resize(160, 20);
    infoBrowser->move(20, 50);
    infoBrowser->setPlainText("Please input a line number to jump to.");
    this->m_infoBrowser = infoBrowser;

    this->hide();

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

}
