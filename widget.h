#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtAudio>
#include <QFile>
#include <QAudioSink>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void GetWaveFile();
    void handleStateChanged(QtAudio::State state);
    void newSound();
    QString filename;
    QString filenameChosen;
    QFile sourceFile;
    QAudioSink* audioOut;

private slots:

    void on_btnCapture_clicked();

    void on_btnStopSound_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
