fluent see[{"Fork1","Bread4","Ham1","Cheese2","Ham3","Spoon1","Tomatoes3","Ham2","BeigePlate3","WoodenBowl","Knife1"}];
fluent isat[{"Fork1","Bread4","Ham1","Cheese2","Ham3","Spoon1","Tomatoes3","Ham2","BeigePlate3","WoodenBowl","Knife1"}][{"Microwave","Table","Stove"}];
fluent at[{"Microwave","Table","Stove"}];
fluent hold[{"Fork1","Bread4","Ham1","Cheese2","Ham3","Spoon1","Tomatoes3","Ham2","BeigePlate3","WoodenBowl","Knife1"}];

fluent objects[{"Fork1","Bread4","Ham1","Cheese2","Ham3","Spoon1","Tomatoes3","Ham2","BeigePlate3","WoodenBowl","Knife1"}];
objects={<"Fork1">,<"Bread4">,<"Ham1">,<"Cheese2">,<"Ham3">,<"Spoon1">,<"Tomatoes3">,<"Ham2">,<"BeigePlate3">,<"WoodenBowl">,<"Knife1">};

fluent containers[{"UpperCabinet1","UpperCabinet2","UpperCabinet3","UpperCabinet4","UpperCabinet5","BaseCabinet1","BaseCabinet2","BaseCabinet3","BaseCabinet4","BC6_Drawer1"}];
containers={<"UpperCabinet1">,<"UpperCabinet2">,<"UpperCabinet3">,<"UpperCabinet4">,<"UpperCabinet5">,<"BaseCabinet1">,<"BaseCabinet2">,<"BaseCabinet3">,<"BaseCabinet4">,<"BC6_Drawer1">};

fluent open[{"UpperCabinet1","UpperCabinet2","UpperCabinet3","UpperCabinet4","UpperCabinet5","BaseCabinet1","BaseCabinet2","BaseCabinet3","BaseCabinet4","BC6_Drawer1"}];

action look_for($o) external ($x)
effect:
  if ($x == "true") then
    see += {<$o>};
  else
    see -= {<$o>};
  end if 
signal:
  "See "+$o;
end action

action move_to($p)
effect:
  at = {<$p>};
signal:
  "Move "+$p;
end action

action take($o)
effect:
  isat -= {<$o,_>};
  hold = {<$o>};
signal:
  "Take "+$o;
end action

action put($o)
effect:
  hold -={<$o>};
  foreach <$x> in at do
    isat += {<$o, $x>};
  end for
signal:
  "Put " + $o;
end action

action open_container($c)
effect:
  open += {<$c>};
signal:
  "Open "+$c;
end action

action check_above($o1,$o2) external ($x)
effect:
  if ($x == "true") then
    isat += {<$o1,$o2>};
  else
    iast -= {<$o1,$o2>};
  end if 
signal:
  "IsAt " + $o1 + " " + $o2 ;
end action

action load_level($l)
signal:
  "LoadLevel " + $l;
end action

proc transport($o,$p)

  move_to($o);
  take($o);
  move_to($p);
  put($p);

end proc

proc locate($o)

  foreach <$c> in containers do
     
    if(not (<$c> in open)) then

      move_to($c);
      open_container($c);

    end if
  end for

end proc

proc collect()

  foreach <$o> in objects do
    look_for($o);
    if (<$o> in see) then
      transport($o,"Table");
    else
      locate($o);
      if (<$o> in see) then
        transport($o,"Table");
      end if
    end if
  end for 

end proc

