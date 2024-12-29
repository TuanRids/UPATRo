#include "../pch.h"
#include "CviewFrame.h"
//#include <opencv2/cudawarping.hpp> 

CviewFrame::CviewFrame(QWidget* parent): QOpenGLWidget(parent), surface(new QOffscreenSurface)
{
    QOpenGLWidget::setUpdateBehavior(QOpenGLWidget::PartialUpdate);
}
QWidget* CviewFrame::createFrame(){
    if (!graphicsView) {
        graphicsView = std::make_shared<ZoomableGraphicsView>();
    }
    if (!scene) {
        scene = std::make_shared<QGraphicsScene>();
    }
    graphicsView->setScene(scene.get());
    graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatioByExpanding);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //    MouseGetPosXY();

    layout = new QVBoxLayout();
    QWidget* frame = new QWidget();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(this);
    frame->setLayout(layout);
    return frame;

}

void CviewFrame::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.09f, 0.09f, 0.09f, 1.0f);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);

    shaderProgram = std::make_unique<QOpenGLShaderProgram>();
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex,
        R"(
        #version 430 core
        layout (location = 0) in vec3 position;
        layout (location = 1) in vec2 texCoord;
        uniform mat4 mvp;
        uniform bool is3D;
        out vec2 fragTexCoord;
        void main() {
            if (is3D) {
                gl_Position = mvp * vec4(position, 1.0);
            } else {
                gl_Position = vec4(position.xy, 0.0, 1.0);
            }
            fragTexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
        }
        )");
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment,
        R"(
        #version 430 core
        in vec2 fragTexCoord;
        out vec4 FragColor;
        uniform sampler2D u_Texture;
        uniform float mixRatio;
        uniform vec2 zoomCenter;
        uniform float zoomRatio;
        const float kernel[25] = float[](
            1.0 / 256.0,  4.0 / 256.0,  6.0 / 256.0,  4.0 / 256.0, 1.0 / 256.0,
            4.0 / 256.0, 16.0 / 256.0, 24.0 / 256.0, 16.0 / 256.0, 4.0 / 256.0,
            6.0 / 256.0, 24.0 / 256.0, 36.0 / 256.0, 24.0 / 256.0, 6.0 / 256.0,
            4.0 / 256.0, 16.0 / 256.0, 24.0 / 256.0, 16.0 / 256.0, 4.0 / 256.0,
            1.0 / 256.0,  4.0 / 256.0,  6.0 / 256.0,  4.0 / 256.0, 1.0 / 256.0
        );

        const vec2 offsets[25] = vec2[](
            vec2(-2, -2), vec2(-1, -2), vec2(0, -2), vec2(1, -2), vec2(2, -2),
            vec2(-2, -1), vec2(-1, -1), vec2(0, -1), vec2(1, -1), vec2(2, -1),
            vec2(-2,  0), vec2(-1,  0), vec2(0,  0), vec2(1,  0), vec2(2,  0),
            vec2(-2,  1), vec2(-1,  1), vec2(0,  1), vec2(1,  1), vec2(2,  1),
            vec2(-2,  2), vec2(-1,  2), vec2(0,  2), vec2(1,  2), vec2(2,  2)
        );


        void main() {
            vec2 zoomedTexCoord = (fragTexCoord - zoomCenter) * zoomRatio + zoomCenter;
            vec4 blurredColor = vec4(0.0);

            for (int i = 0; i < 25; ++i) {
                vec2 sampleCoord = zoomedTexCoord + offsets[i] / vec2(textureSize(u_Texture, 0));
                blurredColor += texture(u_Texture, sampleCoord) * kernel[i];
            }
    float gray = dot(blurredColor.rgb, vec3(0.299, 0.587, 0.114));
    vec3 bwColor = vec3(gray);

    FragColor = vec4(mix(blurredColor.rgb, bwColor, mixRatio), blurredColor.a);

        }
        )");
    shaderProgram->link();
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
         1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f,  0.0f, 1.0f
    };
    GLuint indices[] = { 0, 1, 2, 2, 3, 0 };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);


    connect(this, &QOpenGLWidget::frameSwapped, this, [&]() {
        QOpenGLWidget::update();
        });
    QOpenGLWidget::update();
}
void CviewFrame::paintGL() {
    static QOpenGLContext* context = QOpenGLContext::currentContext();
    if (!context) return;

    shaderProgram->bind();

    if (pautmgr->prosdt.ArtScan->CViewBuffer) {
        static bool initialized = false;
        if (!initialized || pautmgr->prosdt.viewUpd[0]) {
            pautmgr->prosdt.CBcount[0] = 0;
            int width = pautmgr->prosdt.ringBufferWidth;
            int height = pautmgr->prosdt.cdaproc.ysize;
            std::vector<unsigned char> blackData(width * height * 3, 0); // BGR
            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, blackData.data());
            glBindTexture(GL_TEXTURE_2D, 0);
            initialized = true;
            pautmgr->prosdt.viewUpd[0] = false;
        }
        if (pautmgr->prosdt.CBcount[0] < pautmgr->prosdt.ringBufferWidth) {
            glBindTexture(GL_TEXTURE_2D, textureID);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            {
                std::lock_guard<std::mutex> lock(pautmgr->ArtScanMutex);
                glTexSubImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(pautmgr->prosdt.CBcount[0]), 0, 1, pautmgr->prosdt.cdaproc.ysize, GL_BGR, GL_UNSIGNED_BYTE, pautmgr->prosdt.ArtScan->CViewBuffer->data());
                pautmgr->prosdt.ArtScan->CViewBuffer = nullptr;
            }
            pautmgr->prosdt.CBcount[0]++;
        }
    }

    // Update shader uniforms
    shaderProgram->setUniformValue("zoomCenter", zoomCenter);
    shaderProgram->setUniformValue("zoomRatio", zoomRatio);
    shaderProgram->setUniformValue("mixRatio", ConfigL->visualConfig->mix_Black_White);

    // Always bind texture and render quad
    glBindTexture(GL_TEXTURE_2D, textureID);
    renderQuad();
    glBindTexture(GL_TEXTURE_2D, 0);

    shaderProgram->release();
}

