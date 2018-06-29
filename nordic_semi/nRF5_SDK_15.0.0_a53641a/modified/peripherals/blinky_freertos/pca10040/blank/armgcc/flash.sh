@echo off
@echo w4 4001e504 2 > eraseall.jlink
@echo w4 4001e50c 1 >> eraseall.jlink
@echo w4 4001e514 1 >> eraseall.jlink
@echo sleep 100 >> eraseall.jlink
@echo r >> eraseall.jlink
@echo exit >> eraseall.jlink
jlink -device nRF52832_xxAA -speed 4000 -commanderscript eraseall.jlink

@echo w4 4001e504 1 > nrf51_program_sd.jlink
@echo loadbin s110_softdevice.bin 0 >> nrf51_program_sd.jlink
@echo r >> nrf51_program_sd.jlink
@echo g >> nrf51_program_sd.jlink
@echo exit >> nrf51_program_sd.jlink
jlink -device nRF52832_xxAA -speed 4000 -commanderscript nrf51_program_sd.jlink

# TODO: Write complete shell 