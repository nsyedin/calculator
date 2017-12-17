TEMPLATE = subdirs
CONFIG += c++11

SUBDIRS += \
    app \
    calc

app.depends = calc
