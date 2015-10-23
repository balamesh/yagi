fluent fA[{"1","2"}][{"1","2"}];
fact fB[{"1","2","3","4","5","6","7","8"}][{"1","2","3","4","5","6","7","8"}];
fB = {<"1","2">};

fA = {<"1","1">};

proc exploring()
        search
        	while  not ( <"2","1"> in fA ) do
        		forward(); 
            end while
        end search
end proc

action forward()
precondition:
    true;
effect:
  pick <$x,$y> from fA such
    pick <$x,$x1> from fB such
      fA={<$x1,$y>};
    end pick
  end pick
signal:
  "forward";
end action
