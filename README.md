Drone Navigation in Webots
This project simulates the autonomous navigation of a quadcopter drone using Webots — an open-source 3D robotics simulator. The simulation is focused on creating an environment where a drone can fly from a starting point to a destination while avoiding obstacles.

🚀 Project Overview
The objective of this project is to:

Simulate basic drone flight dynamics in Webots.

Build a custom environment with obstacles.

Implement simple navigation logic using onboard sensors (e.g., distance sensors, GPS).

Eventually expand to advanced control (SLAM or RL-based).

📁 Project Structure
drone-navigation-webots/
├── .gitignore
├── .project
├── README.md ← You're reading this!
├── controllers/
│ └── mavic2pro/
│ ├── Makefile
│ └── mavic2pro.c ← Main drone controller code
├── worlds/
│ ├── .drone-world.jpg
│ └── drone-world.wbt ← Simulation world environment

🛠 Setup Instructions
Install Webots
Download from: https://cyberbotics.com/#download

Clone the Repository
git clone https://github.com/Sahana1230spec/drone-navigation-webots.git
cd drone-navigation-webots

Open Webots
Go to File → Open World → Select drone-world.wbt

Run Simulation
Hit the Play button in Webots
The mavic2pro controller handles the drone’s basic flight logic

🌍 Environment Details
The simulation world (drone-world.wbt) is customizable. You can add:

Solids like Box, Cylinder for obstacles

Custom floor or maze layouts

Use Supervisor nodes for external control or automation

A future update will include:

Dynamic pathfinding

Obstacle avoidance

Goal-point navigation

🧠 Problem Statement
Simulate an autonomous drone that takes off from a predefined start location and navigates toward a destination while avoiding static obstacles in a virtual 3D environment.

This setup serves as a base for experimenting with:

PID tuning

Path planning

Visual SLAM

Reinforcement Learning

💡 Features
✅ Quadcopter take-off and hover

✅ Manual obstacle course setup

🕒 Navigation logic (in progress)

🕒 Autonomous goal-reaching (upcoming)

📸 Demo (Coming Soon!)
GIFs/screenshots will be added once navigation logic is implemented.

✍️ Author
Sahana K
Computer Science Undergraduate, RV Institute of Technology and Management
Interests: AI, Robotics, Research, Finance & building tech for real-world impact

📌 Future Scope
Integrate ORB-SLAM3 for real-time mapping

Use PPO/DQN with OpenAI Gym-style wrappers for autonomous learning

Upgrade the environment to support dynamic moving objects