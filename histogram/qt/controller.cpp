#include "controller.h"
#include "histogram_view.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

Controller::Controller(Histogram& hist, QWidget* parent):
	QDialog(parent)
{
	_hist_view = new HistogramView(hist);
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(_hist_view);

	QHBoxLayout* btns = new QHBoxLayout();
	QPushButton* btn_shrink = new QPushButton("< Shrink");
	QPushButton* btn_enlarge = new QPushButton("> Enlarge");
	btns->addWidget(btn_shrink);
	btns->addWidget(btn_enlarge);

	layout->addLayout(btns);
	setLayout(layout);

	connect(btn_shrink, SIGNAL(clicked()), _hist_view, SLOT(shrink()));
	connect(btn_enlarge, SIGNAL(clicked()), _hist_view, SLOT(enlarge()));
}
