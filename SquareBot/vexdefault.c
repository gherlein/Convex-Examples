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

#include "ch.h"         // needs for all ChibiOS programs
#include "hal.h"        // hardware abstraction layer header
#include "vex.h"        // vex library header

#define DEBOUNCE_VALUE 0


// Digi IO configuration
static  vexDigiCfg  dConfig[kVexDigital_Num] = {
        { kVexDigital_1,    kVexSensorSonarCm,       kVexConfigSonarIn,     kVexSonar_1  },
        { kVexDigital_2,    kVexSensorSonarCm,       kVexConfigSonarOut,    kVexSonar_1  },
        { kVexDigital_3,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_4,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_5,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_6,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_7,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_8,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_9,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_10,   kVexSensorDigitalInput,  kVexConfigInput,       0 },
        { kVexDigital_11,   kVexSensorQuadEncoder,   kVexConfigQuadEnc1,    kVexQuadEncoder_1 },
        { kVexDigital_12,   kVexSensorQuadEncoder,   kVexConfigQuadEnc2,    kVexQuadEncoder_1 }
};

static  vexMotorCfg mConfig[kVexMotorNum] = {
        { kVexMotor_1,      kVexMotor393T,          kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_2,      kVexMotor393T,          kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_3,      kVexMotor393T,          kVexMotorNormal,       kVexSensorNone,        0 },

        { kVexMotor_4,      kVexMotor393T,          kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_5,      kVexMotor393T,          kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_6,      kVexMotor393T,          kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_7,      kVexMotor393T,          kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_8,      kVexMotor393T,          kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_9,      kVexMotor393T,          kVexMotorNormal,       kVexSensorNone,        0 },
        { kVexMotor_10,     kVexMotor393T,          kVexMotorNormal,       kVexSensorNone,        0 }
};

/*-----------------------------------------------------------------------------*/
/** @cond      name the motor ports                                            */
/*-----------------------------------------------------------------------------*/
#define LeftFront       kVexMotor_2
#define LeftBack        kVexMotor_3
#define RightFront      kVexMotor_4
#define RightBack       kVexMotor_5
/** @endcond */


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
