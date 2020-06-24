#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    best_score(0),score(0)
{
    setColonne();
}

void Scene::addBird()
{
    //ajout de l'oiseau
    flappy = new Bird(QPixmap(":/images/flappy_middle.png"));
    addItem(flappy);
}

void Scene::addButton()
{
    //ajout des boutons à la scene
    start_game = new Button("START GAME");
    start_game->setPos(-100,350);
    addItem(start_game);
}

void Scene::incrementeScore()
{
    score++;
    if(score > best_score)
        best_score = score;
    qDebug()<< "Score : " << score << " Best Score : " << best_score;
}

void Scene::setColonne()
{
    time_colonne = new QTimer(this);
    //pour créer un nouveau pillier une fois le timer écoulé
    connect(time_colonne, &QTimer::timeout,[=](){
        Colonne *colonne = new Colonne();
        addItem(colonne);

        connect(colonne,&Colonne::collision,[=](){
            time_colonne->stop();
            stopGame();
        });
    });

    //pour lancer le timer
    time_colonne->start(1000); //permet d'ajouter une colonne chaque 1s
}

void Scene::stopGame()
{
    //Arrêt de l'oiseau
    flappy->stopBird();

    //Arrêt des colonnes
    QList<QGraphicsItem *> sceneItems = items();
    foreach(QGraphicsItem *item, sceneItems){
        Colonne *colonne = dynamic_cast<Colonne *>(item);
        if(colonne){
            colonne->stopColonne();
            showGameOver();
        }
    }
}

// Affiche le Game Over et le score final
void Scene::showGameOver()
{
    game_over_item = new QGraphicsPixmapItem(QPixmap(":/images/game_over.png"));
    addItem(game_over_item);
    game_over_item->setPos(QPointF(0,0)- QPointF(game_over_item->boundingRect().width()/2,
                                                 game_over_item->boundingRect().height()/2));
    score_item = new QGraphicsTextItem();
    QString htmlstr = "<p> Score : " + QString::number(score) + "<p>"
                + "<p> Best Score : " + QString::number(best_score) + "<p>";
    QFont font("Segoe UI", 30, QFont::Bold);
    score_item->setHtml(htmlstr);
    score_item->setFont(font);
    score_item->setDefaultTextColor(Qt::red);
    addItem(score_item);
    score_item->setPos(QPointF(0,0)- QPointF(180,-130));
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Space){
        flappy->upBird();
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        flappy->upBird();
    }
    QGraphicsScene::mousePressEvent(event);
}
