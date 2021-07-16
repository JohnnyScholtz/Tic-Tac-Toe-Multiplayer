#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "boardobject.h"


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    static const int width = 3;
    static const int height = 3;
    BoardObject *board[width][height];
    QLabel *output;
    QLabel *winner;
    QPushButton *newGame;

private slots:
    void objectChanged(ObjectState);
    void clear();

signals:
    void gameOver();
    void nextState(ObjectState);

};
#endif // WIDGET_H
