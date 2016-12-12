#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QDialog>

class Histogram;
class HistogramView;

class Controller: public QDialog
{
public:
	Controller(Histogram& hist, QWidget* parent = nullptr);

private:
	HistogramView& hist_view()             { return *_hist_view; }
	HistogramView const& hist_view() const { return *_hist_view; }
private:
	HistogramView* _hist_view;

};

#endif
