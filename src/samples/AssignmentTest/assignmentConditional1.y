fluent g[{"a","b"}][{"x","y"}];
g = {<"a","x">, <"b","y">};

fluent h[{"a","b"}][{"x","y"}];
fluent flu[{"i","j", "k"}];

if (true) then
  h = {<"a","x">};
end if

if (false) then
  flu = {<"i">};
else
  flu = {<"j">}
end if