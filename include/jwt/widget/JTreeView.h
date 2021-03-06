#ifndef JTREEVIEW_H
#define JTREEVIEW_H

#include "../global.h"
#include <QTreeView>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QStyledItemDelegate>

// - class JTreeItemDelegate -

class JWT_EXPORT JTreeItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit JTreeItemDelegate(QObject *parent = nullptr);
    virtual ~JTreeItemDelegate() J_OVERRIDE;

    static QString simplified(const QString &text);
    virtual QSize sizeHint(const QStyleOptionViewItem &option,
                           const QModelIndex &index) const Q_DECL_OVERRIDE;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
                       const QModelIndex &index) const Q_DECL_OVERRIDE;

    static QStandardItemModel *sourceModel(QAbstractItemModel *model);
    static QStandardItemModel *sourceModel(const QModelIndex &index);
    static QModelIndex mapToSource(const QModelIndex &index);
};

// - class JTreeSortFilterModel -

class JTreeSortFilterModelData;

class JWT_EXPORT JTreeSortFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit JTreeSortFilterModel(QObject *parent = nullptr);
    ~JTreeSortFilterModel();

    QRegExp filterPattern() const;
    void setFilterPattern(const QRegExp &pattern);
    void setFilterPattern(const QString &text);
    void removeFilterPattern();

protected:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

private:
    JTreeSortFilterModelData *d;
    friend class JTreeSortFilterModelData;
};

// - class JTreeViewItem -

class JTreeView;

class JWT_EXPORT JTreeViewItem : public QStandardItem
{
    friend class JTreeView;
public:
    explicit JTreeViewItem(int type = Type);
    explicit JTreeViewItem(const QString &text, int type = Type);
    explicit JTreeViewItem(const QIcon &icon, const QString &text, int type = Type);
    explicit JTreeViewItem(int rows, int columns, int type = Type);
    virtual ~JTreeViewItem() J_OVERRIDE;

    virtual QStandardItem *clone() const override;

    inline JTreeView *view() const;

    inline void setSelected(bool aselect);
    inline bool isSelected() const;

    inline void setHidden(bool ahide);
    inline bool isHidden() const;

    inline void setExpanded(bool aexpand);
    inline bool isExpanded() const;

    inline void setFirstColumnSpanned(bool aspan);
    inline bool isFirstColumnSpanned() const;

    inline void setDisabled(bool disabled);
    inline bool isDisabled() const;

    enum ChildIndicatorPolicy { ShowIndicator, DontShowIndicator, DOntShowIndicatorWhenChildless };
    void setChildIndicatorPolicy(JTreeViewItem::ChildIndicatorPolicy policy);
    JTreeViewItem::ChildIndicatorPolicy childIndicatorPolicy() const;

#ifndef QT_NO_DATASTREAM
    virtual void read(QDataStream &in) override;
    virtual void write(QDataStream &out) const override;
#endif
    virtual bool operator<(const QStandardItem &other) const override;

    inline int type() const override { return type_; }

protected:
    JTreeViewItem(const JTreeViewItem &other);
    JTreeViewItem &operator=(const JTreeViewItem &other);

private:
    int type_;
    ChildIndicatorPolicy policy_;
};

// - class JTreeView -

class JTreeViewPrivate;

class JWT_EXPORT JTreeView : public QTreeView
{
    Q_OBJECT
    Q_PROPERTY(int columnCount READ columnCount WRITE setColumnCount)
    Q_PROPERTY(int topLevelItemCount READ topLevelItemCount)
public:
    explicit JTreeView(QWidget *parent = nullptr);
    ~JTreeView() J_OVERRIDE;

    int columnCount() const;
    void setColumnCount(int columns);

    QStandardItem *invisibleRootItem() const;
    QStandardItem *topLevelItem(int row, int column = 0) const;
    int topLevelItemCount() const;
    void insertTopLevelItem(int index, QStandardItem *item);
    void addTopLevelItem(QStandardItem *item);
    QStandardItem *takeTopLevelItem(int row, int column = 0) const;
    QList<QStandardItem *> takeTopLevelItem(int row);
    int indexOfTopLevelItem(QStandardItem *item) const;

    void insertTopLevelItems(int index, const QList<QStandardItem *> &items);
    void addTopLevelItems(const QList<QStandardItem *> &items);

    QStandardItem *headerItem(int column) const;
    QList<QStandardItem *> headerItems() const;
    void setHeaderItem(int column, QStandardItem *item);
    void setHeaderItems(const QList<QStandardItem *> &items);
    void setHeaderLabels(const QStringList &labels);
    inline void setHeaderLabel(const QString &label);

    QStandardItem *currentItem() const;
    int currentColumn() const;
    void setCurrentItem(QStandardItem *item);
    void setCurrentItem(QStandardItem *item, QItemSelectionModel::SelectionFlags command);

    QStandardItem *itemAt(const QPoint &p) const;
    inline QStandardItem *itemAt(int x, int y) const;
    QRect visualItemRect(const QStandardItem *item) const;

    int sortColumn() const;
    void sortItems(int column, Qt::SortOrder order);

    void editItem(QStandardItem *item);
    void openPersistentEditor(QStandardItem *item);
    void closePersistentEditor(QStandardItem *item);

