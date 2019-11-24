if [ ! -d $HOME/arm-gcc-toolchain ]; then
	pushd .
	cd ~ 
	mkdir arm-gcc-toolchain
	wget -O $HOME/arm-gcc-toolchain/gcc.tar.bz2 $GCC_URL
	cd arm-gcc-toolchain
	tar -jxf gcc.tar.bz2 --strip=1
	popd
fi
export PATH=$HOME/arm-gcc-toolchain/bin:$PATH
