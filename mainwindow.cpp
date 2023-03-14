#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <QFileDialog>
#include <iostream>
#include <QProcess>
#include <vector>
#include <list>
#include <QRegularExpression>
#include <QMessageBox>
#include "translator.h"

#define _UNICODE
#include <MediaInfo/MediaInfo.h>
using namespace std;

#define VIDEO_FILTER(o) << #o
#define VIDEO_MATCH(o) << "*."#o


MediaInfoLib::String toString(QString& str)
{
    int m = str.size() + 1;
    wchar_t wchar[m];
    int l = str.toWCharArray(wchar);
    assert(l + 1 == m);
    wchar[l] = 0;
    return MediaInfoLib::String(wchar);
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

QString trim(const QString& str) {
    return str.split(' ', QString::SkipEmptyParts).join("");
}

QString regularProgressBar = " QProgressBar:horizontal { \
        text-align: center; \
        border-radius: 0px; \
        } \
        QProgressBar::chunk:horizontal { \
        background: rgb(80, 240, 80); \
        }";

QString errorProgressBar = "QProgressBar:horizontal { \
    text-align: center; \
    border-radius: 0px; \
    } \
    QProgressBar::chunk:horizontal { \
    background: rgb(255, 20, 20); \
}";

QString lineEditBackground[2] = {"QLineEdit { background: white; } ","QLineEdit { background: red; } "};
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //Initializes widgets
    #define find_children(classn,varn) { varn = findChild<classn>(#varn); assert(varn); }
    WIDGET_LIST(find_children)
    #undef find_children

    currentFile = 0;

    process = new QProcess();
    initChoose(chooseSourceButton,sourceTable,sourceSize,sourceDir);
    initChoose(chooseTargetButton,targetTable,targetSize,targetDir);
    sourceTable->setDurationLabel(sourceDuration);
    connect(transformType,&QLineEdit::textChanged,this,[&](const QString& str){transformTypeString = str; });

    connect(convertButton,&QPushButton::pressed,this,[&](){
        QString error;
        if (!startConversionFrame(error))
        {
            QMessageBox msgBox;
            msgBox.setText(error);
            msgBox.exec();
            //Throw some error
        }else convert();
    });

    connect(killButton,&QPushButton::pressed,this,[&](){
        process->kill();
        endConversionFrame(2);
    });
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        [=](int exitCode)
    {
        if (exitCode == 0 && currentFile < commandArgs.size())
        {
            convertOutput->clear();
            accumaltedMinutes += partialMinutes;
            partialMinutes = 0;
            convert();
        }
        else if (currentFile == commandArgs.size() || exitCode != 0) endConversionFrame(exitCode);

    });

    connect(process,&QProcess::readyReadStandardError,this,[&](){
        QString data = process->readAllStandardError();
        convertOutput->append(data);
        convertOutput->scroll(0,100);
        QRegularExpression expr("time=[0-9]{2}:[0-9]{2}");
        QRegularExpressionMatch match =expr.match(data);
        if (match.isValid())
        {
            string str = match.captured().toStdString();

            string delimiter = "=";
            str.erase(0, str.find(delimiter) + delimiter.length());

            if (str.size() != 0)
            {
                string hours,minutes;
                delimiter = ":";

                hours = str.substr(0,str.find(delimiter));
                minutes = str.substr(str.find(delimiter) + 1,str.size() - 1);

               // cerr << "Times " << hours << " " << minutes << endl;
                partialMinutes = stoi(hours) * 60 + stoi(minutes);
                updateProgressBar();
            }
        }
    });

    connect(reduceWidth,&QLineEdit::textChanged,this,
            [&](const QString& text) {
                int result = !is_number(text.toStdString());
                reduceWidth->setStyleSheet(lineEditBackground[result]);
            }
    );
    connect(reduceHeight,&QLineEdit::textChanged,this,
            [&](const QString& text) {
                int result = !is_number(text.toStdString());
                reduceHeight->setStyleSheet(lineEditBackground[result]);
            }
    );

    connect(reduceWidth,&QLineEdit::textChanged,this,[&](const QString& text){
        if(!reduceToOption->isChecked()) {
            reduceToOption->toggle();
        }
    });
    connect(reduceHeight,&QLineEdit::textChanged,this,[&](const QString& text){
        if(!reduceToOption->isChecked()) {
            reduceToOption->toggle();
        }
    });

    connect(transformType,&QLineEdit::textChanged,this,[&](const QString& text){
        if(!transformOption->isChecked()) {
            transformOption->toggle();
        }
    });

    connect(audioScaleSlider,&QSlider::valueChanged,this,[&](int value){
        if(value != 100 && !audioScale->isChecked())
        {
            if(normalizeAudio->isChecked()) normalizeAudio->toggle();
            audioScale->toggle();
        }
    });

    connect(endConvertButton,&QPushButton::pressed,this,[&](){
          conversionPanelMode();
    });
    convertResult->setText("");
    languageDialog = new LanguageDialog(this);
    conversionPanelMode();
}

