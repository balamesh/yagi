fluent number[{"1","2","3"}];
number = {<"1">,<"2">,<"3">};

fluent link[{"1", "2", "3"}][{"a", "b", "c"}];
link = {<"1", "a">, <"2", "b">, <"3", "c">};

action dummy($b)
	signal:
		"dummy called with: " + $b;
end action

proc proc1()
	pick <$n> from number such
		pick <$n, $b> from link such
			dummy($b);
		end pick
	end pick
end proc

proc proc2()
	search
		pick <$n> from number such
			pick <$n, $b> from link such
				dummy($b);
			end pick
		end pick
	end search
end proc

proc1();
proc1();
proc1();
proc1();

proc2();
proc2();
proc2();
proc2();