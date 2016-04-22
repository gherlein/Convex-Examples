/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                        Copyright (c) James Pearman                          */
/*                                   2013                                      */
/*                            All Rights Reserved                              */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*    Module:     vexdefault.c                                                 */
/*    Author:     James Pearman                                                */
/*    Created:    8 July 2013                                                  */
/*                                                                             */
/*    Revisions:                                                               */
/*                V1.00  04 July 2013 - Initial release                        */
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
#include <stdlib.h>
#include "vexdefault.h"

/*-----------------------------------------------------------------------------*/
/** @brief      Cortex default code initialization                             */
/*-----------------------------------------------------------------------------*/
/** @details
 *  Setup motors and digital ports
 */

void
vexCortexDefaultSetup(void)
{
    vexDigitalConfigure( dConfig, DIG_CONFIG_SIZE( dConfig ) );
    vexMotorConfigure( mConfig, MOT_CONFIG_SIZE( mConfig ) );
}

/*-----------------------------------------------------------------------------*/
/** @brief      Cortex default code                                            */
/*-----------------------------------------------------------------------------*/
/** @details
 *  This function simulates the cortex default code, it was based on the ROBOTC
 *  implementation but with some changes in structure.
 */
void
vexCortexDefaultDriver(void)
{
  int16_t drive_left  = 0;
  int16_t drive_right = 0;
  
  while( !chThdShouldTerminate() )
  {
    vexMotorDirectionSet( LeftFront,  kVexMotorNormal );
    vexMotorDirectionSet( LeftBack,  kVexMotorNormal );
    vexMotorDirectionSet( RightFront,  kVexMotorNormal );
    vexMotorDirectionSet( RightBack,  kVexMotorNormal );

    drive_left  =  vexControllerGet( Ch3 ); // up = CW
    drive_right = -vexControllerGet( Ch2 ); // up = CCW

    if(abs(drive_right)<DEBOUNCE_VALUE) drive_right=0;
    if(abs(drive_left)<DEBOUNCE_VALUE)  drive_left=0;
    
    // Left drive motors
    vexMotorSet( LeftFront,   drive_left  );
    vexMotorSet( LeftBack,    drive_left  );

    // Right drive motors
    vexMotorSet( RightFront,  drive_right );
    vexMotorSet( RightBack,   drive_right );

    // small delay
    vexSleep(10);
  }
}
