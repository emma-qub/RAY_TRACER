#include <string>
#include <vector>
#include <iostream>
#include <cmath>

#include "Vector3.h"
#include "MainWindow.h"
#include "NewFileWindow.h"
#include "AddShapeWindow.h"
#include "ImageWindow.h"
#include "MakeFilmWindow.h"

MainWindow::MainWindow() {
    createFileMenu();
    createEditMenu();
    createImageMenu();
    createWindowMenu();
    createHelpMenu();
    createShapesDock();
    createLightsDock();
    createToolDock();
    createCameraDock();
    createScreenDock();
    createAnimationDock();

    _tabs = new QTabWidget;
    _tabs->addTab(createNewTab(""), "Introduction");
    _tabs->setGeometry(QRect(100, 0, 1000, 900));
    connect(_tabs, SIGNAL(currentChanged(int)), this, SLOT(changeTab(int)));
    setCentralWidget(_tabs);

    connect(_viewShapesDockAction, SIGNAL(triggered(bool)), _shapesDock, SLOT(setVisible(bool)));
    connect(_shapesDock, SIGNAL(visibilityChanged(bool)), _viewShapesDockAction, SLOT(setChecked(bool)));

    connect(_viewLightsDockAction, SIGNAL(triggered(bool)), _lightsDock, SLOT(setVisible(bool)));
    connect(_lightsDock, SIGNAL(visibilityChanged(bool)), _viewLightsDockAction, SLOT(setChecked(bool)));

    connect(_viewCameraDockAction, SIGNAL(triggered(bool)), _cameraDock, SLOT(setVisible(bool)));
    connect(_cameraDock, SIGNAL(visibilityChanged(bool)), _viewCameraDockAction, SLOT(setChecked(bool)));

    connect(_viewScreenDockAction, SIGNAL(triggered(bool)), _screenDock, SLOT(setVisible(bool)));
    connect(_screenDock, SIGNAL(visibilityChanged(bool)), _viewScreenDockAction, SLOT(setChecked(bool)));

    connect(_viewAnimationDockAction, SIGNAL(triggered(bool)), _animationDock, SLOT(setVisible(bool)));
    connect(_animationDock, SIGNAL(visibilityChanged(bool)), _viewAnimationDockAction, SLOT(setChecked(bool)));

    connect(this, SIGNAL(isSaved(bool)), this, SLOT(setTabTitle(bool)));

    connect(this, SIGNAL(changeShapes(QStringList)), this, SLOT(updateShapesList(QStringList)));
    connect(this, SIGNAL(changeLights(QStringList)), this, SLOT(updateLightsList(QStringList)));
    connect(this, SIGNAL(changeCamera(QStringList)), this, SLOT(updateCameraList(QStringList)));
    connect(this, SIGNAL(changeScreen(QStringList)), this, SLOT(updateScreenList(QStringList)));

    connect(this, SIGNAL(enableButtons(bool)), this, SLOT(enableSceneButtons(bool)));

    _statusBar = statusBar();
    QLabel* defaultMessage = new QLabel("Ready");
    _statusBar->addWidget(defaultMessage);

    setWindowTitle("RayTracer Creator");
    setWindowState(Qt::WindowMaximized);
    enableSceneButtons(false);

    QString buttonFlatStyle = getButtonFlatStyle();
    QString dockWidgetStyle = getDockWidgetStyle();
    QString tabBarStyle = getTabBarStyle();
    setStyleSheet(buttonFlatStyle + dockWidgetStyle + tabBarStyle);
}

/****************
 * STYLE SHEETS *
 ****************/
QString MainWindow::getButtonFlatStyle() {
    QString buttonFlatStyle;
    buttonFlatStyle += "QPushButton:flat {";
    buttonFlatStyle += "    border: none;";
    buttonFlatStyle += "    margin: -5px;";
    buttonFlatStyle += "}";
    buttonFlatStyle += "QPushButton:flat:hover {";
    buttonFlatStyle += "    border: none;";
    buttonFlatStyle += "    background-color: #cccccc;";
    buttonFlatStyle += "}";
    buttonFlatStyle += "QPushButton:flat:pressed {";
    buttonFlatStyle += "    border: none;";
    buttonFlatStyle += "    padding: 1px -1px -1px 1px;";
    buttonFlatStyle += "}";

    return buttonFlatStyle;
}

QString MainWindow::getTabBarStyle() {
    QString tabBarStyle;
    tabBarStyle += "QTabBar::scroller {";
    tabBarStyle += "    width: 20px;";
    tabBarStyle += "}";

    tabBarStyle += "QTabBar QToolButton::right-arrow {";
    tabBarStyle += "    image: url(\"../RayTracer/icones/rightarrow.png\");";
    tabBarStyle += "}";

    tabBarStyle += "QTabBar QToolButton::left-arrow {";
    tabBarStyle += "    image: url(\"../RayTracer/icones/leftarrow.png\");";
    tabBarStyle += "}";

    return tabBarStyle;
}

