/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                        Copyright (c) Greg Herlein                           */
/*                                   2016                                      */
/*                            All Rights Reserved                              */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*    Module:     vexmain.c                                                    */
/*    Author:     Greg Herlein                                                 */
/*    Created:    21 May 2016                                                  */
/*                                                                             */
/*    Revisions:                                                               */

/*                                                                             */
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*    The author is supplying this software for use with the VEX cortex        */
/*    control system. This file can be freely distributed and teams are        */
/*    authorized to freely use this program , however, it is requested that    */
/*    improvements or additions be shared with the Vex community via the vex   */
/*    forum.  Please acknowledge the work of the authors when appropriate.     */
/*    Thanks.                                                                  */
/*                                                                             */
/*    Licensed under the Apache License, Version 2.0 (the "License");          */
/*    you may not use this file except in compliance with the License.         */
/*    You may obtain a copy of the License at                                  */
/*                                                                             */
/*      http://www.apache.org/licenses/LICENSE-2.0                             */
/*                                                                             */
/*    Unless required by applicable law or agreed to in writing, software      */
/*    distributed under the License is distributed on an "AS IS" BASIS,        */
/*    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. */
/*    See the License for the specific language governing permissions and      */
/*    limitations under the License.                                           */
/*                                                                             */
/*    The author can be contacted on the vex forums as jpearman                */
/*    or electronic mail using jbpearman_at_mac_dot_com                        */
/*    Mentor for team 8888 RoboLancers, Pasadena CA.                           */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

#include <string.h>

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "vex.h"

#include "smartmotor.h"
#include "apollo.h"



/*-----------------------------------------------------------------------------*/
//  Application entry point.											       */
/*-----------------------------------------------------------------------------*/

int main(void)
{
	short	timeout = 0;

	// System initializations.
  // - HAL initialization, this also initializes the configured device drivers
  //   and performs the board-specific initializations.
  // - Kernel initialization, the main() function becomes a thread and the
  //   RTOS is active.
	halInit();
	chSysInit();

	// Init the serial port associated with the console
	vexConsoleInit();

  // init VEX
  vexCortexInit();

  // wait for good spi comms
  while( vexSpiGetOnlineStatus() == 0 )
  {
    // wait for a while
    chThdSleepMilliseconds(100);
    // dump after 5 seconds
    if(timeout++ == 50)
      break;
  }

}

