# FAUST filters

A collection of virtual-analog filters from the [FAUST] standard library
packaged as multi-format plugins via the [DPF].


## Plugins

All plugins are mono, i.e. they have one audio input and output, unless noted
otherwise. They all have two (automatable) parameters:

* Cutoff / center frequency in Hertz (`20.0 - 20,000.0`)
* Q factor (range varies)

The plugins depend on the host to provide a generic UI to control parameters.


### Diode Ladder

A diode ladder 24 dB lowpass filter


### Korg 35 HPF

A Korg 35 24 dB high pass filter as found in the MS-10 and early MS-20s


### Korg 35 LPF

A Korg 35 24 dB low pass filter as found in the MS-10 and early MS-20s


### Moog Ladder LPF

A Moog ladder-style 24 dB low pass filter


### Moog Half Ladder LPF

A Moog ladder-style 12 dB low pass filter


### Oberheim Multi-mode Filter

A multi-mode, state-variable filter as found in Oberheim synthesizers

This filter has four outputs:

* Bandstop
* Bandpass
* Highpass
* Lowpass


## Formats

All plugins in this collection come in the following plug-in formats:

* CLAP
* LADSPA
* LV2
* VST2
* VST3


## Compiling

Make sure you have installed the required build tools and libraries (see
section "Prerequisites" below) and then clone this repository (including
sub-modules) and simply run `make` in the project's root directory:

    $ git clone --recursive https://github.com/SpotlightKid/faustfilters.git
    $ cd faustfilters
    $ make


## Installation

To install all plugin formats to their appropriate system-wide location, run
the following command:

    make install

The makefiles support the usual `PREFIX` and `DESTDIR` variables to change the
installation prefix and set an installation root directory (default: empty).
`PREFIX` defaults to `/usr/local`, but on macOS and Windows it is not used,
since the system-wide installation directories for plugins are fixed.

Use make's `-n` option to see where the plugins would be installed without
actually installing them.

You can also set the installation directory for each plugin format with a
dedicated makefile variable.

* CLAP: `CLAP_DIR` (`<prefix>/lib/clap`)
* LADSPA: `LADSPA_DIR` (`<prefix>/lib/ladspa`)
* LV2: `LV2_DIR` (`<prefix>/lib/lv2`)
* VST2: `VST2_DIR` (`<prefix>/lib/vst`)
* VST2: `VST3_DIR` (`<prefix>/lib/vst3`)

Example: `make DESTDIR=/tmp/build-root VST_DIR=/usr/lib/lxvst install`

To install the plugins only for your current user account, run
`make install-user`.

Again, you can also set the installation directory for each plugin format with
a dedicated makefile variable.

* CLAP: `USER_CLAP_DIR` (`$HOME/.clap`)
* LADSPA: `USER_LADSPA_DIR` (`$HOME/.ladspa`)
* LV2: `USER_LV2_DIR` (`$HOME/.lv2`)
* VST2: `USER_VST2_DIR` (`$HOME/.vst`)
* VST3: `USER_VST3_DIR` (`$HOME/.vst3`)

*Note: The given default values for all of the above listed environment
variables differ depending on the target OS.*


## Prerequisites

* The GCC C++ compiler, library and the usual associated software build tools
  (`make`, etc.).

  Debian / Ubuntu users should install the `build-essential` package
  to get these.

* [pkgconf]

* The [faustpp] pre-processor (optional)

The [CLAP], [LV2], [LADSPA], [VST]2 (vestige) and VST3 headers are included in
the [DPF] framework, which is integrated as a Git sub-module. These need not be
installed separately to build the software in the respective plug-in formats.

`faustpp` and FAUST are only needed to re-generate C++ source and headers files
if the FAUST DSP source files in the `faust` directory are changed.


## Author

This software project was put together by *Christopher Arndt*.


## Acknowledgements

The idea for this project was inspired by the [poly_filters] LV2 plugin
collection.

The DSP code is generated from the FAUST sources via the [faustpp]
pre-processor.

The project is built using the DISTRHO Plugin Framework ([DPF]) and set up
with the [cookiecutter-dpf-effect] project template (with additional
customization).


[CLAP]: https://cleveraudio.org/
[cookiecutter-dpf-effect]: https://github.com/SpotlightKid/cookiecutter-dpf-effect
[DPF]: https://github.com/DISTRHO/DPF
[FAUST]: https://faust.grame.fr/
[faustpp]: https://github.com/jpcima/faustpp.git
[LADSPA]: http://www.ladspa.org/
[LV2]: http://lv2plug.in/
[pkgconf]: https://github.com/pkgconf/pkgconf
[poly_filters]: https://github.com/polyeffects/poly_filters.git
[VST]: https://en.wikipedia.org/wiki/Virtual_Studio_Technology
