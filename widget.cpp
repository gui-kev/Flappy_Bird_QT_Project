#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>                      // permet d'ajouter les images à notre scène
#include <QGraphicsView>                            //widget pour afficher le contenu
#include "button.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    //création de la scene
    scene = new Scene(this);   //initialisation de la scène
    QGraphicsPixmapItem *ar_plan = new QGraphicsPixmapItem(QPixmap(":/images/nuage.png"));   //pour définir l'arrière-plan de notre jeu
    scene->addItem(ar_plan);    // pour ajouter l'arrière-plan dans la scène
    ar_plan->setPos(QPointF(0,0) - QPointF(ar_plan->boundingRect().width()/2,
                                           ar_plan->boundingRect().height()/2)); // pour centrer l'arrière-plan
    scene->addBird();
    scene->addButton();
    connect(scene->start_game, SIGNAL(clicked()), this, SLOT(start()));

    //Afficher la scene
    view = new QGraphicsView(scene, parent);
    view->setFixedSize(WIDTH_SCENE, HEIGHT_SCENE);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();
    ui->setupUi(view);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::start()
{
    QGraphicsView *view2 = view;
    Scene *scene2 = scene;
    int best_score_backup = scene->best_score;

    //Création d'une nouvelle scène
    scene = new Scene(this);
    scene->best_score = best_score_backup;
    QGraphicsPixmapItem *ar_plan = new QGraphicsPixmapItem(QPixmap(":/images/nuage.png"));
    scene->addItem(ar_plan);    // pour ajouter l'arrière-plan dans la scène
    ar_plan->setPos(QPointF(0,0) - QPointF(ar_plan->boundingRect().width()/2,
                                        ar_plan->boundingRect().height()/2));
    scene->addBird();
    scene->addButton();
    connect(scene->start_game, SIGNAL(clicked()), this, SLOT(start()));
    view = new QGraphicsView(scene);
    view->setFixedSize(WIDTH_SCENE, HEIGHT_SCENE);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();
    ui->setupUi(view);

    //Suppression de l'ancienne scène
    delete view2;
    delete scene2;
}

