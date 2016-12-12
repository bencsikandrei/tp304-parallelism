#include <iostream>
#include <exception>

#include <QApplication>

#include "controller.h"
#include "histogram.h"
#include "tools.h"

int main(int argc, char** argv)
{
	Histogram hist;
	try {
		hist = std::move(parse_args(argc, argv));
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error while parsing args: " << e.what() << std::endl;
		std::cerr << "Usage: " << argv[0] << " [--file file] [--gen-uniform N] [--gen-normal N]" << std::endl;
		return 1;
	}

	QApplication app(argc, argv);
	Controller* view = new Controller(hist, nullptr);
	view->show();

	return app.exec();
}
