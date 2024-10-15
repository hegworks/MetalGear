#include "precomp.h"
#include "pixelPerfectCollisionChecker.h"

PixelPerfectCollisionChecker::PixelPerfectCollisionChecker(Surface* screenP)
{
	m_screenP = screenP;
}

bool PixelPerfectCollisionChecker::IsColliding(Sprite* aSprite, Sprite* bSprite, float2 aPos, float2 bPos, int aFrame, int bFrame)
{
	// data preparation----------
	const uint* aBuffer = aSprite->GetBuffer();
	const uInt* bBuffer = bSprite->GetBuffer();

	const int2 aSize = {aSprite->GetWidth(),aSprite->GetHeight()};
	const int2 bSize = {bSprite->GetWidth(),bSprite->GetHeight()};

	const int2 aPosInt = {static_cast<int>(aPos.x), static_cast<int>(aPos.y)};
	const int2 bPosInt = {static_cast<int>(bPos.x), static_cast<int>(bPos.y)};
	// ----------data preparation

	// AABB check----------
	const int2 aMin = aPosInt;
	const int2 aMax = aPosInt + aSize;
	const int2 bMin = bPosInt;
	const int2 bMax = bPosInt + bSize;

#ifdef _DEBUG
	m_screenP->Box(aMin.x, aMin.y, aMax.x, aMax.y, 0xff0000);
	m_screenP->Box(bMin.x, bMin.y, bMax.x, bMax.y, 0xff0000);
#endif

	const bool isAabbColliding =
		aMin.x <= bMax.x &&
		aMax.x >= bMin.x &&
		aMin.y <= bMax.y &&
		aMax.y >= bMin.y;

	if(!isAabbColliding)
	{
		return false;
	}

#ifdef _DEBUG
	m_screenP->Box(aMin.x, aMin.y, aMax.x, aMax.y, 0x00ff00);
	m_screenP->Box(bMin.x, bMin.y, bMax.x, bMax.y, 0x00ff00);
#endif
	// ----------AABB check

	// overlap----------
	const int2 aTopLeft = aMin;
	const int2 aBottomRight = aMax;
	const int2 aTopRight = {aMax.x,aMin.y};
	const int2 aBottomLeft = {aMin.x,aMax.y};

	const int2 bTopLeft = bMin;
	const int2 bBottomRight = bMax;
	const int2 bTopRight = {bMax.x,bMin.y};
	const int2 bBottomLeft = {bMin.x,bMax.y};

	const int oTop = max(aTopLeft.y, bTopLeft.y);
	const int oBottom = min(aBottomLeft.y, bBottomLeft.y);
	const int oLeft = max(aTopLeft.x, bTopLeft.x);
	const int oRight = min(aTopRight.x, bTopRight.x);

	const int2 oTopLeft = {oLeft,oTop};
	const int2 oTopRight = {oRight,oTop};
	const int2 oBottomLeft = {oLeft,oBottom};
	const int2 oBottomRight = {oRight,oBottom};

#ifdef _DEBUG
	const float2 oTopLeftInt = {static_cast<float>(oTopLeft.x),static_cast<float>(oTopLeft.y)};
	const float2 oTopRightInt = {static_cast<float>(oTopRight.x),static_cast<float>(oTopRight.y)};
	const float2 oBottomLeftInt = {static_cast<float>(oBottomLeft.x),static_cast<float>(oBottomLeft.y)};
	const float2 oBottomRightInt = {static_cast<float>(oBottomRight.x),static_cast<float>(oBottomRight.y)};
	m_screenP->Line(oTopLeftInt.x, oTopLeftInt.y, oTopRightInt.x, oTopRightInt.y, 0x0000ff);
	m_screenP->Line(oTopLeftInt.x, oTopLeftInt.y, oBottomLeftInt.x, oBottomLeftInt.y, 0x0000ff);
	m_screenP->Line(oBottomLeftInt.x, oBottomLeftInt.y, oBottomRightInt.x, oBottomRightInt.y, 0x0000ff);
	m_screenP->Line(oBottomRightInt.x, oBottomRightInt.y, oTopRightInt.x, oTopRightInt.y, 0x0000ff);
#endif
	// ----------overlap

	// check transparency----------
	const int oRows = oBottomLeft.y - oTopLeft.y - 1;
	const int oColumns = oTopRight.x - oTopLeft.x - 1;

	const int aFrameOffset = aFrame * aSize.x;
	const int bFrameOffset = bFrame * bSize.x;

	const int aFrameCount = static_cast<int>(aSprite->Frames());
	const int bFrameCount = static_cast<int>(bSprite->Frames());

	for(int y = 0; y < oRows; ++y)
	{
		for(int x = 0; x < oColumns; ++x)
		{
			// local overlaps
			const int2 aLocal = {oLeft + x - aPosInt.x,oTop + y - aPosInt.y};
			const int2 bLocal = {oLeft + x - bPosInt.x,oTop + y - bPosInt.y};

			// check bounds
			if(aLocal.x >= 0 && aLocal.x < aSize.x && aLocal.y >= 0 && aLocal.y < aSize.y &&
			   bLocal.x >= 0 && bLocal.x < bSize.x && bLocal.y >= 0 && bLocal.y < bSize.y)
			{
				// a & b buffer value
				const int abv = aLocal.x + aLocal.y * aSize.x * aFrameCount + aFrameOffset;
				const int bbv = bLocal.x + bLocal.y * bSize.x * bFrameCount + bFrameOffset;

				const uint aPixel = aBuffer[abv];
				const uint bPixel = bBuffer[bbv];

				const bool isATrans = aPixel == 0;
				const bool isBTrans = bPixel == 0;

				if(!isATrans && !isBTrans)
				{
//#ifdef _DEBUG
					//m_screenP->Plot(oLeft + x, oTop + y, 0xff0000);
//#else

					return true;
//#endif
				}
			}
		}
	}
	return false;
}
