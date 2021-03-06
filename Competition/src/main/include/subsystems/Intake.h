#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/PWMVictorSPX.h>

#include "Constants.h"

#ifndef INTAKE_H
#define INTAKE_H

class Intake : public frc2::SubsystemBase {
 public:

    Intake();

    static Intake& GetInstance();

    void SetIntakePower(double power);

    void Periodic() override;

 private:

    frc::PWMVictorSPX intakeMtr;

};

#endif
