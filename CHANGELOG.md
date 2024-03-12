# CHANGELOG

# v0.4.0 (2024-03-12)

Changes:

* Added Oberheim LPF/HPF/Bandpass/Bandstop filter.
* Replaced FAUST implementation of MoogLadder
   (the previous one stopped working with newer FAUST versions).
* Added CLAP and VST3 format.
* Bumped minor LV2 bundle version of all plugins.
* Updated DPF sub-module to commit `1504e7d3`.

Fixes:

* Fixed typo in plugin display name of Korg filters.
* Updated deprecated DPF param flag enum value in plugin sources.
* Updated signatures in FAUST source code comment.
* Removed debugging output to stderr.
* Corrected LV2 plugin category for korg35hpf.


# v0.3.0 (2020-08-10)

Changes:

* Use unnormalized Hz values for cutoff param for all filters


# v0.1.0 (2020-06-30)

Initial release
