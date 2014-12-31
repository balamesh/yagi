fluent see[{"Fork1","Bread4","Ham1","Cheese2","Ham3","Spoon1","Tomatoes3","Ham2","BeigePlate3","WoodenBowl","Knife1"}];
fluent isat[{"Fork1","Bread4","Ham1","Cheese2","Ham3","Spoon1","Tomatoes3","Ham2","BeigePlate3","WoodenBowl","Knife1"}][{"Microwave","Table","Stove"}];
fluent at[{"Microwave","Table","Stove"}];
fluent hold[{"Fork1","Bread4","Ham1","Cheese2","Ham3","Spoon1","Tomatoes3","Ham2","BeigePlate3","WoodenBowl","Knife1"}];

action move_to($p)
effect:
  at = {<$p>};
signal:
  "Move "+$p;
end action

proc testProc()

  move_to("UpperCabinet1");

end proc