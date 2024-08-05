#pragma once

#include "esphome/components/climate_ir/climate_ir.h"

namespace esphome {
namespace whirlpool {





// Temperature
const float MAX_TEMP = 30.0;
const float MIN_TEMP = 16.0;


class WhirlpoolClimate : public climate_ir::ClimateIR {
 public:
  WhirlpoolClimate()
      : climate_ir::ClimateIR(MIN_TEMP, MAX_TEMP, 1.0f, true, true,
                              {climate::CLIMATE_FAN_AUTO, climate::CLIMATE_FAN_LOW, climate::CLIMATE_FAN_MEDIUM,
                               climate::CLIMATE_FAN_HIGH},
                              {climate::CLIMATE_SWING_OFF, climate::CLIMATE_SWING_VERTICAL}) {}

  void setup() override {
    climate_ir::ClimateIR::setup();

    this->powered_on_assumed = this->mode != climate::CLIMATE_MODE_OFF;
  }

  /// Override control to change settings of the climate device.
  void control(const climate::ClimateCall &call) override {
    send_swing_cmd_ = call.get_swing_mode().has_value();
    climate_ir::ClimateIR::control(call);
  }

  

  // used to track when to send the power toggle command
  bool powered_on_assumed;

 protected:
  /// Transmit via IR the state of this climate controller.
  void transmit_state() override;
  /// Handle received IR Buffer
  bool on_receive(remote_base::RemoteReceiveData data) override;
  /// Set the time of the last transmission.
  int32_t last_transmit_time_{};

  bool send_swing_cmd_{false};


};

}  // namespace whirlpool
}  // namespace esphome
