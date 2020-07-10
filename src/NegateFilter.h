//
// Created by SuNNjek on 10.07.20.
//

#pragma once

#include <avisynth.h>

class NegateFilter : public GenericVideoFilter
{
public:
    NegateFilter(PClip src, IScriptEnvironment* env);

    PVideoFrame GetFrame(int n, IScriptEnvironment *env) override;

    static AVSValue __cdecl Create(AVSValue args, void*, IScriptEnvironment* env);
};
