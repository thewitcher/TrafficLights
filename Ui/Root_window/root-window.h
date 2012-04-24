#ifndef ROOTWINDOW_H
#define ROOTWINDOW_H

#include <QMainWindow>
//#include <phonon/AudioOutput>
//#include <phonon/MediaObject>

namespace Ui {
    class RootWindow;
}

class RootWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RootWindow(QWidget *parent = 0);
    ~RootWindow();

private:
    Ui::RootWindow *ui;
//    QAction *m_moute;
//    Phonon::AudioOutput *m_audioOutput;
//    Phonon::MediaObject *m_mediaObject;
//    void setActionButtonToToolBar();
//    void setAudio();

//private slots:
//    void regulateVoice();
//    void playAgain();
};

#endif // ROOTWINDOW_H
