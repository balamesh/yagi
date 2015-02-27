/***************************************************************************
 *  llsf2014_prod.y - LLSF2014 production phase example
 *
 *  Created: Thu Feb 26 17:57:31 2015
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

fluent machine_types[{"M1","M2","M3","M4","M5","M6","M7","M8","M9","M10","M11","M12", "M13",
                      "M14", "M15", "M16", "M17", "M18", "M19", "M20", "M21", "M22", "M23", "M24",
                      "R1", "R2", "D1", "D2", "D3", "D4", "D5", "D6"}]
                    [{"T1", "T2", "T3", "T4", "T5", "DELIVER", "RECYCLE"}];
fluent machines[{"M1","M2","M3","M4","M5","M6","M7","M8","M9","M10","M11","M12", "M13",
                 "M14", "M15", "M16", "M17", "M18", "M19", "M20", "M21", "M22", "M23", "M24",
                 "R1", "R2", "D1", "D2", "D3", "D4", "D5", "D6"}];

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

action sleep($time_ms)
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

action get_s0($place) external ($status)
effect:
  skill_status = {<$status>};
signal:
  "skill-exec-wait get_s0{place='" + $place + "'}";
end action


action finish_puck_at($M, $T) external ($status)
effect:
  skill_status = {<$status>};
signal:
  "skill-exec-wait finish_puck_at{place='" + $M + "', mtype='" + $T + "'}";
end action

action deliver_puck($D) external ($status)
effect:
  skill_status = {<$status>};
signal:
  "skill-exec-wait finish_puck_at{place='" + $D + "', mtype='DE', dont_wait=true}";
end action

proc init()
  blackboard_connect("localhost", "1921");
  blackboard_open_reading("RobotinoLightInterface", "/machine-signal/best");
end proc

exogenous-event game_state ($state, $phase)
  state = {<$state>};
  phase = {<$phase>};
end exogenous-event

exogenous-event machine_type ($name, $type)
  machine_types += {<$name, $type>};
  machines += {<$name>};
end exogenous-event

proc production()
  log("info", "Waiting for machine types");
  while (phase != {<"PRODUCTION">} and not (exists <$M> in machines)) do
    sleep("1000");
  end while
  log("info", "Fetching Raw Product");
  while phase == {<"PRODUCTION">} do
    get_s0("Ins1");
    // Should work, but does not, cf. YAGI issue #30
    //pick <$M,"T5"> from machine_types such
    foreach <$M,$T> in machine_types do
      if ({<$T>} == {<"T5">}) then
        log("info", "Finishing puck");
        finish_puck_at($M, $T);
      end if
    end for
    log("info", "Delivering puck");
    deliver_puck("deliver1");
  end while
end proc


proc main()
  init();
  production();
end proc

main();
