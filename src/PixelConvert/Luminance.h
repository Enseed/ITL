/*******************************************************************************
 Copyright 2009 Enseed Inc. & Gaspard Petit <gaspardpetit@enseed.com>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*******************************************************************************/
#ifndef __ITL_PIXELCONVERTER_LUMINANCE_H__
#define __ITL_PIXELCONVERTER_LUMINANCE_H__

//==============================================================================
// EXTERNAL DECLARATIONS
//==============================================================================
#include "Luminance.declare.h"
#include "Range.h"
#include "YCbCrFromRGB.h"

#ifndef _WIN32
#include <tr1/type_traits>
#else
#include <type_traits> 
#endif


//==============================================================================
// CASE: Same color space and source has the component
//==============================================================================
template<typename SRC_PIXELTYPE, typename DST_PIXELTYPE, typename SRC_COMPONENTMODEL, typename DST_COMPONENTMODEL, typename SAME_COLORSPACE>
struct PixelConvertExtractLuminance<SRC_PIXELTYPE, DST_PIXELTYPE, SRC_COMPONENTMODEL, SAME_COLORSPACE, DST_COMPONENTMODEL, SAME_COLORSPACE, true>
{
	typedef typename SRC_PIXELTYPE::LuminanceStorageType SrcStorage;
	typedef typename DST_PIXELTYPE::LuminanceStorageType DstStorage;
	
	static typename DstStorage::ComponentType eval(const SRC_PIXELTYPE &src)
	{	return ConvertComponentRange<SrcStorage, DstStorage>::eval(src.luminance()); }
};


//==============================================================================
// CASE: From sRGB
//==============================================================================
template<typename SRC_PIXELTYPE, typename DST_PIXELTYPE, typename SRC_COMPONENTMODEL, typename DST_COMPONENTMODEL, typename DST_COLORSPACE>
struct PixelConvertExtractLuminance<SRC_PIXELTYPE, DST_PIXELTYPE, SRC_COMPONENTMODEL, ColorSpace_sRGB, DST_COMPONENTMODEL, DST_COLORSPACE, false>
{
	typedef typename DST_PIXELTYPE::LuminanceStorageType DstStorage;
	
	static typename DstStorage::ComponentType eval(const SRC_PIXELTYPE &src)
	{	return PixelConvertYCbCrFromRGB<SRC_PIXELTYPE, DST_PIXELTYPE>(src).luminance(); }
};

//==============================================================================
// CASE: Not from RGB, converting to RGB
//==============================================================================
#include "RGBFromCMYK.h"
template<typename SRC_PIXELTYPE, typename DST_PIXELTYPE, typename SRC_COMPONENTMODEL, typename SRC_COLORSPACE, typename DST_COMPONENTMODEL, typename DST_COLORSPACE>
struct PixelConvertExtractLuminance<SRC_PIXELTYPE, DST_PIXELTYPE, SRC_COMPONENTMODEL, SRC_COLORSPACE, DST_COMPONENTMODEL, DST_COLORSPACE, false>
{
	typedef typename DST_PIXELTYPE::LuminanceStorageType DstStorage;
	
	static typename DstStorage::ComponentType eval(const SRC_PIXELTYPE &src)
	{
		RGB32fPixel rgb32f;
		PixelConvert(src, &rgb32f);
		return PixelConvertExtractLuminance<RGB32fPixel, DST_PIXELTYPE>::eval(rgb32f);
	}
};


#endif // __ITL_PIXELCONVERTER_LUMINANCE_H__