    QWidget *itemWidget(QStandardItem *item) const;
    void setItemWidget(QStandardItem *item, QWidget *widget);
    inline void removeItemWidget(QStandardItem *item);

    bool isItemSelected(const QStandardItem *item) const;
    void setItemSelected(const QStandardItem *item, bool select);
    QList<QStandardItem *> selectedItems() const;
    QList<QStandardItem *> findItems(const QString &text, Qt::MatchFlags flags,
                                     int column = 0) const;

    bool isItemHidden(const QStandardItem *item) const;
    void setItemHidden(const QStandardItem *item, bool hide);

    bool isItemExpanded(const QStandardItem *item) const;
    void setItemExpanded(const QStandardItem *item, bool expand);

    bool isFirstItemColumnSpanned(const QStandardItem *item) const;
    void setFirstItemColumnSpanned(const QStandardItem *item, bool span);

    QStandardItem *itemAbove(const QStandardItem *item) const;
    QStandardItem *itemBelow(const QStandardItem *item) const;

    void setSelectionModel(QItemSelectionModel *selectionModel) Q_DECL_OVERRIDE;

    QStandardItemModel *sourceModel() const;

    QSortFilterProxyModel *filterModel() const;
    void setFilterModel(QSortFilterProxyModel *model);

Q_SIGNALS:
    void itemPressed(QStandardItem *item);
    void itemClicked(QStandardItem *item);
    void itemDoubleClicked(QStandardItem *item);
    void itemActivated(QStandardItem *item);
    void itemEntered(QStandardItem *item);
    void itemChanged(QStandardItem *item);
    void itemExpanded(QStandardItem *item);
    void itemCollapsed(QStandardItem *item);
    void currentItemChanged(QStandardItem *current, QStandardItem *previous);
    void itemSelectionChanged();

public Q_SLOTS:
    void scrollToItem(const QStandardItem *item,
                      QAbstractItemView::ScrollHint hint = EnsureVisible);
    void expandItem(const QStandardItem *item);
    void collapseItem(const QStandardItem *item);
    void clear();
    void clearContents();

    void clearChildren(QStandardItem *item);
    void expandItem(const QStandardItem *item, bool expanded, int deep = -1);

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    virtual QStringList mimeTypes() const;
    virtual QMimeData *mimeData(const QList<QStandardItem *> &items) const;
    virtual bool dropMimeData(QStandardItem *parent, int row, int column,
                              const QMimeData *data, Qt::DropAction action);
    virtual Qt::DropActions supportedDropActions() const;
    QList<QStandardItem *> items(const QMimeData *data) const;

    QModelIndex indexFromItem(QStandardItem *item) const;
    QStandardItem *itemFromIndex(const QModelIndex &index) const;

private:
    void setModel(QAbstractItemModel *model) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(JTreeView)
    J_DECLARE_PRIVATE(JTreeView)
    friend class JTreeModel;
    friend class JTreeViewItem;
};

// for JTreeViewItem

inline JTreeView *JTreeViewItem::view() const
{
    QStandardItemModel *model = this->model();
    if (model) {
        return qobject_cast<JTreeView *>(model->QObject::parent());
    } else {
        return nullptr;
    }
}

inline void JTreeViewItem::setSelected(bool aselect)
{ JTreeView *view = this->view(); if (view) view->setItemSelected(this, aselect); }

inline bool JTreeViewItem::isSelected() const
{ JTreeView *view = this->view(); return (view ? view->isItemSelected(this) : false); }

inline void JTreeViewItem::setHidden(bool ahide)
{ JTreeView *view = this->view(); if (view) view->setItemHidden(this, ahide); }

inline bool JTreeViewItem::isHidden() const
{ JTreeView *view = this->view(); return (view ? view->isItemHidden(this) : false); }

inline void JTreeViewItem::setExpanded(bool aexpand)
{ JTreeView *view = this->view(); if (view) view->setItemExpanded(this, aexpand); }

inline bool JTreeViewItem::isExpanded() const
{ JTreeView *view = this->view(); return (view ? view->isItemExpanded(this) : false); }

inline void JTreeViewItem::setFirstColumnSpanned(bool aspan)
{ JTreeView *view = this->view(); if (view) view->setFirstItemColumnSpanned(this, aspan); }

inline bool JTreeViewItem::isFirstColumnSpanned() const
{ JTreeView *view = this->view(); return (view ? view->isFirstItemColumnSpanned(this) : false); }

inline void JTreeViewItem::setDisabled(bool disabled)
{ setFlags(disabled ? (flags() & ~Qt::ItemIsEnabled) : flags() | Qt::ItemIsEnabled); }

inline bool JTreeViewItem::isDisabled() const
{ return !(flags() & Qt::ItemIsEnabled); }

// for JTreeView

inline void JTreeView::removeItemWidget(QStandardItem *item)
{ setItemWidget(item, nullptr); }

inline QStandardItem *JTreeView::itemAt(int ax, int ay) const
{ return itemAt(QPoint(ax, ay)); }

inline void JTreeView::setHeaderLabel(const QString &alabel)
{ setHeaderLabels(QStringList(alabel)); }

#endif // JTREEVIEW_H
