#!/bin/sh

glib-compile-resources --target=src/hpresources_external.c --generate-source --manual-register src/resources.gresource.xml
#glib-compile-resources --target=hpresources_external.h --generate-header --manual-register resources.gresource.xml
