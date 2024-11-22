#ifndef DJUMPWINDOW_H
#define DJUMPWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QTextBrowser>

class DJumpWindow: public QWidget
{
public:
    DJumpWindow(QWidget *parent = nullptr);
    ~DJumpWindow();


public slots:
    void getInput();
    // void cancelWindow();


private:
    QLineEdit* m_inputLine;
    QTextBrowser* m_infoBrowser;
    QWidget* m_parent;

};

#endif // DJUMPWINDOW_H
