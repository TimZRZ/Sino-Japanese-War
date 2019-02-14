#ifndef SELECTMODEL_H
#define SELECTMODEL_H


#include <QWidget>
#include <QToolButton>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QPainter>
#include <QString>
#include <QDir>
#include "GameWidget.h"
#include "warshipButtonWidget.h"
#include "QMenu"
#include "QAction"
#include "QToolBar"
#include "QLabel"
#include "QLabel"
#include "QPixmap"
#include "fstream"
#include "qmessagebox.h"

class selectModel: public QWidget
{
    Q_OBJECT
public:
    explicit selectModel(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    QPushButton *backToMenu;
    GameWidget *enterGame;
    QVector<int> userSelect;
private:

    QLabel *selectModelTitle;
    int smallship = 2;
    int middleship = 5;
    int largeship = 10;
    int total = 0;
    int csmship = 0;
    int csship = 0;
    int cmship = 0;
    int cmnship = 0;
    int clship = 0;
    int country = 0;
    QToolButton *showCredit;
    QToolButton *showFleetTitle;
    QToolButton *showFleet;
    QPushButton *sship;
    QPushButton *smship;
    QPushButton *mship;
    QPushButton *mnship;
    QPushButton *lship;

    QMenu *smenu;
    QMenu *smmenu;
    QMenu *mmenu;
    QMenu *mnmenu;
    QMenu *lmenu;

    QAction *sac1;
    QAction *sac2;
    QAction *sac3;

    QAction *smac1;
    QAction *smac2;
    QAction *smac3;

    QAction *mac1;
    QAction *mac2;
    QAction *mac3;

    QAction *mnac1;
    QAction *mnac2;
    QAction *mnac3;

    QAction *lac1;
    QAction *lac2;
    QAction *lac3;

    QToolButton *clearAll;
    QToolButton *Start;
    QString strship = "铁甲舰：0艘； 穹甲巡洋舰：0艘； 装甲巡洋舰：0艘； 木壳快船：0艘； 钢壳快船： 0艘";

    QLabel *fleetlable;
    QLabel *arrowl;
    QLabel *tjjlable;
    QLabel *zjxyjlabel;
    QLabel *gjxyjlabel;
    QLabel *gkkclabel;
    QLabel *mkkclabel;

    QPixmap *background;
    QPixmap *arrow;
    QPixmap *tjj;
    QPixmap *zjxyj;
    QPixmap *gjxyj;
    QPixmap *gkkc;
    QPixmap *mkkc;
signals:

public slots:
        void returnSlot();

        void adds1shipSlot();
        void adds2shipSlot();
        void adds3shipSlot();

        void addsm1shipSlot();
        void addsm2shipSlot();
        void addsm3shipSlot();

        void addm1shipSlot();
        void addm2shipSlot();
        void addm3shipSlot();

        void addmn1shipSlot();
        void addmn2shipSlot();
        void addmn3shipSlot();

        void addl1shipSlot();
        void addl2shipSlot();
        void addl3shipSlot();

        void clearAllSlot();

        void adds1shipSlotr();
        void adds2shipSlotr();
        void adds3shipSlotr();

        void addsm1shipSlotr();
        void addsm2shipSlotr();
        void addsm3shipSlotr();

        void addm1shipSlotr();
        void addm2shipSlotr();
        void addm3shipSlotr();

        void addmn1shipSlotr();
        void addmn2shipSlotr();
        void addmn3shipSlotr();

        void addl1shipSlotr();
        void addl2shipSlotr();
        void addl3shipSlotr();

        void clearAllSlotr();


        void StartFleetGameSlot();
};

#endif // SELECTMODEL_H
