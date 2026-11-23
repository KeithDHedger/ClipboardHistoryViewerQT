
AUTOMAKE_OPTIONS = subdir-objects
include ../flagsandlibs
include ../sources

clipboardhistoryviewerqt_SOURCES = $(COMMONSRC)

pixfilesdir = $(pkgdatadir)/pixmaps
pixfiles_DATA = ../resources/pixmaps/*

#docfilesdir = $(pkgdatadir)/docs/help
#pkgdatadir = $(datadir)/docs
#nobase_dist_pkgdata_DATA = ../resources/docs/gpl-3.0.txt ../resources/docs/help/help.html

#//helpfilesdir = $(pkgdatadir)/docs/help
#helpfiles_DATA = ../resources/docs/help/*

bin_PROGRAMS = clipboardhistoryviewerqt

man1_MANS = ../resources/man/clipboardhistoryviewerqt.1

install-exec-hook:
	install -D ../resources/pixmaps/ClipboardHistoryViewerQT.png $(DESTDIR)${prefix}/share/pixmaps/ClipboardHistoryViewerQT.png
	install -D ../resources/pixmaps/ClipboardHistoryViewerQT.desktop $(DESTDIR)${prefix}/share/applications/ClipboardHistoryViewerQT.desktop
	$(MKDIR_P) "$(DESTDIR)$(pkgdatadir)/docs"
	cp -r "$(srcdir)/../resources/docs/." "$(DESTDIR)$(pkgdatadir)/docs/"
	cp -r "../resources/icons" "$(DESTDIR)$(pkgdatadir)"

uninstall-hook:
	rm -f $(DESTDIR)${prefix}/share/applications/ClipboardHistoryViewerQT.desktop
	rm -f $(DESTDIR)${prefix}/share/pixmaps/ClipboardHistoryViewerQT.png
	rm -fr $(DESTDIR)$(pkgdatadir)

