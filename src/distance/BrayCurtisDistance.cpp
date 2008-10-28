/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2008 Christian Gehl
 * Copyright (C) 2008 Fraunhofer Institute FIRST
 */

#include "lib/config.h"
#include "lib/common.h"
#include "lib/io.h"
#include "distance/BrayCurtisDistance.h"
#include "features/Features.h"
#include "features/RealFeatures.h"

CBrayCurtisDistance::CBrayCurtisDistance()
: CSimpleDistance<float64_t>()
{
}

CBrayCurtisDistance::CBrayCurtisDistance(CRealFeatures* l, CRealFeatures* r)
: CSimpleDistance<float64_t>()
{
	init(l, r);
}

CBrayCurtisDistance::~CBrayCurtisDistance()
{
	cleanup();
}

bool CBrayCurtisDistance::init(CFeatures* l, CFeatures* r)
{
	bool result=CSimpleDistance<float64_t>::init(l,r);

	return result;
}

void CBrayCurtisDistance::cleanup()
{
}

bool CBrayCurtisDistance::load_init(FILE* src)
{
	return false;
}

bool CBrayCurtisDistance::save_init(FILE* dest)
{
	return false;
}

float64_t CBrayCurtisDistance::compute(int32_t idx_a, int32_t idx_b)
{
	int32_t alen, blen;
	bool afree, bfree;

	float64_t* avec=
		((CRealFeatures*) lhs)->get_feature_vector(idx_a, alen, afree);
	float64_t* bvec=
		((CRealFeatures*) rhs)->get_feature_vector(idx_b, blen, bfree);

	ASSERT(alen==blen);

	float64_t s1=0;
	float64_t s2=0;
	{
		for (int32_t i=0; i<alen; i++)
		{
			s1+=fabs(avec[i]-bvec[i]);
			s2+=fabs(avec[i]+bvec[i]);
		}
	}

	((CRealFeatures*) lhs)->free_feature_vector(avec, idx_a, afree);
	((CRealFeatures*) rhs)->free_feature_vector(bvec, idx_b, bfree);
	
	// trap division by zero
	if(s2==0)
		return 0;

	return (s1/s2);
}
