//
// Created by SuNNjek on 10.07.20.
//

#include "NegateFilter.h"

NegateFilter::NegateFilter(PClip src, IScriptEnvironment *env) : GenericVideoFilter(src)
{
    // Since this is just an example, this plugin only supports planar RGB
    // for simplicity
    if (!vi.IsColorSpace(VideoInfo::CS_RGBP8))
        env->ThrowError("Negate: Input must be RGB24 colorspace");
}

AVSValue NegateFilter::Create(AVSValue args, void *, IScriptEnvironment *env)
{
    PClip clip = args[0].AsClip();
    return new NegateFilter(clip, env);
}

PVideoFrame NegateFilter::GetFrame(int n, IScriptEnvironment *env)
{
    // Get frame of source clip and create a new frame based on its properties
    PVideoFrame src = child->GetFrame(n, env);
    PVideoFrame dst = env->NewVideoFrameP(vi, &src);

    // Apply the filter to each plane
    const int planes[] = { PLANAR_R, PLANAR_G, PLANAR_B };
    for (int p = 0; p < 3; p++)
    {
        // Get pointers to the source and destination frame data
        const int plane = planes[p];
        const BYTE *readPtr = src->GetReadPtr(plane);
        BYTE *writePtr = dst->GetWritePtr(plane);

        // Needed to loop over the pixels of the source frame and write to the
        // correct location in the destination data
        const int srcPitch = src->GetPitch(plane);
        const int dstPitch = dst->GetPitch(plane);
        const int width = dst->GetRowSize(plane);
        const int height = dst->GetHeight(plane);

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                // Get source and destination pixel locations
                const BYTE *srcPixelLocation = readPtr + y * srcPitch + x;
                BYTE *dstPixelLocation = writePtr + y * dstPitch + x;

                // Negate the pixel value at the current location
                *dstPixelLocation = 0xFF - *srcPixelLocation;
            }
        }
    }

    return dst;
}
