
/*******************************************************************************
** exvr-designer                                                              **
** No license (to be defined)                                                 **
** Copyright (c) [2018] [Florian Lance][EPFL-LNCO]                            **
********************************************************************************/

#pragma once

// Qt
#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>

// local
#include "argument.hpp"

namespace tool::ex {

class GenUIItemDialog : public QDialog{

public:

    GenUIItemDialog(QString title);
    GenUIItemDialog(UiType type);

    bool show_dialog(QStringList othersParameters);

    void add_row(QString name, QWidget *w);
    void add_widget(QWidget *w);

    Arg generate_arg(UiElementKey key) const;
    QString name() const;

private:

    UiType m_type;

    const QString m_notEmptyStr {"(Parameter name must not be empty)"};
    const QString m_aldreayUsedStr {"(Parameter name is already used)"};

    QVBoxLayout *m_layout = nullptr;
    QLabel *m_laValid = nullptr;
    QLineEdit *m_leName = nullptr;
    QWidget *m_genW = nullptr;
};
}
