# Real-Time Phased Array Ultrasound: Robotic Integration and Vision Detection

## Results (Ongoing)

https://github.com/user-attachments/assets/10336cc9-0363-4367-a08f-b49187899e87

https://github.com/user-attachments/assets/ecc3c03d-404a-428e-8a4e-52ce408c8e0f

https://github.com/user-attachments/assets/5e93d6a6-586f-4af1-8c2d-9144a7439617

![RealtimePAUT GPU All Mode](https://github.com/user-attachments/assets/ef7d6936-ffc7-44f1-a2c9-dd81e2192ca0)
   
Note: The source code is private due to privacy policies. For inquiries, contact:

📧 Email: ngdtuan.dn@gmail.com

🔗 LinkedIn: [Nguyen Tuan](https://www.linkedin.com/in/nguyen-tuan-a2a589128/)
---
# Real-Time Phased Array Ultrasound: Robotic Integration and GPU-Accelerated Low-Latency Processing

### Phased Array Ultrasound Testing (PAUT) for Real-Time Industrial Non-Destructive Testing (NDT)

## Project Overview

This project implements a GPU-accelerated real-time Phased Array Ultrasound Testing (PAUT) system integrated with robotic control and simplified vision-based object positioning. Specifically designed for industrial Non-Destructive Testing (NDT), the system achieves stringent low-latency and throughput targets. Optimizations in CUDA processing, data streaming, and synchronization enable sustained scanning at the hardware-constrained input rate of 60 MB/s, with a practical data acquisition interval of 1.7 ms per frame (~588 Hz).

---

## Key Features & Innovations

### 1. Low-Latency GPU Processing Pipeline
- CUDA-based data pipeline reduces CPU overhead and host-device transfer delays.
- Real-time PAUT scanning achieves sub-millisecond GPU processing latency (~0.15 ms per frame), significantly below typical PAUT hardware latency (2.5 ms).
- Integrated OpenGL and CUDA rendering for smooth, low-latency visualization.

### 2. Encoder-Free Robotic Synchronization
- Completely eliminates physical encoders through a custom-developed synchronization method:
  - Uses real-time GPU-processed ultrasound signals to generate stitchID (beamformed average), providing precise positioning feedback.
  - Incorporates a start-stop mechanism controlled via IO signals from a custom-designed hardware module, measuring real-time robot states without encoders.
  - Planned implementation of an alignment-processing algorithm to minimize positional discrepancies across multiple scans through interpolation techniques.

### 3. Vision-Assisted Positioning (Auxiliary)
- Utilizes Intel RealSense camera to detect approximate XY coordinates for scan initiation.
- Simplified vision system designed for basic spatial alignment purposes (no complex object recognition involved).

### 4. CUDA Optimizations for Real-Time Performance
- GPU-side computation significantly reduces CPU involvement.
- Triple-buffered asynchronous CUDA streaming minimizes latency, maximizing GPU utilization.
- Efficient use of pinned memory and concurrent streams enhances overall throughput.

### 5. Data Management and I/O Optimizations
- Custom binary data format optimized for real-time streaming, replacing traditional formats such as HDF5.
- Chunked data streaming (10 MB chunks) maintains low-latency immediate processing access.
- Current GPU performance primarily constrained by PAUT hardware input limits (60 MB/s).

### 6. Addressing PAUT Beamforming Challenges
- Beamforming interdependencies due to adjacent beam calculations.
- Non-sequential memory access patterns addressed via pipeline staging (Ascan → Beamforming → Scanline).

---

## Performance Benchmarks
- **Input Data Rate:** 60 MB/s (PAUT hardware limit)
- **Frame Acquisition Rate:** 588 Hz (1.7 ms per frame)
- **Average GPU Processing Latency:** 0.15 ms/frame
- **Maximum GPU Latency:** 0.35 ms/frame (including detailed scanline processing)
- **CPU-side Processing Overhead:** 0.02 ms/frame
- **Internal GPU Processing Throughput:** 8–10 Gb/s
- **Bottleneck:** PAUT hardware SDK input limitation (60 MB/s)

![image](https://github.com/user-attachments/assets/5707fe41-1e33-4121-81ed-ee6f605a1f71)
![image](https://github.com/user-attachments/assets/6746f567-d7dc-4480-aed0-40cae1b67cf8)

*Note: Throughput reflects total internal GPU memory operations, distinct from external network or I/O bandwidth.*

---

## Pipeline Optimizations
- Double-buffering reduces GPU idle times.
- Triple-buffering with asynchronous CUDA streams for processing efficiency.
- Dedicated post-processing and visualization threads to prevent pipeline stalls.

---

## Future Optimization Plans
- Upgrade PAUT acquisition hardware to exceed current 60 MB/s limitation.
- Implement Ring-0 driver for direct GPU memory access, bypassing OS-level latency.

---

## Technologies Used
- **Programming Languages:** Modern C++23, CUDA
- **Parallel Computing:** CUDA, OpenMP, Multi-threading
- **Real-Time Visualization:** CUDA-OpenGL Interop
- **Phased Array Ultrasound:** Olympus X3 series
- **Computer Vision (Auxiliary):** OpenCV, Intel RealSense
- **Robotics:** Yaskawa YRC 1000, Custom real-time synchronization (encoder-free)
- **System-Level Optimizations (planned):** Direct GPU access via Ring-0 driver

---

## Applications
- Industrial real-time Non-Destructive Testing (NDT)
- Automated robotic scanning and inspections
- Real-time positioning and alignment solutions

---

## Project Status
- Independently developed over six months with mechanical engineering collaboration.
- Specifically optimized for real-time GPU acceleration and robotic integration.

---

## Summary
This project delivers a robust GPU-accelerated real-time PAUT inspection system, emphasizing low-latency GPU processing, innovative encoder-free robotic synchronization via custom IO and ultrasound-based positioning methods, and optimized real-time data management, effectively overcoming existing hardware limitations to enable advanced real-time industrial inspection workflows.

