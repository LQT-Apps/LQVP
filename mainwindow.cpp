#include <QMediaPlaylist>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenuBar>
#include <QInputDialog>
#include <QShortcut>
#include <QKeyEvent>
#include <QStatusBar>

#include "mainwindow.h"

MainWindow::MainWindow() {
    this->setWindowTitle(tr("Lightweight Qt Video Editor"));

    this->central = new QVideoWidget;
    this->setCentralWidget(central);

    this->player = new QMediaPlayer;
    player->setVideoOutput(central);

    QMenu *fileMenu = menuBar()->addMenu(tr("&File..."));

    fileMenu->addAction(QIcon::fromTheme(tr("document-open")), tr("&Open..."), this, [this] {
        open(pathPrompt());
    }, QKeySequence(tr("Ctrl+O")));

    fileMenu->addAction(QIcon::fromTheme(tr("link")), tr("&Open URL..."), this, [this] {
        open(urlPrompt());
    }, QKeySequence(tr("Ctrl+Shift+O")));

    this->resize(800, 450);
    connect(player, &QMediaPlayer::stateChanged, this, [this](QMediaPlayer::State state) {
        if (state == QMediaPlayer::StoppedState) {
            this->setWindowTitle(tr("Lightweight Qt Video Editor"));
        }
    });
}

void MainWindow::open(QUrl url) {
    if (!QUrl(url).isValid()) {
        QMessageBox box(QMessageBox::Warning, tr("Invalid File or URL"), tr("The file or URL is invalid."), QMessageBox::Ok);
        box.exec();
        return;
    }

    player->setMedia(url);
    this->setWindowTitle(url.toString());
    player->play();
}

QUrl MainWindow::pathPrompt() {
    return QFileDialog::getOpenFileUrl(nullptr, tr("Open File"), QUrl(), tr("Videos (*.mp4 *.webm *.mov *.gif *.mkv);;Audio (*.mp3 *.ogg *.wav"), nullptr);
}

QUrl MainWindow::urlPrompt() {
    return QUrl(QInputDialog::getText(nullptr, tr("URL of Media"), tr("Enter a URL to media to play."), QLineEdit::Normal, "", nullptr, Qt::WindowFlags(), Qt::ImhUrlCharactersOnly));
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->type() == QKeyEvent::KeyPress && event->key() == Qt::Key_Space) {
        toggleState();
    }
}

void MainWindow::toggleState() {
    if (player->state() == QMediaPlayer::PlayingState) {
        player->pause();
    } else {
        player->play();
        this->setWindowTitle(player->media().request().url().toString());
    }
}
