#include <QApplication>
#include "MainMenu.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*QStringListModel *listModel = new QStringListModel;
    QListView* listView = new QListView;
    QStringList nameList;
    nameList<<"Zhang Ruozhou"<<"Ding Xuanyu"<<"Ji Wenjing"<<"Juesha Ge";
    listModel->setStringList(nameList);
    listView->setModel(listModel);
    listView->setEditTriggers(QAbstractItemView::AnyKeyPressed|
                              QAbstractItemView::DoubleClicked);*/
    MainMenu k;
    k.show();

    return a.exec();


}
