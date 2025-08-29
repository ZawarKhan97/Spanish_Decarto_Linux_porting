#In Order to buid the driver you need to do this 
gcc -o tc358870_init tc358870_init.c
sudo ./tc358870_init
gcc -Wall -o tc_init tc358870_init.c
gcc -g -o tc358870_init tc358870_init.c
