
AUTOMAKE_OPTIONS = subdir-objects
include ../flagsandlibs
include ../sources

clipboardhistoryviewerqt_SOURCES = $(COMMONSRC)

pixfilesdir = $(pkgdatadir)/pixmaps
pixfiles_DATA = ../resources/pixmaps/*

docfilesdir = $(pkgdatadir)/docs
docfiles_DATA = ../resources/docs/*

bin_PROGRAMS = clipboardhistoryviewerqt

man1_MANS = ../resources/man/clipboardhistoryviewerqt.1

install-exec-hook:
	install -D ../resources/pixmaps/ClipboardHistoryViewerQT.png $(DESTDIR)${prefix}/share/pixmaps/ClipboardHistoryViewerQT.png
	install -D ../resources/pixmaps/ClipboardHistoryViewerQT.desktop $(DESTDIR)${prefix}/share/applications/ClipboardHistoryViewerQT.desktop

uninstall-hook:
	rm -f $(DESTDIR)${prefix}/share/applications/ClipboardHistoryViewerQT.desktop
	rm -f $(DESTDIR)${prefix}/share/pixmaps/ClipboardHistoryViewerQT.png
	rm -fr $(DESTDIR)$(pkgdatadir)

