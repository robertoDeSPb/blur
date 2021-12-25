#include <iostream>

#include <QApplication>
#include <QtGui/QtGui>

#include <QVBoxLayout>
#include <QSlider>
#include <QPushButton>
#include <QLabel>

#include <QFileDialog>

#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>

#include <QSize>

QImage blurImage(QImage source, int blurRadius) {
    if(source.isNull()) return QImage();
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(source));

    auto *blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(blurRadius);
    item.setGraphicsEffect(blur);
    scene.addItem(&item);
    QImage result(source.size(), QImage::Format_ARGB32);
    result.fill(Qt::transparent);
    QPainter painter(&result);
    scene.render(&painter, QRectF(),
                 QRectF(0, 0, source.width(), source.height()));
    return result;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto *mainWindow = new QWidget;
    mainWindow->resize(640,480);

    auto *vbox = new QVBoxLayout(mainWindow);
    auto *blurWindow = new QLabel;
    blurWindow->setScaledContents(true);
    auto *blurSlider = new QSlider;
    blurSlider->setOrientation(Qt::Horizontal);
    blurSlider->setMinimum(0);
    blurSlider->setMaximum(10);
    auto *oButton = new QPushButton(nullptr);
    oButton->setText("Open");

    vbox->addWidget(blurWindow);
    vbox->addWidget(blurSlider);
    vbox->addWidget(oButton);

    QString filePath;

    QObject::connect(oButton, &QPushButton::clicked, [&filePath, blurWindow, blurSlider]() {
        filePath = QFileDialog::getOpenFileName(nullptr,
                                     "Open jpg image",
                                     "D://c++//Docs//Images",
                                     "jpg files (*.jpg)");
        blurWindow->setPixmap(QPixmap::fromImage(QImage(filePath).scaled(
                                        blurWindow->width(),
                                        blurWindow->height(),
                                        Qt::KeepAspectRatio)));
//нужно ли добавлять многопоточность?
        QObject::connect(blurSlider, &QSlider::valueChanged, [&blurSlider, blurWindow, filePath](int newValue) {

            blurWindow->setPixmap(QPixmap::fromImage(blurImage(QImage(filePath), blurSlider->value()).scaled(
                                                         blurWindow->width(),
                                                         blurWindow->height(),
                                                         Qt::KeepAspectRatio)));
        });
    });



    mainWindow->show();
    return a.exec();
}
