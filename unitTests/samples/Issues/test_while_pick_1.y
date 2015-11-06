fluent fA[{"1","2"}][{"1","2"}];
fact fB[{"1","2","3","4","5","6","7","8"}][{"1","2","3","4","5","6","7","8"}];
fB = {<"1","2">};

fA = {<"1","1">};

proc exploring()
        search
        	while  not ( <"2","1"> in fA ) do
        	  pick <$x,$y> from fA such
        		forward($x, $y); 
    		  end pick
            end while
        end search
end proc

action forward($x, $y)
precondition:
    true;
effect:
    pick <$x,$x1> from fB such
      fA={<$x1,$y>};
    end pick

signal:
  "forward";
end action
