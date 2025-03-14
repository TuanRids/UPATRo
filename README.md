# 3D PAUT Visualization and Real-time Robotics Integration


## Results (Ongoing)

https://github.com/user-attachments/assets/10336cc9-0363-4367-a08f-b49187899e87

https://github.com/user-attachments/assets/ecc3c03d-404a-428e-8a4e-52ce408c8e0f

https://github.com/user-attachments/assets/5e93d6a6-586f-4af1-8c2d-9144a7439617

![RealtimePAUT GPU All Mode](https://github.com/user-attachments/assets/ef7d6936-ffc7-44f1-a2c9-dd81e2192ca0)
   
Note: The source code is private due to privacy policies. For inquiries, contact:

📧 Email: ngdtuan.dn@gmail.com

🔗 LinkedIn: [Nguyen Tuan](https://www.linkedin.com/in/nguyen-tuan-a2a589128/)

# **3D Real-time PAUT & Robotics Integration – Ultra-Low Latency GPU Processing**
### Phased Array Ultrasound Testing Industry integrating with Robotics
### HPC System Engineering (Industry, Real-Time, GPU Processing)

## **Project Overview**
This project is an example of **HPC System Engineering (Industry, Real-Time, GPU Processing)**, implementing an advanced **real-time 3D Phased Array Ultrasonic Testing (PAUT) system**, seamlessly integrated with robotics and accelerated GPU processing (CUDA). Designed for **industrial Non-Destructive Testing (NDT)**, the system achieves ultra-low latency through highly optimized CUDA processing, custom encoder-free robotic synchronization, and a **High-Performance GPU Data Management & I/O Optimization** for real-time PAUT data streaming.
---

### **Key Features & Innovations**  

#### **1. Real-Time GPU Processing: Ultra-Low Latency**
- Full GPU-based PAUT processing pipeline, eliminating redundant CPU-GPU data transfers.  
- Achieves real-time PAUT inspection at hardware limits **60 MB/s throughput**.  
- **Processes frames 12.5× faster than PAUT hardware requirement (2.5ms → 0.2ms), ensuring ultra-low latency.**  
- Advanced OpenGL + CUDA rendering for high-performance visualization.  

#### **2. Advanced Robotics Integration (Encoder-Free)**
- Custom algorithm synchronizes robotic motion with PAUT scanning without traditional encoders.  
- Adaptive real-time scanning using OpenCV and deep learning, allowing autonomous detection and tracking of objects without pre-defined coordinates.  
- Supports high-speed robotic movement synchronization, reducing scan time while maintaining accuracy.  

#### **3. Optimized CUDA Performance & High-Performance Computing**
- Full parallelization using CUDA Streams and asynchronous pipelines.  
- **GPU-side processing eliminates CPU bottlenecks, reaching real-time PAUT limits.**  
- Minimized host-device memory transfers for reduced latency.  
- Triple-buffered staging technique achieves throughput over **700 MB/s**.  

#### **4. High-Performance Data Management & I/O Optimization**
- Custom PAUT data format replacing HDF5 to minimize I/O overhead.  
- Optimized binary data structure for low-latency memory access and real-time processing.  
- Implements chunked data writing (~10MB per chunk) for efficient large-scale data handling.  
- **Tailored for low-latency robotics & high-speed scanning, outperforming standard industrial storage formats.**  
- **GPU is no longer the bottleneck; PAUT SDK limits data transfer to 60 MB/s.**  

#### **5. Upcoming Kernel-Level Optimization (Ring-0 Driver)**
- Planned Ring-0 kernel driver for direct memory access and reduced system-level data transfer latency.  
- Bypassing traditional OS I/O bottlenecks to achieve sub-millisecond data handling performance.  

---

# Performance Benchmarks
### **Summary**
This benchmark reflects the latest performance of our PAUT-GPU pipeline after optimization.

| **Metric** | **Result** |
|------------|-----------|
| **PAUT Data Throughput** | **60 MB/s (Hardware Limit)** |
| **Total HPC Process Speed** | **0.2 ms** |
| **FrameRate Hz** | **401 Hz (Limited by PAUT hardware)** |
| **Max Achievable Throughput MB/s** | **~750 MB/s (High-Performance GPU Computing)** |
| **Rendering Resolution** | **656 × 1788 (~1.1 MPixels/frame)** |

### **Pipeline Optimization**
- **Double Buffering** implemented → Reduces GPU idle time.
- **triple-buffered staging** enabled → Achieves **max throughput (311 MB/s theoretically)**.
- **Post-processing & Rendering moved to separate threads** → Minimizes blocking.
- **Final bottleneck:** **PAUT SDK (Olympus) limits data transfer to 60 MB/s.**

### Next Steps for Optimization
- The **current limit is hardware-bound**. Further optimization requires **changes in PAUT SDK** or a **faster hardware interface**.
- **GPU is NOT the bottleneck anymore**. Further improvements must focus on **PAUT Data Acquisition speed**.
- Testing with a higher bandwidth data transfer is recommended if new hardware or firmware updates become available.

## **Technologies Used**
- **Programming:** Modern **C++23, CUDA**
- **Real-time Processing:** CUDA, OpenMP, Multi-threading
- **HPC System Engineering:** Industry, Real-Time, GPU Processing ✅
- **Computer Vision & AI:** OpenCV, Deep Learning
- **Robotics Integration:** Custom algorithms for encoder-free robotic control
- **Kernel-Level Optimizations (Upcoming):** Planned Ring-0 driver to optimize PAUT data transfer throughput by reducing Olympus Driver overhead.
- **Data Management & Storage:** Optimized **binary PAUT format, chunked data writing, memory-mapped storage**

## **Applications**
- **High-precision real-time NDT inspection**
- **Autonomous robotics scanning**
- **Advanced industrial inspections requiring minimal latency**
- **AI-driven adaptive scanning for real-time object tracking**

## **Project Status**
- **Solo-developed** over 6 months with mechanical engineering support.
- **Enhanced real-time data processing pipeline** with **optimized I/O and GPU rendering**.
- **Planned future enhancements** with **kernel-level optimizations (Ring-0 Driver)**.
- **Current implementation surpasses** standard industry benchmarks, setting a new standard for **ultra-low latency PAUT processing**.

## **Why This System Stands Out**
- **Achieves real-time PAUT inspection at hardware limits 60Mb/s throughput.**
- **Pioneers full GPU-side processing** to reach the limit latency, touch to High Performance Computing 300Mb/s.
- **Innovative encoder-free robotic synchronization** and **AI-driven adaptive scanning**.
- **Optimized I/O management** for real-time high-speed PAUT data handling.
- **Processes frames 12.5×** faster than the PAUT hardware requirement (2.5ms → 0.2ms), ensuring ultra-low latency.

---
This project pushes the boundaries of real-time industrial inspection, combining **ultra-low latency GPU processing, autonomous robotics integration, and optimized I/O management** into one high-performance system.
