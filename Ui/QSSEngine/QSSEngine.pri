SOURCES += \
    QSSEngine/style-loader.cpp

HEADERS += \
    QSSEngine/style-loader.h

#This part allow to copy qss files to appriopriate directory. Remeber to add make install in building step.
qss.path = $${OUT_PWD}/../Build/Data/Qss
qss.files = $${PWD}/Qss/*

INSTALLS += qss
