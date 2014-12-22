#!/bin/sh
#params: 1 = yagi program file name, 2 = yagi performance out file name 
#        3 = golog program file name, 4 = golog performance out file name

  echo "Run YAGI program and wait until finished..."
  ./yagi -p -f $1 -o $2 &
  echo "running..."

  timeToLive=600 #seconds
  
  #YAGI first...
  while [ $timeToLive -gt 0 ]
  do
      #check if YAGI is still running
      procdir=$(ps -C yagi | grep yagi)
      if [ -n "$procdir" ];
      then
	sleep 1; #wait 1 seconds if YAGI is still working
	timeToLive=$(( $timeToLive -1 ))
	if [ $timeToLive -eq 0 ];
	then
	  echo "Timout! Killing YAGI..."
	  killall -s KILL yagi
	  sleep 1;
	  break
	fi
      else
        break #yagi has finished 
      fi
  done
  
  if [ $# -eq 2 ]
  then
    return
  fi
  
  #...then Golog
  timeToLive=600 #seconds
    
  echo "Run swipl program and wait until finished..."
  swipl -f $3 $4 &
  echo "running..."
  
  while [ $timeToLive -gt 0 ]
  do
      #check if swipl is still running
      procdir=$(ps -C swipl | grep swipl)
      if [ -n "$procdir" ];
      then
	sleep 1; #wait 1 seconds if swipl is still working
	timeToLive=$(( $timeToLive -1 ))
	if [ $timeToLive -eq 0 ];
	then
	  echo "Timout! Killing swipl"
	  killall -s KILL swipl
	  sleep 1;
	  break
	fi
      else
        break #swipl has finished 
      fi
  done
 
procdir=$(ps -C swipl | grep swipl)
if [ -n "$procdir" ];
then
  killall -s KILL swipl
fi