fact floors[{"1","2","3","4","5","6"}];
floors = {<"1">, <"2">, <"3">, <"4">, <"5">, <"6">};

fluent fon[{"1","2","3","4","5","6"}];
fon = {<"3">,<"5">};

fluent currFloor[{"1","2","3","4","5","6"}];
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
effect:
  $dummy = "dummy";
signal:
  "Open door";
end action

action close()
effect:
  $dummy = "dummy";
signal:
  "Close door";
end action

action up($n)
precondition:
  exists <$x> in floors
  such (currFloor == {<$x>} and $x < $n);
effect:
  currFloor = {<$n>};
signal:
  "Move up to floor " + $n;
end action

action down($n)
precondition:
  exists <$x> in floors
  such (currFloor == {<$x>} and $x > $n);
effect:
  currFloor = {<$n>};  
signal:
  "Move down to floor " + $n;
end action

proc goto($n)
  if (currFloor != {<$n>}) then
    choose
      up($n);
    or
     down($n);
    end choose
  end if
end proc

proc serve($n)
  goto($n);
  turnoff($n);
  open();
  close();
end proc

proc serveafloor()
    pick <$n> from fon such
      serve($n);
    end pick
end proc

proc park()
  if (currFloor == {<"0">}) then
    open();
  else
     down("0");
     open();
  end if
end proc

proc control()
  while exists <$n> in fon do
    serveafloor();
  end while
  
  park();
end proc