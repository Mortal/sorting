// -*- mode: c++; tab-width: 4; indent-tabs-mode: t; c-file-style: "stroustrup"; -*-
// vi:set ts=4 sts=4 sw=4 noet cino+=(0 :

#include <sys/time.h>
#include <boost/random/linear_congruential.hpp>

typedef int type;

double operator - (const timeval & a, const timeval & b)
{
	long sec = a.tv_sec - b.tv_sec;
	long usec = a.tv_usec - b.tv_usec;
	if (usec < 0) {
		usec += 1000000;
		sec -= 1;
	}
	return double(sec) + double(usec) / 1000000.;
}

