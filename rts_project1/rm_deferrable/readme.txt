* Before running the RM simulator with the deferrable server please change the path to the input file and path to the output file in the source code rmdef.c


* It has been indicated in the source codes rmdef.c and where the path to the input file and path to the output file has to be changed.


* To compile the rm simulator with the deferrable server type the following command on the command line in the current directory:
	gcc my_def_func.c rmdef.c -o def
and then run the simulator using:
	./def
	
* The file sample_defoutput.txt is the output file generated when the input to the rm simulator with deferrable server is question2_taskset.txt.

* All the coding and testing was done on UBUNTU 16.04
