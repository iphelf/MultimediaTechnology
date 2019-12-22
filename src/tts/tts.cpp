#include "tts.h"
#include "ui_tts.h"
#include "src/console.h"

TTS::TTS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TTS) {
    ui->setupUi(this);
    tts=new QTextToSpeech(this);
    QVector<QLocale> locales=tts->availableLocales();
    for(const QLocale &locale:locales) {
        QString localName(
            QString("%1 (%2)")
            .arg(QLocale::languageToString(locale.language()))
            .arg(QLocale::countryToString(locale.country()))
        );
        QVariant localVariant(locale);
        ui->cbLanguage->addItem(localName,localVariant);
    }
    ui->cbLanguage->setCurrentIndex(0);
    on_cbLanguage_currentIndexChanged(0);
    localeChanged(ui->cbLanguage->itemData(0).toLocale());
    ui->cbVoice->setCurrentIndex(0);
    connect(tts,SIGNAL(localeChanged(const QLocale&)),
            this,SLOT(localeChanged(const QLocale&)));
    connect(tts,SIGNAL(stateChanged(QTextToSpeech::State)),
            this,SLOT(stateChanged(QTextToSpeech::State)));
    connect(ui->sldrVolume,SIGNAL(valueChanged(int)),
            this,SLOT(setVolume(int)));
    connect(ui->sldrRate,SIGNAL(valueChanged(int)),
            this,SLOT(setRate(int)));
    connect(ui->sldrPitch,SIGNAL(valueChanged(int)),
            this,SLOT(setPitch(int)));
    ui->btnStop->setEnabled(false);
}

TTS::~TTS() {
    delete ui;
}

void TTS::play() {
    if(tts->state()==QTextToSpeech::Paused) tts->resume();
    else tts->say(ui->text->toPlainText());
}

void TTS::pause() {
    tts->pause();
}

void TTS::stop() {
    tts->stop();
}

void TTS::setRate(int rate) {
    tts->setRate(rate/10.0);
}

void TTS::setPitch(int pitch) {
    tts->setPitch(pitch/10.0);
}

void TTS::setVolume(int volume) {
    tts->setVolume(volume/100.0);
}

void TTS::on_cbLanguage_currentIndexChanged(int index) {
    tts->setLocale(ui->cbLanguage->itemData(index).toLocale());
}

void TTS::localeChanged(const QLocale&) {
    ui->cbVoice->clear();
    voices=tts->availableVoices();
    QVoice currentVoice=tts->voice();
    for(int i=0; i<voices.size(); i++) {
        ui->cbVoice->addItem(QString("%1 - %2 - %3")
                             .arg(voices[i].name())
                             .arg(QVoice::genderName(voices[i].gender()))
                             .arg(QVoice::ageName(voices[i].age())));
        if(voices[i].name()==currentVoice.name())
            ui->cbVoice->setCurrentIndex(i);
    }
}

void TTS::stateChanged(QTextToSpeech::State s) {
    if(s==QTextToSpeech::Speaking) {
        ui->btnPlay->setText("&Pause");
        ui->btnStop->setEnabled(true);
    } else if(s==QTextToSpeech::Paused) {
        ui->btnPlay->setText("R&esume");
        ui->btnStop->setEnabled(true);
    } else if(s==QTextToSpeech::Ready) {
        ui->btnPlay->setText("&Play");
        ui->btnStop->setEnabled(false);
    }
}

void TTS::on_btnPlay_clicked() {
    if(tts->state()==QTextToSpeech::Speaking) pause();
    else play();
}

void TTS::on_btnStop_clicked() {
    stop();
}

void TTS::on_cbVoice_currentIndexChanged(int index) {
    if(index<0||index>=voices.size()) return;
    tts->setVoice(voices[index]);
}
