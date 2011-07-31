/********************************************************************************
** Form generated from reading ui file 'MainWindowBase.ui'
**
** Created: Thu Jul 23 09:52:06 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef MAINWINDOWBASE_H
#define MAINWINDOWBASE_H

#include <PropertiesEditor/PropertiesEditor.h>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowBase
{
public:
    QAction *action_New;
    QAction *action_Open;
    QAction *action_Save;
    QAction *action_Save_As;
    QAction *action_Quit;
    QAction *action_About;
    QAction *actionAbout_Qt;
    QAction *actionRun;
    QAction *actionLkjsd;
    QAction *action_PluginManager;
    QAction *actionEnableLiveView;
    QAction *action_VirtualMidiPort;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menuRecent_Files;
    QMenu *menuHelp;
    QMenu *menuView;
    QMenu *menuInputDevice;
    QMenu *menuMidiOut;
    QMenu *menu_Plugins;
    QToolBar *toolBar;
    QDockWidget *propertiesDock;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout;
    MidiMe::PropertiesEditor *properties;

    void setupUi(QMainWindow *MainWindowBase)
    {
    if (MainWindowBase->objectName().isEmpty())
        MainWindowBase->setObjectName(QString::fromUtf8("MainWindowBase"));
    MainWindowBase->resize(809, 600);
    MainWindowBase->setMinimumSize(QSize(150, 150));
    MainWindowBase->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks|QMainWindow::VerticalTabs);
    action_New = new QAction(MainWindowBase);
    action_New->setObjectName(QString::fromUtf8("action_New"));
    action_Open = new QAction(MainWindowBase);
    action_Open->setObjectName(QString::fromUtf8("action_Open"));
    action_Save = new QAction(MainWindowBase);
    action_Save->setObjectName(QString::fromUtf8("action_Save"));
    action_Save_As = new QAction(MainWindowBase);
    action_Save_As->setObjectName(QString::fromUtf8("action_Save_As"));
    action_Quit = new QAction(MainWindowBase);
    action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
    action_Quit->setMenuRole(QAction::QuitRole);
    action_About = new QAction(MainWindowBase);
    action_About->setObjectName(QString::fromUtf8("action_About"));
    action_About->setMenuRole(QAction::AboutRole);
    actionAbout_Qt = new QAction(MainWindowBase);
    actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
    actionAbout_Qt->setMenuRole(QAction::AboutQtRole);
    actionRun = new QAction(MainWindowBase);
    actionRun->setObjectName(QString::fromUtf8("actionRun"));
    actionRun->setCheckable(true);
    actionLkjsd = new QAction(MainWindowBase);
    actionLkjsd->setObjectName(QString::fromUtf8("actionLkjsd"));
    action_PluginManager = new QAction(MainWindowBase);
    action_PluginManager->setObjectName(QString::fromUtf8("action_PluginManager"));
    actionEnableLiveView = new QAction(MainWindowBase);
    actionEnableLiveView->setObjectName(QString::fromUtf8("actionEnableLiveView"));
    actionEnableLiveView->setCheckable(true);
    actionEnableLiveView->setChecked(true);
    action_VirtualMidiPort = new QAction(MainWindowBase);
    action_VirtualMidiPort->setObjectName(QString::fromUtf8("action_VirtualMidiPort"));
    centralwidget = new QWidget(MainWindowBase);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    MainWindowBase->setCentralWidget(centralwidget);
    menubar = new QMenuBar(MainWindowBase);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 809, 22));
    menu_File = new QMenu(menubar);
    menu_File->setObjectName(QString::fromUtf8("menu_File"));
    menuRecent_Files = new QMenu(menu_File);
    menuRecent_Files->setObjectName(QString::fromUtf8("menuRecent_Files"));
    menuHelp = new QMenu(menubar);
    menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
    menuView = new QMenu(menubar);
    menuView->setObjectName(QString::fromUtf8("menuView"));
    menuInputDevice = new QMenu(menuView);
    menuInputDevice->setObjectName(QString::fromUtf8("menuInputDevice"));
    menuMidiOut = new QMenu(menubar);
    menuMidiOut->setObjectName(QString::fromUtf8("menuMidiOut"));
    menu_Plugins = new QMenu(menubar);
    menu_Plugins->setObjectName(QString::fromUtf8("menu_Plugins"));
    MainWindowBase->setMenuBar(menubar);
    toolBar = new QToolBar(MainWindowBase);
    toolBar->setObjectName(QString::fromUtf8("toolBar"));
    MainWindowBase->addToolBar(Qt::TopToolBarArea, toolBar);
    propertiesDock = new QDockWidget(MainWindowBase);
    propertiesDock->setObjectName(QString::fromUtf8("propertiesDock"));
    propertiesDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    dockWidgetContents = new QWidget();
    dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
    gridLayout = new QGridLayout(dockWidgetContents);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    properties = new MidiMe::PropertiesEditor(dockWidgetContents);
    properties->setObjectName(QString::fromUtf8("properties"));

    gridLayout->addWidget(properties, 0, 0, 1, 1);

    propertiesDock->setWidget(dockWidgetContents);
    MainWindowBase->addDockWidget(static_cast<Qt::DockWidgetArea>(1), propertiesDock);

    menubar->addAction(menu_File->menuAction());
    menubar->addAction(menuView->menuAction());
    menubar->addAction(menuMidiOut->menuAction());
    menubar->addAction(menu_Plugins->menuAction());
    menubar->addAction(menuHelp->menuAction());
    menu_File->addAction(action_New);
    menu_File->addAction(action_Open);
    menu_File->addAction(menuRecent_Files->menuAction());
    menu_File->addSeparator();
    menu_File->addAction(action_Save);
    menu_File->addAction(action_Save_As);
    menu_File->addSeparator();
    menu_File->addAction(action_Quit);
    menuHelp->addAction(action_About);
    menuHelp->addAction(actionAbout_Qt);
    menuView->addAction(menuInputDevice->menuAction());
    menuMidiOut->addSeparator();
    menuMidiOut->addAction(action_VirtualMidiPort);
    menu_Plugins->addAction(action_PluginManager);
    menu_Plugins->addSeparator();
    toolBar->addAction(actionRun);
    toolBar->addAction(actionEnableLiveView);

    retranslateUi(MainWindowBase);
    QObject::connect(action_Quit, SIGNAL(triggered()), MainWindowBase, SLOT(close()));

    QMetaObject::connectSlotsByName(MainWindowBase);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowBase)
    {
    MainWindowBase->setWindowTitle(QApplication::translate("MainWindowBase", "Midi-Me", 0, QApplication::UnicodeUTF8));
    action_New->setText(QApplication::translate("MainWindowBase", "&New", 0, QApplication::UnicodeUTF8));
    action_Open->setText(QApplication::translate("MainWindowBase", "&Open...", 0, QApplication::UnicodeUTF8));
    action_Save->setText(QApplication::translate("MainWindowBase", "&Save", 0, QApplication::UnicodeUTF8));
    action_Save_As->setText(QApplication::translate("MainWindowBase", "Save &As...", 0, QApplication::UnicodeUTF8));
    action_Quit->setText(QApplication::translate("MainWindowBase", "&Quit", 0, QApplication::UnicodeUTF8));
    action_About->setText(QApplication::translate("MainWindowBase", "&About...", 0, QApplication::UnicodeUTF8));
    actionAbout_Qt->setText(QApplication::translate("MainWindowBase", "About &Qt...", 0, QApplication::UnicodeUTF8));
    actionRun->setText(QApplication::translate("MainWindowBase", "Run", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
    actionRun->setToolTip(QApplication::translate("MainWindowBase", "Run the OIS to midi converter", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP

    actionRun->setShortcut(QApplication::translate("MainWindowBase", "Space", 0, QApplication::UnicodeUTF8));
    actionLkjsd->setText(QApplication::translate("MainWindowBase", "lkjsd", 0, QApplication::UnicodeUTF8));
    action_PluginManager->setText(QApplication::translate("MainWindowBase", "Plugin &Manager...", 0, QApplication::UnicodeUTF8));
    actionEnableLiveView->setText(QApplication::translate("MainWindowBase", "Enable Live View", 0, QApplication::UnicodeUTF8));
    action_VirtualMidiPort->setText(QApplication::translate("MainWindowBase", "&Virtual Midi Port", 0, QApplication::UnicodeUTF8));
    menu_File->setTitle(QApplication::translate("MainWindowBase", "&File", 0, QApplication::UnicodeUTF8));
    menuRecent_Files->setTitle(QApplication::translate("MainWindowBase", "Recent Files", 0, QApplication::UnicodeUTF8));
    menuHelp->setTitle(QApplication::translate("MainWindowBase", "&Help", 0, QApplication::UnicodeUTF8));
    menuView->setTitle(QApplication::translate("MainWindowBase", "&View", 0, QApplication::UnicodeUTF8));
    menuInputDevice->setTitle(QApplication::translate("MainWindowBase", "InputDevice", 0, QApplication::UnicodeUTF8));
    menuMidiOut->setTitle(QApplication::translate("MainWindowBase", "&Midi-out", 0, QApplication::UnicodeUTF8));
    menu_Plugins->setTitle(QApplication::translate("MainWindowBase", "&Plugins", 0, QApplication::UnicodeUTF8));
    toolBar->setWindowTitle(QApplication::translate("MainWindowBase", "toolBar", 0, QApplication::UnicodeUTF8));
    propertiesDock->setWindowTitle(QApplication::translate("MainWindowBase", "Properties", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowBase: public Ui_MainWindowBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOWBASE_H
