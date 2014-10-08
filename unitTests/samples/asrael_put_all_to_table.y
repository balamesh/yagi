fluent see[{"Fork1","Bread4","Ham1","Cheese2","Ham3","Spoon1","Tomatoes3","Ham2","BeigePlate3","WoodenBowl","Knife1"}];
fluent isat[{"Fork1","Bread4","Ham1","Cheese2","Ham3","Spoon1","Tomatoes3","Ham2","BeigePlate3","WoodenBowl","Knife1"}][{"Microwave","Table","Stove"}];
fluent at[{"Microwave","Table","Stove"}];


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
