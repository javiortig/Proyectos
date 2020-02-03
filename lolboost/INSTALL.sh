#!/bin/bash

if  [ -z "$( which curl )" ]; then
    sudo yum -y install curl
fi

if [ -z "$( which column )" ]; then
    sudo yum -y install column
fi

if [ -z "$( which awk )" ]; then
    sudo yum -y install awk
fi

if [ -z "$( which sed )" ]; then
    sudo yum -y install sed
fi

echo "Done!"

exit 0
