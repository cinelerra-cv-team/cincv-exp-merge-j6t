THEMES= \
	suv \
	bluedottheme \
	defaulttheme

SUBDIRS= \
	$(THEMES) \
	libfourier \
	colors \
	libeffecttv

AM_LDFLAGS = -avoid-version -module -shared
AM_CXXFLAGS = $(LARGEFILE_CFLAGS)
AM_CPPFLAGS = \
	-I$(top_srcdir)/guicast \
	-I$(top_srcdir)/cinelerra \
	-I$(top_srcdir)/quicktime
LIBTOOL = $(SHELL) $(top_builddir)/libtool $(LTCXX_FLAGS)

%_png.h : %.png
	$(top_builddir)/guicast/pngtoh $< > $@ || { rm -f $@; exit 1; }

plugin_LTLIBRARIES = \
	1080to540.la \
	720to480.la \
	c41.la \
	aging.la \
	bandslide.la \
	bandwipe.la \
	bluebanana.la \
	blur.la \
	brightness.la \
	burn.la \
	cdripper.la \
	chromakey.la \
	chromakeyhsv.la \
	color3way.la \
	colorbalance.la \
	compressor.la \
	crossfade.la \
	decimate.la \
	deinterlace.la \
	delayaudio.la \
	delayvideo.la \
	denoise.la \
	denoisefft.la \
	denoiseseltempavg.la \
	denoisevideo.la \
	despike.la \
	diffkey.la \
	dissolve.la \
	dot.la \
	downsample.la \
	fieldframe.la \
	flash.la \
	flip.la \
	framefield.la \
	freeverb.la \
	freezeframe.la \
	gain.la \
	gamma.la \
	gradient.la \
	greycstoration.la \
	histogram.la \
	holo.la \
	huesaturation.la \
	interpolateaudio.la \
	interpolatevideo.la \
	invertaudio.la \
	invertvideo.la \
	irissquare.la \
	ivtc.la \
	lens.la \
	level.la \
	linearblur.la \
	liveaudio.la \
	livevideo.la \
	loopaudio.la \
	loopvideo.la \
	motion.la \
	motionblur.la \
	normalize.la \
	oilpainting.la \
	overlay.la \
	overlayaudio.la \
	parametric.la \
	perspective.la \
	pitch.la \
	polar.la \
	radialblur.la \
	reframe.la \
	reframert.la \
	reroute.la \
	resample.la \
	reverb.la \
	reverseaudio.la \
	reversevideo.la \
	rgb601.la \
	rotate.la \
	scale.la \
	sharpen.la \
	shapewipe.la \
	shiftinterlace.la \
	slide.la \
	spectrogram.la \
	svg.la \
	swapchannels.la \
	synthesizer.la \
	threshold.la \
	timeavg.la \
	timefront.la \
	timestretch.la \
	titler.la \
	translate.la \
	unsharp.la \
	videoscope.la \
	wave.la \
	whirl.la \
	wipe.la \
	yuv.la \
	zoomblur.la

1080to540_la_SOURCES = 1080to540/1080to540.C
1080to540_la_CXXFLAGS = $(AM_CXXFLAGS) -I1080to540

720to480_la_SOURCES = 720to480/720to480.C
720to480_la_CXXFLAGS = $(AM_CXXFLAGS) -I720to480

c41_la_SOURCES = C41/c41.C
c41_la_CXXFLAGS = $(AM_CXXFLAGS) -IC41 -I$(top_srcdir)/plugins/colors
c41_la_LIBADD = colors/libcolors.la

aging_la_SOURCES = aging/aging.C aging/agingwindow.C
aging_la_CXXFLAGS = $(AM_CXXFLAGS) -Iaging -I$(top_srcdir)/plugins/libeffecttv -I$(top_srcdir)/plugins/colors
aging_la_LIBADD = libeffecttv/libeffecttv.la

bandslide_la_SOURCES = bandslide/bandslide.C
bandslide_la_CXXFLAGS = $(AM_CXXFLAGS) -Ibandslide

bandwipe_la_SOURCES = bandwipe/bandwipe.C
bandwipe_la_CXXFLAGS = $(AM_CXXFLAGS) -Ibandwipe

bluebanana_la_SOURCES = \
	bluebanana/bluebanana.C \
	bluebanana/bluebananaconfig.C \
	bluebanana/bluebananaslider.C \
	bluebanana/bluebananawindow.C \
	bluebanana/bluebananalookups.C \
	bluebanana/bluebananaengine.C
bluebanana_la_CXXFLAGS = $(AM_CXXFLAGS) -Ibluebanana -I$(top_srcdir)/plugins/colors
bluebanana_la_LIBADD = colors/libcolors.la

blur_la_SOURCES = blur/blur.C blur/blurwindow.C
blur_la_CXXFLAGS = $(AM_CXXFLAGS) -Iblur

