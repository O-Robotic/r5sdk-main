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

#include "Recast/Include/Recast.h"
#include "Shared/Include/SharedAssert.h"

void rcFilterLowHangingWalkableObstacles(rcContext* context, const int walkableClimb, rcHeightfield& heightfield)
{
	rdAssert(context);

	rcScopedTimer timer(context, RC_TIMER_FILTER_LOW_OBSTACLES);

	const int xSize = heightfield.width;
	const int ySize = heightfield.height;

	for (int y = 0; y < ySize; ++y)
	{
		for (int x = 0; x < xSize; ++x)
		{
			rcSpan* previousSpan = NULL;
			bool previousWasWalkable = false;
			unsigned char previousArea = RC_NULL_AREA;

			for (rcSpan* span = heightfield.spans[x + y * xSize]; span != NULL; previousSpan = span, span = span->next)
			{
				const bool walkable = span->area != RC_NULL_AREA;
				// If current span is not walkable, but there is walkable
				// span just below it, mark the span above it walkable too.
				if (!walkable && previousWasWalkable)
				{
					if (rdAbs((int)span->smax - (int)previousSpan->smax) <= walkableClimb)
					{
						span->area = previousArea;
					}
				}
				// Copy walkable flag so that it cannot propagate
				// past multiple non-walkable objects.
				previousWasWalkable = walkable;
				previousArea = span->area;
			}
		}
	}
}

void rcFilterLedgeSpans(rcContext* context, const int walkableHeight, const int walkableClimb,
                        const bool cullSteepNeiSlopes, rcHeightfield& heightfield)
{
	rdAssert(context);
	
	rcScopedTimer timer(context, RC_TIMER_FILTER_BORDER);

	const int xSize = heightfield.width;
	const int ySize = heightfield.height;
	
	// Mark border spans.
	for (int y = 0; y < ySize; ++y)
	{
		for (int x = 0; x < xSize; ++x)
		{
			for (rcSpan* span = heightfield.spans[x + y * xSize]; span; span = span->next)
			{
				// Skip non walkable spans.
				if (span->area == RC_NULL_AREA)
				{
					continue;
				}

				const int bot = (int)(span->smax);
				const int top = span->next ? (int)(span->next->smin) : RC_SPAN_MAX_HEIGHT;

				// Find neighbours minimum height.
				int minNeighborHeight = RC_SPAN_MAX_HEIGHT;

				// Min and max height of accessible neighbours.
				int accessibleNeighborMinHeight = span->smax;
				int accessibleNeighborMaxHeight = span->smax;

				for (int direction = 0; direction < 4; ++direction)
				{
					int dx = x + rcGetDirOffsetX(direction);
					int dy = y + rcGetDirOffsetY(direction);
					// Skip neighbours which are out of bounds.
					if (dx < 0 || dy < 0 || dx >= xSize || dy >= ySize)
					{
						minNeighborHeight = (-walkableClimb - 1);
						break;
					}

					// From minus infinity to the first span.
					const rcSpan* neighborSpan = heightfield.spans[dx + dy * xSize];
					int neighborTop = neighborSpan ? (int)neighborSpan->smin : RC_SPAN_MAX_HEIGHT;
					
					// Skip neighbour if the gap between the spans is too small.
					if (rdMin(top, neighborTop) - bot >= walkableHeight)
					{
						minNeighborHeight = (-walkableClimb - 1);
						break;
					}

					// Rest of the spans.
					for (neighborSpan = heightfield.spans[dx + dy * xSize]; neighborSpan; neighborSpan = neighborSpan->next)
					{
						const int neighborBot = (int)neighborSpan->smax;
						neighborTop = neighborSpan->next ? (int)neighborSpan->next->smin : RC_SPAN_MAX_HEIGHT;
						
						// Skip neighbour if the gap between the spans is too small.
						if (rdMin(top, neighborTop) - rdMax(bot, neighborBot) >= walkableHeight)
						{
							const int accessibleNeighbourHeight = neighborBot - bot;
							minNeighborHeight = rdMin(minNeighborHeight, accessibleNeighbourHeight);

							// Find min/max accessible neighbour height.
							if (rdAbs(accessibleNeighbourHeight) <= walkableClimb)
							{
								if (neighborBot < accessibleNeighborMinHeight) accessibleNeighborMinHeight = neighborBot;
								if (neighborBot > accessibleNeighborMaxHeight) accessibleNeighborMaxHeight = neighborBot;
							}
							else if (accessibleNeighbourHeight < -walkableClimb)
							{
								break;
							}
						}
					}
				}

				// The current span is close to a ledge if the drop to any
				// neighbour span is less than the walkableClimb.
				if (minNeighborHeight < -walkableClimb)
				{
					span->area = RC_NULL_AREA;
				}
				// If the difference between all neighbours is too large,
				// we are at steep slope, mark the span as ledge.
				//
				// note(amos): since we mostly work with relatively large
				// voxels (8 - 15), this test can be quite aggressive
				// causing the beginning of stairs to be culled away due
				// to the limited amount of voxels that could fit inside
				// the agent's radius. However, these spans perfectly
				// climbable. Added an option to opt out of this feature.
				else if (cullSteepNeiSlopes && (accessibleNeighborMaxHeight - accessibleNeighborMinHeight) > walkableClimb)
				{
					span->area = RC_NULL_AREA;
				}
			}
		}
	}
}

void rcFilterWalkableLowHeightSpans(rcContext* context, const int walkableHeight, rcHeightfield& heightfield)
{
	rdAssert(context);
	
	rcScopedTimer timer(context, RC_TIMER_FILTER_WALKABLE);
	
	const int xSize = heightfield.width;
	const int ySize = heightfield.height;
	
	// Remove walkable flag from spans which do not have enough
	// space above them for the agent to stand there.
	for (int y = 0; y < ySize; ++y)
	{
		for (int x = 0; x < xSize; ++x)
		{
			for (rcSpan* span = heightfield.spans[x + y*xSize]; span; span = span->next)
			{
				const int bot = (int)(span->smax);
				const int top = span->next ? (int)(span->next->smin) : RC_SPAN_MAX_HEIGHT;
				if ((top - bot) < walkableHeight)
				{
					span->area = RC_NULL_AREA;
				}
			}
		}
	}
}
