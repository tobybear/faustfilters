
//------------------------------------------------------------------------------
// This file was generated using the Faust compiler (https://faust.grame.fr),
// and the Faust post-processor (https://github.com/jpcima/faustpp).
//
// Source: diodeladder.dsp
// Name: DiodeLadder
// Author: Christopher Arndt
// Copyright: 
// License: MIT-style STK-4.3 license
// Version: 
//------------------------------------------------------------------------------







#include "DiodeLadder.hpp"



#include <utility>
#include <cmath>

class DiodeLadder::BasicDsp {
public:
    virtual ~BasicDsp() {}
};

//------------------------------------------------------------------------------
// Begin the Faust code section

namespace {

template <class T> inline T min(T a, T b) { return (a < b) ? a : b; }
template <class T> inline T max(T a, T b) { return (a > b) ? a : b; }

class Meta {
public:
    // dummy
    void declare(...) {}
};

class UI {
public:
    // dummy
    void openHorizontalBox(...) {}
    void openVerticalBox(...) {}
    void closeBox(...) {}
    void declare(...) {}
    void addButton(...) {}
    void addCheckButton(...) {}
    void addVerticalSlider(...) {}
    void addHorizontalSlider(...) {}
    void addVerticalBargraph(...) {}
    void addHorizontalBargraph(...) {}
};

typedef DiodeLadder::BasicDsp dsp;

} // namespace

#define FAUSTPP_VIRTUAL // do not declare any methods virtual
#define FAUSTPP_PRIVATE public // do not hide any members
#define FAUSTPP_PROTECTED public // do not hide any members

// define the DSP in the anonymous namespace
#define FAUSTPP_BEGIN_NAMESPACE namespace {
#define FAUSTPP_END_NAMESPACE }


#if defined(__GNUC__)
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#ifndef FAUSTPP_PRIVATE
#   define FAUSTPP_PRIVATE private
#endif
#ifndef FAUSTPP_PROTECTED
#   define FAUSTPP_PROTECTED protected
#endif
#ifndef FAUSTPP_VIRTUAL
#   define FAUSTPP_VIRTUAL virtual
#endif

#ifndef FAUSTPP_BEGIN_NAMESPACE
#   define FAUSTPP_BEGIN_NAMESPACE
#endif
#ifndef FAUSTPP_END_NAMESPACE
#   define FAUSTPP_END_NAMESPACE
#endif

FAUSTPP_BEGIN_NAMESPACE

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

FAUSTPP_END_NAMESPACE
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>
FAUSTPP_BEGIN_NAMESPACE

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

static float mydsp_faustpower2_f(float value) {
	return value * value;
}
static float mydsp_faustpower4_f(float value) {
	return value * value * value * value;
}
static float mydsp_faustpower3_f(float value) {
	return value * value * value;
}

class mydsp : public dsp {
	
 FAUSTPP_PRIVATE:
	
	int fSampleRate;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider0;
	float fRec5[2];
	float fConst3;
	FAUSTFLOAT fHslider1;
	float fRec1[2];
	float fRec2[2];
	float fRec3[2];
	float fRec4[2];
	
 public:
	mydsp() {}

	void metadata(Meta* m) { 
		m->declare("../../faust/diodeladder.dsp/diodeLadder:author", "Eric Tarr");
		m->declare("../../faust/diodeladder.dsp/diodeLadder:license", "MIT-style STK-4.3 license");
		m->declare("author", "Christopher Arndt");
		m->declare("compile_options", "-a /home/chris/tmp/tmp7hoz0_gh.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("description", "FAUST Diode Ladder 24 dB LPF");
		m->declare("filename", "diodeladder.dsp");
		m->declare("license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.7.0");
		m->declare("misceffects.lib/cubicnl:author", "Julius O. Smith III");
		m->declare("misceffects.lib/cubicnl:license", "STK-4.3");
		m->declare("misceffects.lib/name", "Misc Effects Library");
		m->declare("misceffects.lib/version", "2.4.0");
		m->declare("name", "DiodeLadder");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.5.0");
	}

	FAUSTPP_VIRTUAL int getNumInputs() {
		return 1;
	}
	FAUSTPP_VIRTUAL int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
	}
	
