#ifndef TTS_H
#define TTS_H

#include <QMainWindow>
#include <QtTextToSpeech>

namespace Ui {
class TTS;
}

class TTS : public QMainWindow {
    Q_OBJECT

  public:
    explicit TTS(QWidget *parent = nullptr);
    ~TTS();

  public slots:
    void play();
    void pause();
    void stop();
    void setRate(int rate);
    void setPitch(int pitch);
    void setVolume(int volume);

  private slots:
    void on_cbLanguage_currentIndexChanged(int index);
    void localeChanged(const QLocale&);
    void stateChanged(QTextToSpeech::State);
    void on_btnPlay_clicked();
    void on_btnStop_clicked();
    void on_cbVoice_currentIndexChanged(int index);

  private:
    Ui::TTS *ui;
    QTextToSpeech *tts;
    QVector<QVoice> voices;
};

#endif // TTS_H