void MainWindow::conversionPanelMode() {
    endConvertButton->setVisible(false);
    convertButton->setVisible(true);
    convertPanel->setVisible(true);
    convertStatus->setVisible(false);
    killButton->setVisible(false);
}

void MainWindow::conversionStatusMode() {

    convertButton->setVisible(false);
    convertPanel->setVisible(false);
    convertStatus->setVisible(true);
    killButton->setVisible(true);

    convertProgress->setValue(0);
    convertProgress->setFormat("%p%");
    convertProgress->setStyleSheet(regularProgressBar);

    convertProgress->setEnabled(true);
    convertResult->setText("");
    convertResult->setEnabled(false);
    convertButton->setEnabled(false);
    killButton->setEnabled(true);
    etaLabel->setEnabled(true);
    etaValue->setEnabled(true);

}
void MainWindow::conversionEndedMode() {
    endConvertButton->setVisible(true);
    killButton->setVisible(false);

}
bool MainWindow::reduceToSize(QString& width, QString& height) {
    width = trim(reduceWidth->text());
    height = trim(reduceHeight->text());

    if(!is_number(width.toStdString()) || !is_number(height.toStdString())) return false;

    return true;
}
bool MainWindow::transformFlag() {
    return transformOption->isChecked();
}

bool MainWindow::reduceFlag() {
    return reduceOption->isChecked();
}
bool MainWindow::reduceToFlag() {
    return reduceToOption->isChecked();
}
bool MainWindow::scaleAudioFlag() {
    return audioScale->isChecked();
}

bool MainWindow::normalizeAudioFlag() {
    return normalizeAudio->isChecked();
}
float MainWindow::scaleAudioValue()
{
    float scale = audioScaleSlider->value();
    scale /= 100.0f;
    return scale;

}

void MainWindow::initChoose(QPushButton *button, FileTable *table,QLabel* sizeLabel,QLabel* dirLabel)
{
    table->setSizeLabel(sizeLabel);
    connect(button,&QPushButton::pressed,this,[dirLabel,table,this](){

        QDir dir = QFileDialog::getExistingDirectory(this,"Escoge directorio",".",QFileDialog::ReadOnly);
        QStringList videos = dir.entryList(QStringList() REGISTERED_VIDEO_TYPES(VIDEO_MATCH),QDir::Files);
        dirLabel->setText(dir.absolutePath());
        table->reset();
        vector<int> durationVector(videos.size());
        vector<QString> resolutionVector(videos.size());

        {
            vector<QString> fileNameS;
            foreach(QString filename,videos) { fileNameS.push_back(dir.absoluteFilePath(filename)); }

            #pragma omp parallel for
            for (size_t i = 0; i < fileNameS.size(); i++) {

                MediaInfoLib::MediaInfo MI;
                MI.Open(toString(fileNameS[i]));
                durationVector[i] = wcstod(MI.Get(MediaInfoLib::Stream_General,0,L"Duration").c_str(),NULL) / (60 * 1000);

                resolutionVector[i] =
                QString::fromWCharArray(MI.Get(MediaInfoLib::Stream_General,0,L"Aspect").c_str()) + "x" +
                QString::fromWCharArray(MI.Get(MediaInfoLib::Stream_General,0,L"height").c_str());
            }
        }
        int i = 0;
        foreach(QString filename,videos){
            QString fileName = dir.absoluteFilePath(filename);
            table->addFile(filename,double(QFile(fileName).size()) / (1024.0 * 1024.0),durationVector[i],resolutionVector[i]);
            i++;
        }
        table->dirPath = dir;
    });
}

