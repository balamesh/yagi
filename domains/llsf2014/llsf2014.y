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


fluent expl_machines[{"M1","M2","M3","M4","M5","M6","M7","M8","M9","M10","M11","M12"}];
expl_machines = {<"M1">,<"M2">,<"M3">,<"M4">,<"M5">,<"M6">,<"M7">,<"M8">,<"M9">,<"M10">,<"M11">,<"M12">};

fluent skill_status[{"S_INACTIVE", "S_RUNNING", "S_FINAL", "S_FAILED"}];

fluent red_light[{"ON", "OFF", "BLINKING", "UNKNOWN"}];
fluent yellow_light[{"ON", "OFF", "BLINKING", "UNKNOWN"}];
fluent green_light[{"ON", "OFF", "BLINKING", "UNKNOWN"}];
red_light = {<"UNKNOWN">};
yellow_light = {<"UNKNOWN">};
green_light = {<"UNKNOWN">};

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
  red_light = {<$red>};
  yellow_light = {<$yellow>};
  green_light = {<$green>};
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

proc explore($M)
  goto($M);
  // give vision some time to read signal, in real life we would
  // wait for the visibility history to be acceptable
  sleep("2000");
  mark_explored($M);
  blackboard_read("RobotinoLightInterface::/machine-signal/best");
  read_light();
end proc

proc exploration()
  while exists <$M> in expl_machines do
    pick <$M> from expl_machines such
      explore($M);
    end pick
  end while
end proc


proc main()
  init();
  exploration();
end proc

main();
