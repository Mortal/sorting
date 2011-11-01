// -*- mode: c++; tab-width: 4; indent-tabs-mode: t; c-file-style: "stroustrup"; -*-
// vi:set ts=4 sts=4 sw=4 noet cino+=(0 :

#ifdef SORTING_MEMORY
// from tpie/test/blocksize2MB.h:

	// Define logical block size factor (default is 32)
	// This yields a 2 MB block size
	#ifdef WIN32
		// the block size on windows is larger than on linux,
		#define STREAM_UFS_BLOCK_FACTOR 32
	#else
		#define STREAM_UFS_BLOCK_FACTOR 512
	#endif
#endif

#include "common.h"

#include <tpie/tpie.h>
#include <tpie/sort.h>
#include <tpie/stream.h>

using namespace tpie;

void sort_test(size_t n, int seed = 42) {
	std::cout << "Generating " << n << " elements with seed " << seed << std::endl;
	ami::stream<type> mystream;
	boost::rand48 prng(seed);
	for(size_t i=0; i < n; ++i) {
		type x(prng());
		mystream.write_item(x);
	}

	std::cout << "tpie::ami::sort()" << std::endl;
	sorttimer _(n, sizeof(type));
	ami::sort(&mystream);
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

	std::cout << "Memory limit: " << (memory >> 20) << " MiB" << std::endl;
	tpie::tpie_init();
	tpie::get_memory_manager().set_limit(memory);
	sort_test(n, seed);
}

