#ifndef FILETABLE_H
#define FILETABLE_H

#include <QTableWidget>
#include <QObject>
#include <QVector>
#include <QMap>
#include <QCheckBox>
#include <QLabel>
#include <QDir>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class FileTable; }
QT_END_NAMESPACE

struct Item
{
    double tamany;
    int duracio;
};

class FileTable : public QTableWidget
{
    Q_OBJECT

public:
    FileTable(QWidget* parent = nullptr);

    void updateSizeLabel();
    void setSizeLabel(QLabel* sizeLabel);
    void updateDurationLabel();
    void setDurationLabel(QLabel* durationLabel);
    void addFile(const QString& name,double tamany,int duracio);
    void reset();

    QVector<QString> getFiles() const;

    QDir dirPath;

    int getTotalDuration() const;

private:

    QVector<Item> items;
    QMap<QCheckBox*,int> map;

    QLabel* sizeLabel;
    QLabel* durationLabel;

    double m_tamany_total;
    int m_duracio_total;
};

#endif // FILETABLE_H
