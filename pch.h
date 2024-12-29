#ifndef PCH_H
#define PCH_H

// ======== Standard C++ Headers ============
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <deque>
#include <future>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <sstream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <shared_mutex>

// ========  YMCONNECT ROBOT YASKAWA ===========
#include "YMConnect/YMConnect.h"
// ======== Windows-Specific Headers ============
#include <windows.h>

// ======== Boost Library ============
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "boost/di.hpp"
#include <boost/lockfree/queue.hpp>



// ======== JSON Parsing Library ============
#include "nlohmann/json.hpp"

// ======== QT UI ============
#include <QApplication>
#include <QTextEdit>
#include <QWidget>
#include <QPushButton>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QSplitter>
#include <QFrame>
#include <QSettings>
#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMutex>
#include <QTime>
#include <QTabWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QHeaderView>
// ======== Additional QT UI Components ============
#include <QComboBox>
#include <QSlider>
#include <QLineEdit>
#include <QCheckBox>
#include <QRadioButton>
#include <QDockWidget>
#include <QSize>
#include <QStyleFactory>
#include <QGraphicsTextItem>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSpinBox>
#include <QToolTip>
#include <QMenu>
#include <QGroupBox>
//#include <qcustomplot.h>
#include <QMenuBar>
#include <QMenu>
#include <QProgressDialog>
#include <QOffscreenSurface>
#include <QTimer>
#include <QShortcut>
#include <QTableWidget>
#include <QDesktopServices>
#include <QFormLayout>

// ======== Qt Charts ============
#include <QtCharts/qchart.h>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/qsplineseries.h>
#include <QtCharts/QValueAxis>

// ======== Project-Specific Headers ============
#include <instrumentation/Instrumentation.h>
#include <Storage/Storage.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// ======== QTVulkan ============
#include <QVulkanWindow>
#include <QVulkanFunctions>
#include <QVulkanFunctions>
#include <QApplication>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QLCDNumber>

// ======== OpenCV CUDA ============
#include <opencv2/opencv.hpp>

//#include <opencv2/cudawarping.hpp>
//#include <opencv2/cudaimgproc.hpp>
//#include <opencv2/cudaarithm.hpp>

// ======== Olympus ============
#include <Storage/Storage.h>

// ======= OpenGL ============
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector2D>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLWindow>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions_4_3_Core> 

// ======== Logs ============
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h> 
#include <spdlog/fmt/fmt.h> 

// return -1 if no update, otherwise return the Frametime.
struct FrameTimeTracker {
    std::chrono::high_resolution_clock::time_point timer;
    double totalFrameTime = 0.0;
    int totalFrames = 0;
};
inline void StartFrameTimer(FrameTimeTracker& tracker) {
    tracker.timer = std::chrono::high_resolution_clock::now();
}

inline float EndFrameTimer(FrameTimeTracker& tracker) {
    auto endTime = std::chrono::high_resolution_clock::now();
    double currentFrameTime = std::chrono::duration<double, std::micro>(endTime - tracker.timer).count();
    tracker.totalFrameTime += currentFrameTime;
    tracker.totalFrames++;

    if (tracker.totalFrames >= 100.0) {
        double avgFrameTime = tracker.totalFrameTime / tracker.totalFrames;
        tracker.totalFrameTime = 0.0;
        tracker.totalFrames = 0;
        return avgFrameTime;

    }
    return -1.0f;
}

// return Loger File_Logger for recording.
// can recheck the loger file in the folder.
inline std::shared_ptr<spdlog::logger> CoutLogger() {
    static std::shared_ptr<spdlog::logger> debugLogger = nullptr;

    if (!debugLogger) {
        debugLogger = spdlog::get("file_logger");
        if (!debugLogger) {
            std::cerr << "Could not find logger 'file_logger'" << std::endl;
            return nullptr;
        }
    }
    return debugLogger;
}
inline std::filesystem::path getFilePath()
{
    QSettings settings("Ohlabs", "RobView");
    QString lastPath = settings.value("lastUsedPath", QDir::homePath()).toString();
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Open File", lastPath);
    if (!filePath.isEmpty()) {
        settings.setValue("lastUsedPath", QFileInfo(filePath).absolutePath());
        return std::filesystem::path(filePath.toStdString());
    }
    return std::filesystem::path();
}
inline QMainWindow* getMainWindow() {
    foreach(QWidget * widget, QApplication::topLevelWidgets()) {
        if (QMainWindow* mainWindow = qobject_cast<QMainWindow*>(widget)) {
            return mainWindow;
        }
    }
    return nullptr;
}





#endif // PCH_H
