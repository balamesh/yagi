/***************************************************************************
 *  llsf2014.y - LLSF2014 game
 *
 *  Created: Fri Feb 20 09:32:21 2015
 *  Copyright  2015  Tim Niemueller [www.niemueller.de]
 ****************************************************************************/

/* Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
fluent blackboard_connected[{"true", "false"}];
blackboard_connected = {<"false">};


fluent expl_machines[{"M1","M2","M3","M4","M5","M6","M7","M8","M9","M10","M11","M12", "M13",
                      "M14", "M15", "M16", "M17", "M18", "M19", "M20", "M21", "M22", "M23", "M24"}];
fluent expl_types[{"T1", "T2", "T3", "T4", "T5"}][{"ON", "OFF"}][{"ON", "OFF"}][{"ON", "OFF"}];
//expl_machines = {<"M1">};

fluent skill_status[{"S_INACTIVE", "S_RUNNING", "S_FINAL", "S_FAILED"}];

fluent light_state[{"ON", "OFF", "BLINKING", "UNKNOWN"}]
		  [{"ON", "OFF", "BLINKING", "UNKNOWN"}]
		  [{"ON", "OFF", "BLINKING", "UNKNOWN"}];
light_state = {<"UNKNOWN","UNKNOWN","UNKNOWN">};

fluent state[{"INIT", "WAIT_START", "RUNNING", "PAUSED"}];
state = {<"INIT">};
fluent phase[{"PRE_GAME", "SETUP", "EXPLORATION", "PRODUCTION", "POST_GAME"}];
phase = {<"PRE_GAME">};


action blackboard_connect($host, $port)
precondition:
  blackboard_connected == {<"false">};
effect:
  blackboard_connected = {<"true">};
signal:
  "bb-connect " + $host + " " + $port;
end action

action blackboard_open_reading($type, $id)
precondition:
  blackboard_connected == {<"true">};
signal:
  "bb-open READ " + $type + " " + $id;
end action

action blackboard_read($interface)
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

action wait($time_ms)
precondition:
  true;
signal:
  "sleep " + $time_ms;
end action

action read_light() external ($red, $yellow, $green)
precondition:
  true;
effect:
  light_state = {<$red, $yellow, $green>};
signal:
  "bb-get RobotinoLightInterface::/machine-signal/best";
end action

action goto($place) external ($status)
precondition:
  true;
effect:
  skill_status = {<$status>};
signal:
  "skill-exec-wait ppgoto{place='" + $place + "'}";
end action

proc init()
  blackboard_connect("localhost", "1921");
  blackboard_open_reading("RobotinoLightInterface", "/machine-signal/best");
end proc

action mark_explored($M)
precondition:
  true;
effect:
  expl_machines -= {<$M>};
//signal:
//  "";
end action

action report_machine($M, $T)
signal:
  "pb-send-report " + $M + " " + $T;
end action

//exogenous-event protobuf_msg ($endpoint_host, $endpoint_port, $component_id, $msg_type, $ptr, $client_type, $client_id)
//end exigenous-event

exogenous-event game_state ($state, $phase)
  state = {<$state>};
  phase = {<$phase>};
end exogenous-event

exogenous-event exploration_machine ($machine)
  expl_machines += {<$machine>};
end exogenous-event

exogenous-event exploration_type ($type, $red, $yellow, $green)
  expl_types += {<$type, $red, $yellow, $green>};
end exogenous-event


proc exploration_report($M)
  pick <$red,$yellow,$green> from light_state such
    foreach <$type,$tred,$tyellow,$tgreen> in expl_types do
      if ({<$red,$yellow,$green>} == {<$tred,$tyellow,$tgreen>}) then
        report_machine($M, $type);
      end if
    end for
  end pick
end proc

proc explore($M)
  goto($M);
  // give vision some time to read signal, in real life we would
  // wait for the visibility history to be acceptable
  //wait("2000");
  mark_explored($M);
  blackboard_read("RobotinoLightInterface::/machine-signal/best");
  read_light();
  exploration_report($M);
end proc

proc exploration()
  while not (exists <$M> in expl_machines) do
    wait("1000");
  end while
  while phase == {<"EXPLORATION">} do
    if (exists <$M> in expl_machines) then
      pick <$M> from expl_machines such
        explore($M);
      end pick
    end if
  end while
  log("error", "Exploration finished");
end proc


proc main()
  init();
  exploration();
end proc

main();
