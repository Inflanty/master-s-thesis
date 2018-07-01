#!/bin/sh

FILE_PATH="_build/nrf52832_xxaa.hex"
SOFTDEVICE_FILE_PATH="../../../../../../components/softdevice/s132/hex/s132_nrf52_6.0.0_softdevice.hex"

FUNCTION_FindProjectHex()
{
if [ -s $FILE_PATH ]
then  
  echo "Found Project's .hex file !"
  ERRORCODE=0
else
  echo "ERROR: No Project's .hex file !"
  ERRORCODE=1
  exit
fi
}

FUNCTION_FindSoftDevHex()
{
if [ -s $SOFTDEVICE_FILE_PATH ]
then
  echo "Found SoftDevice .hex file !"
  ERRORCODE=0
else
  echo "ERROR: No SoftDevice .hex file !"
  ERRORCODE=1
  exit
fi
}

FUNCTION_MergeFiles()
{
  echo "SUCCESS: All .hex files found, MERGING ..."
  mergehex -m $SOFTDEVICE_FILE_PATH $FILE_PATH -o SoC.hex
}

echo "
███╗   ██╗██████╗ ███████╗   ██╗██████╗ ██████╗  ██████╗  ██████╗     
████╗  ██║██╔══██╗██╔════╝   ██║██╔══██╗██╔══██╗██╔═══██╗██╔════╝     
██╔██╗ ██║██████╔╝█████╗     ██║██████╔╝██████╔╝██║   ██║██║  ███╗    
██║╚██╗██║██╔══██╗██╔══╝██   ██║██╔═══╝ ██╔══██╗██║   ██║██║   ██║    
██║ ╚████║██║  ██║██║   ╚█████╔╝██║     ██║  ██║╚██████╔╝╚██████╔╝    
╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝    ╚════╝ ╚═╝     ╚═╝  ╚═╝ ╚═════╝  ╚═════╝     
                                                                      
███████╗██╗      █████╗ ███████╗██╗  ██╗██╗███╗   ██╗ ██████╗         
██╔════╝██║     ██╔══██╗██╔════╝██║  ██║██║████╗  ██║██╔════╝         
█████╗  ██║     ███████║███████╗███████║██║██╔██╗ ██║██║  ███╗        
██╔══╝  ██║     ██╔══██║╚════██║██╔══██║██║██║╚██╗██║██║   ██║        
██║     ███████╗██║  ██║███████║██║  ██║██║██║ ╚████║╚██████╔╝        
╚═╝     ╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝
"

echo "nRF52832_xxaa flashing"
echo "family : NRF52"
echo "clockspeed : 4000"
echo "checking for file ..."

IS_BLE=$(grep -crwn ../../../main.c -e ble.h)
if [ $? -ne 0 ]; then
	MERGEIT=1
else	
	MERGEIT=0
fi

if [ ! $MERGEIT -eq 1 ]; then
	echo "Find BLE files, merging project's hex with softdevice hex"
  FUNCTION_FindProjectHex
  FUNCTION_FindSoftDevHex
  FUNCTION_MergeFiles
  if [ -s SoC.hex ]; then
    echo "SUCCESS: File SoC.hex exist, FLASHING ..."
    nrfjprog --family NRF52 --clockspeed 4000 --program SoC.hex --chiperase
  else
    echo "ERROR: No merged file ! Exiting..."
    exit
  fi
else
	echo "No BLE files, merging skip"
  FUNCTION_FindProjectHex
  nrfjprog --family NRF52 --clockspeed 4000 --program $FILE_PATH --chiperase
fi


