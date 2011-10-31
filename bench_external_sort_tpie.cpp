// -*- mode: c++; tab-width: 4; indent-tabs-mode: t; c-file-style: "stroustrup"; -*-
// vi:set ts=4 sts=4 sw=4 noet :
// Copyright 2009, The TPIE development team
// 
// This file is part of TPIE.
// 
// TPIE is free software: you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the
// Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
// 
// TPIE is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with TPIE.  If not, see <http://www.gnu.org/licenses/>
//#include "app_config.h"
//#include <tpie/portability.h>
#include <tpie/tpie.h>
//#include <tpie/util.h>
#include <tpie/sort.h>
#include <tpie/stream.h>
//#include <tpie/prime.h>
//#include <ctime>
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

using namespace tpie;

void sort_test(size_t n, int seed = 42) {
	std::cout << "Generating " << n << " elements with seed " << seed << std::endl;
	ami::stream<type> mystream;
	boost::rand48 prng(seed);
	for(size_t i=0; i < n; ++i) {
		type x(prng());
		mystream.write_item(x);
	}

	timeval before;
	gettimeofday(&before, 0);

	std::cout << "tpie::ami::sort()" << std::endl;
	ami::sort(&mystream);
	mystream.seek(0);

	timeval after;
	gettimeofday(&after, 0);

	double seconds = after - before;
	double MiB = double(n * sizeof(type)) / double(1 << 20);

	std::cout << "Sorted " << n << " elements of size " << sizeof(type) << " (total " << (MiB / 1024) << " GiB) in " << seconds << " seconds, " << (double(n) / seconds) << " items/sec " << (MiB / seconds) << " MiB/s" << std::endl;
}


int main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " bytes [seed]" << std::endl;
		return 1;
	}

	size_t n = atol(argv[1]) / sizeof(type);
	int seed = getpid();
	if (argc > 2)
		seed = atoi(argv[2]);

	tpie::tpie_init();
	tpie::get_memory_manager().set_limit(4096L*1024*1024);
	sort_test(n, seed);
}
