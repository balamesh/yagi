//location of the robot (room1, ..., room3)
fluent at [{"r1","r2","r3"}];                              
at = {<"r1">};

//location of objects (object1 in room1 etc)
fluent is_at[{"o1","o2","o3"}][{"r1","r2","r3"}];                
is_at = {<"o1","r1">, <"o2","r2">, <"o3","r3">};

//object carried by robot
fluent carry[{"o1","o2","o3"}];

//requests moving an object (param 1) from a sender (param 2) 
//to a receiver (param 3)
fluent request[{"o1","o2","o3"}][{"p1","p2","p3"}][{"p1","p2","p3"}];

//states what person has been detected in what room 
//(will be sensed to its value)
fluent detectedPerson[{"p1","p2","p3"}][{"r1","r2","r3"}];

//one or more rooms are assigned to one person, 
//i.e. the persons' offices 
fact office [{"p1","p2","p3"}][{"r1","r2","r3"}];
office = {<"p1","r1">, <"p1","r2">, <"p2","r2">, <"p3","r3">};

//exogenous event to initiate transportation
//of object $o from $sender to $receiver
exogenous-event receiveRequest($o, $sender, $receiver)
  //add request
  request += {<$o,$sender,$receiver>};
end exogenous-event

//"setting" action to detect a person, i.e.
//$p gets its value from an external src
action detectPerson() external $p
effect:
  //remove person
  detectedPerson -= {<$p, _>};

  //add the sensed person + room tuple to the fluent
  foreach <$r> in at
    detectedPerson += {<$p, $r>};
  end for	
  
signal:
  "detect person";
end action

//move robot to room $r
action move($r)
precondition:
  //robot is not in room $r
  not (<$r> in at); 
effect:
  //now he is in room $r
  at = {<$r>};
    
  //everything he carries also moves to $r
  foreach <$o> in carry
    is_at -= {<$o,_>};
    is_at += {<$o,$r>};
  end for
  
signal: 
  "Move to room " + $r;
end action

//pickup object $o
action pickup($o)
precondition:
  //robot doesn't carry anything
  not (exists <$x> in carry);
effect:
  //now he carries $o
  carry += {<$o>};
signal: 
  "Pickup object " + $o;
end action

//putdown object
action putdown($o)
precondition:
  //he carries the object stored in $o
  <$o> in carry;
effect:
  //now he's not
  carry -= {<$o>}; 
signal: 
  "Put down object " + $o;
end action



//serves a request
proc serve($object, $sender, $receiver)

  pick <$sender,$roomSender> from office such
    move($roomSender);
	
    //sense person
    detectPerson();
	
    //sender is actually in the room
    if (exists <$sender, $roomSender> in detectedPerson) then 
      pickup($object); 
      
      //deliver object to receiver
      pick <$receiver, $roomReceiver> from office such
        move($roomReceiver);

        //sense person
        detectPerson();
		
        //receiver is actually in the room
        if (exists <$receiver, $roomReceiver> in detectedPerson) then 		
          putdown($object);
        end if
      end pick
    end if
  end pick	
end proc

proc main()
  //serve a random request
  pick <$x> from request such
    serve($x);
  end pick
end proc