QString MainWindow::getDockWidgetStyle() {
    QString dockWidgetStyle = "";
    dockWidgetStyle += "QDockWidget { ";
    dockWidgetStyle += "    font-size: 12pt;";
    dockWidgetStyle += "    border: solid 3px black;";
    dockWidgetStyle += "    color: #eeeeee;";
    dockWidgetStyle += "}";

    QString dockWidgetTitleStyle;
    dockWidgetTitleStyle += "QDockWidget::title {";
    dockWidgetTitleStyle += "    text-align: center;";
    dockWidgetTitleStyle += "    padding: 3px;";
    dockWidgetTitleStyle += "    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,";
    dockWidgetTitleStyle += "                stop: 0 #6a6a6a, stop: 0.4 #444444,";
    dockWidgetTitleStyle += "                stop: 0.5 #272727, stop: 1.0 #4a4a4a);";
    dockWidgetTitleStyle += "}";

    QString dockWidgetButtonsStyle;
    dockWidgetButtonsStyle += "QDockWidget {";
    dockWidgetButtonsStyle += "    titlebar-close-icon: url(\"../RayTracer/icones/closeIcon.png\");";
    dockWidgetButtonsStyle += "    titlebar-normal-icon: url(\"../RayTracer/icones/reduceIcon.png\");";
    dockWidgetButtonsStyle += "}";
    dockWidgetButtonsStyle += "QDockWidget::close-button, QDockWidget::float-button {";
    dockWidgetButtonsStyle += "    padding: 0px;";
    dockWidgetButtonsStyle += "}";
    dockWidgetButtonsStyle += "QDockWidget::close-button:pressed, QDockWidget::float-button:pressed {";
    dockWidgetButtonsStyle += "    padding: 1px -1px -1px 1px;";
    dockWidgetButtonsStyle += "}";

    QString style = dockWidgetStyle + dockWidgetTitleStyle + dockWidgetButtonsStyle;
    return style;
}

/********************
 * MENU AND ACTIONS *
 ********************/
void MainWindow::createFileMenu() {
    QMenu* fileMenu = menuBar()->addMenu("&File");

    _newFileAction = fileMenu->addAction("&New...");
    connect(_newFileAction, SIGNAL(triggered()), this, SLOT(newData()));
    _newFileAction->setShortcut(QKeySequence::New);
    _newFileAction->setIcon(QIcon("../RayTracer/icones/newFile.png"));
    fileMenu->addSeparator();

    _openFileAction = fileMenu->addAction("&Open...");
    connect(_openFileAction, SIGNAL(triggered()), this, SLOT(open()));
    _openFileAction->setShortcut(QKeySequence::Open);
    _openFileAction->setIcon(QIcon("../RayTracer/icones/openFile.png"));

    fileMenu->addSeparator();

    _saveFileAction = fileMenu->addAction("&Save...");
    connect(_saveFileAction, SIGNAL(triggered()), this, SLOT(save()));
    _saveFileAction->setShortcut(QKeySequence::Save);
    _saveFileAction->setIcon(QIcon("../RayTracer/icones/saveFile.png"));

    _saveAsFileAction = fileMenu->addAction("Save &as...");
    connect(_saveAsFileAction, SIGNAL(triggered()), this, SLOT(saveAs()));
    _saveAsFileAction->setIcon(QIcon("../RayTracer/icones/saveAsFile.png"));
    _saveAsFileAction->setShortcut(QKeySequence::SaveAs);

    _exportAction = fileMenu->addAction("E&xport...");
    connect(_exportAction, SIGNAL(triggered()), this, SLOT(exportImage()));
    _exportAction->setShortcut(QKeySequence("Ctrl+Shift+Alt+S"));

    fileMenu->addSeparator();

    _closeFileAction = fileMenu->addAction("&Close");
    connect(_closeFileAction, SIGNAL(triggered()), this, SLOT(closeTab()));
    _closeFileAction->setShortcut(QKeySequence::Close);

    _closeAllFileAction = fileMenu->addAction("C&lose all");
    connect(_closeAllFileAction, SIGNAL(triggered()), this, SLOT(closeAllTab()));
    _closeAllFileAction->setShortcut(QKeySequence("Ctrl+Shift+W"));

    _closeExceptFileAction = fileMenu->addAction("Close all except");
    connect(_closeExceptFileAction, SIGNAL(triggered()), this, SLOT(closeExceptTab()));

    fileMenu->addSeparator();

    _quitAction = fileMenu->addAction("&Quit");
    connect(_quitAction, SIGNAL(triggered()), this, SLOT(quitProgram()));
    _quitAction->setShortcut(QKeySequence::Quit);
}

