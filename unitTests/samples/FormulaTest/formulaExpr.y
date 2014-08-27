fluent f[{"a","b","c","d","e","f","g","h","i"}];

action testActionFormula1()
precondition:
  {<"a">, <"b">} - {<"a">} == {<"b">} + {<"a">} - {<"a">};
effect:
  f += {<"a">};
end action

action testActionFormula2()
precondition:
  {<"a">} + {<"b">} != {<"b">} + {<"b">};
effect:
  f += {<"b">};
end action

action testActionFormula3()
precondition:
  "a" != "b";
effect:
  f += {<"c">};
end action

action testActionFormula4()
precondition:
  "b" == "b";
effect:
  f += {<"d">};
end action

action testActionFormula5()
precondition:
  "a" < "b";
effect:
  f += {<"e">};
end action

action testActionFormula6()
precondition:
  "a" >= "a";
effect:
  f += {<"f">};
end action

action testActionFormula7()
precondition:
  "a" <= "b";
effect:
  f += {<"g">};
end action

action testActionFormula8()
precondition:
  true;
effect:
  f += {<"h">};
end action

action testActionFormula9()
precondition:
  false;
effect:
  f += {<"i">};
end action


testActionFormula1();
testActionFormula2();
testActionFormula3();
testActionFormula4();
testActionFormula5();
testActionFormula6();
testActionFormula7();
testActionFormula8();
testActionFormula9();