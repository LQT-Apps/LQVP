#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVideoWidget>
#include <QMediaPlayer>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

    void open(QString path = "");
    void open(QUrl url = QUrl());

    void setMedia(QUrl url);

    QUrl pathPrompt();
    QUrl urlPrompt();

    void keyPressEvent(QKeyEvent *event);

    QString path;

    QVideoWidget *central;
    QMediaPlayer *player;
public slots:
    void toggleState();
};
#endif // MAINWINDOW_H
