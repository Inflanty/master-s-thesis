#!/bin/sh
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

FILE_PATH="_build/nrf52832_xxaa.hex"
SOFTDEVICE_FILE_PATH="../../../../../../../s132_nrf52_4.0.5/s132_nrf52_4.0.5_softdevice.hex"

if [ -s $FILE_PATH ]
then  
  echo "Find Project's .hex file !"
  ERRORCODE=0
else
  echo "ERROR: No Project's .hex file !"
  ERRORCODE=1
  exit
fi

if [ -s $SOFTDEVICE_FILE_PATH ]
then
  echo "Find SoftDevice .hex file !"
  ERRORCODE=0
else
  echo "ERROR: No SoftDevice .hex file !"
  ERRORCODE=1
  exit
fi

if [ $ERRORCODE -eq 0 ]
then
  echo "SUCCESS: All .hex files found, MERGEING ..."
  mergehex -m $SOFTDEVICE_FILE_PATH $FILE_PATH -o SoC.hex
elif [ $ERRORCODE -eq 1 ]
then  
  echo "ERROR: EXIT ..."
elif [ $ERRORCODE -gt 1 ]
then
  echo "ERROR: $ERRORCODE"
fi

if [ -s SoC.hex ]
then
  echo "SUCCESS: File _build/nrf52832_xxaa.hex exist, FLASHING ..."
  #nrfjprog --family NRF52 --clockspeed 4000 --program $FILE_PATH --chiperase
else
  echo "FAIL !"
fi
