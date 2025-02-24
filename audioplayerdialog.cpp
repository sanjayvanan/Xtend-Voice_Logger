#include "audioplayerdialog.h"
#include "ui_audioplayerdialog.h"
#include <QStyle>

AudioPlayerDialog::AudioPlayerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AudioPlayerDialog)
    , mediaPlayer(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
    , updateTimer(new QTimer(this))
{
    ui->setupUi(this);
    setWindowTitle("Audio Player");

    mediaPlayer->setAudioOutput(audioOutput);
    audioOutput->setVolume(ui->volumeSlider->value() / 100.0);

    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &AudioPlayerDialog::updatePosition);
    connect(mediaPlayer, &QMediaPlayer::durationChanged, this, &AudioPlayerDialog::updateDuration);
    connect(mediaPlayer, &QMediaPlayer::playbackStateChanged, this, &AudioPlayerDialog::updateState);

    // Set icons for buttons
    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
}

AudioPlayerDialog::~AudioPlayerDialog()
{
    delete ui;
}

void AudioPlayerDialog::setAudioSource(const QString &filePath)
{
    mediaPlayer->setSource(QUrl::fromLocalFile(filePath));
    mediaPlayer->play();
}

void AudioPlayerDialog::setTitle(const QString &title)
{
    ui->titleLabel->setText("Now Playing: " + title);
}

void AudioPlayerDialog::on_playButton_clicked()
{
    mediaPlayer->play();
}

void AudioPlayerDialog::on_pauseButton_clicked()
{
    mediaPlayer->pause();
}

void AudioPlayerDialog::on_stopButton_clicked()
{
    mediaPlayer->stop();
}

void AudioPlayerDialog::on_positionSlider_sliderMoved(int position)
{
    mediaPlayer->setPosition(position);
}

void AudioPlayerDialog::on_volumeSlider_valueChanged(int value)
{
    audioOutput->setVolume(value / 100.0);
}

void AudioPlayerDialog::updatePosition(qint64 position)
{
    ui->positionSlider->setSliderPosition(position);
    QString timeString;
    formatTime(position, timeString);
    ui->currentTimeLabel->setText(timeString);
}

void AudioPlayerDialog::updateDuration(qint64 duration)
{
    ui->positionSlider->setRange(0, duration);
    QString timeString;
    formatTime(duration, timeString);
    ui->totalTimeLabel->setText(timeString);
}

void AudioPlayerDialog::updateState(QMediaPlayer::PlaybackState state)
{
    ui->playButton->setEnabled(state != QMediaPlayer::PlayingState);
    ui->pauseButton->setEnabled(state == QMediaPlayer::PlayingState);
    ui->stopButton->setEnabled(state != QMediaPlayer::StoppedState);
}

void AudioPlayerDialog::formatTime(qint64 timeInMilliseconds, QString &result)
{
    qint64 seconds = timeInMilliseconds / 1000;
    qint64 minutes = seconds / 60;
    seconds %= 60;
    result = QString("%1:%2")
        .arg(minutes, 2, 10, QLatin1Char('0'))
        .arg(seconds, 2, 10, QLatin1Char('0'));
}
