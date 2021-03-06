﻿#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QLabel>
#include "global.h"

// class HomeWidget

class JSplitter;
class QPlainTextEdit;
class ImageLabel;
class SourceView;
class JRoundButton;

class HomeWindow : public QWidget
{
    Q_OBJECT
public:
    explicit HomeWindow(QWidget *parent = nullptr);
    ~HomeWindow() override;

    bool init();

signals:

public slots:
    void updateImage();

private:
    void recognite();

private:
    Q_DISABLE_COPY(HomeWindow)
    JSplitter *splitter_;
    SourceView *sourceView_;
    ImageLabel *labelBinary_;
    QPlainTextEdit *editDevInfo_;
    JRoundButton *buttonGenReport_;
};

#endif // HOMEWINDOW_H
