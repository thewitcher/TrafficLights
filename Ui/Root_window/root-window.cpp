#include "root-window.h"
#include "ui_root-window.h"
#include "../DatabaseManager/database.h"

RootWindow::RootWindow( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::RootWindow )
{
    ui->setupUi( this );
#ifdef MUSIC
    setActionButtonToToolBar();
    setAudio();
    connect( m_moute, SIGNAL(triggered()), this, SLOT(regulateVoice()) );
    connect( m_mediaObject, SIGNAL(finished()), this, SLOT(playAgain()) );
#endif
}

RootWindow::~RootWindow()
{
    delete ui;
#ifdef MUSIC
    delete m_moute;
    delete m_mediaObject;
    delete m_audioOutput;
#endif
}

#ifdef MUSIC
void RootWindow::setActionButtonToToolBar()
{
    m_moute = new QAction( "Voice", this );
    ui->mainToolBar->addAction( m_moute );
}

void RootWindow::setAudio()
{
    m_audioOutput = new Phonon::AudioOutput( Phonon::MusicCategory, this );
    m_mediaObject = new Phonon::MediaObject( this );
    m_mediaObject->setCurrentSource( Phonon::MediaSource( ":/music/Music/song.mp3" ) );
    Phonon::createPath( m_mediaObject, m_audioOutput );
    m_mediaObject->play();
}

void RootWindow::regulateVoice()
{
    if( m_audioOutput->volume() )
        m_audioOutput->setVolume( 0 );
    else
        m_audioOutput->setVolume( 1 );
}

void RootWindow::playAgain()
{
    m_mediaObject->setCurrentSource( Phonon::MediaSource( ":/music/Music/song.mp3" ) );
    m_mediaObject->play();
}
#endif