brightness_la_SOURCES = brightness/brightness.C brightness/brightnesswindow.C
brightness_la_CXXFLAGS = $(AM_CXXFLAGS) -Ibrightness -I$(top_srcdir)/plugins/colors
brightness_la_LIBADD = colors/libcolors.la

burn_la_SOURCES = burn/burn.C burn/burnwindow.C
burn_la_CXXFLAGS = $(AM_CXXFLAGS) -Iburn -I$(top_srcdir)/plugins/libeffecttv -I$(top_srcdir)/plugins/colors
burn_la_LIBADD = libeffecttv/libeffecttv.la

cdripper_la_SOURCES = cdripper/cdripper.C cdripper/cdripwindow.C
cdripper_la_CXXFLAGS = $(AM_CXXFLAGS) -Icdripper

chromakey_la_SOURCES = chromakey/chromakey.C
chromakey_la_CXXFLAGS = $(AM_CXXFLAGS) -Ichromakey -I$(top_srcdir)/plugins/colors
chromakey_la_LIBADD = colors/libcolors.la

chromakeyhsv_la_SOURCES = chromakeyhsv/chromakey.C chromakeyhsv/chromakey_sl.c
chromakeyhsv_la_CXXFLAGS = $(AM_CXXFLAGS) -Ichromakeyhsv -I$(top_srcdir)/plugins/colors
chromakeyhsv_la_LIBADD = colors/libcolors.la
chromakeyhsv/chromakey_sl.c: chromakeyhsv/chromakey.sl
	(echo "const char _binary_chromakey_sl_start[] ="; \
	sed -e 's/\\/\\\\/' -e 's/"/\\"/' \
	-e 's/^/"/' -e 's/$$/\\n"/' < $(srcdir)/chromakeyhsv/chromakey.sl; \
	echo ";") > chromakeyhsv/chromakey_sl.c

color3way_la_SOURCES = \
	color3way/aggregated.h \
	color3way/color3way.C \
	color3way/color3way.h \
	color3way/color3waywindow.C \
	color3way/color3waywindow.h
color3way_la_CXXFLAGS = $(AM_CXXFLAGS) -Icolor3way

colorbalance_la_SOURCES = colorbalance/colorbalance.C colorbalance/colorbalancewindow.C
colorbalance_la_CXXFLAGS = $(AM_CXXFLAGS) -Icolorbalance -I$(top_srcdir)/plugins/colors
colorbalance_la_LIBADD = colors/libcolors.la

compressor_la_SOURCES = compressor/compressor.C
compressor_la_CXXFLAGS = $(AM_CXXFLAGS) -Icompressor

crossfade_la_SOURCES = crossfade/crossfade.C
crossfade_la_CXXFLAGS = $(AM_CXXFLAGS) -Icrossfade

decimate_la_SOURCES = decimate/decimate.C
decimate_la_CXXFLAGS = $(AM_CXXFLAGS) -Idecimate

deinterlace_la_SOURCES = deinterlace/deinterlace.C deinterlace/deinterwindow.C
deinterlace_la_CXXFLAGS = $(AM_CXXFLAGS) -Ideinterlace

delayaudio_la_SOURCES = delayaudio/delayaudio.C
delayaudio_la_CXXFLAGS = $(AM_CXXFLAGS) -Idelayaudio

delayvideo_la_SOURCES = delayvideo/delayvideo.C
delayvideo_la_CXXFLAGS = $(AM_CXXFLAGS) -Idelayvideo

denoise_la_SOURCES = denoise/denoise.C
denoise_la_CXXFLAGS = $(AM_CXXFLAGS) -Idenoise

denoisefft_la_SOURCES = denoisefft/denoisefft.C
denoisefft_la_CXXFLAGS = $(AM_CXXFLAGS) -Idenoisefft -I$(top_srcdir)/plugins/libfourier
denoisefft_la_LIBADD = libfourier/libfourier.la

denoiseseltempavg_la_SOURCES = denoiseseltempavg/seltempavg.C denoiseseltempavg/seltempavgwindow.C
denoiseseltempavg_la_CXXFLAGS = $(AM_CXXFLAGS) -Idenoiseseltempavg

denoisevideo_la_SOURCES = denoisevideo/denoisevideo.C
denoisevideo_la_CXXFLAGS = $(AM_CXXFLAGS) -Idenoisevideo

despike_la_SOURCES = despike/despike.C despike/despikewindow.C
despike_la_CXXFLAGS = $(AM_CXXFLAGS) -Idespike

diffkey_la_SOURCES = diffkey/diffkey.C
diffkey_la_CXXFLAGS = $(AM_CXXFLAGS) -Idiffkey -I$(top_srcdir)/plugins/colors
diffkey_la_LIBADD = colors/libcolors.la

dissolve_la_SOURCES = dissolve/dissolve.C
dissolve_la_CXXFLAGS = $(AM_CXXFLAGS) -Idissolve

