#include "helpers.h"
#include <QImage>
#include <QString>
#include <QApplication>
#include <QLabel>
#include <QDialog>
#include <QVBoxLayout>
#include <QRgb>
#include <QDesktopWidget>

#include <sys/time.h>
#include <assert.h>

uint8_t* load_image_gray(const char* path, size_t* width, size_t* height)
{
	QImage img(path);
	if (img.isNull()) {
		return NULL;
	}

	assert(width);
	assert(height);

	*width = img.width();
	*height = img.height();

	// Aligned a 16-byte aligned buffer for the gray image
	uint8_t* gray_img;
	if (posix_memalign((void**) &gray_img, 16, img.width()*img.height()*sizeof(uint8_t)) != 0) {
		perror("posix_memalign");
		exit(1);
	}

	// TODO: what about the performance of this ;) ?
	for (int y = 0; y < img.height(); y++) {
		for (int x = 0; x < img.width(); x++) {
			QRgb pixel = img.pixel(x,y);
			gray_img[x+y*img.width()] = qGray(pixel);
		}
	}

	return gray_img;
}

void free_image(uint8_t* img)
{
	free(img);
}

static QImage get_qimage(const uint8_t* gray_img, size_t width, size_t height)
{
	QImage img(width, height, QImage::Format_RGB32);
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			const uint8_t gray = gray_img[x+y*width];
			img.setPixel(x, y, qRgb(gray, gray, gray));
		}
	}
	return img;
}

void show_image(const uint8_t* img, const size_t width, const size_t height)
{
	QImage qimg = get_qimage(img, width, height);

	QDialog* dlg = new QDialog();
	dlg->setWindowTitle("Image");
	QVBoxLayout* layout = new QVBoxLayout();
	QLabel* limg = new QLabel();
	QPixmap pm(QPixmap::fromImage(qimg));
	const QRect screen = qApp->desktop()->screenGeometry();
	if (!screen.contains(pm.rect())) {
		QSize s = screen.size();
		s.setWidth(s.width()*0.8);
		s.setHeight(s.height()*0.8);
		pm = pm.scaled(s, Qt::KeepAspectRatio);
	}
	limg->setPixmap(pm);
	layout->addWidget(limg);
	dlg->setLayout(layout);
	dlg->show();
}

double get_current_timestamp()
{
	struct timeval curt;
	gettimeofday(&curt, NULL);
	return (double)curt.tv_sec + ((double)curt.tv_usec)/1000000.0;
}
