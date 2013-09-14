#!/bin/sh


sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
sudo apt-get update -qq
sudo apt-get install -qq g++-4.8;

TOOL_CHAIN=TRAVIS PROJECT_ROOT_DIR=$PWD ONLY_MODES=CPP make $*