dot_la_SOURCES = dot/dot.C dot/dotwindow.C
dot_la_CXXFLAGS = $(AM_CXXFLAGS) -Idot -I$(top_srcdir)/plugins/libeffecttv -I$(top_srcdir)/plugins/colors
dot_la_LIBADD = libeffecttv/libeffecttv.la

downsample_la_SOURCES = downsample/downsample.C
downsample_la_CXXFLAGS = $(AM_CXXFLAGS) -Idownsample

fieldframe_la_SOURCES = fieldframe/fieldframe.C
fieldframe_la_CXXFLAGS = $(AM_CXXFLAGS) -Ifieldframe

flash_la_SOURCES = flash/flash.C
flash_la_CXXFLAGS = $(AM_CXXFLAGS) -Iflash

flip_la_SOURCES = flip/flip.C flip/flipwindow.C
flip_la_CXXFLAGS = $(AM_CXXFLAGS) -Iflip

framefield_la_SOURCES = framefield/framefield.C
framefield_la_CXXFLAGS = $(AM_CXXFLAGS) -Iframefield

freeverb_la_SOURCES = \
	freeverb/Components/allpass.cpp \
	freeverb/Components/comb.cpp \
	freeverb/Components/revmodel.cpp \
	freeverb/freeverb.C
freeverb_la_CXXFLAGS = $(AM_CXXFLAGS) -Ifreeverb -I$(srcdir)/freeverb/Components

freezeframe_la_SOURCES = freezeframe/freezeframe.C
freezeframe_la_CXXFLAGS = $(AM_CXXFLAGS) -Ifreezeframe

gain_la_SOURCES = gain/gain.C gain/gainwindow.C
gain_la_CXXFLAGS = $(AM_CXXFLAGS) -Igain

gamma_la_SOURCES = gamma/gamma.C gamma/gammawindow.C
gamma_la_CXXFLAGS = $(AM_CXXFLAGS) -Igamma -I$(top_srcdir)/plugins/colors
gamma_la_LIBADD = colors/libcolors.la

gradient_la_SOURCES = gradient/gradient.C
gradient_la_CXXFLAGS = $(AM_CXXFLAGS) -Igradient -I$(top_srcdir)/plugins/colors
gradient_la_LIBADD = colors/libcolors.la

greycstoration_la_SOURCES = greycstoration/greycstorationwindow.C greycstoration/greycstorationplugin.C
greycstoration_la_CXXFLAGS = $(AM_CXXFLAGS) -Igreycstoration

histogram_la_SOURCES = \
	histogram/histogram.C \
	histogram/histogramconfig.C \
	histogram/histogramwindow.C
histogram_la_CXXFLAGS = $(AM_CXXFLAGS) -Ihistogram -I$(top_srcdir)/plugins/colors
histogram_la_LIBADD = colors/libcolors.la

holo_la_SOURCES = holo/holo.C holo/holowindow.C
holo_la_CXXFLAGS = $(AM_CXXFLAGS) -Iholo -I$(top_srcdir)/plugins/libeffecttv -I$(top_srcdir)/plugins/colors
holo_la_LIBADD = libeffecttv/libeffecttv.la

huesaturation_la_SOURCES = huesaturation/huesaturation.C
huesaturation_la_CXXFLAGS = $(AM_CXXFLAGS) -Ihuesaturation -I$(top_srcdir)/plugins/colors
huesaturation_la_LIBADD = colors/libcolors.la

interpolateaudio_la_SOURCES = interpolateaudio/interpolateaudio.C
interpolateaudio_la_CXXFLAGS = $(AM_CXXFLAGS) -Iinterpolateaudio

interpolatevideo_la_SOURCES = interpolatevideo/interpolatevideo.C
interpolatevideo_la_CXXFLAGS = $(AM_CXXFLAGS) -Iinterpolatevideo

invertaudio_la_SOURCES = invertaudio/invert.C
invertaudio_la_CXXFLAGS = $(AM_CXXFLAGS) -Iinvertaudio

invertvideo_la_SOURCES = invertvideo/invert.C
invertvideo_la_CXXFLAGS = $(AM_CXXFLAGS) -Iinvertvideo -I$(top_srcdir)/plugins/colors
invertvideo_la_LIBADD = colors/libcolors.la

irissquare_la_SOURCES = irissquare/irissquare.C
irissquare_la_CXXFLAGS = $(AM_CXXFLAGS) -Iirissquare

ivtc_la_SOURCES = ivtc/ivtc.C ivtc/ivtcwindow.C
ivtc_la_CXXFLAGS = $(AM_CXXFLAGS) -Iivtc

lens_la_SOURCES = lens/lens.C lens/lens.h
lens_la_CXXFLAGS = $(AM_CXXFLAGS) -Ilens

