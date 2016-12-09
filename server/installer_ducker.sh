#!/bin/bash
git clone https://github.com/Taller-7552-II/Jobify
cd Jobify
cd server
chmod +x build.sh
./build.sh
./run_coverage.sh "UPLOAD"
