#!/bin/bash
 
wget http://ftp.de.debian.org/debian/pool/main/l/lcov/lcov_1.11.orig.tar.gz
tar xf lcov_1.11.orig.tar.gz
sudo make -C lcov-1.11/ install
sudo apt-get install ruby
sudo gem install coveralls-lcov
rm lcov_1.11.orig.tar.gz
rm -rf lcov-1.11/