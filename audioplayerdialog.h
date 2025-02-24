#ifndef AUDIOPLAYERDIALOG_H
#define AUDIOPLAYERDIALOG_H

#include <QDialog>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>

namespace Ui {
class AudioPlayerDialog;
}

class AudioPlayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AudioPlayerDialog(QWidget *parent = nullptr);
    ~AudioPlayerDialog();
    void setAudioSource(const QString &filePath);
    void setTitle(const QString &title);

private slots:
    void on_playButton_clicked();
    void on_pauseButton_clicked();
    void on_stopButton_clicked();
    void on_positionSlider_sliderMoved(int position);
    void on_volumeSlider_valueChanged(int value);
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);
    void updateState(QMediaPlayer::PlaybackState state);

private:
    Ui::AudioPlayerDialog *ui;
    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;
    QTimer *updateTimer;
    void formatTime(qint64 timeInMilliseconds, QString &result);
};

#endif // AUDIOPLAYERDIALOG_H
