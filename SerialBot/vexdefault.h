

#include "ch.h"         // needs for all ChibiOS programs
#include "hal.h"        // hardware abstraction layer header
#include "vex.h"        // vex library header

#define DEBOUNCE_VALUE 0


// Digi IO configuration
vexDigiCfg  dConfig[kVexDigital_Num] = {
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

vexMotorCfg mConfig[kVexMotorNum] = {
  { kVexMotor_1,  kVexMotor393T,  kVexMotorNormal,   kVexSensorNone,        0 },
  { kVexMotor_2,  kVexMotor393T,  kVexMotorNormal,   kVexSensorNone,        0 },
  { kVexMotor_3,  kVexMotor393T,  kVexMotorNormal,   kVexSensorNone,        0 },
  { kVexMotor_4,  kVexMotor393T,  kVexMotorNormal,   kVexSensorNone,        0 },
  { kVexMotor_5,  kVexMotor393T,  kVexMotorNormal,   kVexSensorNone,        0 },
  { kVexMotor_6,  kVexMotor393T,  kVexMotorNormal,   kVexSensorNone,        0 },
  { kVexMotor_7,  kVexMotor393T,  kVexMotorNormal,   kVexSensorNone,        0 },
  { kVexMotor_8,  kVexMotor393T,  kVexMotorNormal,   kVexSensorNone,        0 },
  { kVexMotor_9,  kVexMotor393T,  kVexMotorNormal,   kVexSensorNone,        0 },
  { kVexMotor_10, kVexMotor393T,  kVexMotorNormal,   kVexSensorNone,        0 }
};

/*-----------------------------------------------------------------------------*/
/** @cond      name the motor ports                                            */
/*-----------------------------------------------------------------------------*/
#define LeftFront       kVexMotor_2
#define LeftBack        kVexMotor_3
#define RightFront      kVexMotor_4
#define RightBack       kVexMotor_5
/** @endcond */

