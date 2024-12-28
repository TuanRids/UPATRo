# 3D PAUT Visualization and Real-time Robotics Integration

**Note:** The source code is private due to privacy policies. For inquiries, contact:  
📧 Email: ngdtuan.dn@gmail.com  
🔗 LinkedIn: [Nguyen Tuan](https://www.linkedin.com/in/nguyen-tuan-a2a589128/)  

## Overview

This project focuses on real-time 3D visualization of Phased Array Ultrasonic Testing (PAUT) data and integrates it with robotic control for industrial applications. It leverages Vulkan for high-performance rendering and includes plans for AI-based optimization in the future.

## Key Features

### 1. Phased Array Ultrasound in Realtime
- Real-time control and processing of OmniScan PAUT data.
- Full rendering and handling of A, B, S, and C-scan data.
- 3D data visualization using Vulkan.
- **Performance**:
  - Rendered **1,508,832 pixels** across 4 buffers:
    - **SViewBuf**: 292,666 pixels
    - **CViewBuf**: 49,000 pixels
    - **BViewBuf**: 1,166,000 pixels
    - **AViewBuf**: 1,166 pixels
  - Achieved **2ms total frame time** (~500 FPS), meeting industrial-grade real-time requirements.
  - System demonstrates excellent GPU utilization and optimized data processing pipeline.
- Designed for high scalability with support for increased resolution and advanced features.

### 2. Robot Control in Realtime
- Real-time robotic arm control with IPC and C++.
- Vision-based detection for autonomous PAUT scanning.

### 3. AI Application (Planned)
- AI integration to enhance FEM analysis and optimize performance.
- Plans to use GPU-based rendering and OpenCV for AI detection at high frame rates.

### 4. FEM Integration
- Finite Element Method (FEM) applied to processed PAUT data.
- CUDA acceleration for FEM calculations.
- Integrated into Vulkan viewport for simulation.

## Technologies Used
- **PAUT**: Real-time Phased Array Ultrasound processing (C++)
- **Robotics**: Real-time Yaskawa robot arm control (C++)
- **Vulkan**: High-performance 3D rendering (C++)
- **IPC**: Inter-process communication for real-time systems (C++)
- **FEM**: Finite Element Method simulation (C++)
- **CUDA**: Accelerated FEM computation (C++)
- **AI (Planned)**: AI optimization and real-time detection.

## Results (Ongoing)
   https://github.com/user-attachments/assets/8b175165-b30c-47b8-a85f-a454044e6820
   
   ![RealtimePAUT GPU All Mode](https://github.com/user-attachments/assets/ad69d357-cdf9-4876-a386-0e49341529ce)






- **Render Performance**:
  - Successfully rendered **~1.5 million pixels** in **2ms** (~500 FPS).
  - Exceeds real-time industrial standards (60-120 FPS).
- **Buffer Details**:
  - **SViewBuf**: 292,666 pixels
  - **CViewBuf**: 49,000 pixels
  - **BViewBuf**: 1,166,000 pixels
  - **AViewBuf**: 1,166 pixels
- **Efficiency**:
  - Maintains high scalability and GPU utilization.
  - Provides a strong foundation for integrating additional features like AI and FEM.

## Applications
- Real-time robotics control and monitoring.
- Advanced NDT (Non-Destructive Testing) applications.
- Autonomous industrial inspections with enhanced AI integration.

---

This project combines real-time robotics, advanced 3D rendering, and scalable data processing to support high-performance industrial applications.
