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
# Real-Time Phased Array Ultrasound: Robotic Integration and Vision Detection – GPU-Accelerated Low-Latency Processing

### Phased Array Ultrasound Testing (PAUT) for Real-Time Industrial Non-Destructive Testing (NDT)

## Project Overview

This project implements a GPU-accelerated real-time Phased Array Ultrasound Testing (PAUT) system integrated with robotic control and vision-based object detection. Designed specifically for industrial Non-Destructive Testing (NDT), the system meets stringent low-latency and throughput requirements. Optimizations in CUDA processing, data streaming, and synchronization enable sustained scanning at the hardware-constrained input rate of 60 MB/s, with a practical data acquisition interval of 1.7 ms per frame (~588 Hz).

---

## Key Features & Innovations

### 1. Low-Latency GPU Processing Pipeline
- CUDA-based data pipeline reduces CPU overhead and host-device transfer delays.
- Real-time PAUT scanning achieves sub-millisecond GPU processing latency (~0.15 ms per frame), significantly below PAUT hardware requirements (typical latency 2.5 ms).
- Integrated OpenGL and CUDA rendering provides smooth, low-latency visualization.

### 2. Encoder-Free Robotic Synchronization
- Eliminates the need for physical encoders by leveraging real-time GPU-based image analysis.
- AI-assisted adaptive scanning automatically detects and tracks objects, optimizing inspection time.
- Real-time synchronization of robot positioning with PAUT data acquisition and analysis.

### 3. CUDA Optimizations for Real-Time Performance
- GPU-side computation significantly reduces CPU involvement.
- Triple-buffered asynchronous CUDA streaming minimizes latency and maximizes GPU utilization.
- Efficient use of pinned memory and concurrent streams improves overall throughput.

### 4. Data Management and I/O Optimizations
- Custom binary data format optimized for real-time streaming, replacing traditional formats like HDF5.
- Chunked data streaming (10 MB chunks) maintains low-latency access for immediate processing.
- GPU performance is effectively balanced, with current limitations primarily from PAUT hardware constraints (60 MB/s input limit).

### 5. Addressing PAUT Beamforming Challenges
PAUT beamforming poses inherent challenges for GPU parallelization:
- Beamforming interdependency: each beam calculation depends on adjacent beam data.
- Non-sequential memory access patterns reduce memory bandwidth utilization due to non-coalesced memory accesses.
- Pipeline staging (Ascan → Beamforming → Scanline) required to mitigate synchronization overhead.

---

## Performance Benchmarks
- **Input Data Rate:** 60 MB/s (PAUT hardware limit)
- **Frame Acquisition Rate:** 588 Hz (1.7 ms per frame)
- **Average GPU Processing Latency:** 0.15 ms per frame
- **Maximum GPU Latency:** 0.35 ms per frame (including infrequent detailed scanline processing)
- **CPU-side Processing Overhead:** 0.02 ms per frame
- **Internal GPU Processing Throughput:** 8–10 Gb/s
- **Bottleneck:** PAUT hardware SDK input limitation (60 MB/s)

*Note: Throughput reflects total internal GPU memory operations, distinct from external network or I/O bandwidth.*

---

## Pipeline Optimizations
- Double-buffering reduces GPU idle times.
- Triple-buffering with asynchronous CUDA streams maintains high processing efficiency.
- Separate threads dedicated to post-processing and visualization to avoid pipeline stalls.
- Remaining bottleneck identified as hardware input bandwidth limitation (60 MB/s from PAUT hardware SDK).

---

## Future Optimization Plans
- With GPU performance now optimized, future improvements will focus on upgrading PAUT acquisition hardware to exceed the current 60 MB/s input limitation.
- Planned Ring-0 driver implementation for direct GPU memory access to bypass OS-level latency.

---

## Technologies Used
- **Programming Languages:** Modern C++23, CUDA
- **Parallel Computing:** CUDA, OpenMP, Multi-threading
- **Real-Time Visualization:** CUDA-OpenGL Interop
- **Computer Vision & AI:** OpenCV, Deep Learning methods
- **Robotics:** Custom real-time, encoder-free synchronization algorithms
- **System-Level Optimizations (planned):** Direct GPU access via Ring-0 driver

---

## Applications
- Industrial real-time Non-Destructive Testing (NDT)
- Robotic automated scanning and inspection
- AI-enhanced adaptive object detection and tracking

---

## Project Status
- Developed independently over six months, with collaborative mechanical engineering support.
- Optimized specifically for real-time GPU acceleration and robotic integration.

---

## Summary
This project provides a robust GPU-accelerated real-time PAUT inspection platform, featuring low-latency GPU processing, integrated robotics, and optimized data management, effectively addressing current hardware limitations while enabling advanced real-time industrial inspection workflows.


