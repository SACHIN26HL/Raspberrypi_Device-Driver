cmd_/home/enginner/Doc_Raspberry_Pi/Driver/File_operation_User_and_KernelD_app/Module.symvers := sed 's/\.ko$$/\.o/' /home/enginner/Doc_Raspberry_Pi/Driver/File_operation_User_and_KernelD_app/modules.order | scripts/mod/modpost -m -a  -o /home/enginner/Doc_Raspberry_Pi/Driver/File_operation_User_and_KernelD_app/Module.symvers -e -i Module.symvers   -T -
