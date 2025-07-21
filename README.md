# 🚁 Drone Navigation in Webots

This project simulates the autonomous navigation of a quadcopter drone using **Webots** — an open-source 3D robotics simulator. The drone navigates from a defined start point to a destination while avoiding obstacles in a custom environment.

---

## 🚀 Project Goals

- Simulate basic drone flight in Webots  
- Build a custom world with obstacles  
- Implement simple navigation logic using sensors (e.g., GPS, distance sensors)  
- Expand into SLAM and RL-based control

---

## 📁 Project Structure

```
drone-navigation-webots/
├── .gitignore
├── .project
├── README.md              ← You're here!
├── controllers/
│   └── mavic2pro/
│       ├── Makefile
│       └── mavic2pro.c    ← Drone control code
├── worlds/
│   ├── .drone-world.jpg
│   └── drone-world.wbt    ← Simulation world
```

---

## 🛠️ Setup Instructions

1. **Install Webots**  
   Download from: [https://cyberbotics.com/#download](https://cyberbotics.com/#download)

2. **Clone the Repository**
   ```bash
   git clone https://github.com/Sahana1230spec/drone-navigation-webots.git
   cd drone-navigation-webots
   ```

3. **Open Webots**
   - Go to `File → Open World`
   - Select `drone-world.wbt`

4. **Run the Simulation**
   - Click the Play ▶️ button
   - The `mavic2pro` controller handles basic drone logic

---

## 🌍 Environment Details

- Add obstacles using `Box`, `Cylinder`, etc.
- Create floor layouts or simple mazes
- Use Supervisor nodes for high-level control

> **Future Updates:**
> - Obstacle avoidance logic  
> - Goal-based navigation  
> - Dynamic path planning

---

## 🧠 Problem Statement

> Build an autonomous drone system that flies from a defined start point to a goal, while avoiding static obstacles in a 3D virtual world.

This serves as a base for:
- PID tuning  
- Visual SLAM (e.g., ORB-SLAM3)  
- RL-based navigation (e.g., PPO, DQN)

---

## ✅ Features

- Quadcopter take-off & hover  
- Custom obstacle environment  
- Navigation logic (WIP)  
- Autonomous goal-reaching (Coming Soon)

---

## 📌 Future Scope

- ORB-SLAM3 integration  
- RL with PPO/DQN using Gym-style wrappers  
- Dynamic environments with moving obstacles