level_la_SOURCES = level/leveleffect.C
level_la_CXXFLAGS = $(AM_CXXFLAGS) -Ilevel

linearblur_la_SOURCES = linearblur/linearblur.C
linearblur_la_CXXFLAGS = $(AM_CXXFLAGS) -Ilinearblur

liveaudio_la_SOURCES = liveaudio/liveaudio.C
liveaudio_la_CXXFLAGS = $(AM_CXXFLAGS) -Iliveaudio

livevideo_la_SOURCES = livevideo/livevideo.C
livevideo_la_CXXFLAGS = $(AM_CXXFLAGS) -Ilivevideo

loopaudio_la_SOURCES = loopaudio/loopaudio.C
loopaudio_la_CXXFLAGS = $(AM_CXXFLAGS) -Iloopaudio

loopvideo_la_SOURCES = loopvideo/loopvideo.C
loopvideo_la_CXXFLAGS = $(AM_CXXFLAGS) -Iloopvideo

motion_la_SOURCES = motion/motion.C motion/motionwindow.C
motion_la_CXXFLAGS = $(AM_CXXFLAGS) -Imotion

motionblur_la_SOURCES = motionblur/motionblur.C
motionblur_la_CXXFLAGS = $(AM_CXXFLAGS) -Imotionblur

normalize_la_SOURCES = normalize/normalize.C normalize/normalizewindow.C
normalize_la_CXXFLAGS = $(AM_CXXFLAGS) -Inormalize

oilpainting_la_SOURCES = oilpainting/oil.C
oilpainting_la_CXXFLAGS = $(AM_CXXFLAGS) -Ioilpainting

overlay_la_SOURCES = overlay/overlay.C
overlay_la_CXXFLAGS = $(AM_CXXFLAGS) -Ioverlay

overlayaudio_la_SOURCES = overlayaudio/overlayaudio.C
overlayaudio_la_CXXFLAGS = $(AM_CXXFLAGS) -Ioverlayaudio

parametric_la_SOURCES = parametric/parametric.C
parametric_la_CXXFLAGS = $(AM_CXXFLAGS) -Iparametric -I$(top_srcdir)/plugins/libfourier
parametric_la_LIBADD = libfourier/libfourier.la

perspective_la_SOURCES = perspective/perspective.C
perspective_la_CXXFLAGS = $(AM_CXXFLAGS) -Iperspective

pitch_la_SOURCES = pitch/pitch.C
pitch_la_CXXFLAGS = $(AM_CXXFLAGS) -Ipitch -I$(top_srcdir)/plugins/libfourier
pitch_la_LIBADD = libfourier/libfourier.la

polar_la_SOURCES = polar/polar.C
polar_la_CXXFLAGS = $(AM_CXXFLAGS) -Ipolar

radialblur_la_SOURCES = radialblur/radialblur.C
radialblur_la_CXXFLAGS = $(AM_CXXFLAGS) -Iradialblur

reframe_la_SOURCES = reframe/reframe.C
reframe_la_CXXFLAGS = $(AM_CXXFLAGS) -Ireframe

reframert_la_SOURCES = reframert/reframert.C
reframert_la_CXXFLAGS = $(AM_CXXFLAGS) -Ireframert

reroute_la_SOURCES = reroute/reroute.C
reroute_la_CXXFLAGS = $(AM_CXXFLAGS) -Ireroute

resample_la_SOURCES = resample/resample.C
resample_la_CXXFLAGS = $(AM_CXXFLAGS) -Iresample

reverb_la_SOURCES = reverb/reverb.C reverb/reverbwindow.C
reverb_la_CXXFLAGS = $(AM_CXXFLAGS) -Ireverb

reverseaudio_la_SOURCES = reverseaudio/reverseaudio.C
reverseaudio_la_CXXFLAGS = $(AM_CXXFLAGS) -Ireverseaudio

reversevideo_la_SOURCES = reversevideo/reversevideo.C
reversevideo_la_CXXFLAGS = $(AM_CXXFLAGS) -Ireversevideo

rgb601_la_SOURCES = rgb601/rgb601.C rgb601/rgb601window.C
rgb601_la_CXXFLAGS = $(AM_CXXFLAGS) -Irgb601

rotate_la_SOURCES = rotate/rotate.C
rotate_la_CXXFLAGS = $(AM_CXXFLAGS) -Irotate

scale_la_SOURCES = scale/scale.C scale/scalewin.C
scale_la_CXXFLAGS = $(AM_CXXFLAGS) -Iscale

shapewipe_la_SOURCES = shapewipe/shapewipe.C
shapewipe_la_CXXFLAGS = $(AM_CXXFLAGS) -DDEFAULT_SHAPE=\"$(shapewipedir)/heart.png\" -Ishapewipe
shapewipedir = $(plugindir)/shapewipe
shapewipe_DATA = \
	shapewipe/circle.png \
	shapewipe/clock.png \
	shapewipe/heart.png \
	shapewipe/tile2x2h.png \
	shapewipe/tile2x2v.png

