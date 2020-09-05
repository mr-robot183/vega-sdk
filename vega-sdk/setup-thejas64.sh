#-------------------------------------------------------------------- 
#Project Name		: MDP - Microprocessor Development Project
#Project Code		: HD083D
#Created		: 07-Jan-2020
#Filename		: setup-thejas64.sh
#Purpose		: Environment script
#Description		: 
#Author(s)		: Premjith A V
#Email			: premjith@cdac.in
#--------------------------------------------------------------------    
#See LICENSE for license details.
#/bin/bash

VEGA_SDK=`pwd`

CONFIG_PATH=~/.config/vega-tools
mkdir -p $CONFIG_PATH

set_property(){
filename=$CONFIG_PATH/settings.mk

if ! grep -R "^[#]*\s*${1}=.*" $filename &> /dev/null; then
  #echo "APPENDING because '${1}' not found"
  echo "$1=$2" >> $filename 
else
  #echo "SETTING because '${1}' found already"
  sed -i "s|^[#]*\s*${1}=.*|$1=$2|" $filename
fi
}

get_property()
{
 filename=$CONFIG_PATH/settings.mk
 sed -rn "s/^${1}=([^\n]+)$/\1/p" $filename
}

package_install()
{
    echo "Checking for libraries: git, build-essential, autoconf, minicom"
    ## Prompt the user 
    read -p "Do you want to install missing libraries? [y/n]: " answer
    ## Set the default value if no answer was given
    answer=${answer:Y}
    ## If the answer matches y or Y, install
    [[ $answer =~ [Yy] ]] && sudo apt install ${libnames[@]}
}


setup_minicom()
{
echo "Configuring minicom & adding user to 'dialout' group"
 echo "# Machine-generated file - use setup menu in minicom to change parameters.
pu port             /dev/ttyUSB1
pu baudrate         115200
pu bits             8
pu parity           N
pu stopbits         1
pu updir            $VEGA_SDK/bin
pu rtscts           No 
" > ~/.minirc.thejas64
mkdir -p /etc/minicom/
sudo -i cp ~/.minirc.thejas64 /etc/minicom/minirc.thejas64
sudo usermod -a -G dialout $USER
echo "---------------------------------------------------------------------"
echo "Minicom configured for thejas64 hardware & user added to 'dialout' group."
echo "Command for uart access: minicom thejas64"
echo "[If permission denied, try restart the system]"
echo "---------------------------------------------------------------------"
}


libnames=("git" "build-essential" "autoconf" "minicom" )
## Run the package_install function if sany of the libraries are missing
dpkg -s "${libnames[@]}" >/dev/null 2>&1 || package_install


echo "Setting up VEGA SDK Environment"

set_property "VEGA_SDK" "$VEGA_SDK"
set_property "VEGA_MACHINE" "THEJAS64"



cd ./bsp && ./clean.sh > /dev/null && autoreconf -f -i 
cd ..
make clean > /dev/null

setup_minicom

echo "VEGA SDK Environment added"

vega_tool_flag=$(get_property "VEGA_TOOLS")

if [ -z "$vega_tool_flag" ]
then
      echo "WARNING: Please install vega-tools, and setup environment!"
fi