	FAUSTPP_VIRTUAL void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		float fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
		fConst3 = 3.1415927f / fConst0;
	}
	
	FAUSTPP_VIRTUAL void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(2e+04f);
		fHslider1 = FAUSTFLOAT(1.0f);
	}
	
	FAUSTPP_VIRTUAL void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec5[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec1[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec2[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec3[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec4[l4] = 0.0f;
		}
	}
	
	FAUSTPP_VIRTUAL void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	FAUSTPP_VIRTUAL void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	FAUSTPP_VIRTUAL mydsp* clone() {
		return new mydsp();
	}
	
	FAUSTPP_VIRTUAL int getSampleRate() {
		return fSampleRate;
	}
	
	FAUSTPP_VIRTUAL void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("DiodeLadder");
		ui_interface->declare(&fHslider0, "0", "");
		ui_interface->declare(&fHslider0, "abbrev", "cutoff");
		ui_interface->declare(&fHslider0, "scale", "log");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->declare(&fHslider0, "symbol", "cutoff");
		ui_interface->declare(&fHslider0, "unit", "hz");
		ui_interface->addHorizontalSlider("Cutoff frequency", &fHslider0, FAUSTFLOAT(2e+04f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+04f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "abbrev", "q");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->declare(&fHslider1, "symbol", "q");
		ui_interface->addHorizontalSlider("Q", &fHslider1, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.7072f), FAUSTFLOAT(25.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	FAUSTPP_VIRTUAL void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = fConst1 * float(fHslider0);
		float fSlow1 = float(fHslider1) + -0.707f;
		float fSlow2 = 0.0051455153f * fSlow1;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec5[0] = fSlow0 + fConst2 * fRec5[1];
			float fTemp0 = std::tan(fConst3 * fRec5[0]);
			float fTemp1 = fTemp0 + 1.0f;
			float fTemp2 = fTemp0 * (1.0f - 0.25f * (fTemp0 / fTemp1)) + 1.0f;
			float fTemp3 = 0.5f * (fRec1[1] * fTemp0 / fTemp1) + fRec2[1];
			float fTemp4 = fTemp0 * fTemp3 / fTemp2;
			float fTemp5 = 0.5f * fTemp4;
			float fTemp6 = fTemp1 * fTemp2;
			float fTemp7 = mydsp_faustpower2_f(fTemp0);
			float fTemp8 = fTemp0 * (1.0f - 0.25f * (fTemp0 / fTemp2)) + 1.0f;
			float fTemp9 = fTemp5 + fRec3[1];
			float fTemp10 = fTemp0 * fTemp9 / fTemp8;
			float fTemp11 = fTemp2 * fTemp8;
			float fTemp12 = fTemp0 * (1.0f - 0.5f * (fTemp0 / fTemp8)) + 1.0f;
			float fTemp13 = fTemp10 + fRec4[1];
			float fTemp14 = 17.0f - 9.7f * std::pow(-(0.33333334f * (1.0f - (std::log10(fRec5[0]) + -0.30103f))), 1e+01f);
			float fTemp15 = std::max<float>(-1.0f, std::min<float>(1.0f, 1e+02f * float(input0[i0])));
			float fTemp16 = fTemp0 * ((1.5f * fTemp15 * (1.0f - 0.33333334f * mydsp_faustpower2_f(fTemp15)) - fSlow1 * (fTemp14 * (0.041164123f * fRec1[1] + 0.020582061f * fTemp4 + 0.020582061f * fTemp10 + 0.0051455153f * (mydsp_faustpower3_f(fTemp0) * fTemp13 / (fTemp11 * fTemp12))) / fTemp1)) * (0.5f * (fTemp7 / (fTemp8 * fTemp12)) + 1.0f) / (fSlow2 * (mydsp_faustpower4_f(fTemp0) * fTemp14 / (fTemp6 * fTemp8 * fTemp12)) + 1.0f) + (fTemp9 + 0.5f * (fTemp0 * fTemp13 / fTemp12)) / fTemp8 - fRec4[1]) / fTemp1;
			float fTemp17 = fTemp0 * (0.5f * ((fRec4[1] + fTemp16) * (0.25f * (fTemp7 / fTemp11) + 1.0f) + (fTemp3 + 0.5f * fTemp10) / fTemp2) - fRec3[1]) / fTemp1;
			float fTemp18 = fTemp0 * (0.5f * ((fRec3[1] + fTemp17) * (0.25f * (fTemp7 / fTemp6) + 1.0f) + (fRec1[1] + fTemp5) / fTemp1) - fRec2[1]) / fTemp1;
			float fTemp19 = fTemp0 * (0.5f * (fRec2[1] + fTemp18) - fRec1[1]) / fTemp1;
			float fRec0 = fRec1[1] + fTemp19;
			fRec1[0] = fRec1[1] + 2.0f * fTemp19;
			fRec2[0] = fRec2[1] + 2.0f * fTemp18;
			fRec3[0] = fRec3[1] + 2.0f * fTemp17;
			fRec4[0] = fRec4[1] + 2.0f * fTemp16;
			output0[i0] = FAUSTFLOAT(fRec0);
			fRec5[1] = fRec5[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
		}
	}

};
FAUSTPP_END_NAMESPACE


#if defined(__GNUC__)
#   pragma GCC diagnostic pop
#endif



//------------------------------------------------------------------------------
// End the Faust code section




DiodeLadder::DiodeLadder()
{

    mydsp *dsp = new mydsp;
    fDsp.reset(dsp);
    dsp->instanceResetUserInterface();

}

DiodeLadder::~DiodeLadder()
{
}

void DiodeLadder::init(float sample_rate)
{

    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.classInit(sample_rate);
    dsp.instanceConstants(sample_rate);
    clear();

}

void DiodeLadder::clear() noexcept
{

    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.instanceClear();

}

void DiodeLadder::process(
    const float *in0,
    float *out0,
    unsigned count) noexcept
{

    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    float *inputs[] = {
        const_cast<float *>(in0),
    };
    float *outputs[] = {
        out0,
    };
    dsp.compute(count, inputs, outputs);

}

const char *DiodeLadder::parameter_label(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "Cutoff frequency";
    
    case 1:
        return "Q";
    
    default:
        return 0;
    }
}

const char *DiodeLadder::parameter_short_label(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "cutoff";
    
    case 1:
        return "q";
    
    default:
        return 0;
    }
}

