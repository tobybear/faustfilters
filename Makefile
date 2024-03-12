#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX, Christopher Arndt, and Patrick Desaulniers
#

SHELL=/bin/bash

# error out if DPF is missing, unless the current rule is 'submodules'
define MISSING_SUBMODULES_ERROR
=============================================================================
DPF library not found in directory 'dpf'.
Please run "make submodules" to clone the missing Git submodules, then retry.
=============================================================================
endef

ifneq ($(MAKECMDGOALS), submodules)
ifeq (,$(wildcard dpf/Makefile.base.mk))
    $(info $(MISSING_SUBMODULES_ERROR))
    $(error Unable to continue)
else
    include dpf/Makefile.base.mk
endif
endif

# --------------------------------------------------------------
# Plugin types to build

BUILD_CLAP ?= true
BUILD_DSSI ?= false
BUILD_JACK ?= false
BUILD_LADSPA ?= true
BUILD_LV2 ?= true
BUILD_VST2 ?= true
BUILD_VST3 ?= true

export BUILD_CLAP BUILD_DSSI BUILD_JACK BUILD_LADSPA BUILD_LV2 BUILD_VST2 BUILD_VST3

# --------------------------------------------------------------
# Installation directories

PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
LIBDIR ?= $(PREFIX)/lib
DSSI_DIR ?= $(LIBDIR)/dssi
LADSPA_DIR ?= $(LIBDIR)/ladspa
ifneq ($(MACOS_OR_WINDOWS),true)
CLAP_DIR ?= $(LIBDIR)/clap
LV2_DIR ?= $(LIBDIR)/lv2
VST2_DIR ?= $(LIBDIR)/vst
VST3_DIR ?= $(LIBDIR)/vst3
endif
ifeq ($(MACOS),true)
CLAP_DIR ?= /Library/Audio/Plug-Ins/CLAP
LV2_DIR ?= /Library/Audio/Plug-Ins/LV2
VST2_DIR ?= /Library/Audio/Plug-Ins/VST
VST3_DIR ?= /Library/Audio/Plug-Ins/VST3
endif
ifeq ($(WINDOWS),true)
CLAP_DIR ?= $(COMMONPROGRAMFILES)/CLAP
LV2_DIR ?= $(COMMONPROGRAMFILES)/LV2
VST2_DIR ?= $(COMMONPROGRAMFILES)/VST2
VST3_DIR ?= $(COMMONPROGRAMFILES)/VST3
endif

USER_DSSI_DIR ?= $(HOME)/.dssi
USER_LADSPA_DIR ?= $(HOME)/.ladspa
ifneq ($(MACOS_OR_WINDOWS),true)
USER_CLAP_DIR ?= $(HOME)/.clap
USER_LV2_DIR ?= $(HOME)/.lv2
USER_VST2_DIR ?= $(HOME)/.vst
USER_VST3_DIR ?= $(HOME)/.vst3
endif
ifeq ($(MACOS),true)
USER_CLAP_DIR ?= $(HOME)/Library/Audio/Plug-Ins/CLAP
USER_LV2_DIR ?= $(HOME)/Library/Audio/Plug-Ins/LV2
USER_VST2_DIR ?= $(HOME)/Library/Audio/Plug-Ins/VST
USER_VST3_DIR ?= $(HOME)/Library/Audio/Plug-Ins/VST3
endif
ifeq ($(WINDOWS),true)
USER_CLAP_DIR ?= $(APPDATA)/CLAP
USER_LV2_DIR ?= $(APPDATA)/LV2
USER_VST2_DIR ?= $(APPDATA)/VST
USER_VST3_DIR ?= $(APPDATA)/VST3
endif

export DESTDIR PREFIX BINDIR LIBDIR
export CLAP_DIR DSSI_DIR LADSPA_DIR LV2_DIR VST2_DIR VST3_DIR
export USER_CLAP_DIR USER_DSSI_DIR USER_LADSPA_DIR USER_LV2_DIR USER_VST2_DIR USER_VST3_DIR

# --------------------------------------------------------------

PLUGINS = \
	diodeladder \
	korg35hpf \
	korg35lpf \
	moogladder \
	mooghalfladder \
	oberheim \

PLUGIN_BASE_URI = https://chrisarndt.de/plugins/faustfilters

# --------------------------------------------------------------

all: libs plugins gen

# --------------------------------------------------------------

submodules:
	-test -d .git && git submodule update --init --recursive

libs: submodules

plugins: libs $(PLUGINS)

# --------------------------------------------------------------

$(PLUGINS):
	$(MAKE) all -C plugins/$@

ifneq ($(CROSS_COMPILING),true)
gen: plugins dpf/utils/lv2_ttl_generator
	@$(CURDIR)/dpf/utils/generate-ttl.sh
ifeq ($(MACOS),true)
	@$(CURDIR)/dpf/utils/generate-vst-bundles.sh
endif

dpf/utils/lv2_ttl_generator:
	$(MAKE) -C dpf/utils/lv2-ttl-generator
else
gen: plugins dpf/utils/lv2_ttl_generator.exe
	@$(CURDIR)/dpf/utils/generate-ttl.sh

dpf/utils/lv2_ttl_generator.exe:
	$(MAKE) -C dpf/utils/lv2-ttl-generator WINDOWS=true
endif

# --------------------------------------------------------------

lv2lint: plugins gen
	@echo "Please make sure you have the https://github.com/KXStudio/LV2-Extensions bundles"
	@echo "installed somewhere on your LV2_PATH."
	@for plug in $(PLUGINS); do \
		lv2lint -q -Mpack -s lv2_generate_ttl -t "Plugin Author Email" \
			-I bin/$${plug,,}.lv2/ "$(PLUGIN_BASE_URI)#$${plug,,}"; \
	done

# --------------------------------------------------------------

clean:
	$(MAKE) clean -C dpf/utils/lv2-ttl-generator
	@for plug in $(PLUGINS); do \
		$(MAKE) clean -C plugins/$${plug}; \
	done
	rm -rf bin build

# --------------------------------------------------------------

install: all
	@for plug in $(PLUGINS); do \
		$(MAKE) install -C plugins/$${plug}; \
	done

install-user: all
	@for plug in $(PLUGINS); do \
		$(MAKE) install-user -C plugins/$${plug}; \
	done

# --------------------------------------------------------------

.PHONY: all clean faust gen install install-user libs lv2lint plugins submodule
