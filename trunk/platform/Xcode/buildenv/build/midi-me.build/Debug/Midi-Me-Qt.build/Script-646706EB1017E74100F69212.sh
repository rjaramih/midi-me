#!/bin/sh
for header in $(find ${SOURCE_ROOT}/../../../src/PropertiesEditor/ -name '*.h') ; do if grep --quiet Q_OBJECT ${header}; then echo "Moc'ing ${header}" ; moc -o ${DERIVED_FILES_DIR}/${header}_moc.cpp ${header} ; else echo "Not moc'ing ${header}" ; fi ; done
