#ifndef FILERESMAN_HPP
#define FILERESMAN_HPP


#include <QTreeView>
#include <QFileSystemModel>
#include <QInputDialog>
#include "../pch.h"
#include <MainUI/FacObsFrames/ObserverMgr.h>

class FileResMan : public QObject, public nObserver // to access data
{
    Q_OBJECT

private:
    // -- Singleton Pattern --
    explicit FileResMan(QObject* parent = nullptr)
        : QObject(parent)
    {}

    FileResMan(const FileResMan&) = delete;
    FileResMan& operator=(const FileResMan&) = delete;

    QDockWidget* logDockWidget = nullptr;
    QTreeView* fileTreeView = nullptr;
    QFileSystemModel* fileModel = nullptr;

    void autoExpandDirectories()
    {
        if (!fileTreeView) return;
        QModelIndex rootIndex = fileTreeView->rootIndex();
        if (!rootIndex.isValid()) return;

        fileTreeView->expand(rootIndex);

        int rowCountIndex = fileModel->rowCount(rootIndex);
        for (int i = 0; i < rowCountIndex; ++i) {
            QModelIndex childIndex = fileModel->index(i, 0, rootIndex);
            if (fileModel->isDir(childIndex)) {
                fileTreeView->expand(childIndex);
            }
        }
    }

   
public:
    // -- Singleton getInstance --
    static FileResMan& getInstance()
    {
        static FileResMan instance;
        return instance;
    }

    void initDockWg()
    {
        auto nmainwd = getMainWindow();
        if (!nmainwd) {
            qWarning() << "MainWindow not found!";
            return;
        }

        logDockWidget = new QDockWidget("Scanning Res", nmainwd);
        logDockWidget->setObjectName("FileManagerDockWidget");
        logDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);

        std::ostringstream dir_oss;
        dir_oss << "Scanning result";
        std::filesystem::path scanDir = dir_oss.str();

        if (!std::filesystem::exists(scanDir)) {
            std::filesystem::create_directories(scanDir);
        }

        QString defaultDir = QString::fromStdString(scanDir.string());

        fileModel = new QFileSystemModel(this);
        fileModel->setRootPath(defaultDir);
        fileModel->setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);

        fileTreeView = new QTreeView();
        fileTreeView->setObjectName("FileTreeView");
        fileTreeView->setModel(fileModel);
        fileTreeView->setRootIndex(fileModel->index(defaultDir));

        fileTreeView->setColumnWidth(0, 150); // Name
        fileTreeView->setColumnWidth(1, 80);  // Size
        fileTreeView->setColumnHidden(2, true);
        fileTreeView->setColumnHidden(3, true);

        fileTreeView->setSelectionMode(QAbstractItemView::SingleSelection);
        fileTreeView->setSelectionBehavior(QAbstractItemView::SelectRows);

        fileTreeView->setContextMenuPolicy(Qt::CustomContextMenu);

        connect(fileTreeView, &QTreeView::customContextMenuRequested,
            this, &FileResMan::onCustomContextMenu);

        connect(fileTreeView, &QTreeView::doubleClicked,
            this, &FileResMan::onDoubleClicked);

        QLineEdit* folderInput = new QLineEdit(defaultDir);
        folderInput->setPlaceholderText("Enter folder path...");
        QPushButton* browseButton = new QPushButton("Browse");
        QPushButton* bparent = new QPushButton("Back");

        connect(browseButton, &QPushButton::clicked, [this, folderInput]() {
            QString dir = QFileDialog::getExistingDirectory(nullptr,
                "Select Directory",
                folderInput->text());
            if (!dir.isEmpty()) {
                folderInput->setText(dir);
                fileTreeView->setRootIndex(fileModel->index(dir));
                QTimer::singleShot(0, [this]() { this->autoExpandDirectories(); });
            }
            });
        connect(bparent, &QPushButton::clicked, [this, folderInput]() {
            QString currentDir = folderInput->text();
            QDir dir(currentDir);

            if (dir.cdUp()) { 
                QString parentDir = dir.absolutePath();
                folderInput->setText(parentDir);
                fileTreeView->setRootIndex(fileModel->index(parentDir));
                QTimer::singleShot(0, [this]() { this->autoExpandDirectories(); });
            }
            });

        connect(folderInput, &QLineEdit::editingFinished, [this, folderInput]() {
            QString dir = folderInput->text();
            if (QDir(dir).exists()) {
                fileTreeView->setRootIndex(fileModel->index(dir));
                QTimer::singleShot(0, [this]() { this->autoExpandDirectories(); });
            }
            else {
                qDebug() << "Directory does not exist:" << dir;
            }
            });

        QTimer::singleShot(0, [this]() { this->autoExpandDirectories(); });

        QWidget* dockContent = new QWidget();
        QVBoxLayout* mainLayout = new QVBoxLayout(dockContent);
        QHBoxLayout* topLayout = new QHBoxLayout();
        topLayout->addWidget(folderInput);
        topLayout->addWidget(browseButton);
        topLayout->addWidget(bparent);

        mainLayout->addLayout(topLayout);
        mainLayout->addWidget(fileTreeView);
        dockContent->setLayout(mainLayout);

        logDockWidget->setWidget(dockContent);
        nmainwd->addDockWidget(Qt::RightDockWidgetArea, logDockWidget);

        logDockWidget->show();
    }

