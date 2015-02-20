// Simple testing for skill execution

fluent blackboard_connected[{"true", "false"}];
blackboard_connected = {<"false">};
//fluent blackboard_connected;
//blackboard_connected = "false";
fluent skill_status[{"S_INACTIVE", "S_RUNNING", "S_FINAL", "S_FAILED"}];

action blackboard_connect($host, $port)
precondition:
  blackboard_connected == {<"false">};
effect:
  blackboard_connected = {<"true">};
signal:
  "bb-connect " + $host + " " + $port;
end action

action say($text)
precondition:
  true;
signal:
  "say{text='" + $text + "', wait=true}";
end action


action bb_read($interface)
precondition:
  true;
signal:
  "bb-read " + $interface;
end action

action skill_status_query() external ($status)
precondition:
  true;
effect:
  skill_status = {<$status>};
signal:
  "bb-get SkillerInterface::Skiller";
end action

action log($level, $msg)
precondition:
  true;
signal:
  "log " + $level + " " + $msg;
end action

//proc skill_status_print()
//pick <$sks> from skill_status such
//    log("info", skill_status);
// end pick
//end proc

proc say_test()
  if (blackboard_connected == {<"false">}) then
    blackboard_connect("localhost", "1910");
  end if
  say("This is a longer test to run a while loop");
  bb_read("SkillerInterface::Skiller");
/*
  while <"S_INACTIVE"> in skill_status do
    skill_status_query();
    skill_status_print();
  end while
  while <"S_RUNNING"> in skill_status do
*/
    skill_status_query();
    skill_status_print();
//  end while
end proc

say_test();
