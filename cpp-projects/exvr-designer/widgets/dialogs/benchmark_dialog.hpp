
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QDialog>
#include <QTableWidget>
#include <QAbstractTableModel>

namespace tool::ex {


//class TorrentViewDelegate : public QItemDelegate
//{
//    Q_OBJECT
//public:
//    inline TorrentViewDelegate(MainWindow *mainWindow) : QItemDelegate(mainWindow) {}

//    inline void paint(QPainter *painter, const QStyleOptionViewItem &option,
//                      const QModelIndex &index ) const
//    {
//        if (index.column() != 2) {
//            QItemDelegate::paint(painter, option, index);
//            return;
//        }

//        // Set up a QStyleOptionProgressBar to precisely mimic the
//        // environment of a progress bar.
//        QStyleOptionProgressBar progressBarOption;
//        progressBarOption.state = QStyle::State_Enabled;
//        progressBarOption.direction = QApplication::layoutDirection();
//        progressBarOption.rect = option.rect;
//        progressBarOption.fontMetrics = QApplication::fontMetrics();
//        progressBarOption.minimum = 0;
//        progressBarOption.maximum = 100;
//        progressBarOption.textAlignment = Qt::AlignCenter;
//        progressBarOption.textVisible = true;

//        // Set the progress and text values of the style option.
//        int progress = qobject_cast<MainWindow *>(parent())->clientForRow(index.row())->progress();
//        progressBarOption.progress = progress < 0 ? 0 : progress;
//        progressBarOption.text = QString().sprintf("%d%%", progressBarOption.progress);

//        // Draw the progress bar onto the view.
//        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);
//    }
//};

//void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
//                     const QModelIndex &index) const
//{
//    QStyleOptionViewItem opt(option);
//    initStyleOption(&opt, index);

//    const QPalette &palette(opt.palette);
//    const QRect &rect(opt.rect);
//    const QRect &contentRect(rect.adjusted(m_ptr->margins.left(),
//                                           m_ptr->margins.top(),
//                                           -m_ptr->margins.right(),
//                                           -m_ptr->margins.bottom()));
//    const bool lastIndex = (index.model()->rowCount() - 1) == index.row();
//    const bool hasIcon = !opt.icon.isNull();
//    const int bottomEdge = rect.bottom();
//    QFont f(opt.font);

//    f.setPointSize(m_ptr->timestampFontPointSize(opt.font));

//    painter->save();
//    painter->setClipping(true);
//    painter->setClipRect(rect);
//    painter->setFont(opt.font);

//    // Draw background
//    painter->fillRect(rect, opt.state & QStyle::State_Selected ?
//                                                               palette.highlight().color() :
//                                                               palette.light().color());

//    // Draw bottom line
//    painter->setPen(lastIndex ? palette.dark().color()
//                              : palette.mid().color());
//    painter->drawLine(lastIndex ? rect.left() : m_ptr->margins.left(),
//                      bottomEdge, rect.right(), bottomEdge);

//    // Draw message icon
//    if (hasIcon)
//        painter->drawPixmap(contentRect.left(), contentRect.top(),
//                            opt.icon.pixmap(m_ptr->iconSize));

//    // Draw timestamp
//    QRect timeStampRect(m_ptr->timestampBox(opt, index));

//    timeStampRect.moveTo(m_ptr->margins.left() + m_ptr->iconSize.width()
//                             + m_ptr->spacingHorizontal, contentRect.top());

//    painter->setFont(f);
//    painter->setPen(palette.text().color());
//    painter->drawText(timeStampRect, Qt::TextSingleLine,
//                      index.data(Qt::UserRole).toString());

//    // Draw message text
//    QRect messageRect(m_ptr->messageBox(opt));

//    messageRect.moveTo(timeStampRect.left(), timeStampRect.bottom()
//                                                 + m_ptr->spacingVertical);

//    painter->setFont(opt.font);
//    painter->setPen(palette.windowText().color());
//    painter->drawText(messageRect, Qt::TextSingleLine, opt.text);

//    painter->restore();
//}

class Table : public QAbstractTableModel{

public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    void update();

    std::vector<std::tuple<std::string_view, std::int64_t, size_t>> times;
    //int headerData(int section, Qt::Orientation orientation, int role) const;


    std::unordered_map<std::string_view, std::tuple<QString, std::int64_t, bool, size_t>> elements;
    std::vector<std::string_view> order;

//    std::vector<
};

class BenchmarkDialog : public QDialog{

    Q_OBJECT

public :

    BenchmarkDialog();


public slots:

    void update();

    void show_dialog(){
        show();
        raise();
    }

private:

    QTableView *view = nullptr;
    Table *model = nullptr;

    QCheckBox *sort = nullptr;
};
}
