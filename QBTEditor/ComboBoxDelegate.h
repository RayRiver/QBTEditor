#ifndef ComboBoxDelegate_h__
#define ComboBoxDelegate_h__

#include <QMap>
#include <QStyledItemDelegate>

class ComboBoxDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	enum class ComboType
	{
		Precondition,
	};
private:
	static QMap<ComboType, QString> s_defaultValues;

public:
	ComboBoxDelegate(ComboType type, QObject *parent = 0);

	// override
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

	static const QString &defaultValue(ComboType type);
	
private:
	QStringList m_items;
	ComboType m_type;

};

#endif // ComboBoxDelegate_h__
