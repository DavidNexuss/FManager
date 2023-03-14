#include "filetable.h"
#include <QHeaderView>
#include <QLabel>

FileTable::FileTable(QWidget* parent) : QTableWidget(parent)
{
    m_tamany_total = 0;
    m_duracio_total = 0;

    int tableIndex = 0;
    auto setHeader = [&](const QString& name)
    {
        QTableWidgetItem *header2 = new QTableWidgetItem();
        header2->setText(name);
        setHorizontalHeaderItem(tableIndex++,header2);
    };
    setColumnCount(4);
    horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    horizontalHeader()->setStretchLastSection(true);
    verticalHeader()->setVisible(false);

    setHeader(tr("File"));
    setHeader(tr("Size"));
    setHeader(tr("Duration"));
    setHeader(tr("Resolution"));
}

void FileTable::reset()
{
    while(rowCount()) removeRow(rowCount() - 1);
    m_tamany_total = 0.0;
    m_duracio_total = 0;
    map.clear();
    items.clear();
    updateSizeLabel();
    updateDurationLabel();
}
void FileTable::setSizeLabel(QLabel *sizeLabel)
{
    this->sizeLabel = sizeLabel;
    updateSizeLabel();
}
inline float decimalSize(float size) {
    return float(int(size * 100)) / 100.0f;
}
void FileTable::updateSizeLabel()
{
    if (sizeLabel != nullptr)sizeLabel->setText(QString::number(decimalSize(m_tamany_total)) + " MB");
}

void FileTable::setDurationLabel(QLabel *durationLabel)
{
    this->durationLabel = durationLabel;
    updateDurationLabel();
}
void FileTable::updateDurationLabel()
{
    if (durationLabel != nullptr) durationLabel->setText(QString::number(m_duracio_total) + " m");
}
int FileTable::getTotalDuration() const
{
    return m_duracio_total;
}
void FileTable::addFile(const QString& name,double tamany,int duracio,const QString& res)
{
    QCheckBox* checkBox = new QCheckBox(name);
    checkBox->setText(name);
    int row = rowCount();
    insertRow(row);

    auto format = [](QWidget* widget)
    {
        widget->setStyleSheet("* { padding: 8px; }");
        return widget;
    };

    auto label = [format](const QString& data){
        //QFrame* f = new QFrame();
        //f->setLayout(new 3)
        QLabel* q = new QLabel(data);
        q->setAlignment(Qt::AlignCenter);
        return format(q);
    };

    setCellWidget(row,0,format(checkBox));
    setCellWidget(row,1,label(QString::number(decimalSize(tamany))));
    setCellWidget(row,2,label(QString::number(duracio)));
    setCellWidget(row,3,label(res));

    horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    map[checkBox] = items.size();
    items.push_back({tamany,duracio});

    connect(checkBox,&QCheckBox::stateChanged,this,[this,checkBox](int newState){
        int mul = newState ? 1 : -1;
        m_tamany_total += mul * items[map[checkBox]].tamany;
        m_duracio_total += mul * items[map[checkBox]].duracio;
        updateSizeLabel();
        updateDurationLabel();
    });
}
QVector<QString> FileTable::getFiles() const {
    QVector<QString> files;

    for (int i = 0;i< rowCount(); i++ ) {
        QCheckBox* check = static_cast<QCheckBox*>(cellWidget(i,0));
        if (check->isChecked()) files.append(check->text());
    }
    return files;
}
