//
// Copyright (c) 2009-2010 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#include "NavEditor/Include/PerfTimer.h"

#if defined(WIN32)

// Win32
#include <windows.h>

rdTimeType getPerfTime()
{
	rdTimeType count;
	QueryPerformanceCounter((LARGE_INTEGER*)&count);
	return count;
}

rdTimeType getPerfTimeUsec(const rdTimeType duration)
{
	static rdTimeType freq = 0;
	if (freq == 0)
		QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	return (rdTimeType)(duration*1000000 / freq);
}

#else

// Linux, BSD, OSX

#include <sys/time.h>

rdTimeType getPerfTime()
{
	timeval now;
	gettimeofday(&now, 0);
	return (rdTimeType)now.tv_sec*1000000L + (rdTimeType)now.tv_usec;
}

rdTimeType getPerfTimeUsec(const rdTimeType duration)
{
	return duration;
}

#endif