sharpen_la_SOURCES = sharpen/sharpen.C sharpen/sharpenwindow.C
sharpen_la_CXXFLAGS = $(AM_CXXFLAGS) -Isharpen

shiftinterlace_la_SOURCES = shiftinterlace/shiftinterlace.C
shiftinterlace_la_CXXFLAGS = $(AM_CXXFLAGS) -Ishiftinterlace

slide_la_SOURCES = slide/slide.C
slide_la_CXXFLAGS = $(AM_CXXFLAGS) -Islide

spectrogram_la_SOURCES = spectrogram/spectrogram.C
spectrogram_la_CXXFLAGS = $(AM_CXXFLAGS) -Ispectrogram -I$(top_srcdir)/plugins/libfourier
spectrogram_la_LIBADD = libfourier/libfourier.la

svg_la_SOURCES = svg/svg.C svg/svgwin.C
svg_la_CXXFLAGS = $(AM_CXXFLAGS) -Isvg

swapchannels_la_SOURCES = swapchannels/swapchannels.C
swapchannels_la_CXXFLAGS = $(AM_CXXFLAGS) -Iswapchannels

synthesizer_la_SOURCES = synthesizer/synthesizer.C
synthesizer_la_CXXFLAGS = $(AM_CXXFLAGS) -Isynthesizer

threshold_la_SOURCES = \
	threshold/threshold.C \
	threshold/thresholdwindow.C \
	threshold/histogramengine.C
threshold_la_CXXFLAGS = $(AM_CXXFLAGS) -Ithreshold -I$(top_srcdir)/plugins/colors
threshold_la_LIBADD = colors/libcolors.la

timeavg_la_SOURCES = timeavg/timeavg.C timeavg/timeavgwindow.C
timeavg_la_CXXFLAGS = $(AM_CXXFLAGS) -Itimeavg

timefront_la_SOURCES = timefront/timefront.C
timefront_la_CXXFLAGS = $(AM_CXXFLAGS) -Itimefront -I$(top_srcdir)/plugins/colors
timefront_la_LIBADD = colors/libcolors.la

timestretch_la_SOURCES = timestretch/timestretch.C timestretch/timestretchengine.C
timestretch_la_CXXFLAGS = $(AM_CXXFLAGS) -Itimestretch -I$(top_srcdir)/plugins/libfourier
timestretch_la_LIBADD = libfourier/libfourier.la

titler_la_SOURCES = titler/title.C titler/titlewindow.C
titler_la_CXXFLAGS = $(AM_CXXFLAGS) -Ititler ${FREETYPE_CFLAGS} -I$(top_srcdir)/plugins/colors
titler_la_LIBADD = colors/libcolors.la

translate_la_SOURCES = translate/translate.C translate/translatewin.C
translate_la_CXXFLAGS = $(AM_CXXFLAGS) -Itranslate

unsharp_la_SOURCES = unsharp/unsharp.C unsharp/unsharpwindow.C
unsharp_la_CXXFLAGS = $(AM_CXXFLAGS) -Iunsharp

videoscope_la_SOURCES = videoscope/videoscope.C
videoscope_la_CXXFLAGS = $(AM_CXXFLAGS) -Ivideoscope -I$(top_srcdir)/plugins/colors
videoscope_la_LIBADD = colors/libcolors.la

wave_la_SOURCES = wave/wave.C
wave_la_CXXFLAGS = $(AM_CXXFLAGS) -Iwave

whirl_la_SOURCES = whirl/whirl.C
whirl_la_CXXFLAGS = $(AM_CXXFLAGS) -Iwhirl

wipe_la_SOURCES = wipe/wipe.C
wipe_la_CXXFLAGS = $(AM_CXXFLAGS) -Iwipe

yuv_la_SOURCES = yuv/yuv.C
yuv_la_CXXFLAGS = $(AM_CXXFLAGS) -Iyuv -I$(top_srcdir)/plugins/colors
yuv_la_LIBADD = colors/libcolors.la

zoomblur_la_SOURCES = zoomblur/zoomblur.C
zoomblur_la_CXXFLAGS = $(AM_CXXFLAGS) -Izoomblur

