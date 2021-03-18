#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>
#include <QProcess>
#define _UNICODE
#include <MediaInfo/MediaInfo.h>
#include <vector>
#include <list>
#include <QRegularExpression>
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

const QStringList typeList = QStringList() REGISTERED_VIDEO_TYPES(VIDEO_FILTER);

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
    connect(transformType,&QComboBox::currentTextChanged,this,[&](const QString& str){transformTypeString = str; });

    connect(convertButton,&QPushButton::pressed,this,[&](){
        QString error;
        if (!startConversionFrame(error))
        {
            cerr << error.toStdString() << endl;
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

                cerr << "Times " << hours << " " << minutes << endl;
                partialMinutes = stoi(hours) * 60 + stoi(minutes);
                updateProgressBar();
            }
        }
    });

    transformType->insertItems(0,typeList);
}

bool MainWindow::transformFlag()
{
    return transformOption->isChecked();
}
bool MainWindow::reduceFlag()
{
    return reduceOption->isChecked();
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
        {
            vector<QString> fileNameS;
            foreach(QString filename,videos) { fileNameS.push_back(dir.absoluteFilePath(filename)); }

            #pragma omp parallel for
            for (size_t i = 0; i < fileNameS.size(); i++) {

                MediaInfoLib::MediaInfo MI;
                MI.Open(toString(fileNameS[i]));
                durationVector[i] = wcstod(MI.Get(MediaInfoLib::Stream_General,0,L"Duration").c_str(),NULL) / (60 * 1000);
            }
        }
        int i = 0;
        foreach(QString filename,videos){
            QString fileName = dir.absoluteFilePath(filename);
            table->addFile(filename,double(QFile(fileName).size()) / (1024.0 * 1024.0),durationVector[i]);
            i++;
        }
        table->dirPath = dir;
    });
}

#define cerror(x) { error = (x); return false; }
bool MainWindow::startConversionFrame(QString& error)
{
    if(!sourceTable->dirPath.exists()) cerror("El directori font" + sourceTable->dirPath.dirName() + " no existeix");
    if(!targetTable->dirPath.exists()) cerror("EL directori objectiu" + sourceTable->dirPath.dirName() + " no existeix");

    QVector<QString> files = sourceTable->getFiles();

    if (files.size() == 0) cerror("No has seleccionat cap arxiu");

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
            target_file += "." + transformType->currentText();
        }


        argument << "-y" << "-i"
                 << (sourceDir.absolutePath() + "/" + files[i]);

        if(reduceFlag()) argument << "-vf" << "scale=iw/2:ih/2";
        argument << (targetDir.absolutePath() + "/" + target_file);
        commandArgs.push_back(argument);
        conversionFiles.push_back(target_file);
    }

    /*
    foreach(QStringList list,commandArgs)
    {
        foreach(QString name,list) cerr << name.toStdString() << " ";
        cerr << endl;
    }
    */

    convertProgress->setEnabled(true);
    convertResult->setEnabled(false);
    convertButton->setEnabled(false);
    killButton->setEnabled(true);

    targetMinutes = sourceTable->getTotalDuration();
    partialMinutes = 0;
    accumaltedMinutes = 0;

    convertProgress->setValue(0);
    convertProgress->setFormat("%p%");

    return true;
}
void MainWindow::endConversionFrame(int exitCode)
{
    convertResult->setEnabled(true);
    convertButton->setEnabled(true);
    killButton->setEnabled(false);

    switch (exitCode) {
        case 0: convertResult->setText("Conversió finalitzada amb éxit!"); break;
        case 2: convertResult->setText("Conversió aturada forzosament."); break;
        default:convertResult->setText("Conversió fallida!"); break;
    }

    currentFile = 0;
    partialMinutes = 0;
    accumaltedMinutes = 0;
    targetMinutes = 0;
}

void MainWindow::updateProgressBar()
{
    convertProgress->setFormat("%p% " + conversionFiles[currentFile - 1] + " (" + QString(currentFile) + "/" + QString(conversionFiles.size()) + ")");
    convertProgress->setValue((accumaltedMinutes + partialMinutes) * 100 / targetMinutes);
}
void MainWindow::convert()
{
    int m = commandArgs.size();
    int i = currentFile;
    if (i < m)
    {
        process->start("ffmpeg",commandArgs[currentFile]);
        currentFile++;
        updateProgressBar();
    }
    else
    {
    }
}
MainWindow::~MainWindow()
{
    delete ui;
    delete process;
    /*
    delete sourceFileModel;
    delete targetFileModel;
    */
}

