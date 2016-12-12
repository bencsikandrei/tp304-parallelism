TEMPLATE = subdirs
SUBDIRS = core benchs qt benchs_plot

benchs.depends = core 
qt.depends = core
