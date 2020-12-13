#!/bin/bash

#Johnathan Hampton
#CST 221
# User managament as a shell script


group="testGroup"


if grep -q $group /etc/group

then

   echo "group exists"

else

   groupadd $group

fi




filename="users.txt"

while read -r username password

do

      name="$username"

   pass="$password"

   echo "Username: $name"

   echo "Password: $pass"

      if [ $(id -u) -eq 0 ]; then

       egrep "^$name" /etc/passwd >/dev/null

       if [ $? -eq 0 ]; then

           echo "$name exists!"

           exit 1

       else

           useradd -m -p $pass $name

           [ $? -eq 0 ] && echo "User has been added to     system!" || echo "Failed to add a user!"

       fi

   else

       echo "Only root may add a user to the system"

       exit 2

   fi

   usermod -aG $group $name

done < "$filename"




filename="users.txt"

while read -r username password

do

   name="$username"

   pass="$password"

   userdel -r $name

   echo "User Deleted."

done < "$filename"




if grep -q $group /etc/group

then

   groupdel $group

else

       echo "Group does not exist."

fi
