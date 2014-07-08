action testAction()
precondition:
  not({<"a">, <"b">} == {<"a">});
effect:
  x = x;
end action