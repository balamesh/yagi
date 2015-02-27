fluent link[{"1", "2", "3"}][{"a", "b", "c"}];

action dummy($a, $b)
	effect:
		link += {<$a, $b>};
	signal:
		"dummy called with: a:" + $a + " and b: " + $b;
end action

link;
dummy("1", "a");
link;

dummy("1");