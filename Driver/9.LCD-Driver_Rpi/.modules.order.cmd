cmd_/home/pi/workspace/DriverImplementaion/LCD-Driver_Rpi/modules.order := {   echo /home/pi/workspace/DriverImplementaion/LCD-Driver_Rpi/mydriver.ko; :; } | awk '!x[$$0]++' - > /home/pi/workspace/DriverImplementaion/LCD-Driver_Rpi/modules.order