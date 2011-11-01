// -*- mode: c++; tab-width: 4; indent-tabs-mode: t; c-file-style: "stroustrup"; -*-
// vi:set ts=4 sts=4 sw=4 noet cino+=(0 :

#include <sys/time.h>
#include <boost/random/linear_congruential.hpp>

typedef int type;

const size_t memory = 2L * 1024 * 1024 * 1024;

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

struct sorttimer {
	sorttimer(size_t n, size_t size) : n(n), size(size) {
		gettimeofday(&before, 0);
	}
	~sorttimer() {
		timeval after;
		gettimeofday(&after, 0);

		double seconds = after - before;
		double MiB = double(n * sizeof(type)) / double(1 << 20);

		std::cout << "Sorted " << n << " elements of size " << size << " (total " << (MiB / 1024) << " GiB) in " << seconds << " seconds, " << (double(n) / seconds) << " items/sec " << (MiB / seconds) << " MiB/s" << std::endl;
	}
private:
	timeval before;
	size_t n;
	size_t size;
};