noinst_HEADERS = \
	1080to540/1080to540.h \
	720to480/720to480.h \
	aging/aging.h aging/agingwindow.h \
	bandslide/bandslide.h \
	bandwipe/bandwipe.h \
	bluebanana/bluebanana.h bluebanana/bluebananaconfig.h \
	bluebanana/bluebananaslider.h bluebanana/bluebananacolor.c \
	bluebanana/bluebananawindow.h \
	blur/blur.h blur/blur.inc \
	blur/blurwindow.h blur/blurwindow.inc \
	brightness/brightness.h brightness/brightnesswindow.h \
	burn/burn.h burn/burnwindow.h \
	cdripper/cdripper.h cdripper/cdripwindow.h \
	chromakey/chromakey.h \
	chromakeyhsv/chromakey.h \
	colorbalance/aggregated.h colorbalance/colorbalance.h \
	colorbalance/colorbalancewindow.h \
	compressor/compressor.h \
	crossfade/crossfade.h \
	deinterlace/deinterlace.h deinterlace/deinterwindow.h \
	delayaudio/delayaudio.h \
	delayvideo/delayvideo.h \
	denoise/denoise.h \
	denoiseseltempavg/seltempavg.h denoiseseltempavg/seltempavgwindow.h \
	denoisevideo/denoisevideo.h \
	despike/despike.h despike/despikewindow.h \
	dissolve/dissolve.h \
	dot/dot.h dot/dotwindow.h \
	flash/flash.h \
	flip/flip.h flip/flipwindow.h \
	freeverb/Components/allpass.hpp freeverb/Components/comb.hpp \
	freeverb/Components/denormals.h freeverb/Components/revmodel.hpp \
	freeverb/Components/tuning.h \
	freezeframe/freezeframe.h \
	gain/gain.h gain/gainwindow.h \
	gamma/aggregated.h gamma/gamma.h \
	gamma/gammawindow.h \
	gradient/gradient.h \
	greycstoration/greycstorationplugin.h greycstoration/greycstorationwindow.h \
	greycstoration/greycstoration.h \
	histogram/aggregated.h histogram/histogram.h \
	histogram/histogramconfig.h histogram/histogramwindow.h \
	histogram/histogram.inc histogram/histogramconfig.inc \
	histogram/histogramwindow.inc \
	holo/holo.h holo/holowindow.h \
	irissquare/irissquare.h \
	ivtc/ivtc.h ivtc/ivtcwindow.h \
	level/leveleffect.h \
	motion/motion.h motion/motion.inc \
	motion/motionwindow.h motion/motionwindow.inc \
	normalize/normalize.h normalize/normalizewindow.h \
	parametric/parametric.h \
	perspective/perspective.h \
	pitch/pitch.h \
	reframe/reframe.h \
	resample/resample.h \
	reverb/reverb.h reverb/reverb.inc \
	reverb/reverbwindow.h reverb/reverbwindow.inc \
	rgb601/rgb601.h rgb601/rgb601window.h \
	scale/scale.h scale/scalewin.h \
	shapewipe/shapewipe.h \
	sharpen/sharpen.h sharpen/sharpenwindow.h \
	slide/slide.h \
	spectrogram/spectrogram.h \
	svg/empty_svg.h svg/svg.h \
	svg/svgwin.h \
	swapchannels/swapchannels.h \
	synthesizer/synthesizer.h synthesizer/synthesizer.inc \
	synthesizer/synthwindow.inc \
	threshold/histogramengine.h threshold/histogramengine.inc \
	threshold/threshold.h threshold/threshold.inc \
	threshold/thresholdwindow.h threshold/thresholdwindow.inc \
	timeavg/timeavg.h timeavg/timeavgwindow.h \
	timefront/timefront.h \
	timestretch/timestretch.h timestretch/timestretchengine.h \
	timestretch/timestretchengine.inc \
	titler/title.h titler/titlewindow.h \
	translate/translate.h translate/translatewin.h \
	unsharp/unsharp.h unsharp/unsharp.inc \
	unsharp/unsharpwindow.h unsharp/unsharpwindow.inc \
	wipe/wipe.h

