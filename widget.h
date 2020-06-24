#ifndef WIDGET_H
#define WIDGET_H
#define WIDTH_SCENE 650
#define HEIGHT_SCENE 850
#include <QWidget>
#include "scene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void start(); //relance le jeu lorsque l'on clique sur le bouton START GAME

private:
    Ui::Widget *ui;
    Scene* scene;   //création  de la scène
    QGraphicsView *view;
};
#endif // WIDGET_H
