#ifndef BOARDOBJECT_H
#define BOARDOBJECT_H

#include <QLabel>
#include <QMouseEvent>

enum ObjectState
{
    blank = 0,
    X = 1,
    O = 2,
    gameover = 3
};

class BoardObject : public QLabel
{
    Q_OBJECT
public:
    BoardObject(QWidget *parent = nullptr);
    void makeX();
    void makeO();
    ObjectState state();

private:
    ObjectState objectState;
    ObjectState nextstate;
    void mousePressEvent(QMouseEvent*) override;

signals:
    void iwaschanged(ObjectState);

private slots:
    void clear();
    void makeGameOver();
    void nextState(ObjectState);

};

#endif // BOARDOBJECT_H
