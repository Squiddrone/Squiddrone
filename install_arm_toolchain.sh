if [ ! -d $HOME/arm-gcc-toolchain/bin ]; then
	pushd .
	cd ~ 
	if [ ! -d $HOME/arm-gcc-toolchain ]; then
		mkdir arm-gcc-toolchain
	fi
	wget -O $HOME/arm-gcc-toolchain/gcc.tar.bz2 $GCC_URL
	cd arm-gcc-toolchain
	tar -jxf gcc.tar.bz2 --strip=1
	popd
fi
export PATH=$HOME/arm-gcc-toolchain/bin:$PATH
