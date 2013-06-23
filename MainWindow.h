#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QUndoStack>

#include "ParserXML.h"
#include "ImageWindow.h"
#include "AnimationWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

    QString getButtonFlatStyle();
    QString getDockWidgetStyle();
    QString getTabBarStyle();
    QString getToolBoxStyle();

    void createFileMenu();
    void createEditMenu();
    void createImageMenu();
    void createWindowMenu();
    void createHelpMenu();
    void createShapesDock();
    void createLightsDock();
    void createCameraDock();
    void createScreenDock();
    void createDockIcon(QPushButton* button, const QString& iconFileName,
                        const QString& title);
    void createToolDock();
    void createAnimationDock();

    void closeEvent(QCloseEvent* event);
    bool aboutToClear();

    QWidget* createNewTab(QString fileName = "", QVector<int> screen = QVector<int>(), RayTracer::Resolution resolution = RayTracer::high, const Camera& camera = Camera(), bool openedFile = true);
    ImageWindow* currentTab();

private:
    // Tabs
    QTabWidget* _tabs;

    // File menu actions
    QAction* _newFileAction;
    QAction* _openFileAction;
    QAction* _saveFileAction;
    QAction* _saveAsFileAction;
    QAction* _exportAction;
    QAction* _closeFileAction;
    QAction* _closeAllFileAction;
    QAction* _closeExceptFileAction;
    QAction* _quitAction;

    // Edit menu actions
    QAction* _undoAction;
    QAction* _redoAction;
    QAction* _settingsAction;

    // Image menu actions
    QAction* _addShapeAction;
    QAction* _addLightAction;
    QAction* _setCameraAction;
    QAction* _setScreenAction;
    QAction* _generateAction;
    QAction* _makeFilmAction;

    // Window menu actions
    QAction* _viewShapesDockAction;
    QAction* _viewLightsDockAction;
    QAction* _viewCameraDockAction;
    QAction* _viewScreenDockAction;
    QAction* _viewAnimationDockAction;
    QAction* _restoreDefaultDocksAction;

    // Help menu actions
    QAction* _indexAction;
    QAction* _aboutAction;

    // Shapes dock widget
    QDockWidget* _shapesDock;
    QWidget* _shapesWidget;
    QStringListModel* _shapesListModel;
    QListView* _shapesListView;
    QPushButton* _shapeUpdateButton;
    QPushButton* _shapeRemoveButton;

    // Lights dock widget
    QDockWidget* _lightsDock;
    QWidget* _lightsWidget;
    QStringListModel* _lightsListModel;
    QListView* _lightsListView;
    QPushButton* _lightUpdateButton;
    QPushButton* _lightRemoveButton;

    // Camera dock widget
    QDockWidget* _cameraDock;
    QWidget* _cameraWidget;
    QTextEdit* _cameraLineEdit;
    QPushButton* _updateCameraButton;

    // Screen dock widget
    QDockWidget* _screenDock;
    QWidget* _screenWidget;
    QTextEdit* _screenLineEdit;
    QPushButton* _updateScreenButton;

    // Tools dock widget
    QDockWidget* _toolDock;
    QWidget* _toolWidget;
    QPushButton* _newFileButton;
    QPushButton* _openFileButton;
    QPushButton* _addShapeButton;
    QPushButton* _addLightButton;
    QPushButton* _exportButton;
    QPushButton* _generateButton;

    // Animation dock widget
    QDockWidget* _animationDock;
    AnimationWidget* _animationWidget;

    // Status bar
    QStatusBar* _statusBar;

signals:
    void changeShapes(QStringList);
    void changeLights(QStringList);
    void changeCamera(QStringList);
    void changeScreen(QStringList);
    void enableButtons(bool b);
    void isSaved(bool b);

public slots:
    void newData();
    void open();
    void save();
    void saveAs();
    void exportImage();
    void closeTab();
    void closeAllTab();
    void closeExceptTab();
    void quitProgram();
    void undo();
    void redo();
    void settings();
    void addShape();
    void addLight();
    void generate();
    void makeFilm();
    void restoreDefaultDocks();
    void index();
    void about();

    void updateShapesList(QStringList shapesList);
    void updateLightsList(QStringList lightsList);
    void updateCameraList(QStringList cameraList);
    void updateScreenList(QStringList screenList);

    void updateShape();
    void removeShape();
    void updateLight();
    void removeLight();
    void setCamera();
    void setScreen();

    void changeTab(int indexTab);

    void enableSceneButtons(bool b);
    void setTabTitle(bool b);
};

#endif // MAINWINDOW_H
