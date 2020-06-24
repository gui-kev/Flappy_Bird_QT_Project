#ifndef BIRD_H
#define BIRD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Bird : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)

public:
    explicit Bird(QPixmap img);
    qreal rotation() const;
    qreal y() const;
    void upBird(); // pour déplacer l'oiseau lorsqu'on tape la barre d'espacement
    void stopBird();

signals:

public slots:
    void setRotation(qreal rotation);
    void setY(qreal y);
    void rotation(const qreal end, const int duration, const QEasingCurve& curve);
    void afterUpBird();   //permet de faire en sorte que l'oiseau ne reste pas vers le haut après un upBird()

private :
    enum position_aile{
        Up,
        Middle,
        Down,
    };
    position_aile position_aile;
    bool direction_aile; // 1:up, 0:down
    void newImg(); //positionne une nouvelle image à la fin d'un timer

    qreal m_y;
    qreal m_rotation;
    QPropertyAnimation *m_y_animation; //déplace la position y pour matérialiser la chute de l'oiseau
    QPropertyAnimation *m_rotation_animation;  //modifie l'angle de l'oiseau pour matérialiser la chute
    qreal y_max;
};

#endif // BIRD_H
