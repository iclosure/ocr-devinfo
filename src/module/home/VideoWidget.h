﻿#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include "global.h"
#include <QCameraViewfinder>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

// class VideoWidget

class QCamera;
class QCameraImageCapture;

class VideoWidget : public QCameraViewfinder
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr);
    ~VideoWidget() J_OVERRIDE;

    bool init();

    void updateBoundRect(const std::vector<std::vector<cv::Point> > &contours);

    QCamera *camera() const;
    QCameraImageCapture *cameraImageCapture() const;
    std::vector<std::vector<cv::Point> > &contours();
    const std::vector<std::vector<cv::Point> > &contours() const;
    bool isCameraValid() const;

    QImage imageCaptured() const;
    void setImageCaptured(const QImage &image);
    QImage clipedImageCaptured(const QImage &image) const;

    QSize anchorErode() const;
    void setAnchorErode(const QSize &size);

    QSize clipedSize() const;
    void setClipedSize(const QSize &size);

    QSize resolution() const;
    void setResolution(const QSize &resolution);

    const cv::Mat &binaryImage() const;
    void setBinaryImage(cv::Mat image);
    void releaseBinaryImage();

Q_SIGNALS:
    void readyForCaptureChanged(bool ready);
    void captured(const QImage &image);
    void anchorErodeChanged(const QSize &size);

public Q_SLOTS:
    bool start();
    void stop();
    void capture();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    bool isCaptureDestinationSupported_;
    QCamera *camera_;
    QCameraImageCapture *cameraImageCapture_;
    std::vector<std::vector<cv::Point> > contours_;
    QImage imageCaptured_;
    cv::Mat binaryImage_;
    QSize anchorErode_;
    QSize clipedSize_;
};

#endif // VIDEOWIDGET_H