const char *DiodeLadder::parameter_symbol(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "cutoff";
    
    case 1:
        return "q";
    
    default:
        return 0;
    }
}

const char *DiodeLadder::parameter_unit(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return "hz";
    
    case 1:
        return "";
    
    default:
        return 0;
    }
}

const DiodeLadder::ParameterRange *DiodeLadder::parameter_range(unsigned index) noexcept
{
    switch (index) {
    
    case 0: {
        static const ParameterRange range = { 20000.0, 20.0, 20000.0 };
        return &range;
    }
    
    case 1: {
        static const ParameterRange range = { 1.0, 0.7072, 25.0 };
        return &range;
    }
    
    default:
        return 0;
    }
}

bool DiodeLadder::parameter_is_trigger(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool DiodeLadder::parameter_is_boolean(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool DiodeLadder::parameter_is_integer(unsigned index) noexcept
{
    switch (index) {
    
    default:
        return false;
    }
}

bool DiodeLadder::parameter_is_logarithmic(unsigned index) noexcept
{
    switch (index) {
    
    case 0:
        return true;
    
    default:
        return false;
    }
}

float DiodeLadder::get_parameter(unsigned index) const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    switch (index) {
    
    case 0:
        return dsp.fHslider0;
    
    case 1:
        return dsp.fHslider1;
    
    default:
        (void)dsp;
        return 0;
    }
}

void DiodeLadder::set_parameter(unsigned index, float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    switch (index) {
    
    case 0:
        dsp.fHslider0 = value;
        break;
    
    case 1:
        dsp.fHslider1 = value;
        break;
    
    default:
        (void)dsp;
        (void)value;
        break;
    }
}


float DiodeLadder::get_cutoff() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider0;
}

float DiodeLadder::get_q() const noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    return dsp.fHslider1;
}


void DiodeLadder::set_cutoff(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider0 = value;
}

void DiodeLadder::set_q(float value) noexcept
{
    mydsp &dsp = static_cast<mydsp &>(*fDsp);
    dsp.fHslider1 = value;
}



