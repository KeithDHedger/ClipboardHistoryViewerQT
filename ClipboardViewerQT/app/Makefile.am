
AUTOMAKE_OPTIONS = subdir-objects
include ../flagsandlibs
include ../sources

clipboardviewerqt_SOURCES = $(COMMONSRC)

pixfilesdir = $(pkgdatadir)/pixmaps
pixfiles_DATA = ../resources/pixmaps/*

bin_PROGRAMS = clipboardviewerqt

man1_MANS = ../resources/man/clipboardviewerqt.1

install-exec-hook:
	install -D ../resources/pixmaps/ClipboardViewerQT.png $(DESTDIR)${prefix}/share/pixmaps/ClipboardViewerQT.png
	install -D ../resources/pixmaps/ClipboardViewerQT.desktop $(DESTDIR)${prefix}/share/applications/ClipboardViewerQT.desktop

uninstall-hook:
	rm -f $(DESTDIR)${prefix}/share/applications/ClipboardViewerQT.desktop
	rm -f $(DESTDIR)${prefix}/share/pixmaps/ClipboardViewerQT.png
	rm -fr $(pkgdatadir)

