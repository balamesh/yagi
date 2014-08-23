fact floors[{"0","1","2","3","4","5","6"}];
floors = {<"0">, <"1">, <"2">, <"3">, <"4">, <"5">, <"6">};

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

proc control()
  search
    while exists <$n> in fon do
      serveafloor();
    end while
  end search
  park();
end proc

control();