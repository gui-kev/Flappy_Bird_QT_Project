#include "bird.h"
#include <QTimer>
#include<QGraphicsScene>

Bird::Bird(QPixmap img) :
    position_aile(position_aile::Middle),
    direction_aile(0)
{
    setPixmap(img);
    QTimer * aile_timer = new QTimer(this);
    /*chaque 80ms, afficher la nouvelle image de l'oiseau
      grace à la connection du timer à la méthode newImg)*/
    connect(aile_timer,&QTimer::timeout,[=](){
        newImg();
    });
    aile_timer->start(80);

    //déplacement de la position y de l'oiseau vers le bas
    y_max = scenePos().y()+375;
    m_y_animation = new QPropertyAnimation(this,"y",this);
    m_y_animation->setStartValue(scenePos().y()); //position initiale de l'oiseau
    m_y_animation->setEndValue(y_max);
    m_y_animation->setEasingCurve(QEasingCurve::InQuad);
    m_y_animation->setDuration(1500);
    m_y_animation->start();

    //rotation de l'oiseau
    m_rotation_animation = new QPropertyAnimation(this,"rotation",this);
    rotation(90,10000, QEasingCurve::InQuad);
}


qreal Bird::rotation() const
{
    return m_rotation;
}

qreal Bird::y() const
{
    return m_y;
}

void Bird::upBird()
{
    m_y_animation->stop();
    m_rotation_animation->stop();
    qreal bird_pos_y = y();
    m_y_animation->setStartValue(bird_pos_y);
    m_y_animation->setEndValue(bird_pos_y-scene()->sceneRect().height()/15);
    m_y_animation->setDuration(285);

    //une fois l'animation terminée, y reprend l'animation initiale
    connect(m_y_animation, &QPropertyAnimation::finished,[=](){
        afterUpBird();
    });

    m_y_animation->start();
    rotation(-20,200,QEasingCurve::OutCubic);
}

void Bird::stopBird()
{
   m_y_animation->stop();
   m_rotation_animation->stop();
}

void Bird::setRotation(qreal rotation)
{
    m_rotation = rotation;
    QPointF c = boundingRect().center();
    QTransform t;
    t.translate(c.x(), c.y());
    t.rotate(rotation);
    t.translate(-c.x(), -c.y());
    setTransform(t);
}

void Bird::setY(qreal y)
{
    moveBy(0,y-m_y);
    m_y = y;
}

void Bird::rotation(const qreal end, const int duration, const QEasingCurve &curve)
{
    m_rotation_animation->setStartValue(rotation());
    m_rotation_animation->setEndValue(end);
    m_rotation_animation->setEasingCurve(curve);
    m_rotation_animation->setDuration(duration);
    m_rotation_animation->start();
}

void Bird::afterUpBird()
{
    if(y()<y_max){
        /*reinitialiser les animations de la position y et de la rotation
         pour éviter que l'oiseau ne reste vers le haut à cause de upBird*/
        m_rotation_animation->stop();
        m_y_animation->setStartValue(scenePos().y()); //position initiale de l'oiseau
        m_y_animation->setEndValue(y_max);
        m_y_animation->setEasingCurve(QEasingCurve::InQuad);
        m_y_animation->setDuration(2800);
        m_y_animation->start();

        rotation(90,2000, QEasingCurve::InQuad);
    }
}

void Bird::newImg()
{
    if(position_aile == position_aile::Middle){
        if(direction_aile){
            //direction Up vers Down
            setPixmap(QPixmap(":/images/flappy up.png"));
            position_aile = position_aile::Up;
            direction_aile = 0;
        }else{
            //direction Down vers Up
            setPixmap(QPixmap(":/images/flappy_down.png"));
            position_aile = position_aile::Down ;
            direction_aile = 1;
        }

    } else{
        setPixmap(QPixmap(":/images/flappy_middle.png"));
        position_aile = position_aile::Middle;
    }
}
