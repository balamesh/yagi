fluent fA[{"1","2"}][{"1","2"}];
fluent fB[{"1","2"}][{"1","2"}];

fB = {
<"1","1">,<"1","2">
};

fA = {<"1","1">};

proc procA()
    search
    pick <$x,$y> from fB such
	while  not ( <$x,$y> in fA ) do
		doAction();
        end while
    end pick
    end search
end proc

action doAction()
signal:
  "doAction";
end action
