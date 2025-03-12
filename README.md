# 3D PAUT Visualization and Real-time Robotics Integration


## Results (Ongoing)

https://github.com/user-attachments/assets/10336cc9-0363-4367-a08f-b49187899e87

https://github.com/user-attachments/assets/ecc3c03d-404a-428e-8a4e-52ce408c8e0f

https://github.com/user-attachments/assets/5e93d6a6-586f-4af1-8c2d-9144a7439617

![RealtimePAUT GPU All Mode](https://github.com/user-attachments/assets/ef7d6936-ffc7-44f1-a2c9-dd81e2192ca0)
   
Note: The source code is private due to privacy policies. For inquiries, contact:

📧 Email: ngdtuan.dn@gmail.com

🔗 LinkedIn: [Nguyen Tuan](https://www.linkedin.com/in/nguyen-tuan-a2a589128/)
# 3D Real-time PAUT and Robotics Integration with Ultra-Low Latency

## Project Overview
This project involves developing a cutting-edge system for real-time 3D visualization and robotic integration of Phased Array Ultrasonic Testing (PAUT) data. Designed specifically for high-precision industrial inspection and Non-Destructive Testing (NDT), it seamlessly integrates advanced robotics, GPU-accelerated computation (CUDA), and computer vision, operating entirely without external encoders by employing custom-developed synchronization algorithms. The system achieves ultra-low latency data handling, with current frame processing times as low as 0.5 milliseconds (2000+ FPS), significantly surpassing standard industry benchmarks.

## Key Features & Technical Innovations

- **Real-time PAUT Data Visualization:**
  - High-performance GPU rendering using Vulkan and CUDA.
  - Achieves real-time processing at an exceptionally low frame time (~0.5ms/frame, ~2000 FPS).
  - Manages large-scale rendering across multiple view buffers, current size 656x1788 (not maximum) which is totaling over 1.1 million pixels per frame.

- **Advanced Robotics Integration (Encoder-free):**
  - Developed a custom algorithm to synchronize robotic movements with PAUT scans, eliminating the need for traditional encoders.
  - Enables autonomous, precise positional tracking using self-developed algorithms.

- **Computer Vision Integration:**
  - Implements automated object detection with OpenCV and deep-learning methods to dynamically determine scan coordinates.
  - Real-time adaptive scanning for objects without pre-defined coordinates.

- **Robotics Integration & Custom Algorithm Development:**
  - Fully autonomous robotic integration with PAUT, removing dependency on traditional encoders.
  - Developed custom algorithms for real-time synchronization between PAUT data acquisition and robotic control.

- **Upcoming Kernel-Level Optimization (Ring 0 Driver):**
  - Planned development of a custom Ring-0 kernel driver to significantly reduce data transfer latency (current bottleneck at ~1.8ms).
  - Direct memory mapping to kernel space for ultra-low latency data handling and optimized real-time performance.

---

## Current Performance Benchmarks
- **Rendering & Visualization:**
  - Over 1.5 million pixels rendered within ~0.5ms.
  - Exceeds typical industrial standards (60-120 FPS) by achieving ~2000 FPS.

- **Data Acquisition and Robotics Integration:**
  - Fully autonomous synchronization without external encoder data.
  - Adaptive real-time object tracking and scanning.

---

## Technologies Used
- **Languages & Frameworks:** Modern C++23, CUDA, OpenGL
- **Real-time Computing:** CUDA, OpenMP, Multithreading, Memory Management
- **Computer Vision:** OpenCV, Deep Learning
- **Robotics, Simulation & Analysis:** Custom algorithms for real-time robot synchronization, accelerated via CUDA
- **Kernel Development:** Planned Ring-0 Driver for ultra-low latency performance optimization

---

## Applications
- Real-time robotic control for automated industrial inspections.
- Advanced PAUT-based NDT systems.
- Autonomous inspection solutions with adaptive AI-driven scanning.

---

## Project Status
- Duration: R&D in 6 months from concept to complete R&D, with supporting of some members from mechanical engineering.
- Successfully implemented a fully operational real-time PAUT system integrated with robotics within a 6-month solo R&D period.
- Current performance surpasses typical industrial standards.
- Planning advanced optimizations (Ring-0 Driver) to further enhance real-time data acquisition.

---
