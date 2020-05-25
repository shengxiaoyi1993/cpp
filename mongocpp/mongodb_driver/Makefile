linux: c_linux cxx_linux

windows:c_windows cxx_windows


c_linux:
	-mkdir c
	cd c && cmake ../mongo-c-driver-1.14.0/ -DCMAKE_INSTALL_PREFIX=`pwd`/usr/ && make -j4 && sudo make install

c_windows:
	-mkdir c
	cd c && cmake ../mongo-c-driver-1.14.0/ -G "Unix Makefiles" -DCMAKE_C_FLAGS="-D__USE_MINGW_ANSI_STDIO=1" -DCMAKE_INSTALL_PREFIX=`pwd`/usr/ && make -j4 && make install

cxx_linux:
	-mkdir cxx
	cd cxx && cmake ../mongo-cxx-driver-3.4.0 -DCMAKE_PREFIX_PATH=`pwd`/../c/usr/ -DCMAKE_INSTALL_PREFIX=`pwd`/usr/ && make && sudo make install

cxx_windows:
	-mkdir cxx
	cd cxx && cmake ../mongo-cxx-driver-3.4.0 -G "Unix Makefiles" -DCMAKE_PREFIX_PATH=`pwd`/../c/usr/ -DCMAKE_C_FLAGS="-D__USE_MINGW_ANSI_STDIO=1" -DCMAKE_INSTALL_PREFIX=`pwd`/usr/ && make  && make install
