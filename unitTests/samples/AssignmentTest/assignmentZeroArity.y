fluent zeroAry;

action set()
  effect:
    zeroAry = {<>};
  signal:
    "Set the fluent";
end action

action clear()
  effect:
    zeroAry = {};
  signal:
    "clear the fluent";
end action
