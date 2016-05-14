fluent pit[{"1","2","3","4","5","6","7","8"}][{"1","2","3","4","5","6","7","8"}];
fluent wumpus[{"1","2","3","4","5","6","7","8"}][{"1","2","3","4","5","6","7","8"}];
fluent gold[{"1","2","3","4","5","6","7","8"}][{"1","2","3","4","5","6","7","8"}];
fluent at[{"1","2","3","4","5","6","7","8"}][{"1","2","3","4","5","6","7","8"}];
fluent explore[{"1","2","3","4","5","6","7","8"}][{"1","2","3","4","5","6","7","8"}];
fluent frontier[{"1","2","3","4","5","6","7","8"}][{"1","2","3","4","5","6","7","8"}];
fluent heading[{"E","N","W","S"}];

fact numbers [{"1","2","3","4","5","6","7","8"}];
numbers = {<"1">, <"2">, <"3">, <"4">, <"5">, <"6">, <"7">, <"8">};

fact up[{"1","2","3","4","5","6","7","8"}][{"1","2","3","4","5","6","7","8"}];
up = {<"1","2">, <"2","3">, <"3","4">, <"4","5">, <"5","6">, <"6","7">, <"7","8">};

fact down[{"1","2","3","4","5","6","7","8"}][{"1","2","3","4","5","6","7","8"}];
down = {<"2","1">, <"3","2">, <"4","3">, <"5","4">, <"6","5">, <"7","6">,<"8","7">};

fact turn_left[{"E","N","W","S"}][{"E","N","W","S"}];
turn_left={<"E","N">,<"N","W">,<"W","S">,<"S","E">};

fact turn_right[{"E","N","W","S"}][{"E","N","W","S"}];
turn_right={<"E","S">,<"S","W">,<"W","N">,<"N","E">};

pit = {

};

wumpus = {
<"1","1">,<"1","2">,<"1","3">,<"1","4">,<"1","5">,<"1","6">,<"1","7">,<"1","8">,
<"2","1">,<"2","2">,<"2","3">,<"2","4">,<"2","5">,<"2","6">,<"2","7">,<"2","8">,
<"3","1">,<"3","2">,<"3","3">,<"3","4">,<"3","5">,<"3","6">,<"3","7">,<"3","8">,
<"4","1">,<"4","2">,<"4","3">,<"4","4">,<"4","5">,<"4","6">,<"4","7">,<"4","8">,
<"5","1">,<"5","2">,<"5","3">,<"5","4">,<"5","5">,<"5","6">,<"5","7">,<"5","8">,
<"6","1">,<"6","2">,<"6","3">,<"6","4">,<"6","5">,<"6","6">,<"6","7">,<"6","8">,
<"7","1">,<"7","2">,<"7","3">,<"7","4">,<"7","5">,<"7","6">,<"7","7">,<"7","8">,
<"8","1">,<"8","2">,<"8","3">,<"8","4">,<"8","5">,<"8","6">,<"8","7">,<"8","8">
};




at = {<"1","1">};
heading = {<"E">};
explore = {<"2","1">};


// loops forever !!!
proc exploring4()


search

while not ( <"3","1"> in at ) do


forward(); 

end while

end search

end proc






action forward()

effect:
  if (<"E"> in heading) then
    pick <$x,$y> from at such
      pick <$x,$x1> from up such
        at={<$x1,$y>};
        explore-={<$x1,$y>};
      end pick
    end pick
  end if
  if (<"W"> in heading) then
    pick <$x,$y> from at such
      pick <$x,$x1> from down such
        at={<$x1,$y>};
        explore-={<$x1,$y>};
      end pick
    end pick
  end if
  if (<"N"> in heading) then
    pick <$x,$y> from at such
      pick <$y,$y1> from up such
        at={<$x,$y1>};
        explore-={<$x,$y1>};
      end pick
    end pick
  end if
  if (<"S"> in heading) then
    pick <$x,$y> from at such
      pick <$y,$y1> from down such
        at={<$x,$y1>};
        explore-={<$x,$y1>};
      end pick
    end pick
  end if
signal:
  "forward";
end action



