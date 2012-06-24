#ifndef ROOTWINDOW_H
#define ROOTWINDOW_H

#include <QMainWindow>
#ifdef MUSIC
#include <phonon/AudioOutput>
#include <phonon/MediaObject>
#endif
namespace Ui {
    class RootWindow;
}

class RootWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RootWindow( QWidget *parent = 0 );
    ~RootWindow();

private:
    Ui::RootWindow *ui;
#ifdef MUSIC
    QAction *m_moute;
    Phonon::AudioOutput *m_audioOutput;
    Phonon::MediaObject *m_mediaObject;
    void setActionButtonToToolBar();
    void setAudio();

private slots:
    void regulateVoice();
    void playAgain();
#endif
};

#endif // ROOTWINDOW_H
