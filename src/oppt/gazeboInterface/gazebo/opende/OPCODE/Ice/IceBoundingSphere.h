///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Contains code to compute the minimal bounding sphere.
 *	\file		IceBoundingSphere.h
 *	\author		Pierre Terdiman
 *	\date		January, 29, 2000
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Guard
#pragma once

	enum BSphereMethod
	{
		BS_NONE,
		BS_GEMS,
		BS_MINIBALL,

		BS_FORCE_DWORD	= 0x7fffffff
	};

	class ICEMATHS_API Sphere
	{
		public:
		//! Constructor
		inline_					Sphere()																		{}
		//! Constructor
		inline_					Sphere(const Point& center, float radius) : mCenter(center), mRadius(radius)	{}
		//! Constructor
								Sphere(udword nb_verts, const Point* verts);
		//! Copy constructor
		inline_					Sphere(const Sphere& sphere) : mCenter(sphere.mCenter), mRadius(sphere.mRadius)	{}
		//! Destructor
		inline_					~Sphere()																		{}

				BSphereMethod	Compute(udword nb_verts, const Point* verts);
				bool			FastCompute(udword nb_verts, const Point* verts);

		// Access methods
		inline_	const Point&	GetCenter()						const		{ return mCenter; }
		inline_	float			GetRadius()						const		{ return mRadius; }

		inline_	const Point&	Center()						const		{ return mCenter; }
		inline_	float			Radius()						const		{ return mRadius; }

		inline_	Sphere&			Set(const Point& center, float radius)		{ mCenter = center; mRadius = radius; return *this; }
		inline_	Sphere&			SetCenter(const Point& center)				{ mCenter = center; return *this; }
		inline_	Sphere&			SetRadius(float radius)						{ mRadius = radius; return *this; }

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	Tests if a point is contained within the sphere.
		 *	\param		p	[in] the point to test
		 *	\return		true if inside the sphere
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		inline_	bool			Contains(const Point& p)		const
								{
									return mCenter.SquareDistance(p) <= mRadius*mRadius;
								}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	Tests if a sphere is contained within the sphere.
		 *	\param		sphere	[in] the sphere to test
		 *	\return		true if inside the sphere
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		inline_	bool			Contains(const Sphere& sphere)	const
								{
									// If our radius is the smallest, we can't possibly contain the other sphere
									if(mRadius < sphere.mRadius)	return false;
									// So r is always positive or null now
									float r = mRadius - sphere.mRadius;
									return mCenter.SquareDistance(sphere.mCenter) <= r*r;
								}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	Tests if a box is contained within the sphere.
		 *	\param		aabb	[in] the box to test
		 *	\return		true if inside the sphere
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		inline_ BOOL			Contains(const AABB& aabb)	const
								{
									// I assume if all 8 box vertices are inside the sphere, so does the whole box.
									// Sounds ok but maybe there's a better way?
									float R2 = mRadius * mRadius;
#ifdef USE_MIN_MAX
									const Point& Max = ((ShadowAABB&)&aabb).mMax;
									const Point& Min = ((ShadowAABB&)&aabb).mMin;
#else
									Point Max; aabb.GetMax(Max);
									Point Min; aabb.GetMin(Min);
#endif
									Point p;
									p.x=Max.x; p.y=Max.y; p.z=Max.z;	if(mCenter.SquareDistance(p)>=R2)	return FALSE;
									p.x=Min.x;							if(mCenter.SquareDistance(p)>=R2)	return FALSE;
									p.x=Max.x; p.y=Min.y;				if(mCenter.SquareDistance(p)>=R2)	return FALSE;
									p.x=Min.x;							if(mCenter.SquareDistance(p)>=R2)	return FALSE;
									p.x=Max.x; p.y=Max.y; p.z=Min.z;	if(mCenter.SquareDistance(p)>=R2)	return FALSE;
									p.x=Min.x;							if(mCenter.SquareDistance(p)>=R2)	return FALSE;
									p.x=Max.x; p.y=Min.y;				if(mCenter.SquareDistance(p)>=R2)	return FALSE;
									p.x=Min.x;							if(mCenter.SquareDistance(p)>=R2)	return FALSE;

									return TRUE;
								}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	Tests if the sphere intersects another sphere
		 *	\param		sphere	[in] the other sphere
		 *	\return		true if spheres overlap
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		inline_	bool			Intersect(const Sphere& sphere)	const
								{
									float r = mRadius + sphere.mRadius;
									return mCenter.SquareDistance(sphere.mCenter) <= r*r;
								}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	Checks the sphere is valid.
		 *	\return		true if the box is valid
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		inline_	BOOL			IsValid()	const
								{
									// Consistency condition for spheres: Radius >= 0.0f
									if(mRadius < 0.0f)	return FALSE;
									return TRUE;
								}
		public:
				Point			mCenter;		//!< Sphere center
				float			mRadius;		//!< Sphere radius
	};

