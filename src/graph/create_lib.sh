#!/bin/bash
#NOTE: the Makefile should compile with "-c"

install_destination='../../lib/'
libname="libzgraph.a"
object_files="Graph_Node.o"

tmp_destination="lib/"


##################
function if_error
##################
{
if [[ $? -ne 0 ]]; then # check return code passed to function
echo "$1" 
exit $?
fi
}

echo "Compiling..."
make compile 2>/dev/null 1>/dev/null
if_error "ERROR: Source Code does not compile!"

mkdir $tmp_destination

echo "Creating Libraries:"

echo "Building lib..."
ar rcs $tmp_destination$libname $object_files

mv $tmp_destination$libname $install_destination
rmdir $tmp_destination
rm *.o



