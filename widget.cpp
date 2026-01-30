#include "widget.h"
#include "ui_widget.h"
#include <QMediaDevices>
#include <QUrl>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->cboFiles->addItem("select file");
    ui->cboFiles->addItem("v43.wav");
    ui->cboFiles->addItem("v45.wav");
    ui->cboFiles->addItem("v47.wav");
    ui->cboFiles->addItem("v48.wav");
    ui->cboFiles->addItem("v50.wav");
    ui->cboFiles->addItem("v52.wav");
    ui->cboFiles->addItem("v54.wav");
    ui->cboFiles->addItem("v55.wav");
    ui->cboFiles->addItem("click6L.wav");
    QObject::connect(ui->cboFiles, &QComboBox::currentTextChanged, this, &Widget::newSound);
    QAudioFormat format;
    // Set up the format, eg.
    format.setSampleRate(44100);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);

    QAudioDevice info(QMediaDevices::defaultAudioOutput());
    if (!info.isFormatSupported(format)) {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
        return;
    }

    audioOut = new QAudioSink(format, this);
    connect(audioOut, &QAudioSink::stateChanged, this, &Widget::handleStateChanged);
}

Widget::~Widget()
{
    delete ui;
    delete audioOut;
}

void Widget::GetWaveFile()
{
    qDebug() << "enter get wave...";
    bool ok;
    sourceFile.close();
    sourceFile.setFileName("C:/QtWorking/AudioSinkUIExample/v_sounds/" + filename);
    ok = sourceFile.open(QIODevice::ReadOnly);
    qDebug() << ok;

    audioOut->start(&sourceFile);
    qDebug() << QtAudio::State();
}

void Widget::handleStateChanged(QtAudio::State newState)
{
    qDebug() << "-->" << newState;
    switch (newState) {

    case QtAudio::IdleState:
        // Finished playing (no more data)
        //Widget::stopAudioOutput();
        audioOut->reset();
        qDebug() << QtAudio::State();
        break;

    case QtAudio::StoppedState:
        // Stopped for other reasons
        if (audioOut->error() != QtAudio::NoError) {
            // Error handling
            qDebug() << "-->" << QtAudio::State();
        }
        break;

    case QtAudio::ActiveState:
        qDebug() << QtAudio::State();
        break;

    default:
        // ... other cases as appropriate
        qDebug() << QtAudio::State();
        break;
    }
}

void Widget::newSound()
{
    sourceFile.readAll();
    sourceFile.close();
    filename = ui->cboFiles->currentText();
    qDebug () << filename;
    GetWaveFile();
}

void Widget::on_btnCapture_clicked()
{

}


void Widget::on_btnStopSound_clicked()
{
    audioOut->reset();
    sourceFile.readAll();
    sourceFile.close();
}

