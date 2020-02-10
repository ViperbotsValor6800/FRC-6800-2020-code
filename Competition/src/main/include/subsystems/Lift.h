#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/PWMVictorSPX.h>
#include <frc/SpeedControllerGroup.h>
#include "Constants.h"

class Lift : public frc2::SubsystemBase {
 public:

    Lift();

    static Lift& GetInstance();

    void SetLiftPower(double power);
    void Periodic() override;

 private:

    frc::PWMVictorSPX liftMtrA;
    frc::PWMVictorSPX liftMtrB;

    frc::SpeedControllerGroup liftMtrs{liftMtrA, liftMtrB};

};