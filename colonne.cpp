#include "colonne.h"
#include "bird.h"
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QDebug>
#include "scene.h"

Colonne::Colonne(): pass_bird(false)
{
    colonne_bas = new QGraphicsPixmapItem(QPixmap(":/images/colonne.png"));
    colonne_haut = new QGraphicsPixmapItem(QPixmap(":/images/colonne.png"));

    //pour positionner et centrer les colonnes sur la scène
    colonne_bas->setPos(QPointF(0,0)+ QPointF(colonne_bas->boundingRect().width()/2, 60));
    colonne_haut->setPos(QPointF(0,0)- QPointF(colonne_haut->boundingRect().width()/2,
                                               colonne_haut->boundingRect().height()+180));

    addToGroup(colonne_bas);
    addToGroup(colonne_haut);

    //générer un début aléatoire pour le pillier
    int rand_posX = QRandomGenerator::global()->bounded(150);
    rand_posy = QRandomGenerator::global()->bounded(150);

    setPos(QPoint(0,0)+QPoint(260+rand_posX, rand_posy));

    //propriété de l'animation
    x_animation = new QPropertyAnimation(this,"x",this);
    x_animation->setStartValue(260+rand_posX);
    x_animation->setEndValue(-260);
    x_animation->setEasingCurve(QEasingCurve::Linear);  //permet de rendre les transitions plus naturelles
    x_animation->setDuration(2000);

    //pour effacer la colonne une fois l'animation terminer
    connect(x_animation,&QPropertyAnimation::finished,[=](){
        qDebug() <<"Animation terminée";
        scene()->removeItem(this);
        delete this;
    });

    x_animation->start();
}

Colonne::~Colonne()
{
 qDebug() <<"Colonne effacée";
}

qreal Colonne::x() const
{
    return m_x;
}

void Colonne::stopColonne()
{
    x_animation->stop();
}


void Colonne::setX(qreal x)
{
    m_x = x;

    //incrémenter le score pour chaque pillier traversé par l'oiseau
    if(x<0 && !pass_bird){
        pass_bird = true;
        QGraphicsScene *m_scene = scene();
        Scene *my_scene = dynamic_cast<Scene * >(m_scene);
        if(my_scene){
            my_scene->incrementeScore();
        }
    }


    if(collisionbird()){
        emit collision();
    }
    setPos(QPoint(0,0)+QPointF(x,rand_posy));
}

//pour détecter les collision entre l'oiseau et une colonne
bool Colonne::collisionbird()
{
    QList<QGraphicsItem*> collidingItems = colonne_haut->collidingItems();
    collidingItems.append(colonne_bas->collidingItems());
    foreach (QGraphicsItem * item, collidingItems) {
        Bird *birdItem = dynamic_cast<Bird*>(item);
        if(birdItem){
            return true;
        }
    }
    return false;
}
