#ifndef COLONNE_H
#define COLONNE_H

#include <QObject>
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Colonne :
        public QObject, public QGraphicsItemGroup //permet de traiter un groupe d'éléments
                                                  //comme un seul élément
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)

public:
    explicit Colonne();
    ~Colonne();

    qreal x() const;
    void stopColonne();

signals:
    void collision();

public slots:

    void setX(qreal x);

private:
    QGraphicsPixmapItem *colonne_haut;
    QGraphicsPixmapItem *colonne_bas;
    QPropertyAnimation *x_animation;

    qreal m_x;
    int rand_posy;
    bool collisionbird();
    bool pass_bird;
};

#endif // COLONNE_H
