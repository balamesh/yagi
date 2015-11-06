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

fluent machine_types[{"M1","M2","M3","M4","M5","M6","M7","M8","M9","M10","M11","M12", "M13",
                      "M14", "M15", "M16", "M17", "M18", "M19", "M20", "M21", "M22", "M23", "M24",
                      "R1", "R2", "D1", "D2", "D3", "D4", "D5", "D6"}]
                    [{"T1", "T2", "T3", "T4", "T5", "DELIVER", "RECYCLE"}];

action machine_type ($name, $type)
effect:
  machine_types += {<$name, $type>};
end action

action print($name, $type)
signal:
  "machine " + $name + " with type " + $type;
end action

proc production()
    // Should work, but does not, cf. YAGI issue #30
    pick <$M,"T5"> from machine_types such
      print($M, "T5");
    end pick
end proc

machine_types;
machine_type("M1", "T5");
machine_types;
production();
