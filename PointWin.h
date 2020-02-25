#ifndef POINTWIN_H
#define POINTWIN_H

#include <QWidget>
#include <QtGui>


namespace Ui {
class PointWin;
}

class PointWin : public QWidget
{
    Q_OBJECT

public:
    explicit PointWin(QWidget *parent = 0);
    ~PointWin();

protected:
    //将matlab窗口设置为随着窗口变化而变化
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    Ui::PointWin *ui;

};

#endif // POINTWIN_H
