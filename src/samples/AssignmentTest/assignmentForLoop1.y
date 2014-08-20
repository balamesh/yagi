fluent g1[{"a","b"}][{"x","y"}];
g1 = {<"a","x">, <"b","y">};

fluent h[{"a","b"}][{"x","y"}];

foreach <$first, $second> in g do
  h += {<$first, $second>};
end for


fluent flu[{"i","j","k"}];

foreach <$val> in {<"i">,<"j">,<"k">} do
  flu += {<$val>};
end for
