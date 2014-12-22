@include "fluents.y";

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

proc park()
  if (currFloor == {<"0">}) then
    open();
  else
    down("0");
    open();
  end if
end proc

proc goto($n)
  if (exists <$x> in currFloor such $x < $n) then
    up($n);
  else
    down($n);
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
  
    park();
  end search
end proc

control();