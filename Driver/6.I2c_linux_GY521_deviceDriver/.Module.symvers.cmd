cmd_/home/pi/workspace/DriverImplementaion/2.I2c_linux_GY521_deviceDriver/Module.symvers := sed 's/\.ko$$/\.o/' /home/pi/workspace/DriverImplementaion/2.I2c_linux_GY521_deviceDriver/modules.order | scripts/mod/modpost -m -a  -o /home/pi/workspace/DriverImplementaion/2.I2c_linux_GY521_deviceDriver/Module.symvers -e -i Module.symvers   -T -