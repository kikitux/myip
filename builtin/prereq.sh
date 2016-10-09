#!/bin/bash
if [ -d bash ]; then
  echo "bash/ found, skipping"
else
  mkdir -p bash
  pushd bash

  major="${BASH_VERSINFO[0]}"
  minor="${BASH_VERSINFO[1]}"

  which apt-get &>/dev/null
  if [ $? -eq 0 ]; then
    [ -f bash_${major}.${minor}.orig.tar.gz ] || apt-get source -d bash
    [ -d bash-${major}.${minor} ] || tar zxvf ./bash_${major}.${minor}.orig.tar.gz --strip=1 -C.
    [ -f Makefile ] || ./configure
    make
  else
    [ -f bash-*.src.rpm ] || yumdownloader --source bash
    [ -f /root/rpmbuild/SOURCES/bash-*.tar.gz ] || rpm -Uvh bash-*.src.rpm
    [ -d /usr/src/bash-${major}.${minor} ] || tar zxvf ~/rpmbuild/SOURCES/bash-${major}.${minor}.tar.gz --strip=1 -C.
    [ -f Makefile ] || ./configure
    make
  fi
fi