BUILT_SOURCES = \
	1080to540/picon_png.h \
	C41/picon_png.h \
	aging/picon_png.h \
	bandslide/picon_png.h \
	bandwipe/picon_png.h \
	bluebanana/picon_png.h \
	blur/picon_png.h \
	brightness/picon_png.h \
	burn/picon_png.h \
	chromakey/picon_png.h \
	chromakeyhsv/chromakey_sl.c \
	chromakeyhsv/picon_png.h \
	color3way/picon_png.h \
	colorbalance/picon_png.h \
	compressor/picon_png.h \
	crossfade/picon_png.h \
	decimate/picon_png.h \
	deinterlace/picon_png.h \
	delayaudio/picon_png.h \
	delayvideo/picon_png.h \
	denoise/picon_png.h \
	denoisefft/picon_png.h \
	denoiseseltempavg/picon_png.h \
	denoisevideo/picon_png.h \
	despike/picon_png.h \
	diffkey/picon_png.h \
	dissolve/picon_png.h \
	dot/picon_png.h \
	downsample/picon_png.h \
	fieldframe/picon_png.h \
	flash/picon_png.h \
	flip/picon_png.h \
	framefield/picon_png.h \
	freeverb/picon_png.h \
	freezeframe/picon_png.h \
	gain/picon_png.h \
	gamma/picon_png.h \
	gradient/picon_png.h \
	greycstoration/picon_png.h \
	histogram/picon_png.h \
	histogram/max_picon_png.h \
	histogram/mid_picon_png.h \
	histogram/min_picon_png.h \
	holo/picon_png.h \
	huesaturation/picon_png.h \
	interpolateaudio/picon_png.h \
	interpolatevideo/picon_png.h \
	invertaudio/picon_png.h \
	invertvideo/picon_png.h \
	irissquare/picon_png.h \
	ivtc/picon_png.h \
	lens/picon_png.h \
	level/picon_png.h \
	linearblur/picon_png.h \
	liveaudio/picon_png.h \
	livevideo/picon_png.h \
	loopaudio/picon_png.h \
	loopvideo/picon_png.h \
	motion/picon_png.h \
	motionblur/picon_png.h \
	normalize/picon_png.h \
	oilpainting/picon_png.h \
	overlay/picon_png.h \
	overlayaudio/picon_png.h \
	parametric/picon_png.h \
	perspective/picon_png.h \
	pitch/picon_png.h \
	polar/picon_png.h \
	radialblur/picon_png.h \
	reframe/picon_png.h \
	reframert/picon_png.h \
	reroute/picon_png.h \
	resample/picon_png.h \
	reverb/picon_png.h \
	reverseaudio/picon_png.h \
	reversevideo/picon_png.h \
	rgb601/picon_png.h \
	rotate/picon_png.h \
	scale/picon_png.h \
	shapewipe/picon_png.h \
	sharpen/picon_png.h \
	shiftinterlace/picon_png.h \
	slide/picon_png.h \
	spectrogram/picon_png.h \
	svg/picon_png.h \
	swapchannels/picon_png.h \
	synthesizer/picon_png.h \
	threshold/picon_png.h \
	timeavg/picon_png.h \
	timefront/picon_png.h \
	timestretch/picon_png.h \
	titler/picon_png.h \
	translate/picon_png.h \
	unsharp/picon_png.h \
	videoscope/picon_png.h \
	wave/picon_png.h \
	whirl/picon_png.h \
	wipe/picon_png.h \
	yuv/picon_png.h \
	zoomblur/picon_png.h

clean-local:
	$(RM) 1080to540/picon_png.h
	$(RM) C41/picon_png.h
	$(RM) aging/picon_png.h
	$(RM) bandslide/picon_png.h
	$(RM) bandwipe/picon_png.h
	$(RM) bluebanana/picon_png.h
	$(RM) blur/picon_png.h
	$(RM) brightness/picon_png.h
	$(RM) burn/picon_png.h
	$(RM) chromakey/picon_png.h
	$(RM) chromakeyhsv/chromakey_sl.c
	$(RM) chromakeyhsv/picon_png.h
	$(RM) color3way/picon_png.h
	$(RM) colorbalance/picon_png.h
	$(RM) compressor/picon_png.h
	$(RM) crossfade/picon_png.h
	$(RM) decimate/picon_png.h
	$(RM) deinterlace/picon_png.h
	$(RM) delayaudio/picon_png.h
	$(RM) delayvideo/picon_png.h
	$(RM) denoise/picon_png.h
	$(RM) denoisefft/picon_png.h
	$(RM) denoiseseltempavg/picon_png.h
	$(RM) denoisevideo/picon_png.h
	$(RM) despike/picon_png.h
	$(RM) diffkey/picon_png.h
	$(RM) dissolve/picon_png.h
	$(RM) dot/picon_png.h
	$(RM) downsample/picon_png.h
	$(RM) fieldframe/picon_png.h
	$(RM) flash/picon_png.h
	$(RM) flip/picon_png.h
	$(RM) framefield/picon_png.h
	$(RM) freeverb/picon_png.h
	$(RM) freezeframe/picon_png.h
	$(RM) gain/picon_png.h
	$(RM) gamma/picon_png.h
	$(RM) gradient/picon_png.h
	$(RM) greycstoration/picon_png.h
	$(RM) histogram/picon_png.h
	$(RM) histogram/max_picon_png.h
	$(RM) histogram/mid_picon_png.h
	$(RM) histogram/min_picon_png.h
	$(RM) holo/picon_png.h
	$(RM) huesaturation/picon_png.h
	$(RM) interpolateaudio/picon_png.h
	$(RM) interpolatevideo/picon_png.h
	$(RM) invertaudio/picon_png.h
	$(RM) invertvideo/picon_png.h
	$(RM) irissquare/picon_png.h
	$(RM) ivtc/picon_png.h
	$(RM) lens/picon_png.h
	$(RM) level/picon_png.h
	$(RM) linearblur/picon_png.h
	$(RM) liveaudio/picon_png.h
	$(RM) livevideo/picon_png.h
	$(RM) loopaudio/picon_png.h
	$(RM) loopvideo/picon_png.h
	$(RM) motion/picon_png.h
	$(RM) motionblur/picon_png.h
	$(RM) normalize/picon_png.h
	$(RM) oilpainting/picon_png.h
	$(RM) overlay/picon_png.h
	$(RM) overlayaudio/picon_png.h
	$(RM) parametric/picon_png.h
	$(RM) perspective/picon_png.h
	$(RM) pitch/picon_png.h
	$(RM) polar/picon_png.h
	$(RM) radialblur/picon_png.h
	$(RM) reframe/picon_png.h
	$(RM) reframert/picon_png.h
	$(RM) reroute/picon_png.h
	$(RM) resample/picon_png.h
	$(RM) reverb/picon_png.h
	$(RM) reverseaudio/picon_png.h
	$(RM) reversevideo/picon_png.h
	$(RM) rgb601/picon_png.h
	$(RM) rotate/picon_png.h
	$(RM) scale/picon_png.h
	$(RM) shapewipe/picon_png.h
	$(RM) sharpen/picon_png.h
	$(RM) shiftinterlace/picon_png.h
	$(RM) slide/picon_png.h
	$(RM) spectrogram/picon_png.h
	$(RM) svg/picon_png.h
	$(RM) swapchannels/picon_png.h
	$(RM) synthesizer/picon_png.h
	$(RM) threshold/picon_png.h
	$(RM) timeavg/picon_png.h
	$(RM) timefront/picon_png.h
	$(RM) timestretch/picon_png.h
	$(RM) titler/picon_png.h
	$(RM) translate/picon_png.h
	$(RM) unsharp/picon_png.h
	$(RM) videoscope/picon_png.h
	$(RM) wave/picon_png.h
	$(RM) whirl/picon_png.h
	$(RM) wipe/picon_png.h
	$(RM) yuv/picon_png.h
	$(RM) zoomblur/picon_png.h

