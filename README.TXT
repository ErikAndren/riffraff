Stolen from https://raw.githubusercontent.com/bucanero/apollo-ps3/master/source/rifrap.c

This program can generate .rap files from .rip and vice versa.

Tested with mbedtls 2.25 on mac os X Catalina
Tested with mbedtls 2.16 on Debian Buster

Use str2idps to convert idps as a string to a hex file
Use riffraff to convert between rip and rap files with the following arguments:
First argument is path to idps_key (16 bytes)
Second argument is path to where act.dat is located
Third argument is path to rif/rap file
Fourth argument is the path where the generated rifrap is to be stored
