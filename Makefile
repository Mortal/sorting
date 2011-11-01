WORKSPACE=/home/rav/work
TPIEMEMORY=$(WORKSPACE)/tpie-memory
TPIEFILESTREAM=$(WORKSPACE)/tpie
STXXL=$(WORKSPACE)/stxxl-1.3.1

all: bench_external_sort-memory bench_external_sort-filestream bench_external_sort-stxxl

clean:
	rm -f bench_external_sort-memory bench_external_sort-filestream bench_external_sort_stxxl.pmstxxl_boost.o bench_external_sort-stxxl

bench_external_sort-memory: bench_external_sort_tpie.cpp common.h
	g++ -DSORTING_MEMORY -o $@ bench_external_sort_tpie.cpp -I$(TPIEMEMORY) -I$(TPIEMEMORY)/Release -L$(TPIEMEMORY)/Release/tpie -ltpie -lboost_date_time -lboost_thread -lboost_filesystem -lboost_system -O3 -DNDEBUG

bench_external_sort-filestream: bench_external_sort_tpie.cpp common.h
	g++ -DSORTING_FILESTREAM -o $@ bench_external_sort_tpie.cpp -I$(TPIEFILESTREAM) -I$(TPIEFILESTREAM)/Release -L$(TPIEFILESTREAM)/Release/tpie -ltpie -lboost_date_time -lboost_thread -lboost_filesystem -lboost_system -O3 -DNDEBUG

bench_external_sort_stxxl.pmstxxl_boost.o: bench_external_sort_stxxl.cpp common.h
	g++  -pthread  -I$(STXXL)/include -include $(STXXL)/include/stxxl/bits/defines.h -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE  -O3   -W -Wall -Woverloaded-virtual -Wundef  -fopenmp -D_GLIBCXX_PARALLEL  -DSTXXL_BOOST_CONFIG -DSTXXL_BOOST_FILESYSTEM -DSTXXL_BOOST_RANDOM -DSTXXL_BOOST_THREADS  -c -o bench_external_sort_stxxl.pmstxxl_boost.o bench_external_sort_stxxl.cpp

bench_external_sort-stxxl: bench_external_sort_stxxl.pmstxxl_boost.o
	g++  bench_external_sort_stxxl.pmstxxl_boost.o   -pthread -L$(STXXL)/lib -lstxxl_boost -fopenmp  -lboost_thread -lboost_date_time -lboost_iostreams -lboost_system -lboost_filesystem  -o $@
