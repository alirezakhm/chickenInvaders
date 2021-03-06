#include "bullet.h"
#include <QGraphicsScene>
#include <QMediaPlayer>
#include "game.h"

extern Game * game;

bullet::bullet(qreal bulletAngel)
{
    setPixmap(QPixmap(":img/bullet.png"));
    speed = 10;
    angle = bulletAngel - 90;
    setRotation(angle);
}

void bullet::advance(int phase)
{
    if(!phase)
        return;

    if(x() > 1200 || y() < 0){
        scene()->removeItem(this);
        delete this;
        return;
    }

    QList<QGraphicsItem *> items = collidingItems();
    for(int i=0 ; i<items.size() ;i++)
    {
        if(typeid(*(items[i])) == typeid(Bird))
        {
            scene()->removeItem(items[i]);
            QVector<Bird *>::Iterator it = game->lvl->birds.begin();

            for(int j=0 ; j<game->lvl->birds.size() ;j++)
            {
                if(game->lvl->birds.at(j) == items[i])
                    game->lvl->birds.erase(it+j);
            }
            QMediaPlayer * death = new QMediaPlayer();
            death->setMedia(QUrl("qrc:sound/chicken.mp3"));
            death->play();

            game->lvl->sc->increase();
            game->lvl->plane->chickensKilled++;
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    //QPointF location = this->pos();
    setPos(mapToParent(0, -speed));
}

