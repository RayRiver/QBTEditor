#include "ComboBoxDelegate.h"

#include <QMap>
#include <QComboBox>

QMap<ComboBoxDelegate::ComboType, QString> ComboBoxDelegate::s_defaultValues;

const QString & ComboBoxDelegate::defaultValue( ComboType type )
{
	if (s_defaultValues.size() == 0)
	{
		s_defaultValues.insert(ComboType::Precondition, QObject::tr("false"));
	}
	return s_defaultValues[type];
}

ComboBoxDelegate::ComboBoxDelegate(ComboType type, QObject *parent)
    : QStyledItemDelegate(parent)
	, m_type(type)
{
	switch (type)
	{
	case ComboType::Precondition:
		m_items << "true" << "false";
		break;
	default:
		Q_ASSERT(false);
		break;
	}
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->setFrame(false);
	editor->addItems(m_items);
	editor->setCurrentIndex(0);

    const auto &val = index.model()->data(index, Qt::EditRole).toString();
	auto s = val.data();

    return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    const auto &val = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *combobox = static_cast<QComboBox *>(editor);
	int i = combobox->findText(val);
    combobox->setCurrentIndex(i);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *combobox = static_cast<QComboBox *>(editor);
    const auto &val = combobox->currentText();
    model->setData(index, val, Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
