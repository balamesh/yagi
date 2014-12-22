@include "fluents.y";
@include "fluentsNoSearch.y";

action move($b1, $b2)
precondition:
  (<$b1> in fclear and 
  (<$b2> in fclear and 
  $b1 != $b2));
effect:
  onTable -= {<$b1>};
  fclear -= {<$b2>};
  
  foreach <$x1, $y1> in bon do
    if ($x1 == $b1) then
      fclear += {<$y1>};
    end if
  end for

  bon -= {<$b1, _>};
  bon += {<$b1, $b2>};

signal:
  "Move " + $b1 + " on top of " + $b2;
end action

action moveToTable($b)
precondition:
  (<$b> in fclear and not(<$b> in onTable));
effect:
  onTable += {<$b>};
  
  foreach <$xx, $yy> in bon do
    if ($xx == $b) then
      fclear += {<$yy>};
    end if
  end for

  bon -= {<$b, _>};
  
signal:
  "Move " + $b + " to table";
end action

proc doMove()
  pick <$x> from fclear such
    pick <$y> from fclear such
      doExec($x,$y);
    end pick
  end pick
end proc

proc doExec($first, $second)
  choose 
    moveToTable($first);
  or
    move($first,$second);
  end choose
end proc

control();