void CviewFrame::renderQuad() {
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}



void CviewFrame::updateRealTime()
{
    if (!isRealTime)
    {
        if (graphicsView) {
            layout->removeWidget(graphicsView.get());
            graphicsView->hide();
        }
        layout->addWidget(this);
        this->show();
        isRealTime = true;
    }
}
void CviewFrame::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}




void CviewFrame::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        isSelectingRegion = true;
        selectionStart = event->pos();
        selectionEnd = event->pos();
    }
    else if (event->button() == Qt::RightButton) {
        isDragging = true;
        lastMousePos = event->pos();
    }
}
void CviewFrame::mouseMoveEvent(QMouseEvent* event) {
    if (isSelectingRegion) {
        selectionEnd = event->pos();
        update();
    }
    else if (isDragging) {
        QPointF currentMousePos = event->pos();
        QPointF delta = currentMousePos - lastMousePos;
        zoomCenter.setX(zoomCenter.x() - delta.x() / this->width());
        zoomCenter.setY(zoomCenter.y() - delta.y() / this->height());
        zoomCenter.setX(std::clamp(zoomCenter.x(), 0.0f, 1.0f));
        zoomCenter.setY(std::clamp(zoomCenter.y(), 0.0f, 1.0f));
        lastMousePos = currentMousePos;
        update();
    }
}
void CviewFrame::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && isSelectingRegion) {
        isSelectingRegion = false;
        QRectF selectionRect = QRectF(selectionStart, selectionEnd).normalized();
        if (selectionRect.width() > 5 && selectionRect.height() > 5) {
            float centerX = (selectionRect.x() + selectionRect.width() / 2.0f) / this->width();
            float centerY = (selectionRect.y() + selectionRect.height() / 2.0f) / this->height();
            centerY = 1.0f - centerY;
            float xRatio = (float)this->width() / (float)selectionRect.width();
            float yRatio = (float)this->height() / (float)selectionRect.height();
            float newZoomRatio = std::min(xRatio, yRatio);
            zoomCenter = QVector2D(centerX, centerY);
            zoomRatio = std::clamp(1.0f / newZoomRatio, 0.1f, 20.0f);
            update();
        }
        selectionStart = QPointF();
        selectionEnd = QPointF();
    }
    else if (event->button() == Qt::RightButton) {
        isDragging = false;
    }
}
void CviewFrame::wheelEvent(QWheelEvent* event) {
    QPointF mousePos = event->position();
    float x = static_cast<float>(mousePos.x()) / this->width();
    float y = static_cast<float>(mousePos.y()) / this->height();
    y = 1.0f - y;
    zoomCenter = QVector2D(x, y);
    float delta = event->angleDelta().y();
    float zoomStep = 0.05f;
    if (delta > 0) {
        zoomRatio += zoomStep;
    }
    else {
        zoomRatio -= zoomStep;
    }
    if (zoomRatio > 1.0f) zoomRatio = 1.0f;
    zoomRatio = std::clamp(zoomRatio, 0.1f, 5.0f);
    update();
}
void CviewFrame::paintEvent(QPaintEvent* event) {
    QOpenGLWidget::paintEvent(event);
    if (isSelectingRegion) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, false);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
        painter.setPen(Qt::DashLine);
        painter.setBrush(Qt::NoBrush);
        QRectF selectionRect = QRectF(selectionStart, selectionEnd).normalized();
        painter.drawRect(selectionRect);
    }
}

