fact floors[{"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39"}];
floors = {<"0">,<"1">,<"2">,<"3">,<"4">,<"5">,<"6">,<"7">,<"8">,<"9">,<"10">,<"11">,<"12">,<"13">,<"14">,<"15">,<"16">,<"17">,<"18">,<"19">,<"20">,<"21">,<"22">,<"23">,<"24">,<"25">,<"26">,<"27">,<"28">,<"29">,<"30">,<"31">,<"32">,<"33">,<"34">,<"35">,<"36">,<"37">,<"38">,<"39">};

fluent fon[{"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39"}];
fon = {<"1">, <"3">, <"5">, <"7">, <"9">, <"11">, <"13">, <"15">, <"17">, <"19">, <"21">, <"23">, <"25">, <"27">, <"29">, <"31">, <"33">, <"35">, <"37">, <"39">};

fluent currFloor[{"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39"}];
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
  if (currFloor != {<"0">}) then
    down("0");
  end if
  
  open();
end proc

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
  
    park();
  end search
end proc

control();