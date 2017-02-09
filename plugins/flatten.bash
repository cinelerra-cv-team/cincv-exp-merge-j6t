#!/bin/bash

plugins=($(sed -n < Makefile.am \
		-e '/SUBDIRS/,/^$/s/\\$//p') )

unexpected() {
	echo "$mf: unexpected $*"
	echo "$line"
	bogus=t
} >&2

for p in $(IFS=$'\n'; echo "${plugins[*]}" | sort)
do
	mf="$p/Makefile.am"
	[ -f "$mf" ] && grep -q plugin_LTLIBRARIES "$mf" ||
		continue

	lp=${p,[A-Z]}	# lowercase
	bogus= picon= cppfl= header=() libadd=() extra=

	while read line
	do
		case $line in
		plugin_LTLIBRARIES*)
			if [ "${line#*= }" != "$lp.la" ]; then
				unexpected plugin_LTLIBRARIES line
			fi
			;;
		*_la_LIBADD*)
			libadd=(${line#*=})
			;;
		*_la_SOURCES*)
			sources=(${line#*=})
			;;
		AM_CXXFLAGS*)
			if [ "$line" != 'AM_CXXFLAGS = $(LARGEFILE_CFLAGS)' ]; then
				unexpected AM_CXXFLAGS
			fi
			;;
		AM_CPPFLAGS*)
			for f in ${line#*=}; do
				case $f in
				*/cinelerra | */guicast | */quicktime)
					;;
				*/libeffecttv | */colors | */libfourier)
					cppfl="$cppfl $f"
					;;
				*)
					unexpected AM_CPPFLAGS
					continue
					;;
				esac
			done
			;;
		noinst_HEADER*)
			header=(${line#*=})
			;;
		EXTRA_DIST*)
			extra=(${line#*=})
			if [ "${extra[0]}" = picon.png ]; then
				picon=$p/picon.png
				unset extra[0]
				if [ -n "$extra" ]; then
					unexpected EXTRA_DIST line
				fi
				if [ ! -f "$picon" ]; then
					unexpected missing picon.png
				fi
			fi
			;;
		"" | *_la_LDFLAGS* | "BUILT_SOURCES = picon_png.h" | \
		LIBTOOL* | "picon_png.h: picon.png" | *guicast/pngtoh* | \
		"clean-local:" | '$(RM) picon_png.h')
			# ignored lines
			;;
		*)
			unexpected line
			;;
		esac
	done < "$mf"

	if [ "$bogus" = t ]; then
		echo >&2 "SKIPPING $p"
		continue
	fi

	ltlibs+=" \\
	$lp.la"

	# if more than two sources, line up in a column
	if [ ${#sources[*]} -gt 2 ]; then
		printf -v tmp ' \\\n\t%s' "${sources[@]/#/$p/}"
	else
		tmp=" ${sources[@]/#/$p/}"
	fi
	text+="

${lp}_la_SOURCES =$tmp
${lp}_la_CXXFLAGS = \$(AM_CXXFLAGS) -I$p$cppfl"

	if [ -n "$libadd" ]; then
		libadd=(${libadd[*]#\$(top_builddir)/plugins/})
		text+="
${lp}_la_LIBADD = ${libadd[*]#../}"
	fi

	if [ -n "$header" ]; then
		# place only two per line
		printf -v tmp ' \\\n\t%s %s' "${header[@]/#/$p/}"
		noinsthdr+="${tmp% }"
	fi

	if [ -n "$picon" ]; then
		builtsrc+=" \\
	${picon/./_}.h"
		extradist+=" \\
	$picon"
		clean+="
	\$(RM) ${picon/./_}.h"
	fi

	sed -i -e "/plugins.$p.Makefile/d" ../configure.ac
	sed -i -e "/	$p /d" Makefile.am
	rm "$mf"
done

sed -i -e '/AUTOMAKE_OPTIONS/,$d' Makefile.am

cat <<\EOF >> Makefile.am
AM_LDFLAGS = -avoid-version -module -shared
AM_CXXFLAGS = $(LARGEFILE_CFLAGS)
AM_CPPFLAGS = \
	-I$(top_srcdir)/guicast \
	-I$(top_srcdir)/cinelerra \
	-I$(top_srcdir)/quicktime
LIBTOOL = $(SHELL) $(top_builddir)/libtool $(LTCXX_FLAGS)

%_png.h : %.png
	$(top_builddir)/guicast/pngtoh $< > $@ || { rm -f $@; exit 1; }
EOF
cat <<EOF >> Makefile.am

plugin_LTLIBRARIES =$ltlibs$text

noinst_HEADERS =$noinsthdr

BUILT_SOURCES =$builtsrc

clean-local:$clean

EXTRA_DIST =$extradist
EOF
