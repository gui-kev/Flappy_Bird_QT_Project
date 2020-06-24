#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsSimpleTextItem>
#include <QGraphicsScene>
#include <QTimer>
#include "colonne.h"
#include "bird.h"
#include "button.h"

class Scene : public QGraphicsScene //pour créer la scene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void addBird();
    void addButton();
    void incrementeScore();
    Button *start_game;
    int best_score;

    void setScore(int value);

signals:

private:
    void setColonne(); //pour l'ajout des colonnes
    void stopGame();  //pour l'arrêt du jeu
    void showGameOver();

    QTimer *time_colonne;
    Bird *flappy;
    int score;

    QGraphicsPixmapItem * game_over_item;
    QGraphicsTextItem * score_item;


protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENE_H
