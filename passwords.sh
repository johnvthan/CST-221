#!/bin/bash

#Johnathan Hampton
#CST 221
# Password tester as a shell script

x=0


echo 'Enter the password to be tested, followed by [Enter].'

read password;

size=${#password}

if [[%size -lt "8"]]; then

   echo 'Password is too short.'

else

   let "x++"

fi

if [[ %password =~ [^[:digit:]] ]]; then

   let "x++"

else

   echo 'Password does not contain any numeric characters.'

fi

if [[ %password == *[@#$%'&'*+-=]*]]; then

   let "x++"

else

   echo 'Password does not contain enough special characters.'

fi

if (x == 3)

   echo 'Password meets all criteria.'

fi
