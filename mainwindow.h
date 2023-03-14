#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QRadioButton>
#include <QLineEdit>
#include <QProgressBar>
#include <QTextBrowser>
#include <QProcess>
#include <QSlider>
#include "languagedialog.h"
#include "filetable.h"

#define WIDGET_LIST(o) \
o(QProgressBar* ,convertProgress)\
o(QTextBrowser* ,convertOutput)\
o(QPushButton* ,convertButton) \
o(QPushButton* ,endConvertButton) \
o(QLabel* ,convertResult)\
o(QLabel* ,sourceSize)\
o(QLabel* ,sourceDir)\
o(QLabel* ,sourceDuration)\
o(QLabel* ,targetDir)\
o(QLabel* ,targetSize)\
o(QLabel* ,etaLabel)\
o(QLabel* ,etaValue)\
o(QPushButton *, chooseSourceButton)\
o(QPushButton * ,chooseTargetButton)\
o(QPushButton * ,killButton)\
o(QCheckBox* ,transformOption)\
o(QLineEdit* ,transformType)\
o(QRadioButton* ,reduceOption)\
o(QRadioButton* ,reduceToOption) \
o(QSlider*,audioScaleSlider) \
o(QRadioButton*,audioScale) \
o(QRadioButton*,normalizeAudio) \
o(QLineEdit*, reduceWidth) \
o(QLineEdit*, reduceHeight) \
o(FileTable* ,sourceTable)\
o(FileTable* ,targetTable) \
o(QTabWidget*,convertPanel) \
o(QFrame*,convertStatus)

#define REGISTERED_VIDEO_TYPES(o) \
o(mp4) o(mkv) o(avi) o(mp3)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void convert();
    void initChoose(QPushButton* button,FileTable* table,QLabel* sizeLabel,QLabel* dirLabel);
    bool startConversionFrame(QString& error);
    void endConversionFrame(int errorCode);

    void updateProgressBar();

    Ui::MainWindow *ui;

    #define declare_widget(classn,varn) classn varn;
    WIDGET_LIST(declare_widget)
    #undef declare_widget

    bool canConvert();

    bool reduceToSize(QString& width,QString& height);
    bool reduceToFlag();
    bool reduceFlag();
    bool transformFlag();
    bool scaleAudioFlag();
    bool normalizeAudioFlag();
    float scaleAudioValue();

    void conversionStatusMode();
    void conversionPanelMode();
    void conversionEndedMode();

    QString transformTypeString;
    QProcess* process;
    LanguageDialog* languageDialog;

    QVector<QStringList> commandArgs;
    QVector<QString> conversionFiles;
    int currentFile;

    int targetMinutes = 0;
    int partialMinutes = 0;
    int accumaltedMinutes = 0;

public slots:
    void showLanguageDialog();

};

#endif // MAINWINDOW_)
