fluent fA[{"1","2"}][{"1","2"}];

fact fB [{"1","2"}];
fB = {<"1">, <"2">};

fact fC[{"1","2"}][{"1","2"}];
fC = {<"2","1">};

fA = {<"2","1">};

proc pA()

    search
    pick <$x,$y> from fA such
	pick <$z> from fB such
	        test (<$x,$z> in fC and not (<$z,$y> in fA));
	end pick

    end pick
    end search

end proc
