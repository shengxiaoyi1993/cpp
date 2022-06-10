set -e

if [ $# -eq 0 ];then
echo 'para is needed: "'"start"'" or "'"continue"'"'
elif [ $1 == 'start' ];then


  cd gsoap_bin/
  BIN_DIR=`pwd`
  cd ..

  echo 'start to install tools ...'
  sudo yum install  openssl
  sudo yum install flex
  sudo yum install bison
  sudo yum install openssl-devel.x86_64
  sudo yum install -y byacc
  sudo yum install openssl-devel.x86_64
  sudo yum install libuuid-devel
  echo 'end to install tools ...'


  echo 'start to install gsoap ...'
  wget -O gsoap_2.8.51.zip ftp://pub:9900@192.168.1.238/lib/gsoap_2.8.51.zip
  unzip gsoap_2.8.51.zip
  cd gsoap-2.8/
  ./configure --prefix=$BIN_DIR
  make
  sudo make install
  cd ..
  cp gsoap-2.8/gsoap/typemap.dat OnvifFrameWork/level1/level2/GenerateSource/
  cp gsoap_bin/bin/* OnvifFrameWork/level1/level2/GenerateSource/
  echo 'end to install gsoap ...'


  echo 'start to compile onvif ...'
  cd OnvifFrameWork/level1/level2/GenerateSource/
  ./wsdl2h -t  typemap.dat -c  -o onvif.h remotediscovery.wsdl devicemgmt.wsdl analytics.wsdl analyticsdevice.wsdl media.wsdl deviceio.wsdl display.wsdl event.wsdl imaging.wsdl recording.wsdl replay.wsdl search.wsdl receiver.wsdl ptz.wsdl

  echo 'please modify the onvif.h'
  exit

elif [ $1 == 'continue' ];then
  cd OnvifFrameWork/level1/level2/GenerateSource/
  ./soapcpp2 -C -L onvif.h -x -I ../../../../gsoap-2.8/gsoap/import:../../../../gsoap-2.8/gsoap:../../../../gsoap-2.8/gsoap/plugin:../../../../gsoap-2.8/gsoap/custom
  if [ -d "../FrameworkSource" ] 
  then
    rm "../FrameworkSource" -rf
  fi
  mkdir ../FrameworkSource
  cp soapC.c soapClient.c soapH.h soapStub.h wsdd.nsmap ../FrameworkSource/
  cd ../FrameworkSource
  cp ../../../../gsoap-2.8/gsoap/stdsoap2.c ../../../../gsoap-2.8/gsoap/stdsoap2.h .
  cp ../../../../gsoap-2.8/gsoap/custom/duration* .
  cp ../../../../gsoap-2.8/gsoap/import/wsa5.h .
  cp ../../../../gsoap-2.8/gsoap/plugin/wsaapi.* ../../../../gsoap-2.8/gsoap/plugin/wsseapi.c ../../../../gsoap-2.8/gsoap/plugin/wsseapi.h .
  cp ../../../../gsoap-2.8/gsoap/plugin/threads.* .
  cp ../../../../gsoap-2.8/gsoap/dom.c ../../../../gsoap-2.8/gsoap/import/dom.h .
  cp ../../../../gsoap-2.8/gsoap/plugin/mecevp.* .
  cp ../../../../gsoap-2.8/gsoap/plugin/smdevp.* .
  echo 'end to compile onvif ...'

  BIN_SRC=`pwd`
  echo 'source code is in' \'$BIN_SRC\'

  cp * ../../../../../src/onvif

elif [ $1 == 'clean' ];then
  echo 'start to clean'

rm gsoap_2.8.51.zip
rm gsoap-2.8 -rf
cd gsoap_bin/
sudo rm * -rf
cd ../

cd OnvifFrameWork/level1/level2/GenerateSource/
rm *.c
rm *.h
rm *.nsmap
rm soapcpp2
rm wsdl2h

cd ../FrameworkSource/
rm * -rf
 cd ../../../../
echo 'end to clean'


else
echo 'para is needed: "'"start"'" or "'"continue"'"'
fi
