FROM ubuntu:14.04

RUN apt-get update \
    && apt-get install -y \
    cmake \
    build-essential \
    gcc \
    make \
	python2.7 \
    python2.7-dev \
    python3.4 \
    python3.4-dev \
    python-pycurl \
    python-pip \
	gcc-multilib \
	libgcc1-dbg \
	libgomp1-dbg \
	libitm1-dbg \
	libatomic1-dbg \
	libtsan0-dbg \
	libquadmath0-dbg \
	zlib1g-dev \
	libbz2-dev \
	libcurl4-openssl-dev \
	libsnappy-dev   \
	autoconf \
	curl \
	git \
	g++ \
	libgflags-dev \
	libssl-dev \
	libtool \
	openssl \
	python \
    && apt-get autoremove \
    && apt-get clean

#Le mando el lcov
RUN apt-get install -y lcov

# Install levelDB
RUN apt-get install -y libleveldb-dev

# Install crypto
RUN apt-get install -y libcrypto++9 libcrypto++9-dbg libcrypto++-dev

# Install libjansson
RUN apt-get install -y libjansson4 libjansson-dev libjansson-dbg

# Install coveralls
RUN apt-get install -y python-pip
RUN pip install cpp-coveralls
	
# Clone repository and checkout AppServer
RUN git clone https://github.com/Taller-7552-II/Jobify
# Make
RUN chmod +x Jobify/server/build.sh
RUN cd Jobify/server;./build.sh;./run_coverage.sh "UPLOAD"


# Expose ports
EXPOSE 8000
