/********************************************************************************
** Form generated from reading ui file 'PluginWidgetBase.ui'
**
** Created: Wed Jul 22 11:37:21 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef PLUGINWIDGETBASE_H
#define PLUGINWIDGETBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QTextEdit>
#include <QtGui/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_PluginWidgetBase
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QTextEdit *textDescription;
    QTreeWidget *treePlugins;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PluginWidgetBase)
    {
    if (PluginWidgetBase->objectName().isEmpty())
        PluginWidgetBase->setObjectName(QString::fromUtf8("PluginWidgetBase"));
    PluginWidgetBase->resize(400, 400);
    PluginWidgetBase->setMinimumSize(QSize(400, 400));
    PluginWidgetBase->setSizeGripEnabled(true);
    gridLayout_2 = new QGridLayout(PluginWidgetBase);
    gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
    groupBox = new QGroupBox(PluginWidgetBase);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    gridLayout = new QGridLayout(groupBox);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    textDescription = new QTextEdit(groupBox);
    textDescription->setObjectName(QString::fromUtf8("textDescription"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(textDescription->sizePolicy().hasHeightForWidth());
    textDescription->setSizePolicy(sizePolicy);
    textDescription->setMinimumSize(QSize(0, 50));
    textDescription->setMaximumSize(QSize(16777215, 50));
    textDescription->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textDescription->setReadOnly(true);

    gridLayout->addWidget(textDescription, 1, 0, 1, 1);

    treePlugins = new QTreeWidget(groupBox);
    treePlugins->setObjectName(QString::fromUtf8("treePlugins"));
    treePlugins->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    treePlugins->setAlternatingRowColors(true);
    treePlugins->setRootIsDecorated(false);
    treePlugins->setHeaderHidden(true);

    gridLayout->addWidget(treePlugins, 0, 0, 1, 1);


    gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

    buttonBox = new QDialogButtonBox(PluginWidgetBase);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Vertical);
    buttonBox->setStandardButtons(QDialogButtonBox::Close);

    gridLayout_2->addWidget(buttonBox, 0, 1, 1, 1);


    retranslateUi(PluginWidgetBase);
    QObject::connect(buttonBox, SIGNAL(accepted()), PluginWidgetBase, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), PluginWidgetBase, SLOT(reject()));

    QMetaObject::connectSlotsByName(PluginWidgetBase);
    } // setupUi

    void retranslateUi(QDialog *PluginWidgetBase)
    {
    PluginWidgetBase->setWindowTitle(QApplication::translate("PluginWidgetBase", "Plugins", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("PluginWidgetBase", "Plugins", 0, QApplication::UnicodeUTF8));
    treePlugins->headerItem()->setText(0, QApplication::translate("PluginWidgetBase", "1", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(PluginWidgetBase);
    } // retranslateUi

};

namespace Ui {
    class PluginWidgetBase: public Ui_PluginWidgetBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // PLUGINWIDGETBASE_H