void MainWindow::createEditMenu() {
    QMenu* editMenu = menuBar()->addMenu("&Edit");

    _undoAction = editMenu->addAction("&Undo");
    connect(_undoAction, SIGNAL(triggered()), this, SLOT(undo()));
    _undoAction->setShortcut(QKeySequence::Undo);

    _redoAction = editMenu->addAction("&Redo");
    connect(_redoAction, SIGNAL(triggered()), this, SLOT(redo()));
    _redoAction->setShortcut(QKeySequence::Redo);

    editMenu->addSeparator();

    _settingsAction = editMenu->addAction("&Preferences...");
    _settingsAction->setShortcut(QKeySequence::Preferences);
    connect(_settingsAction, SIGNAL(triggered()), this, SLOT(settings()));
}

void MainWindow::createImageMenu() {
    QMenu* imageMenu = menuBar()->addMenu("&Image");

    _addShapeAction = imageMenu->addAction("Add &shape...");
    connect(_addShapeAction, SIGNAL(triggered()), this, SLOT(addShape()));
    _addShapeAction->setIcon(QIcon("../RayTracer/icones/newShapeColoredIco.png"));
    _addShapeAction->setShortcut(QKeySequence("Alt+Shift+S"));

    _addLightAction = imageMenu->addAction("Add &light...");
    connect(_addLightAction, SIGNAL(triggered()), this, SLOT(addLight()));
    _addLightAction->setIcon(QIcon("../RayTracer/icones/newLightColoredIco.png"));
    _addLightAction->setShortcut(QKeySequence("Alt+Shift+L"));

    imageMenu->addSeparator();

    _setCameraAction = imageMenu->addAction("Set &camera...");
    connect(_setCameraAction, SIGNAL(triggered()), this, SLOT(setCamera()));
    _setCameraAction->setShortcut(QKeySequence("Alt+Shift+C"));

    imageMenu->addSeparator();

    _setScreenAction = imageMenu->addAction("Set &screen parameters...");
    connect(_setScreenAction, SIGNAL(triggered()), this, SLOT(setScreen()));
    _setScreenAction->setShortcut(QKeySequence("Alt+Shift+E"));

    imageMenu->addSeparator();

    _generateAction = imageMenu->addAction("&Generate");
    connect(_generateAction, SIGNAL(triggered()), this, SLOT(generate()));
    _generateAction->setIcon(QIcon("../RayTracer/icones/buildImage.png"));
    _generateAction->setShortcut(QKeySequence("Ctrl+B"));

    _makeFilmAction = imageMenu->addAction("&Make film...");
    connect(_makeFilmAction, SIGNAL(triggered()), this, SLOT(makeFilm()));
    _makeFilmAction->setShortcut(QKeySequence("Ctrl+M"));

}

void MainWindow::createWindowMenu() {
    QMenu* windowMenu = menuBar()->addMenu("&Window");

    _viewShapesDockAction = windowMenu->addAction("Display &shapes information");
    _viewShapesDockAction->setCheckable(true);
    _viewShapesDockAction->setChecked(true);

    _viewLightsDockAction = windowMenu->addAction("Display &lights information");
    _viewLightsDockAction->setCheckable(true);
    _viewLightsDockAction->setChecked(true);

    _viewCameraDockAction = windowMenu->addAction("Display &camera information");
    _viewCameraDockAction->setCheckable(true);
    _viewCameraDockAction->setChecked(true);

    _viewScreenDockAction = windowMenu->addAction("Display scr&een information");
    _viewScreenDockAction->setCheckable(true);
    _viewScreenDockAction->setChecked(true);

    _viewAnimationDockAction = windowMenu->addAction("&Animation");
    _viewAnimationDockAction->setIcon(QIcon("../RayTracer/icones/animation.png"));
    _viewAnimationDockAction->setCheckable(true);
    _viewAnimationDockAction->setChecked(false);

    windowMenu->addSeparator();

    _restoreDefaultDocksAction = windowMenu->addAction("&Restore default configuration");
    connect(_restoreDefaultDocksAction, SIGNAL(triggered()), this, SLOT(restoreDefaultDocks()));
}

