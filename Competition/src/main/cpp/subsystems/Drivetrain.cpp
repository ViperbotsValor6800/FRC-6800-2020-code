#include "subsystems/Drivetrain.h"
#include <frc/kinematics/DifferentialDriveOdometry.h>

Drivetrain::Drivetrain() : boostMultiplier{0.5},
                           kDriveKinematics{DriveConstants::kTrackwidth},
                           kSimpleMotorFeedforward{RamseteConstants::kS, RamseteConstants::kV, RamseteConstants::kA},
                           kTrajectoryConfigF{RamseteConstants::kMaxSpeed, RamseteConstants::kMaxAcceleration},
                           kTrajectoryConfigR{RamseteConstants::kMaxSpeed, RamseteConstants::kMaxAcceleration},
                           kDifferentialDriveVoltageConstraint{kSimpleMotorFeedforward, kDriveKinematics, 10_V},
                           m_leftDriveLead{DriveConstants::CAN_ID_LEFT_LEAD, rev::CANSparkMax::MotorType::kBrushless},
                           m_leftDriveFollowA{DriveConstants::CAN_ID_LEFT_FOLLOW_A, rev::CANSparkMax::MotorType::kBrushless},
                           m_leftDriveFollowB{DriveConstants::CAN_ID_LEFT_FOLLOW_B, rev::CANSparkMax::MotorType::kBrushless},
                           m_rightDriveLead{DriveConstants::CAN_ID_RIGHT_LEAD, rev::CANSparkMax::MotorType::kBrushless},
                           m_rightDriveFollowA{DriveConstants::CAN_ID_RIGHT_FOLLOW_A, rev::CANSparkMax::MotorType::kBrushless},
                           m_rightDriveFollowB{DriveConstants::CAN_ID_RIGHT_FOLLOW_B, rev::CANSparkMax::MotorType::kBrushless},
                           m_odometry{frc::Rotation2d(units::degree_t(GetHeading()))},
                           limelight_state{1} // Init as on so it immediately will turn off in the state machine
                           
{
    // drive.SetMaxOutput(kMaxOutput);
    // drive.SetDeadband(kDeadband);

    kTrajectoryConfigF.SetKinematics(kDriveKinematics);
    kTrajectoryConfigF.AddConstraint(kDifferentialDriveVoltageConstraint);
    kTrajectoryConfigF.SetReversed(false);

    kTrajectoryConfigR.SetKinematics(kDriveKinematics);
    kTrajectoryConfigR.AddConstraint(kDifferentialDriveVoltageConstraint);
    kTrajectoryConfigR.SetReversed(true);

    imu.Calibrate();

    InitDrives(rev::CANSparkMax::IdleMode::kCoast);
}

Drivetrain& Drivetrain::GetInstance()
{
    static Drivetrain instance; // Guaranteed to be destroyed. Instantiated on first use.
    return instance;
}

void Drivetrain::Periodic() {
    m_odometry.Update(frc::Rotation2d(units::degree_t(GetHeading())), GetLeftDistance(), GetRightDistance());
    frc::SmartDashboard::PutNumber("Heading", imu.GetAngle());
}

void Drivetrain::InitDrives(rev::CANSparkMax::IdleMode idleMode) {
    m_leftDriveLead.SetIdleMode(idleMode);
    m_leftDriveFollowA.SetIdleMode(idleMode);
    m_leftDriveFollowB.SetIdleMode(idleMode);
    m_rightDriveLead.SetIdleMode(idleMode);
    m_rightDriveFollowA.SetIdleMode(idleMode);
    m_rightDriveFollowB.SetIdleMode(idleMode);

    m_leftDriveFollowA.Follow(m_leftDriveLead);
    m_leftDriveFollowB.Follow(m_leftDriveLead);

    m_rightDriveFollowA.Follow(m_rightDriveLead);
    m_rightDriveFollowB.Follow(m_rightDriveLead);

    m_leftPIDController.SetP(kP);
    m_leftPIDController.SetI(kI);
    m_leftPIDController.SetD(kD);
    m_leftPIDController.SetIZone(kIz);
    m_leftPIDController.SetFF(kFF);
    m_leftPIDController.SetOutputRange(kMinOutput, kMaxOutput);

    m_rightPIDController.SetP(kP);
    m_rightPIDController.SetI(kI);
    m_rightPIDController.SetD(kD);
    m_rightPIDController.SetIZone(kIz);
    m_rightPIDController.SetFF(kFF);
    m_rightPIDController.SetOutputRange(kMinOutput, kMaxOutput);

    m_rightPIDController.SetSmartMotionMaxVelocity(kMaxVel);
    m_rightPIDController.SetSmartMotionMinOutputVelocity(kMinVel);
    m_rightPIDController.SetSmartMotionMaxAccel(kMaxAccel);
    m_rightPIDController.SetSmartMotionAllowedClosedLoopError(kAllError);
    
    m_leftPIDController.SetSmartMotionMaxVelocity(kMaxVel);
    m_leftPIDController.SetSmartMotionMinOutputVelocity(kMinVel);
    m_leftPIDController.SetSmartMotionMaxAccel(kMaxAccel);
    m_leftPIDController.SetSmartMotionAllowedClosedLoopError(kAllError);

    m_leftDriveLead.SetInverted(false);
    m_rightDriveLead.SetInverted(true);
}

void Drivetrain::ResetEncoders() {
    m_leftEncoder.SetPosition(0);
    m_rightEncoder.SetPosition(0);
}

void Drivetrain::ResetOdometry(frc::Pose2d pose) {
    ResetEncoders();
    m_odometry.ResetPosition(pose, frc::Rotation2d(units::degree_t(GetHeading())));
}
void Drivetrain::ResetIMU() {
    imu.Reset();
}

