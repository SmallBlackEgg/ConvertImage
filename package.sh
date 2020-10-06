#!/bin/bash

if [ $# -ne 1 ]; then
  echo "./package.sh [linux|osx]"
fi

package_name="image_tools"
package_path="`pwd`"
platform=$1

mkdir -p $package_name/bin
mkdir -p $package_name/scripts
mkdir -p $package_name/conf
mkdir -p $package_name/lib
mkdir -p $package_name/test_data

case $platform in
"osx")
target_os="Darwin"
;;
"linux")
target_os="Linux"
;;
*)
  echo "The platform is [linux|osx]"
  exit 1;
esac

#pack lib
echo "[`date +"%H:%M:%S"`] pack lib"
cp -a $package_path/3rdparty/opencv/lib/$target_os/* $package_name/lib
echo "[`date +"%H:%M:%S"`] pack lib finish"

#pack bin
echo "[`date +"%H:%M:%S"`] pack bin"
cp $package_path/bin/$target_os/* $package_name/bin
echo "[`date +"%H:%M:%S"`] pack bin finish"

#pack scripts
echo "[`date +"%H:%M:%S"`] pack scripts"
cp $package_path/scripts/* $package_name/scripts
echo "[`date +"%H:%M:%S"`] pack scripts finish"

#pack data
echo "[`date +"%H:%M:%S"`] pack test_data"
cp -r $package_path/test_data/* $package_name/test_data
echo "[`date +"%H:%M:%S"`] pack test_data finish"

#pack config
echo "[`date +"%H:%M:%S"`] pack config"
cp $package_path/convert_image.json $package_name/conf
echo "[`date +"%H:%M:%S"`] pack config finish"

#package
echo "[`date +"%H:%M:%S"`] start packing"
tar -zcf image_tools_$target_os.tar.gz ./image_tools
rm -rf image_tools
echo "[`date +"%H:%M:%S"`] end packing"