#define cerror(x) { error = (x); return false; }
bool MainWindow::startConversionFrame(QString& error)
{
    const static QString sourceDirectory_error = tr("Source directory %1 does not exists!");
    const static QString targetDirectory_error = tr("Target directory %1 does not exists!");

    if(!sourceTable->dirPath.exists()) cerror(sourceDirectory_error.arg(sourceTable->dirPath.dirName()));
    if(!targetTable->dirPath.exists()) cerror(targetDirectory_error.arg(targetTable->dirPath.dirName()));

    QString reduce_width,reduce_height;
    if(reduceToFlag() && !reduceToSize(reduce_width,reduce_height)) cerror(tr("Wrong resolution parameters"));
    QVector<QString> files = sourceTable->getFiles();

    if (files.size() == 0) cerror(tr("No source file has been selected"));

    commandArgs.clear();
    conversionFiles.clear();

    QDir sourceDir = sourceTable->dirPath;
    QDir targetDir = targetTable->dirPath;

    for (int i = 0; i < files.size(); i++) {
        QStringList argument;
        QString target_file = files[i];

        if (transformFlag())
        {
            target_file =files[i].split(".",QString::SkipEmptyParts).at(0);
            target_file += "." + transformType->text();
        }

        argument << "-y" << "-i"
                 << (sourceDir.absolutePath() + "/" + files[i]);

        //TODO: Move conversion argument parameters outside loop

        if(reduceFlag()) argument << "-vf" << "scale=iw/2:ih/2";
        if(reduceToFlag()) argument << "-vf" << QString("scale=" + reduce_width + ":" + reduce_height);
        if(scaleAudioFlag()) argument << QString("-filter:a") << QString("volume=" + QString::number(scaleAudioValue()));
        if(normalizeAudioFlag()) argument << QString("-filter:a") << QString("loudnorm");

        argument << (targetDir.absolutePath() + "/" + target_file);
        commandArgs.push_back(argument);
        conversionFiles.push_back(target_file);
    }

    targetMinutes = sourceTable->getTotalDuration();
    partialMinutes = 0;
    accumaltedMinutes = 0;

    conversionStatusMode();
    return true;
}
void MainWindow::endConversionFrame(int exitCode)
{
    convertResult->setEnabled(true);
    convertButton->setEnabled(true);
    killButton->setEnabled(false);
    etaLabel->setEnabled(false);
    etaValue->setEnabled(false);

    switch (exitCode) {
        case 0: convertResult->setText(tr("Conversion successful")); break;
        case 2: convertResult->setText(tr("Conversion necessarily stopped")); break;
        default:convertResult->setText(tr("Conversion failure")); break;
    }

    if (exitCode) {
        convertProgress->setStyleSheet(errorProgressBar);
    }

    currentFile = 0;
    partialMinutes = 0;
    accumaltedMinutes = 0;
    targetMinutes = 0;

    conversionEndedMode();
}

void MainWindow::updateProgressBar()
{
    convertProgress->setFormat("%p% " + conversionFiles[currentFile - 1] + " (" + QString::number(currentFile) + "/" + QString::number(conversionFiles.size()) + ")");
    convertProgress->setValue((accumaltedMinutes + partialMinutes) * 100 / targetMinutes);
}
void MainWindow::convert()
{
    cout << "Using parameters for conversion " << currentFile << ": ";

    for (QString& arg : commandArgs[currentFile]) {
        cout << arg.toStdString() << " ";
    }
    process->start("ffmpeg",commandArgs[currentFile]);
    currentFile++;
    updateProgressBar();
}
void MainWindow::showLanguageDialog()
{
    languageDialog->show();
}
MainWindow::~MainWindow()
{
    delete ui;
    delete process;
    delete languageDialog;
}