private slots:
    void onCustomContextMenu(const QPoint& pos)
    {
        if (!fileTreeView) return;

        QModelIndex index = fileTreeView->indexAt(pos);
        if (!index.isValid()) {
            return;
        }

        QString filePath = fileModel->filePath(index);
        QFileInfo fileInfo(filePath);

        QMenu contextMenu;
        QAction* renameAction = contextMenu.addAction("Rename File");
        QAction* deleteAction = contextMenu.addAction("Delete File");
        QAction* selectedAction = contextMenu.exec(fileTreeView->viewport()->mapToGlobal(pos));
        if (!selectedAction) return;

        if (selectedAction == renameAction) {
            bool ok;
            QString newName = QInputDialog::getText(nullptr,
                "Rename File",
                "Enter new name:",
                QLineEdit::Normal,
                fileInfo.fileName(),
                &ok);
            if (ok && !newName.isEmpty()) {
                QString newPath = fileInfo.absolutePath() + "/" + newName;
                QFile file(filePath);
                if (file.rename(newPath)) {
                    qDebug() << "File renamed to:" << newPath;
                }
                else {
                    qDebug() << "Failed to rename file:" << filePath;
                    QMessageBox::warning(nullptr, "Rename Failed",
                        "Could not rename the file.");
                }
            }
        }
        else if (selectedAction == deleteAction) {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(nullptr, "Delete File",
                "Are you sure you want to delete this file?",
                QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                if (fileInfo.isDir()) {
                    QDir dir(filePath);
                    if (dir.removeRecursively()) {
                        qDebug() << "Directory deleted:" << filePath;
                    }
                    else {
                        qDebug() << "Failed to delete directory:" << filePath;
                        QMessageBox::warning(nullptr, "Delete Failed",
                            "Could not delete the directory.");
                    }
                }
                else {
                    QFile file(filePath);
                    if (file.remove()) {
                        qDebug() << "File deleted:" << filePath;
                    }
                    else {
                        qDebug() << "Failed to delete file:" << filePath;
                        QMessageBox::warning(nullptr, "Delete Failed",
                            "Could not delete the file.");
                    }
                }
            }
        }
    }

    void onDoubleClicked(const QModelIndex& index) {
        if (!index.isValid()) return;

        QString filePath = fileModel->filePath(index);
        QFileInfo fileInfo(filePath);

        if (fileInfo.isDir()) {
            fileTreeView->setRootIndex(index);
            QTimer::singleShot(0, [this]() { this->autoExpandDirectories(); });
        }
        else {
            /*try
            {*/
                if (fileInfo.suffix().toLower() == "dat") {
                    // Open the file in binary mode
                    std::ifstream inFile(filePath.toStdString(), std::ios::binary);
                    if (!inFile) {
                        qDebug() << "Failed to open file for reading:" << filePath;
                        return;
                    }

                    // Deserialize metadata
                    auto tempRes = std::make_unique<ScanMetadata>();

                    tempRes->loadFromStream(inFile);

                    // Read dataset
                    size_t totalSize = tempRes->xSize * tempRes->ySize * tempRes->zSize;
                    tempRes->DataSet.resize(totalSize);
                    inFile.read(reinterpret_cast<char*>(tempRes->DataSet.data()), totalSize * sizeof(int));

                    if (inFile.eof() || inFile.fail()) {
                        qDebug() << "Failed to read dataset from file.";
                        return;
                    }

                    // Successfully loaded all data
                    scanningRes = std::move(tempRes);
                    inFile.close();

                    if (inFile.fail()) {
                        qDebug() << "Failed to read data completely from file:" << filePath;
                        return;
                    }
                    processLoadedData();
                    qDebug() << "Data loaded successfully from:" << filePath;
                }
            //}
            //catch (std::exception& e)
            //{ qDebug() << "Error while reading. "; };
        }
    }

    void processLoadedData() {
        if (!scanningRes) {
            std::cerr << "No data loaded." << std::endl;
            return;
        }

        int xSize = scanningRes->xSize;
        int ySize = scanningRes->ySize;
        int zSize = scanningRes->zSize;
        qDebug() << " x, y, z size: " << xSize << " " << ySize << " " << zSize;

        int x = 5, y = 5, z = 5;
        if (x >= xSize || y >= ySize || z >= zSize) {
            std::cerr << "Specified x, y, or z is out of range." << std::endl;
            return;
        }

        // Create C-view (x + y at z = 5) with Vec3b
        cv::Mat cView(ySize, xSize, CV_8UC3);
        for (int xi = 0; xi < xSize; ++xi) {
            for (int yi = 0; yi < ySize; ++yi) {
                auto co = everyColors[static_cast<int16_t>(scanningRes->DataSet[xi * ySize * zSize + yi * zSize + z] / 32.768)];
                cView.at<cv::Vec3b>(yi, xi) = co;
            }
        }

        // Create B-view (x + z at y = 5) with Vec3b
        cv::Mat bView(zSize, xSize, CV_8UC3);
        for (int xi = 0; xi < xSize; ++xi) {
            for (int zi = 0; zi < zSize; ++zi) {
                auto co = everyColors[static_cast<int16_t>(scanningRes->DataSet[xi * ySize * zSize + y * zSize + zi] / 32.768)];
                bView.at<cv::Vec3b>(zi, xi) = co;
            }
        }

        // Create S-view (y + z at x = 5) with Vec3b
        cv::Mat sView(zSize, ySize, CV_8UC3);
        for (int yi = 0; yi < ySize; ++yi) {
            for (int zi = 0; zi < zSize; ++zi) {
                auto co = everyColors[static_cast<int16_t>(scanningRes->DataSet[x * ySize * zSize + yi * zSize + zi] / 32.768)];
                sView.at<cv::Vec3b>(zi, yi) = co;
            }
        }

        // Combine C-view, B-view, and S-view into one image
        int combinedWidth = xSize * 3 + ySize; // Sum of widths of all views
        int combinedHeight = ySize +  3 * zSize;       // Max height of views
        cv::Mat combinedView = cv::Mat::zeros(combinedHeight, combinedWidth, CV_8UC3);

        // Place C-view
        cView.copyTo(combinedView(cv::Rect(10, 10, xSize, ySize)));

        // Place B-view
        bView.copyTo(combinedView(cv::Rect(xSize, 10, xSize, zSize)));

        // Place S-view
        sView.copyTo(combinedView(cv::Rect(2 * xSize + 10, 10, ySize, zSize)));

        // Display combined view
        cv::namedWindow("Combined View (C, B, S)", cv::WINDOW_NORMAL);
        cv::imshow("Combined View (C, B, S)", combinedView);

        cv::waitKey(0); // Wait for key press to exit
    }

public:
    QWidget* createFrame() override { return nullptr; };
    void updateOffLine() override {};
    void updateRealTime() override {};
};

#endif // FILERESMAN_HPP
