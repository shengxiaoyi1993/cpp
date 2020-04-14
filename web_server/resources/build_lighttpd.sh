//!#!/usr/bin/env bash
DIR_SRC='lighttpd-1.4.55/'
if [[ $# -eq 0 ]]; then
  echo 'please input para'

elif [[ $1 == 'clean ' ]]; then
  echo $1' start...'
  rm lighttpd_bin/* -rf
  echo $1' finish...'
elif [[ $1 == 'build' ]]; then
  echo $1' start...'
  cd lighttpd_bin/
  BIN_DIR=`pwd`
  cd ..

  cd $DIR_SRC
  ./configure --prefix=$BIN_DIR --without-bzip2
  make
  sudo make install
  tree .
  mkdir cache cgi-bin config log sockets upload vhosts webpages
  cp ../lighttpd-1.4.55/doc/config/conf.d/ ../lighttpd-1.4.55/doc/config/lighttpd.conf ../lighttpd-1.4.55/doc/config/modules.conf config/ -rf
  echo 'please modify /config/lighttpd.conf ! '
  echo 'see as ../doc/design/design.md'
  echo $1' finish...'

elif [[ $1 == 'launch' ]]; then
  cd lighttpd_bin/sbin/
  sudo ./lighttpd -f ../config/lighttpd.conf
  echo 'launch the browser and input the url:http://local/'

elif [[ $1 == 'relaunch' ]]; then
  cd lighttpd_bin/sbin/
  sudo ./lighttpd stop
  sudo ./lighttpd restart -f ../config/lighttpd.conf
  echo 'launch the browser and input the url:http://local/'
else
  echo 'para is wrong'
  #statements
fi
