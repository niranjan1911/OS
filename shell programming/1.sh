#!bin/sh

fn="aaa.txt"
fn1="bbb.txt"

create()
{
   touch $fn
   echo "" >$fn
   echo "Database is created.."
   temp=0
}

insert()
{
  echo "How many??"
  read n
  
  i=0
  add=1
  p=0
  while [ $i -le $n ] 
  do 
        temp=`expr $temp + $add`
        p=`expr $i + $add`
        echo "$p:"
  	
  	echo "Enter name:"
  	read name
  	echo "Enter mobile:"
  	read mobile
  	echo "Enter address:"
  	read address 
  	
  	echo "$temp\t$name\t$mobile\t$address" >>$fn
  	i=`expr $i + $add`
  done
  	echo "Records inserted successfully..."	
}

display()
{
	 echo "Records in database are..."
	 echo "ID\tNAME\tADDRESS\tMOBILE"
	 cat "$fn"
}

search()
{
  	echo "Enter the name:"
  	read key
  	
  	if grep -i -q $key $fn 
  	then
  	   echo "Record found"
  	   echo "ID\tNAME\tADDRESS\tMOBILE"
  	   grep $key $fn
  	else
  	   echo "Record not found"
  	fi
}

delete()
{
   	echo "Enter the name:"
  	read key
  	
  	if grep -i -q $key $fn 
  	then
  	   echo "Record found"
  	   grep -v $key $fn >$fn1
  	   
  	   echo "Record deleted"
  	   rm $fn
  	   mv $fn1 $fn
  	   display
  	else
  	   echo "Record not found"
  	fi
}

modify()
{
	 echo "Enter the name:"
  	 read key
  	 
  	 row=$(grep -i -w $key $fn)
  	 
  	 if grep -i -q $key $fn 
  	 then
  	   echo "Record found"
  	   
  	   echo "Enter new name:"
  	   read name
  	   echo "Enter new mobile:"
  	   read mobile
  	   echo "Enter new address:"
  	   read address
  	    
  	   sed -i "/$row/c\\$key\t$name\t$mobile\t$address" $fn
  	   echo "Record modified"
  	  
  	   display
  	 else
  	   echo "Record not found"
  	 fi
}


ch=0
while [ $ch -ne 7 ]
do
        
		echo "\n----------MENU'S----------"
		echo "\t1.Create Database\n\t2.Insert Record\n\t3.Display Database\n\t4.Search Record\n\t5.Delete Record\n\t6.Modify Record\n\t7.Exit\nEnter choice:"
	   	read ch
	   	
	   case $ch in
	      1)
		 create;;
	      2) 
		 insert;;
	      3)
		 display;;
	      4)
		 search;;
	      5)
		 delete;;
	      6) 
		 modify;;
	      7)
		  ;;
	      *)
		 echo "Invalid choice...";
	    esac
done  