void MainWindow::createHelpMenu() {
    QMenu* helpMenu = menuBar()->addMenu("&Help");

    _indexAction = helpMenu->addAction("&Index");
    connect(_indexAction, SIGNAL(triggered()), this, SLOT(index()));
    _indexAction->setShortcut(QKeySequence::HelpContents);

    helpMenu->addSeparator();

    _aboutAction = helpMenu->addAction("&About RayTracer Creator...");
    connect(_aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

/*********
 * DOCKS *
 *********/
void MainWindow::createShapesDock() {
    _shapesWidget = new QWidget;
    _shapesListModel = new QStringListModel;
    _shapesListView = new QListView;
    _shapesListView->setModel(_shapesListModel);
    _shapeUpdateButton = new QPushButton("Update", this);
    connect(_shapeUpdateButton, SIGNAL(clicked()), this, SLOT(updateShape()));
    _shapeRemoveButton = new QPushButton("Remove", this);
    connect(_shapeRemoveButton, SIGNAL(clicked()), this, SLOT(removeShape()));
    QHBoxLayout* shapesButtonLayout = new QHBoxLayout;
    shapesButtonLayout->addWidget(_shapeUpdateButton);
    shapesButtonLayout->addWidget(_shapeRemoveButton);
    QVBoxLayout* shapesLayout = new QVBoxLayout;
    shapesLayout->addWidget(_shapesListView);
    shapesLayout->addLayout(shapesButtonLayout);
    _shapesWidget->setLayout(shapesLayout);

    _shapesDock = new QDockWidget("Shapes", this);
    _shapesDock->setFixedWidth(200);
    addDockWidget(Qt::RightDockWidgetArea, _shapesDock);
    _shapesDock->setWidget(_shapesWidget);
    _shapesDock->setAllowedAreas(Qt::RightDockWidgetArea);
}

void MainWindow::createLightsDock() {
    _lightsWidget = new QWidget;
    _lightsListModel = new QStringListModel;
    _lightsListView = new QListView;
    _lightsListView->setModel(_lightsListModel);
    _lightUpdateButton = new QPushButton("Update", this);
    connect(_lightUpdateButton, SIGNAL(clicked()), this, SLOT(updateLight()));
    _lightRemoveButton = new QPushButton("Remove", this);
    connect(_lightRemoveButton, SIGNAL(clicked()), this, SLOT(removeLight()));
    QHBoxLayout* lightsButtonLayout = new QHBoxLayout;
    lightsButtonLayout->addWidget(_lightUpdateButton);
    lightsButtonLayout->addWidget(_lightRemoveButton);
    QVBoxLayout* lightsLayout = new QVBoxLayout;
    lightsLayout->addWidget(_lightsListView);
    lightsLayout->addLayout(lightsButtonLayout);
    _lightsWidget->setLayout(lightsLayout);

    _lightsDock = new QDockWidget("Lights", this);
    _lightsDock->setFixedWidth(200);
    addDockWidget(Qt::RightDockWidgetArea, _lightsDock);
    _lightsDock->setWidget(_lightsWidget);
    _lightsDock->setAllowedAreas(Qt::RightDockWidgetArea);
}

void MainWindow::createCameraDock() {
    _cameraWidget = new QWidget;
    _cameraWidget->setFixedSize(200, 200);
    _cameraLineEdit = new QTextEdit;
    _cameraLineEdit->setReadOnly(true);
    updateCameraList(QStringList());
    _updateCameraButton = new QPushButton("Update", this);
    _updateCameraButton->setFixedWidth(100);
    connect(_updateCameraButton, SIGNAL(clicked()), this, SLOT(setCamera()));

    QVBoxLayout* cameraLayout = new QVBoxLayout;
    cameraLayout->setAlignment(Qt::AlignTop);
    cameraLayout->addWidget(_cameraLineEdit);
    cameraLayout->addWidget(_updateCameraButton, 0, Qt::AlignCenter);
    _cameraWidget->setLayout(cameraLayout);

    _cameraDock = new QDockWidget("Camera", this);
    addDockWidget(Qt::RightDockWidgetArea, _cameraDock);
    _cameraDock->setWidget(_cameraWidget);
    _cameraDock->setAllowedAreas(Qt::RightDockWidgetArea);
}

void MainWindow::createScreenDock() {
    _screenWidget = new QWidget;
    _screenWidget->setFixedSize(200, 170);
    _screenLineEdit = new QTextEdit;
    _screenLineEdit->setReadOnly(true);
    updateScreenList(QStringList());
    _updateScreenButton = new QPushButton("Update");
    _updateScreenButton->setFixedWidth(100);
    connect(_updateScreenButton, SIGNAL(clicked()), this, SLOT(setScreen()));

    QVBoxLayout* screenLayout = new QVBoxLayout;
    screenLayout->setAlignment(Qt::AlignTop);
    screenLayout->addWidget(_screenLineEdit);
    screenLayout->addWidget(_updateScreenButton, 0, Qt::AlignCenter);
    _screenWidget->setLayout(screenLayout);

    _screenDock = new QDockWidget("Screen", this);
    addDockWidget(Qt::RightDockWidgetArea, _screenDock);
    _screenDock->setWidget(_screenWidget);
    _screenDock->setAllowedAreas(Qt::RightDockWidgetArea);
}

void MainWindow::createDockIcon(QPushButton* button, const QString& iconFileName, const QString& title) {
    QPixmap icon(iconFileName);
    QPainter painter;
    painter.begin(&icon);
    QRect titleZone(QPoint(0, 3*icon.height()/4),
                    QPoint(icon.width(), icon.height()));
    painter.setPen(QPen(Qt::white));
    painter.setFont(QFont("", 9, 50));
    painter.drawText(titleZone, Qt::AlignCenter, title);

    button->setIconSize(QSize(60, 60));
    button->setFlat(true);
    button->setFixedSize(60, 60);
    button->setIcon(QIcon(icon));
}

void MainWindow::createToolDock() {
    _toolWidget = new QWidget(this);
    _toolWidget->setFixedWidth(75);

    _newFileButton = new QPushButton(this);
    createDockIcon(_newFileButton, "../RayTracer/icones/newFileDock.png", "New");
    connect(_newFileButton, SIGNAL(clicked()), this, SLOT(newData()));

    _openFileButton = new QPushButton;
    createDockIcon(_openFileButton, "../RayTracer/icones/openFileDock.png", "Open");
    connect(_openFileButton, SIGNAL(clicked()), this, SLOT(open()));

    _exportButton = new QPushButton;
    createDockIcon(_exportButton, "../RayTracer/icones/exportDock.png", "Export");
    connect(_exportButton, SIGNAL(clicked()), this, SLOT(exportImage()));

    _addShapeButton = new QPushButton;
    createDockIcon(_addShapeButton, "../RayTracer/icones/addShapeDock.png", "Shape");
    connect(_addShapeButton, SIGNAL(clicked()), this, SLOT(addShape()));

    _addLightButton = new QPushButton;
    createDockIcon(_addLightButton, "../RayTracer/icones/addLightDock.png", "Light");
    connect(_addLightButton, SIGNAL(clicked()), this, SLOT(addLight()));

    _generateButton = new QPushButton;
    createDockIcon(_generateButton, "../RayTracer/icones/generateDock.png", "Run");
    connect(_generateButton, SIGNAL(clicked()), this, SLOT(generate()));

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(_newFileButton);
    mainLayout->addWidget(_openFileButton);
    mainLayout->addWidget(_exportButton);
    mainLayout->addWidget(_addShapeButton);
    mainLayout->addWidget(_addLightButton);
    mainLayout->addWidget(_generateButton);
    mainLayout->setAlignment(Qt::AlignTop);

    _toolWidget->setLayout(mainLayout);

    QString toolBoxStyle;
    toolBoxStyle += "background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,";
    toolBoxStyle += "                stop: 0 #4a4a4a, stop: 1.0 #6a6a6a);";
    _toolWidget->setStyleSheet(toolBoxStyle);

    _toolDock = new QDockWidget("", this);
    addDockWidget(Qt::LeftDockWidgetArea, _toolDock);
    _toolDock->setWidget(_toolWidget);
    _toolDock->setAllowedAreas(Qt::LeftDockWidgetArea);
    _toolDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
}

void MainWindow::createAnimationDock() {
    _animationWidget = new AnimationWidget;

    _animationDock = new QDockWidget("Animation", this);
    addDockWidget(Qt::BottomDockWidgetArea, _animationDock);
    _animationDock->setWidget(_animationWidget);
    _animationDock->setAllowedAreas(Qt::BottomDockWidgetArea);

    _animationDock->setVisible(false);
}

/*****************
 * OTHER METHODS *
 *****************/
void MainWindow::closeEvent(QCloseEvent* event) {
    if (aboutToClear()) {
        closeAllTab();
    }
    if (currentTab()->getWindowTitle() == "Introduction") {
        event->accept();
    } else {
        event->ignore();
    }
}

bool MainWindow::aboutToClear() {
    return QMessageBox::warning(this, "Warning", "Do you want to quit?",
                                QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
}

QWidget* MainWindow::createNewTab(QString fileName, QVector<int> screen, RayTracer::Resolution resolution, const Camera &camera, bool openedFile) {
    QWidget* newTab = new QWidget;
    ImageWindow* newImageWindow = NULL;

    QVBoxLayout* mainLayout = new QVBoxLayout;

    if (fileName == "") {
        newImageWindow = new ImageWindow();
        mainLayout->setAlignment(Qt::AlignLeft);
    } else {
        mainLayout->setAlignment(Qt::AlignCenter);
        if (openedFile) {
            newImageWindow = new ImageWindow(fileName);
        } else {
            newImageWindow = new ImageWindow(fileName, screen, resolution, camera);
        }
    }

    mainLayout->addWidget(newImageWindow);
    newTab->setLayout(mainLayout);

    return newTab;
}

ImageWindow* MainWindow::currentTab() {
    return _tabs->currentWidget()->findChild<ImageWindow* >();
}

/*********
 * SLOTS *
 *********/
void MainWindow::newData() {
    NewFileWindow* newFileWindow = new NewFileWindow(this);
    if (newFileWindow->exec() == QDialog::Accepted) {
        QString fileName = newFileWindow->getFileName();

        if (fileName.split(".").last() != "xml") {
            fileName.append(".xml");
        }

        QVector<int> screen;
        screen << newFileWindow->getFileWidth() << newFileWindow->getFileHeight();
        RayTracer::Resolution resolution = newFileWindow->getFileResolution();

        Camera camera(newFileWindow->getObserver(),
                      newFileWindow->getAimedPoint(),
                      newFileWindow->getViewAngle(),
                      screen.at(0),
                      screen.at(1)
               );
        camera.initFromDistScreen(newFileWindow->getDistanceScreen());

        QString windowTitle = fileName.split("/").last();
        int indexNewTab = _tabs->addTab(createNewTab(fileName, screen, resolution, camera, false), windowTitle);

        if (currentTab()->getFileName() == "") {
            _tabs->removeTab(_tabs->currentIndex());
        }

        _tabs->setCurrentIndex(indexNewTab);

        emit enableButtons(true);

        statusBar()->showMessage(tr("New file opened"), 2000);
    } else {
        newFileWindow->_id--;
    }
}

void MainWindow::open() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file", "../RayTracer/xml/", "XML File (*.xml)");
    if (fileName == "") {
        return;
    }

    for (int k = 0; k < _tabs->count(); k++) {
        QString currentFileName = ((ImageWindow*) _tabs->widget(k)->findChild<ImageWindow* >())->getFileName();
        if (fileName == currentFileName) {
            _tabs->setCurrentIndex(k);
            emit enableButtons(true);
            return;
        }
    }

    QString windowTitle = fileName.split("/").last();
    int indexNewTab = _tabs->addTab(createNewTab(fileName), windowTitle);

    if (_tabs->tabText(_tabs->currentIndex()) == "Introduction") {
        _tabs->removeTab(_tabs->currentIndex());
    }

    _tabs->setCurrentIndex(indexNewTab);

    emit enableButtons(true);
}

void MainWindow::save() {
    if (currentTab()->getNeverSavedBefore()) {
        saveAs();
    } else {
        currentTab()->save();
    }
    emit isSaved(currentTab()->getSaved());

    if (currentTab()->getSaved())
        statusBar()->showMessage(tr("File saved"), 2000);
}

void MainWindow::saveAs() {
    currentTab()->saveAs();
    emit isSaved(currentTab()->getSaved());

    if (currentTab()->getSaved())
        statusBar()->showMessage(tr("File saved"), 2000);
}

void MainWindow::exportImage() {
    currentTab()->exportImage();
}

void MainWindow::closeTab() {
    if (!currentTab()->getSaved()) {
        int answer = QMessageBox::warning(this, "Close tab", "Warning: do you want to save your work before closing tab?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (answer == QMessageBox::Yes) {
            save();
        } else if (answer == QMessageBox::Cancel) {
            return;
        }
    }

    if (_tabs->count() > 1) {
        _tabs->removeTab(_tabs->currentIndex());
    } else {
        _tabs->addTab(createNewTab(""), "Introduction");
        _tabs->removeTab(_tabs->currentIndex());
        emit enableButtons(false);
    }
}

void MainWindow::closeAllTab() {
    int nbTabs = _tabs->count();
    for (int k = 0; k < nbTabs; k++) {
        if (nbTabs - k == _tabs->count())
            closeTab();
        else
            return;
    }
}

void MainWindow::closeExceptTab() {
    int nbTabs = _tabs->count();
    int currentPos = _tabs->currentIndex();
    for (int k = 0; k < currentPos; k++) {
        _tabs->removeTab(0);
    }
    for (int k = 0; k < nbTabs-currentPos-1; k++) {
        _tabs->removeTab(1);
    }
}

void MainWindow::quitProgram() {
    if (aboutToClear()) {
        closeAllTab();
        if (currentTab()->getWindowTitle() == "Introduction")
            qApp->quit();
    }
}

void MainWindow::undo() {
    _undoAction = currentTab()->getUndoAction();
}

void MainWindow::redo() {
    _redoAction = currentTab()->getRedoAction();
}

void MainWindow::settings() {

}

void MainWindow::addShape() {
    currentTab()->addShape();
    emit isSaved(currentTab()->getSaved());

    QStringList shapesList = currentTab()->getShapesList();
    emit changeShapes(shapesList);

    if (!currentTab()->getSaved())
        statusBar()->showMessage(tr("New shape added"), 2000);
}

void MainWindow::addLight() {
    currentTab()->addLight();
    emit isSaved(currentTab()->getSaved());

    QStringList lightsList = currentTab()->getLightsList();
    emit changeLights(lightsList);

    if (!currentTab()->getSaved())
        statusBar()->showMessage(tr("New light added"), 2000);
}

void MainWindow::generate() {
    statusBar()->showMessage(tr("Generating..."), 2000);
    currentTab()->generate();
}

void MainWindow::makeFilm() {
    MakeFilmWindow* makeFilmWindow = new MakeFilmWindow(this);
    if (makeFilmWindow->exec() == QDialog::Accepted) {
        double normalX = makeFilmWindow->getNormalX();
        double normalY = makeFilmWindow->getNormalY();
        double normalZ = makeFilmWindow->getNormalZ();
        double centerX = makeFilmWindow->getCircleCenterX();
        double centerY = makeFilmWindow->getCircleCenterY();
        double centerZ = makeFilmWindow->getCircleCenterZ();
        double aimedPointX = makeFilmWindow->getAimedPointX();
        double aimedPointY = makeFilmWindow->getAimedPointY();
        double aimedPointZ = makeFilmWindow->getAimedPointZ();
        int nbPoints = makeFilmWindow->getNbPoints();
        double radius = makeFilmWindow->getRadius();
        QString filmName = makeFilmWindow->getFilmName();

        Vector3 normal(normalX, normalY, normalZ);
        Vector3 Oy(0, 1, 0);
        Vector3 cp = cross_product(Oy, normal);
        double norm = cp.norm();
        double dp = dot_product(Oy, normal);

        double theta = atan2(norm, dp);

        cerr << cp << " " << dp << " " << norm << endl;

        QDir currDir("../RayTracer/");
        QString newDir = "films/"+filmName;
        if (currDir.exists(newDir)) {
            QMessageBox::critical(this, "Existing directory", "This directory already exists, please provide another name.");
            return;
        }
        currDir.mkdir(newDir);

        for (int k = 0; k < nbPoints; k++) {
            double phi = 2*k*M_PI / nbPoints;
            Vector3 observer(radius * cos(theta) * sin(phi) + centerX,
                             radius * sin(theta) * sin(phi) + centerY,
                             radius * cos(phi) + centerZ
                    );
            Vector3 aimedPoint(aimedPointX, aimedPointY, aimedPointZ);

            currentTab()->setCamera(observer, aimedPoint);
            currentTab()->generate().wait(10000);

            cerr << k << endl;

            //QMessageBox::warning(this, "Warning", "Click on Ok button when image is done");

            currentTab()->exportImage("films/"+filmName+"/"+QString::number(k)+".png");
        }
    }
}

void MainWindow::restoreDefaultDocks() {
    _shapesDock->setVisible(true);
    _shapesDock->setFloating(false);
    _lightsDock->setVisible(true);
    _lightsDock->setFloating(false);
    _cameraDock->setVisible(true);
    _cameraDock->setFloating(false);
    _screenDock->setVisible(true);
    _screenDock->setFloating(false);
}

void MainWindow::index() {

}

void MainWindow::about() {

}

void MainWindow::updateShapesList(QStringList shapesList) {
    _shapesListModel->setStringList(shapesList);
}

void MainWindow::updateLightsList(QStringList lightsList) {
    _lightsListModel->setStringList(lightsList);
}

void MainWindow::updateCameraList(QStringList cameraList) {
    if (cameraList.isEmpty()) {
        _cameraLineEdit->setText("<b>Observer position</b><br /><br /><b>Aimed point</b><br /><br /><b>View angle</b><br /><br /><b>Distance to screen</b><br />");
    } else {
        _cameraLineEdit->setHtml("<b>Observer position</b><br />" + cameraList.at(0)
                               + "<br /><b>Aimed point</b><br />" + cameraList.at(1)
                               + "<br /><b>View angle</b><br />" + cameraList.at(2)
                               + "<br /><b>Distance to screen</b><br />"+cameraList.at(3)
                         );
    }
}

void MainWindow::updateScreenList(QStringList screenList) {
    if (screenList.isEmpty()) {
        _screenLineEdit->setText("<b>Width</b><br /><br /><b>Height</b><br /><br /><b>Resolution</b><br />");
    } else {
        _screenLineEdit->setHtml("<b>Width</b><br />" + screenList.at(0)
                               + "<br /><b>Height</b><br />" + screenList.at(1)
                               + "<br /><b>Resolution</b><br />" + screenList.at(2)
                         );
    }
}

void MainWindow::updateShape() {
    int idShape = _shapesListView->currentIndex().row();
    if (idShape != -1) {
        currentTab()->updateShape(idShape);
        emit isSaved(currentTab()->getSaved());
    }
    QStringList shapesList = currentTab()->getShapesList();
    emit changeShapes(shapesList);

    if (!currentTab()->getSaved())
        statusBar()->showMessage(tr("Shape updated"), 2000);
}

void MainWindow::removeShape() {
    int idShape = _shapesListView->currentIndex().row();
    if (idShape != -1) {
        currentTab()->removeShape(idShape);
        emit isSaved(currentTab()->getSaved());
    }
    QStringList shapesList = currentTab()->getShapesList();
    emit changeShapes(shapesList);

    if (!currentTab()->getSaved())
        statusBar()->showMessage(tr("Shape removed"), 2000);
}

void MainWindow::updateLight() {
    int idLight = _lightsListView->currentIndex().row();
    if (idLight != -1) {
        currentTab()->updateLight(idLight);
        emit isSaved(currentTab()->getSaved());
    }
    QStringList lightsList = currentTab()->getLightsList();
    emit changeLights(lightsList);

    if (!currentTab()->getSaved())
        statusBar()->showMessage(tr("Light updated"), 2000);
}

void MainWindow::removeLight() {
    int idLight = _lightsListView->currentIndex().row();
    if (idLight != -1) {
        currentTab()->removeLight(idLight);
        emit isSaved(currentTab()->getSaved());
    }
    QStringList lightsList = currentTab()->getLightsList();
    emit changeLights(lightsList);

    if (!currentTab()->getSaved())
        statusBar()->showMessage(tr("Light removed"), 2000);
}

void MainWindow::setCamera() {
    currentTab()->setCamera();
    emit isSaved(currentTab()->getSaved());

    QStringList cameraList = currentTab()->getCameraList();
    emit changeCamera(cameraList);

    if (!currentTab()->getSaved())
        statusBar()->showMessage(tr("Camera updated"), 2000);
}

void MainWindow::setScreen() {
    currentTab()->setScreen();
    emit isSaved(currentTab()->getSaved());

    QStringList screenList = currentTab()->getScreenList();
    emit changeScreen(screenList);

    if (!currentTab()->getSaved())
        statusBar()->showMessage(tr("Screen settings updated"), 2000);
}

void MainWindow::changeTab(int /*indexTab*/) {
    updateShapesList(currentTab()->getShapesList());
    updateLightsList(currentTab()->getLightsList());
    updateScreenList(currentTab()->getScreenList());
    updateCameraList(currentTab()->getCameraList());

    _saveFileAction->setText("&Save "+currentTab()->getWindowTitle()+"...");
    _saveAsFileAction->setText("Save "+currentTab()->getWindowTitle()+" &as...");
    _closeFileAction->setText("&Close "+currentTab()->getWindowTitle());
    _generateAction->setText("&Generate "+currentTab()->getWindowTitle());
    _closeExceptFileAction->setText("Close all except "+currentTab()->getWindowTitle());

    // If windowTitle == "Introduction", that means the current tab is the introduction,
    // not a picture, so we have to disable run, add shape, add light buttons...
    emit enableButtons(currentTab()->getWindowTitle() != "Introduction");
}

void MainWindow::enableSceneButtons(bool b) {
    _saveFileAction->setEnabled(b);
    _saveAsFileAction->setEnabled(b);
    _exportAction->setEnabled(b);
    _exportButton->setEnabled(b);
    _closeFileAction->setEnabled(b);
    _closeAllFileAction->setEnabled(b);
    _closeExceptFileAction->setEnabled(b);
    _addShapeAction->setEnabled(b);
    _addShapeButton->setEnabled(b);
    _addLightAction->setEnabled(b);
    _addLightButton->setEnabled(b);
    _generateAction->setEnabled(b);
    _generateButton->setEnabled(b);
    _setCameraAction->setEnabled(b);
    _setScreenAction->setEnabled(b);
    _viewAnimationDockAction->setEnabled(b);
    _makeFilmAction->setEnabled(b);
    _undoAction->setEnabled(b);
    _redoAction->setEnabled(b);
}

void MainWindow::setTabTitle(bool b) {
    QString tabTitle = currentTab()->getWindowTitle();
    int index = _tabs->currentIndex();
    if (b) {
        _tabs->setTabText(index, tabTitle);
    } else {
        _tabs->setTabText(index, tabTitle+" *");
    }
}