// ********************************************
// Offline Reading
// TODO: Optimize into GPU Rendering
void CviewFrame::updateOffLine() {
    if (isRealTime)
    {
        layout->removeWidget(this);
        this->hide();
        layout->addWidget(graphicsView.get());
        graphicsView->show();
        isRealTime = false;
    }

    static int lastResolution = -1;
    if (scandat.Amplitudes.empty()) { return; }
    if (lastResolution != ConfigL->sysParams->resolution) {
        lastResolution = ConfigL->sysParams->resolution;
        CreateXYview();
    }
    // if Bscan and Cscan layer
    if (ConfigL->sysParams->resolution) {
        CreateXYview();
    }

    static bool lastIsCscanLayer = false;
    if (lastIsCscanLayer != ConfigL->sysParams->isCscanLayer) {
        lastIsCscanLayer = ConfigL->sysParams->isCscanLayer;
        CreateXYview();
    }
    addPoints(true,-1,-1);
}
void CviewFrame::CreateXYview() {
    // Declaration and initialization
    if (scandat.Amplitudes.empty()) {
        return;
    }

    zsize = scandat.AmplitudeAxes[0].Quantity;
    ysize = scandat.AmplitudeAxes[1].Quantity;
    xsize = scandat.AmplitudeAxes[2].Quantity;

    orgimage = std::make_unique<cv::Mat>(ysize, xsize, CV_8UC3);
    scaledImage = std::make_unique<cv::Mat>();

    uint64_t z_offset = curpt[2] * (xsize * ysize);
    double percentAmplitude;

    // Processing amplitude data to assign colors
    for (uint64_t y = 0; y < ysize; ++y) {
        for (uint64_t x = 0; x < xsize; ++x) {
            if (!ConfigL->sysParams->isCscanLayer) {
                int16_t maxAmplitude = 0;
                for (uint64_t z = 0; z < zsize; ++z) {
                    uint64_t index = z * (xsize * ysize) + y * xsize + x;
                    if (index >= scandat.Amplitudes.size()) {
                        sttlogs->logWarning("Out of range data: " + std::to_string(index) + " / " + std::to_string(scandat.Amplitudes.size()));
                        return;
                    }
                    int16_t samplingAmplitude = std::abs(scandat.Amplitudes[index]);
                    if (samplingAmplitude > maxAmplitude) {
                        maxAmplitude = samplingAmplitude;
                    }
                }
                percentAmplitude = maxAmplitude / (32768.0 / 100.0);
            }
            else {
                uint64_t index = z_offset + y * xsize + x;
                if (index >= scandat.Amplitudes.size()) {
                    sttlogs->logWarning("Out of range data: " + std::to_string(index) + " / " + std::to_string(scandat.Amplitudes.size()));
                    return;
                }
                int16_t samplingAmplitude = std::abs(scandat.Amplitudes[index]);
                percentAmplitude = samplingAmplitude / (32768.0 / 100.0);
            }

            cv::Vec3b color = everyColors[static_cast<int16_t>(percentAmplitude)];
            orgimage->at<cv::Vec3b>(y, x) = cv::Vec3b(color[0], color[1], color[2]);
        }
    }

    double frameRatio = static_cast<double>(graphicsView->size().width()) / static_cast<double>(graphicsView->size().height());
    double imageRatio = static_cast<double>(orgimage->cols) / static_cast<double>(orgimage->rows);

    auto newWidth = (frameRatio > imageRatio) ? static_cast<int>(orgimage->rows * frameRatio) : orgimage->cols;
    auto newHeight = (frameRatio > imageRatio) ? orgimage->rows : static_cast<int>(orgimage->cols / frameRatio);

    auto scaleFactor = (!isPanning || ConfigLocator::getInstance().settingconf->bhighResBscan) ? 1 : 1.0;
    cv::resize(*orgimage, *scaledImage, cv::Size(newWidth * scaleFactor, newHeight * scaleFactor), 0, 0, cv::INTER_LINEAR);

    cv::GaussianBlur(*scaledImage, *scaledImage, cv::Size(1, 1), 0);
    auto qImage = std::make_shared<QImage>(scaledImage->data, scaledImage->cols, scaledImage->rows, scaledImage->step, QImage::Format_RGB888);
    *qImage = qImage->rgbSwapped();

    QPixmap pixmap = QPixmap::fromImage(*qImage);
    for (auto item : scene->items()) {
        if (item->data(0).toString() == "artwork") {
            scene->removeItem(item);
            delete item;
            break;
        }
    }
    QGraphicsPixmapItem* artworkItem = scene->addPixmap(pixmap);
    artworkItem->setData(0, "artwork");

    static bool first_flag = true; if (first_flag) graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio); first_flag = false;
    graphicsView->update();
}
void CviewFrame::addPoints(bool Cviewlink, int x, int y)
{
    double pixelX= (Cviewlink) ? static_cast<double>(curpt[0]) * scaledImage->cols / xsize : static_cast<double>(x);
    double pixelY = (Cviewlink) ? static_cast<double>(curpt[1]) * scaledImage->rows / ysize : static_cast<double>(y);

    if (overlay) { overlay->updatePoints(pixelX, pixelY, Qt::blue, Qt::red); }
    graphicsView->update();
}
std::pair<int, int> CviewFrame::calculateOriginalPos(int scaled_x, int scaled_y) {
    if (orgimage == nullptr || scaledImage == nullptr) {
        throw std::exception();
    }
    auto scale_x = static_cast<double>(orgimage->cols) / static_cast<double>(scaledImage->cols);
    auto scale_y = static_cast<double>(orgimage->rows) / static_cast<double>(scaledImage->rows);

    int original_x = static_cast<int>(scaled_x * scale_x);
    int original_y = static_cast<int>(scaled_y * scale_y);

    if (original_x < 0 || original_y < 0 || original_y >= ysize || original_x >= xsize) {
        throw std::exception();
    }
    return { original_x, original_y };
}
void CviewFrame::MouseGetPosXY()
{
    static int temX{ 0 }, temY{ 0 };
    QObject::connect(graphicsView.get(), &ZoomableGraphicsView::mouseMoved, [=](int scaled_x, int scaled_y) {
        try
        {
            temX = scaled_x; temY = scaled_y;
            auto [original_x, original_y] = calculateOriginalPos(scaled_x, scaled_y);
            QString tooltipText = QString("X: %1\nY: %2\nZ: %3").arg(original_x).arg(original_y).arg(curpt[2]);
            QToolTip::showText(QCursor::pos(), tooltipText);
            overlay->updateOverlay(scaled_x, scaled_y, scaledImage->cols, scaledImage->rows);
            graphicsView->update();

        }
        catch (...) { (void)0; }
        });

    QObject::connect(graphicsView.get(), &ZoomableGraphicsView::mouseClicked, [=](int scaled_x, int scaled_y) {
        try
        {
            temX = scaled_x; temY = scaled_y;
            std::tie(curpt[0], curpt[1]) = calculateOriginalPos(scaled_x, scaled_y);
            isPanning = false;

            addPoints(false, scaled_x, scaled_y);
        }
        catch (...) { (void)0; }
        });
    

    QObject::connect(graphicsView.get(), &ZoomableGraphicsView::mouseLeftView, [=]() {
        overlay->ClearLineGroup();
        });

    QObject::connect(graphicsView.get(), &ZoomableGraphicsView::nKeyPressedEvent, [=]() {
        for (auto item : scene->items()) {
            if (item->data(0).toString() == "artwork") {
                graphicsView->fitInView(item->boundingRect(), Qt::KeepAspectRatio);
                break;
            }
        }

        });
}