EXTRA_DIST = \
	1080to540/picon.png \
	C41/picon.png \
	aging/picon.png \
	bandslide/picon.png \
	bandwipe/picon.png \
	bluebanana/picon.png \
	blur/picon.png \
	brightness/picon.png \
	burn/picon.png \
	chromakey/picon.png \
	chromakeyhsv/chromakey.sl \
	chromakeyhsv/picon.png \
	color3way/picon.png \
	colorbalance/picon.png \
	compressor/picon.png \
	crossfade/picon.png \
	decimate/picon.png \
	deinterlace/picon.png \
	delayaudio/picon.png \
	delayvideo/picon.png \
	denoise/picon.png \
	denoisefft/picon.png \
	denoiseseltempavg/picon.png \
	denoisevideo/picon.png \
	despike/picon.png \
	diffkey/picon.png \
	dissolve/picon.png \
	dot/picon.png \
	downsample/picon.png \
	fieldframe/picon.png \
	flash/picon.png \
	flip/picon.png \
	framefield/picon.png \
	freeverb/picon.png \
	freezeframe/picon.png \
	gain/picon.png \
	gamma/picon.png \
	gradient/picon.png \
	greycstoration/picon.png \
	histogram/picon.png \
	histogram/max_picon.png \
	histogram/mid_picon.png \
	histogram/min_picon.png \
	holo/picon.png \
	huesaturation/picon.png \
	interpolateaudio/picon.png \
	interpolatevideo/picon.png \
	invertaudio/picon.png \
	invertvideo/picon.png \
	irissquare/picon.png \
	ivtc/picon.png \
	lens/picon.png \
	level/picon.png \
	linearblur/picon.png \
	liveaudio/picon.png \
	livevideo/picon.png \
	loopaudio/picon.png \
	loopvideo/picon.png \
	motion/picon.png \
	motionblur/picon.png \
	normalize/picon.png \
	oilpainting/picon.png \
	overlay/picon.png \
	overlayaudio/picon.png \
	parametric/picon.png \
	perspective/picon.png \
	pitch/picon.png \
	polar/picon.png \
	radialblur/picon.png \
	reframe/picon.png \
	reframert/picon.png \
	reroute/picon.png \
	resample/picon.png \
	reverb/picon.png \
	reverseaudio/picon.png \
	reversevideo/picon.png \
	rgb601/picon.png \
	rotate/picon.png \
	scale/picon.png \
	shapewipe/picon.png \
	$(shapewipe_DATA) \
	sharpen/picon.png \
	shiftinterlace/picon.png \
	slide/picon.png \
	spectrogram/picon.png \
	svg/picon.png \
	swapchannels/picon.png \
	synthesizer/picon.png \
	threshold/picon.png \
	timeavg/picon.png \
	timefront/picon.png \
	timestretch/picon.png \
	titler/picon.png \
	translate/picon.png \
	unsharp/picon.png \
	videoscope/picon.png \
	wave/picon.png \
	whirl/picon.png \
	wipe/picon.png \
	yuv/picon.png \
	zoomblur/picon.png
