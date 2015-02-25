fact floors[{"0","1","2","3","4","5","6"}];
floors = {<"0">, <"1">, <"2">, <"3">, <"4">, <"5">, <"6">};

fluent fon[{"1","2","3","4","5","6"}];

fluent currFloor[{"0","1","2","3","4","5","6"}];
currFloor = {<"4">};

action turnoff($n)
precondition:
  <$n> in fon;
effect:
  fon -= {<$n>};
signal:
  "Turn-off button at floor " + $n;
end action

action open()
signal:
  "Open door";
end action

action close()
signal:
  "Close door";
end action

action up($n)
precondition:
  exists <$x> in floors
  such (currFloor == {<$x>} and ($x < $n and $n != "0"));
effect:
  currFloor = {<$n>};
signal:
  "Move up to floor " + $n;
end action

action down($n)
precondition:
  exists <$x> in floors
  such (currFloor == {<$x>} and ($x > $n and $n != "0"));
effect:
  currFloor = {<$n>};  
signal:
  "Move down to floor " + $n;
end action

action park()
  effect:
    currFloor = {<"0">};
  signal:
    "Parking the elevator!";
end action

proc goto($n)
  if (exists <$x> in currFloor such $x < $n) then
    up($n);
  else
    down($n);
  end if
end proc

proc serve($n)
  if (exists <$x> in currFloor such $x != $n) then
    goto($n);
  end if
  
  turnoff($n);
  open();
  close();
end proc

proc serveafloor()  
  pick <$n> from fon such
    serve($n);
  end pick
end proc

action dummy()
effect:
  $x = "a";
end action

proc control()
  while not (exists <$n> in fon) do
    dummy();
  end while

  serveafloor();
end proc

exogenous-event setOn($floor)
  fon += {<$floor>};
end exogenous-event

control();