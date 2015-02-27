fluent number[{"1","2","3"}];
number = {<"1">,<"2">,<"3">};

fluent link[{"1", "2", "3"}][{"a", "b", "c"}];

action dummy($b)
	signal:
		"dummy called with: " + $b;
end action

while not (exists <$n, $b> in machines_types) do
	pick <$n, $b> from link such
		dummy($b);
	end pick
end while
