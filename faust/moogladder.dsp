declare name "MoogLadder";
declare description "FAUST Moog Ladder 24 dB LPF";
declare author "Christopher Arndt";
declare license "MIT-style STK-4.3 license";

import("stdfaust.lib");

//------------------`moogLadder`-----------------
// Virtual analog model of the 4th-order Moog Ladder, which is arguably the
// most well-known ladder filter in analog synthesizers. Several
// 1st-order filters are cascaded in series. Feedback is then used, in part, to
// control the cut-off frequency and the resonance.
//
// #### References
//
// [Zavalishin 2012] (revision 2.1.2, February 2020):
//
// * <https://www.native-instruments.com/fileadmin/ni_media/downloads/pdf/VAFilterDesign_2.1.2.pdf>
//
// This fix is based on Lorenzo Della Cioppa's correction to Pirkle's implementation; see this post:
// https://www.kvraudio.com/forum/viewtopic.php?f=33&t=571909
//
// #### Usage
//
// ```
// _ : moogLadder(freq, Q) : _
// ```
//
// Where:
//
// * `freq`: cutoff frequency (20-20000 Hz)
// * `Q`: quality factor between .707 (0 feedback coefficient) to 25 (feedback = 4, which is the self-oscillating threshold).
//---------------------------------------------------------------------
declare moogLadder author "Dario Sanfilippo";
declare moogLadder license "MIT-style STK-4.3 license";
moogLadder(freq, Q, x) = loop ~ si.bus(4) : (!,!,!,!,_)
with {
    loop(s1, s2, s3, s4) =  v1 + lp1 , // define s1
                            v2 + lp2 , // define s2
                            v3 + lp3 , // define s3
                            v4 + lp4 , // define s4
                            lp4 // system output
        with {
            invSqrt2 = 1/sqrt(2);
            T = 1.0 / ma.SR;
            normFreq = freq / ma.SR * 2;
            k = 4.0 * (Q - invSqrt2) / (25.0 - invSqrt2);
            omegaWarp = tan(ma.PI * freq * T);
            g = omegaWarp / (1.0 + omegaWarp);
            G = g * g * g * g; // ladder's G in generalised form y = G * xi + S
            S = g * g * g * (s1 * (1 - g)) + g * g * (s2 * (1 - g)) + g * (s3 * (1 - g)) + (s4 * (1 - g)); // ladder's S in generalised form y = G * xi + S
            u = (x - k * S) / (1.0 + k * G); // input to the first LP stage: u = (x - kS) / (1 + kG)
            v1 = g * (u - s1); // v-signals in TPT integrator (Zavalishin, Figure 3.30)
            v2 = g * (lp1 - s2); // second stage
            v3 = g * (lp2 - s3); // third stage
            v4 = g * (lp3 - s4); // fourth stage
            lp1 = v1 + s1; // define outputs
            lp2 = v2 + s2;
            lp3 = v3 + s3;
            lp4 = v4 + s4;
        };
};

q = hslider("[1]Q[symbol: q][abbrev: q][style:knob]", 1.0, 0.7072, 25, 0.01);
cutoff = hslider("[0]Cutoff frequency[symbol: cutoff][abbrev: cutoff][unit: hz][scale: log][style: knob]", 20000.0, 20.0, 20000, 0.1):si.smoo;

process = moogLadder(cutoff, q);
