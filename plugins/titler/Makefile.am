plugin_LTLIBRARIES = titler.la
titler_la_LDFLAGS = -avoid-version -module -shared 
titler_la_LIBADD = $(top_builddir)/plugins/colors/libcolors.la
titler_la_SOURCES = title.C titlewindow.C 
AM_CXXFLAGS = $(LARGEFILE_CFLAGS)

AM_CPPFLAGS = -I$(top_srcdir)/guicast -I$(top_srcdir)/cinelerra -I$(top_srcdir)/quicktime ${FREETYPE_CFLAGS} -I$(top_srcdir)/plugins/colors
LIBTOOL = $(SHELL) $(top_builddir)/libtool $(LTCXX_FLAGS)

noinst_HEADERS = title.h titlewindow.h 
EXTRA_DIST = picon.png fonts

BUILT_SOURCES = picon_png.h
picon_png.h: picon.png
	$(top_builddir)/guicast/pngtoh $^ || { rm -f $@; exit 1; }
clean-local:
	$(RM) picon_png.h

# need custom install rules because automake does not handle
# file names with blanks
fontpattern = fonts.dir *.ttf

install-data-local:
	f_inst () { \
		echo " $(MKDIR_P) '$(DESTDIR)$(fontsdir)'"; \
		$(MKDIR_P) "$(DESTDIR)$(fontsdir)" || exit 1; \
		for files; do \
			echo " $(INSTALL_DATA) '$$files' '$(DESTDIR)$(fontsdir)'"; \
			$(INSTALL_DATA) -- "$$files" '$(DESTDIR)$(fontsdir)' || exit 1; \
		done; }; \
	cd "$(srcdir)/fonts" && \
	f_inst $(fontpattern)

uninstall-local:
	f_uninst () { if cd "$(DESTDIR)$(fontsdir)"; then $(RM) -- "$$@"; fi; }; \
	cd "$(srcdir)/fonts" && \
	f_uninst $(fontpattern)
