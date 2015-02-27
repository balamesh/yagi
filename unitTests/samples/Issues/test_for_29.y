fluent number[{"1","2","3"}];

fluent link[{"1", "2", "3"}][{"a", "b", "c"}];

action dummy()
	effect:
		$x = "a";
end action

action dummy2()
	effect:
		$x = "a";
	signal:
		"done waiting";
end action

exogenous-event dummyNumber($n)
	number +={<$n>};
end exogenous-event

exogenous-event dummyLink($n, $b)
	link +={<$n, $b>};
end exogenous-event

while not (exists <$n> in number) do
	dummy();
end while
dummy2();

while not (exists <$n, $b> in link) do
	dummy();
end while
dummy2();
