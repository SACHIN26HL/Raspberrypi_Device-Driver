cmd_/home/enginner/Doc_Raspberry_Pi/Driver/Passing_argument_to_driver/Module.symvers := sed 's/\.ko$$/\.o/' /home/enginner/Doc_Raspberry_Pi/Driver/Passing_argument_to_driver/modules.order | scripts/mod/modpost -m -a  -o /home/enginner/Doc_Raspberry_Pi/Driver/Passing_argument_to_driver/Module.symvers -e -i Module.symvers   -T -