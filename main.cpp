//
// Created by SuNNjek on 10.07.20.
//

#include <avisynth.h>
#include "src/NegateFilter.h"

const AVS_Linkage *AVS_linkage = 0;

// This is the entry point that gets called by AviSynth to load the plugin
extern "C" __declspec(dllexport) const char* __stdcall AvisynthPluginInit3(IScriptEnvironment* env, const AVS_Linkage* const vectors)
{
    AVS_linkage = vectors;

    // Add functions here like so:
    env->AddFunction("Negate", "c", NegateFilter::Create, 0);

    // Return a description of the plugin
    // For all I know, you can't see this anywhere, but whatever :P
    return "This plugin negates colors in planar RGB24 clips";
}