// rev::CANEncoder& GetLeftEncoder() {
//     return m_leftEncoder;
// }

// rev::CANEncoder& GetRightEncoder() {
//     return m_rightEncoder;
// }

double Drivetrain::GetEncAvgDistance() {
    return ((m_leftEncoder.GetPosition() * RamseteConstants::kPositionConversionFactor) + (m_rightEncoder.GetPosition() * RamseteConstants::kPositionConversionFactor)) / 2.0;
}

units::meter_t Drivetrain::GetLeftDistance() {
    return m_leftEncoder.GetPosition() * RamseteConstants::kPositionConversionFactor * 1_m;
}

units::meter_t Drivetrain::GetRightDistance() {
    return m_rightEncoder.GetPosition() * RamseteConstants::kPositionConversionFactor * 1_m;
}

double Drivetrain::GetHeading() {
    return std::remainder(imu.GetAngle(), 360) * (RamseteConstants::kGyroReversed ? -1.0 : 1.0);
}

double Drivetrain::GetTurnRate() {
    return imu.GetRate() * (RamseteConstants::kGyroReversed ? -1.0 : 1.0);
}

frc::Pose2d Drivetrain::GetPose() { 
    return m_odometry.GetPose(); 
}

frc::DifferentialDriveWheelSpeeds Drivetrain::GetWheelSpeeds() {
    return { units::meters_per_second_t(m_leftEncoder.GetVelocity() * RamseteConstants::kVelocityConversionFactor),
             units::meters_per_second_t(m_rightEncoder.GetVelocity() * RamseteConstants::kVelocityConversionFactor) };
}

void Drivetrain::TankDriveVolts(units::volt_t leftVolts, units::volt_t rightVolts) {
    m_leftDriveLead.SetVoltage(leftVolts);
    m_rightDriveLead.SetVoltage(rightVolts);
    // m_drive.Feed();
}

void Drivetrain::ArcadeDrive(double leftInput, double rightInput) {
   // drive.ArcadeDrive(leftInput, -rightInput * .5, true);
}

void Drivetrain::RocketLeagueDrive(double straightInput, double reverseInput, double turnInput, bool limelightInput) {
    straightValue = reverseInput - straightInput;
    if (std::abs(straightValue) < kDeadbandY) {
      straightValue = 0;
    }
    directionY = (straightValue >= 0) ? 1 : -1;
    straightTarget = MaxRPM * -std::pow(straightValue, 2) * directionY * kDriveMultiplierY * boostMultiplier;
   
    turnValue = turnInput;

    directionX = (turnValue >= 0) ? 1 : -1;
    turnValue = std::pow(turnValue * kDriveMultiplierX, 2) * directionX;
    turnTarget = MaxRPM * -turnValue;
    // if (directionY == 1) {   //for inverting x and y in revese direction
    //   turnTarget = -turnTarget;
    // }
    
    if (std::abs(turnValue) < kDeadbandX) {
      if (std::abs(straightValue) < kDeadbandY) {
        turnTarget = 0; //if turning, don't use drive straightening
      }
      else {
        turnTarget = (m_leftEncoder.GetVelocity() - m_rightEncoder.GetVelocity()) * kDriveOffset;
        // Robot tends to curve to the left at 50RPM slower
      }
    }

    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    float tx = table->GetNumber("tx", 0.0);
    float tv = table->GetNumber("tv" , 0.0);

    // Limelight button pressed
    if (limelightInput) {

        // Check state of limelight
        // If previously was off, turn on LED and start tracking
        //if (limelight_state == 0) {
            table->PutNumber("ledMode", LimelightConstants::LED_MODE_ON);
            table->PutNumber("camMode", LimelightConstants::TRACK_MODE_ON);
            limelight_state = 1;
        //}

        // Limelight has target, track and move robot
        if (tv == 1)
            turnTarget = kP * tx * MaxRPM;
    } else {

        // Check state of limelight
        // If previously was on, turn off LED and stop tracking
       // if (limelight_state == 1) {
            table->PutNumber("ledMode", LimelightConstants::LED_MODE_OFF);
            table->PutNumber("camMode", LimelightConstants::TRACK_MODE_OFF);
            limelight_state = 0;
        //}
    }
    // if (std::abs(straightTarget) < kDeadbandY && std::abs(turnTarget) < kDeadbandX) {
    //     m_leftDriveLead.Set(0);
    //     m_rightDriveLead.Set(0);
    // }
    // else {
        m_leftPIDController.SetReference(straightTarget - turnTarget, rev::ControlType::kVelocity);
        m_rightPIDController.SetReference(straightTarget + turnTarget, rev::ControlType::kVelocity);
    //}
    

    frc::SmartDashboard::PutNumber("TurnVelocity", turnTarget);
    frc::SmartDashboard::PutNumber("ForwardVelocity", straightTarget);
    frc::SmartDashboard::PutNumber("LeftVelocityVariable", m_leftEncoder.GetVelocity());
    frc::SmartDashboard::PutNumber("RightVelocityVariable", m_rightEncoder.GetVelocity());
}

void Drivetrain::SetMultiplier(double multiplier) {
    boostMultiplier = multiplier;
}

void Drivetrain::Stop() {
    m_leftDriveLead.StopMotor();
    m_leftDriveFollowA.StopMotor();
    m_leftDriveFollowB.StopMotor();
    m_rightDriveLead.StopMotor();
    m_rightDriveFollowA.StopMotor();
    m_rightDriveFollowB.StopMotor();
}
