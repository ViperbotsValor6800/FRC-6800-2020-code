/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/WPILib.h>
#include <frc/TimedRobot.h>
#include <frc/commands/Command.h>
#include "OI.h"
#include "subsystems/Drivetrain.h"

class Robot: public frc::TimedRobot {
public:
    static OI *mOI;
    static Drivetrain *mDrivetrain;

private:
    void RobotInit() override;
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    void TeleopInit() override;
    void TeleopPeriodic() override;
    void TestPeriodic() override;
    void DisabledInit() override;
    void DisabledPeriodic() override;
};
