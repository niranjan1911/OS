#!/bin/bash

fn="abc.dat"
tf="xyz.dat"
ch=0
temp=0
create()
{
	touch $fn
	echo -e " " >$fn
	echo -e "Database is created"
}

insert()
{
	echo -e "How many records you want to add"
	read c
	i=0
	add=1
	while [ $i -ne $c ]
	do
	        p=`expr $i + $add`
		echo -e "Record : $p"
		temp=`expr $temp + $add`
		echo -e "Enter the Name"
		read name
		while [ true ]
		do 
			if ! [[ $name =~ ^[a-zA-Z]+$ ]]
			then
				echo -e "Please Enter Proper name:"
				read name;
			else
			 	break
			 fi
		done
		echo -e "Enter the Address"
		read address
		echo -e "Enter the Mobile number"
		read phone
		#counting number of digit in phone number	
		count="${#phone}"
		#validation for phone number digits
		while [ true ] 
		do
			if [ $count -ne 10 ]
			then
				phone=0;
				echo -e "Entered Mo. number is not a 10 digit.\nEnter properly:"   
				read phone
			else if [[ $phone =~ ^[a-zA-Z]+$ ]]
			then
				echo -e "Entered Mo. number contain alphabet\nEnter properly:"   
				read phone
			else
				break
			fi
			
			
			#validation for pin digits
			
		done
		echo -e "Enter the Pin number"
		read pin
		count="${#pin}"
		while [ $count -ne 6 ]
			do
				pin=0;
				echo -e "Entered pin is not 6 digit.\nEnter properly:"   
				read pin
				count="${#pin}"
			done
		echo -e " $temp\t$name\t$address\t$phone\t$pin" >>$fn
		i=`expr $i + $add`
	done
	echo -e "Records inserted sucessfully..."
}

display_alpha_a()
{
	echo -e "Records in database in alphabetically by name...\n"
	echo -e " ID\tNAME\tADDRESS\tMOBILE\tPIN"
	echo -e "$(sort -k 3 "$fn")">"$fn"
	cat "$fn"
}

display_alpha_n()
{
	echo -e "Records in database in alphabetically by address...\n"
	echo -e " ID\tNAME\tADDRESS\tMOBILE\tPIN"
	echo -e "$(sort -k 2 "$fn")">"$fn"
	cat "$fn"
		
}

display_alpha_p()
{
	echo -e "Records in database in alphabetically by pin code...\n"
	echo -e " ID\tNAME\tADDRESS\tMOBILE\tPIN"
	echo -e "$(sort -k 5 "$fn")">"$fn"
	cat "$fn"
		
}

display_all()
{
	echo -e "Records in database are...\n"
        echo -e " ID\tNAME\tADDRESS\tMOBILE\tPIN"
        echo -e "$(sort -k 1 "$fn")">"$fn"
	cat $fn	

}


display()
{
		
	while [ $ch -ne 4 ]
	do
 		echo -e "\n----------DISPLAY MENU'S----------"
		echo -e "\t1.Display all records\n\t2.Display all records in ascending order by NAME\n\t3.Display all records in ascending order by ADDRESS\n\t4.Display all records in ascending order by Pin-code\n\t5.Return to main menu\nEnter choice:"
		read ch

   	 case $ch in
	
		  1)display_all;;	
		  2)display_alpha_n;;
		  3)display_alpha_a;;
		  4)display_alpha_p;;
		  5);;
		  *)echo -e "\nwrong choice.....\n";;
	 esac
done
}

search()
{
	echo -e "Enter the ID for search"
	read roll
	grep -i -q -w "$roll" "$fn"
	stat=$?
	if [ $stat -eq 0 ]
	then 
		echo -e "Record present"
		grep -i -w -h "$roll" "$fn"
	else
	        echo -e "Record not present"
	fi
}

delete()
{
	echo -e "Enter the ID to be delete"
	read roll
	grep -i -q "$roll" "$fn"
	stat=$?
	if [ $stat -eq 0 ]
	then 
		grep -i -w -v "$roll" "$fn" >>"$tf"
		rm "$fn"
		mv "$tf" "$fn"
		echo -e "Record deleted"
		display_all
		
		
	else
	  	 echo -e "Record not present"
	fi
	
}


modify()
{
	echo -e "Enter the ID to be modify"
	read roll
	row=$(grep -i -w "$roll" "$fn")
	stat=$?
	if [ $stat -eq 0 ]
	then 
		echo -e "Enter the new Name"
		read name
		echo -e "Enter the new Address"
		read address
		echo -e "Enter the new Mobile number"
		read phone
		echo -e "Enter the new pin code"
		read pin	
		#counting number of digit in phone number	
		count="${#phone}"
		#validation for phone number digits
		while [ $count -ne 10 ]
		do
			phone=0;
			echo -e "Entered Mo. number is not a 10 digit.\nEnter properly:"   
			read phone
			count="${#phone}"
		done
		
		count="${#pin}"
		#validation for pin digits
		while [ $count -ne 6 ]
		do
			pin=0;
			echo -e "Entered pin is not 6 digit.\nEnter properly:"   
			read pin
			count="${#pin}"
		done
		
		sed -i "/$row/c\\ $roll\t$name\t$address\t$phone\t$pin" $fn
		echo -e "Record modified\n"
		display_all
	
	else
		echo -e "Record not  present"
	fi
		
		
}
<<comment1
comment in shell script
comment1

while [ $ch -ne 7 ]
do
 	echo -e "\n----------MENU'S----------"
	echo -e "\t1.Create Database\n\t2.Insert Record\n\t3.Display Database\n\t4.Search Record\n\t5.Delete Record\n\t6.Modify Record\n\t7.Exit\nEnter choice:"
	read ch

    case $ch in
	
	  1)create;;
	  2)insert;;
	  3)display;;
	  4)search;;
	  5)delete;;
	  6)modify;;
	  7);;
	  *)echo -e "\nwrong choice.....\n";;
     esac
done
