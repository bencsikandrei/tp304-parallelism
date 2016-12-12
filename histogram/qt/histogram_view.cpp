#include "histogram_view.h"
#include "histogram.h"
#include "tools.h"

#include <QDebug>
#include <QKeyEvent>
#include <QPainter>

#include <iostream>

HistogramView::HistogramView(Histogram& hist, QWidget* parent):
	QWidget(parent),
	_hist(hist),
	_time_compute(0.0)
{
	setFocusPolicy(Qt::StrongFocus);
	compute(0.01);
}

void HistogramView::compute(const double size)
{
	const double start = get_current_timestamp();
	hist().compute(size);
	const double end = get_current_timestamp();
	hist().compute_hist_minmax();
	_time_compute = end-start;
}

void HistogramView::enlarge()
{
	compute(hist().size_interval()*1.1);
	update();
}

void HistogramView::shrink()
{
	compute(hist().size_interval()/1.1);
	update();
}

void HistogramView::keyPressEvent(QKeyEvent* event)
{
	switch (event->key()) {
	case Qt::Key_Left:
		shrink();
		break;
	case Qt::Key_Right:
		enlarge();
		break;
	}
}

void HistogramView::paintEvent(QPaintEvent* /*event*/)
{
	QPainter painter_(this);
	QPainter* const painter = &painter_;
	painter->fillRect(painter->viewport(), Qt::white);

	const int32_t hist_max = hist().hist_max();
	const uint32_t* hist_ = hist().hist();
	const int32_t view_height = painter->viewport().height();
	const int32_t view_width  = painter->viewport().width();
	const double rect_width = (double)view_width/(double)hist().hist_integer_count();

	int32_t pos = 0;
	for (size_t i = 0; i < hist().hist_integer_count(); i++) {
		const uint32_t v = hist_[i];
		const int32_t h = (v*view_height)/hist_max;
		const int32_t color = (v*255)/hist_max;
		const int32_t pos_next = (int32_t) ((double)view_width/2 + (double)((ssize_t)(i+1) - (ssize_t)hist().hist_integer_count()/2)*rect_width);
		painter->fillRect(QRect(pos, view_height-h, pos_next-pos, h), QColor(color, 255-color, 1));
		pos = pos_next;
	}

	painter->setPen(Qt::black);
	QFontMetrics fm = painter->fontMetrics();

	QString str(QString("Bin size: %1").arg(hist().size_interval()));
	painter->drawText(QPoint(std::max(view_width - fm.width(str) - 10, 0), fm.height()+5), str);

	str = QString("Number of bins: %1").arg(hist().hist_integer_count());
	painter->drawText(QPoint(std::max(view_width - fm.width(str) - 10, 0), 2*(fm.height()+5)), str);

	str = QString("Histogram size: %1 KB").arg((sizeof(uint32_t)*hist().hist_integer_count())/1024.0);
	painter->drawText(QPoint(std::max(view_width - fm.width(str) - 10, 0), 3*(fm.height()+5)), str);

	str = QString("Time : %1 ms").arg(_time_compute * 1000.0);
	painter->drawText(QPoint(std::max(view_width - fm.width(str) - 10, 0), 4*(fm.height()+5)), str);
}

QSize HistogramView::sizeHint() const
{
	return QSize(600, 400);
}
