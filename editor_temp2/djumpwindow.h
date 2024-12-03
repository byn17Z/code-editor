#ifndef DJUMPWINDOW_H
#define DJUMPWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QTextBrowser>

class DJumpWindow: public QDialog
{
    Q_OBJECT

public:
    DJumpWindow(QWidget *parent = nullptr);
    ~DJumpWindow();


public slots:
    void getInput();
    void cancelWindow();


signals:
    void sendLineNum(int a);


private:
    QLineEdit* m_inputLine;
    QTextBrowser* m_infoBrowser;

};

#endif // DJUMPWINDOW_H
