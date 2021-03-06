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
#include "../ImageFormat.h"
#include "ImageFormatMapping.h"
#include "ImageFormatSwitch.h"

//==============================================================================
// CLASS Image
//==============================================================================

namespace ITL {

struct TCountPlaneForFormat
{
public:
	TCountPlaneForFormat() : _count(0) {}
	
	template<int FORMAT>
	void call() { _count = ImageTypeToPixMapTypeMapping<FORMAT>::PixMapType::PixelType::PLANE_COUNT; }
	
	int count() { return _count; }
private:
	int _count;
};


int ImageFormat::planes(ImageFormat::Format format)
{
	TCountPlaneForFormat functor;
	TCallWithFormat(format, functor);
	return functor.count();
}


class TDirectionForFormat
{
public:
	TDirectionForFormat() : _direction() {}
	
	template<int FORMAT>
	void call() { _direction = OriginTypeToDirectionEnumMapping< typename ImageTypeToPixMapTypeMapping<FORMAT>::PixMapType::OriginType >::Direction; }

	ImageFormat::Direction direction() { return _direction; }
private:
	ImageFormat::Direction _direction;
};

ImageFormat::Direction ImageFormat::direction(ImageFormat::Format format)
{
	TDirectionForFormat functor;
	TCallWithFormat(format, functor);
	return functor.direction();
}

} // namespace ITL


