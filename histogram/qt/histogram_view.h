#ifndef QT_HISTOGRAM_H
#define QT_HISTOGRAM_H

#include <QWidget>

class Histogram;

class HistogramView: public QWidget
{
	Q_OBJECT

public:
	HistogramView(Histogram& hist, QWidget* parent = nullptr);

public:
	QSize sizeHint() const override;

public slots:
	void enlarge();
	void shrink();

protected:
	void paintEvent(QPaintEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;

private:
	void compute(const double size);

private:
	Histogram& hist() { return _hist; }

private:
	Histogram& _hist;
	double _time_compute;
};

#endif
