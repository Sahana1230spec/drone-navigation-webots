/*
 * Drone Navigation & Control in Webots
 * Author: Sahana R
 * Description:
 *  - Custom-built navigation control system for a drone using Webots simulator.
 *  - Stabilizes using embedded sensors with PID logic for pitch, roll, and yaw.
 *  - Supports manual control using keyboard inputs.
 *  - Created as part of the Drone Navigation Project @ NITK.
 *
 * Based on Cyberbotics Webots base controller (Apache License 2.0)
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <webots/robot.h>
#include <webots/camera.h>
#include <webots/compass.h>
#include <webots/gps.h>
#include <webots/gyro.h>
#include <webots/inertial_unit.h>
#include <webots/keyboard.h>
#include <webots/led.h>
#include <webots/motor.h>

#define SIGN(x) ((x) > 0) - ((x) < 0)
#define CLAMP(value, low, high) ((value) < (low) ? (low) : ((value) > (high) ? (high) : (value)))

int main(int argc, char **argv) {
  wb_robot_init();
  int timestep = (int)wb_robot_get_basic_time_step();

  // 🚀 Initialize devices (camera, sensors, motors, etc.)
  WbDeviceTag camera = wb_robot_get_device("camera");
  wb_camera_enable(camera, timestep);

  WbDeviceTag front_left_led = wb_robot_get_device("front left led");
  WbDeviceTag front_right_led = wb_robot_get_device("front right led");
  WbDeviceTag imu = wb_robot_get_device("inertial unit");
  wb_inertial_unit_enable(imu, timestep);

  WbDeviceTag gps = wb_robot_get_device("gps");
  wb_gps_enable(gps, timestep);

  WbDeviceTag compass = wb_robot_get_device("compass");
  wb_compass_enable(compass, timestep);

  WbDeviceTag gyro = wb_robot_get_device("gyro");
  wb_gyro_enable(gyro, timestep);

  wb_keyboard_enable(timestep);

  WbDeviceTag camera_roll_motor = wb_robot_get_device("camera roll");
  WbDeviceTag camera_pitch_motor = wb_robot_get_device("camera pitch");

  // 🔧 Get motors and set velocity control mode
  WbDeviceTag front_left_motor = wb_robot_get_device("front left propeller");
  WbDeviceTag front_right_motor = wb_robot_get_device("front right propeller");
  WbDeviceTag rear_left_motor = wb_robot_get_device("rear left propeller");
  WbDeviceTag rear_right_motor = wb_robot_get_device("rear right propeller");

  WbDeviceTag motors[4] = {front_left_motor, front_right_motor, rear_left_motor, rear_right_motor};
  for (int m = 0; m < 4; ++m) {
    wb_motor_set_position(motors[m], INFINITY);
    wb_motor_set_velocity(motors[m], 1.0);
  }

  // 🛫 Startup message
  printf("Start the drone...\n");

  // ⏳ Wait before flight
  while (wb_robot_step(timestep) != -1) {
    if (wb_robot_get_time() > 1.0)
      break;
  }

  // 🎮 Manual control instructions
  printf("You can control the drone with your computer keyboard:\n");
  printf("- 'up': move forward.\n");
  printf("- 'down': move backward.\n");
  printf("- 'right': turn right.\n");
  printf("- 'left': turn left.\n");
  printf("- 'shift + up': increase the target altitude.\n");
  printf("- 'shift + down': decrease the target altitude.\n");
  printf("- 'shift + right': strafe right.\n");
  printf("- 'shift + left': strafe left.\n");

  // 📊 PID Tuning Constants (adjusted manually)
  const double k_vertical_thrust = 68.5;
  const double k_vertical_offset = 0.6;
  const double k_vertical_p = 3.0;
  const double k_roll_p = 50.0;
  const double k_pitch_p = 30.0;

  // 🎯 Target altitude
  double target_altitude = 1.0;

  // 🔁 Main control loop
  while (wb_robot_step(timestep) != -1) {
    double time = wb_robot_get_time();

    // 📡 Sensor readings
    double roll = wb_inertial_unit_get_roll_pitch_yaw(imu)[0];
    double pitch = wb_inertial_unit_get_roll_pitch_yaw(imu)[1];
    double altitude = wb_gps_get_values(gps)[2];
    double roll_velocity = wb_gyro_get_values(gyro)[0];
    double pitch_velocity = wb_gyro_get_values(gyro)[1];

    // 💡 LED blink
    bool led_state = ((int)time) % 2;
    wb_led_set(front_left_led, led_state);
    wb_led_set(front_right_led, !led_state);

    // 📷 Camera gimbal stabilization
    double camera_roll_position = CLAMP(-0.115 * roll_velocity, -0.5, 0.5);
    double camera_pitch_position = CLAMP(-0.1 * pitch_velocity, -0.5, 0.5);
    wb_motor_set_position(camera_roll_motor, camera_roll_position);
    wb_motor_set_position(camera_pitch_motor, camera_pitch_position);

    // 🕹️ Keyboard control
    double roll_disturbance = 0.0, pitch_disturbance = 0.0, yaw_disturbance = 0.0;
    int key = wb_keyboard_get_key();
    while (key > 0) {
      switch (key) {
        case WB_KEYBOARD_UP: pitch_disturbance = -2.0; break;
        case WB_KEYBOARD_DOWN: pitch_disturbance = 2.0; break;
        case WB_KEYBOARD_RIGHT: yaw_disturbance = -1.3; break;
        case WB_KEYBOARD_LEFT: yaw_disturbance = 1.3; break;
        case (WB_KEYBOARD_SHIFT + WB_KEYBOARD_RIGHT): roll_disturbance = -1.0; break;
        case (WB_KEYBOARD_SHIFT + WB_KEYBOARD_LEFT): roll_disturbance = 1.0; break;
        case (WB_KEYBOARD_SHIFT + WB_KEYBOARD_UP): target_altitude += 0.05; break;
        case (WB_KEYBOARD_SHIFT + WB_KEYBOARD_DOWN): target_altitude -= 0.05; break;
      }
      key = wb_keyboard_get_key();
    }

    // 🎯 Control logic
    double roll_input = k_roll_p * CLAMP(roll, -1.0, 1.0) + roll_velocity + roll_disturbance;
    double pitch_input = k_pitch_p * CLAMP(pitch, -1.0, 1.0) + pitch_velocity + pitch_disturbance;
    double yaw_input = yaw_disturbance;
    double clamped_diff = CLAMP(target_altitude - altitude + k_vertical_offset, -1.0, 1.0);
    double vertical_input = k_vertical_p * pow(clamped_diff, 3.0);

    // ⚙️ Motor velocity calculations
    double front_left_motor_input = k_vertical_thrust + vertical_input - roll_input + pitch_input - yaw_input;
    double front_right_motor_input = k_vertical_thrust + vertical_input + roll_input + pitch_input + yaw_input;
    double rear_left_motor_input = k_vertical_thrust + vertical_input - roll_input - pitch_input + yaw_input;
    double rear_right_motor_input = k_vertical_thrust + vertical_input + roll_input - pitch_input - yaw_input;

    wb_motor_set_velocity(front_left_motor, front_left_motor_input);
    wb_motor_set_velocity(front_right_motor, -front_right_motor_input);
    wb_motor_set_velocity(rear_left_motor, -rear_left_motor_input);
    wb_motor_set_velocity(rear_right_motor, rear_right_motor_input);

    // 🛬 Auto-landing logic (when altitude is near 0)
    if (altitude < 0.05) {
      printf("🎯 Drone has landed.\n");
      break;
    }
  }

  // 🧹 Cleanup
  wb_robot_cleanup();
  return EXIT_SUCCESS;
}
