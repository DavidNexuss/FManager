#include "myfilesystemmodel.h"

MyFileSystemModel::MyFileSystemModel(QObject* parent) : QFileSystemModel(parent)
{
    m_columnCount = 5;
    bool b = insertColumn(0);
}

int MyFileSystemModel::columnCount(const QModelIndex &parent) const
{
    return (parent.column() > 0) ? 0 : m_columnCount;
}

QVariant MyFileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section == 4 && orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return "Us";
    return QFileSystemModel::headerData(section,orientation,role);
}
MyFileSystemModel::~MyFileSystemModel()
{

}
