#include "RobotContainer.h"


RobotContainer::RobotContainer() /*: m_homeTrenchAuto(&m_drivetrain)*/ {
    // Initialize all of your commands and subsystems here
    m_chooser.AddOption("InitHomeTrench", "InitHomeTrench1");
    m_chooser.AddOption("Test", "Test1");
    m_shuffleboard.GetTab("Autonomous").Add(m_chooser);
    
    m_drivetrain.SetDefaultCommand(DriveManual(&m_drivetrain,
        [this] { return m_GamepadDriver.GetTriggerAxis(frc::GenericHID::kRightHand); },
        [this] { return m_GamepadDriver.GetTriggerAxis(frc::GenericHID::kLeftHand); },
        [this] { return m_GamepadDriver.GetX(frc::GenericHID::kLeftHand); },
        [this] { return m_GamepadDriver.GetBumper(frc::GenericHID::kLeftHand); }));

    m_intake.SetDefaultCommand(SpinIntake(&m_intake, 
        [this] { return m_GamepadDriver.GetTriggerAxis(frc::GenericHID::kRightHand); }, 
        [this] { return m_GamepadDriver.GetBumper(frc::GenericHID::kRightHand); }));
            
    m_hopper.SetDefaultCommand(SpinHopper(&m_hopper, 
        [this] { return m_GamepadDriver.GetTriggerAxis(frc::GenericHID::kLeftHand); }, 
        [this] { return m_GamepadDriver.GetBumper(frc::GenericHID::kLeftHand); }));

    m_arm.SetDefaultCommand(ArmManual(&m_arm, 
        [this] { return m_GamepadDriver.GetY(frc::GenericHID::kLeftHand); }));

    m_lift.SetDefaultCommand(Climb(&m_lift, 
        [this] { return m_GamepadDriver.GetY(frc::GenericHID::kRightHand); }));

    m_muncher.SetDefaultCommand(Munch(&m_muncher, 
        [this] { return m_GamepadDriver.GetYButton(); }));

    // Configure the button bindings
    ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
    frc2::JoystickButton m_start{&m_GamepadDriver, 8};
    frc2::JoystickButton m_back{&m_GamepadDriver, 7};

    // frc::JoystickButton m_a{&m_GamepadDriver, 1};
    frc2::JoystickButton m_b{&m_GamepadDriver, 2};
    // frc::JoystickButton m_x{&m_GamepadDriver, 3};
    //frc2::JoystickButton m_y{&m_GamepadDriver, 4};

    frc2::JoystickButton m_rightBumper{&m_GamepadDriver, 6};
    
    m_rightBumper.WhenPressed(frc2::InstantCommand([this] { m_drivetrain.SetMultiplier(1); }, {&m_drivetrain}));

    m_start.WhenPressed(ShootStart(&m_shooter));
    m_back.WhenPressed(ShootStop(&m_shooter));
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
    // An example command will be run in autonomous
    if (m_chooser.GetSelected() == "InitHomeTrench") {
        return RobotContainer::HomeTrenchAuto();
    }
    else {
        return RobotContainer::TestAuto();
    }
}

frc2::Command* RobotContainer::HomeTrenchAuto() {
   auto trajectory = m_trajectories.GetTrajectory(); 

   frc2::RamseteCommand ramseteCommand(
      trajectory, [this]() { return m_drivetrain.GetPose(); },
      frc::RamseteController(RamseteConstants::kRamseteB, RamseteConstants::kRamseteZeta),
      m_drivetrain.kSimpleMotorFeedforward,
      m_drivetrain.kDriveKinematics,
      [this] { return m_drivetrain.GetWheelSpeeds(); },
      frc2::PIDController(RamseteConstants::kPDriveVel, 0, 0),
      frc2::PIDController(RamseteConstants::kPDriveVel, 0, 0),
      [this](auto left, auto right) { m_drivetrain.TankDriveVolts(left, right); },
      {&m_drivetrain});

   return new frc2::SequentialCommandGroup(
      std::move(ramseteCommand),
      frc2::InstantCommand([this] { m_drivetrain.TankDriveVolts(0_V, 0_V); }, {}));
}

frc2::Command* RobotContainer::TestAuto() {
    return new frc2::SequentialCommandGroup(frc2::InstantCommand([this] { m_drivetrain.TankDriveVolts(0_V, 0_V); }, {}));
}


