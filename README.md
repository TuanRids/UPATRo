# 3D PAUT Visualization and Real-time Robotics Integration


## Results (Ongoing)

https://github.com/user-attachments/assets/10336cc9-0363-4367-a08f-b49187899e87

https://github.com/user-attachments/assets/ecc3c03d-404a-428e-8a4e-52ce408c8e0f

https://github.com/user-attachments/assets/5e93d6a6-586f-4af1-8c2d-9144a7439617

![RealtimePAUT GPU All Mode](https://github.com/user-attachments/assets/ef7d6936-ffc7-44f1-a2c9-dd81e2192ca0)
   
Note: The source code is private due to privacy policies. For inquiries, contact:

📧 Email: ngdtuan.dn@gmail.com

🔗 LinkedIn: [Nguyen Tuan](https://www.linkedin.com/in/nguyen-tuan-a2a589128/)
---
# **3D Real-time PAUT & Robotics Integration – Ultra-Low Latency GPU Processing**  
### **Phased Array Ultrasound Testing (PAUT) with High-Performance GPU Acceleration**  

## **Project Overview**  
This project demonstrates **real-time 3D PAUT scanning with GPU acceleration**, integrated with robotics for **ultra-low latency industrial Non-Destructive Testing (NDT)**. By optimizing **CUDA processing, robotics synchronization, and I/O**, the system reaches **2.91 Gb/s throughput** and **401 Hz framerate**, significantly outperforming standard PAUT hardware.  

---

### **Key Features & Innovations**  

#### **1. Ultra-Low Latency Real-Time GPU Processing**  
- **Fully optimized CUDA pipeline** → Removes CPU bottlenecks and redundant host-device transfers.  
- **Real-time PAUT scanning at 60 MB/s (hardware limit)**, **70x ~ 120x faster than PAUT hardware requirements (2.5ms to 0.02 ~ 0.029 ms)**.  
- Advanced OpenGL + CUDA rendering for seamless visualization.  

#### **2. Robotics Integration (Encoder-Free Synchronization)**  
- **No physical encoder required** → Synchronizes robotic motion with PAUT using real-time image analysis.  
- **AI-driven adaptive scanning** → Automatically detects and tracks objects, reducing scan time.  
- **Full robotic synchronization with real-time adjustments**.  

#### **3. Optimized CUDA Performance for HPC**  
- **GPU-side computation eliminates CPU overhead**.  
- **Triple-buffered staging achieves 5 ~ 7.3Gb/s throughput**.  
- **Minimized memory transfers** using pinned memory & asynchronous CUDA streams.  

#### **4. High-Performance Data Management & I/O Optimization**  
- Custom PAUT binary format → Replaces HDF5 for **low-latency access**.  
- **Efficient data streaming & chunked writing (10MB chunks)** for real-time processing.  
- **GPU is no longer the bottleneck** → Limited by PAUT SDK (60 MB/s).  

#### **5. PAUT Dependency Challenges on GPU**  
**PAUT has high computational dependency, making it difficult to fully parallelize on CUDA:**  
 - **Beamforming dependency:** Each beam relies on adjacent beam data for interpolation.  
 - **Memory access bottleneck:** PAUT data is not sequential, leading to non-coalesced GPU memory access.  
 - **Synchronization overhead:** Processing must be staged (Ascan → Beamform → Scanline) to avoid data conflicts.  

---

## **Performance Benchmarks**  
| **Metric** | **Result** |  
|------------|-----------|  
| **CPU/GPU** | **i7 14700, RTX 4060Ti. Throughput 100%** |  
| **PAUT Data Throughput** | **60 MB/s (Hardware Limit)** |  
| **Total GPU Processing Time** | **~ 0.02 - 0.029 ms** |  
| **FrameRate** | **401 Hz (PAUT-limited)** |  
| **Running Throughput** | **5 ~ 7.3 Gb/s** |  
| **Rendering Resolution** | **656 × 1788 (~1.1 MPixels/frame)** |  

---

## **Pipeline Optimizations**  
✔ **Double Buffering** → Reduces GPU idle time.  
✔ **Triple-buffered staging** → Achieves **5 Gb/s ~ 7.3 Gb/s throughput**.  
✔ **Post-processing & Rendering moved to separate threads** → Minimizes blocking.  
✔ **Final bottleneck:** **PAUT SDK limits data transfer to 60 MB/s.**  

## **Next Optimization Steps**  
➡ The **GPU is no longer the bottleneck**, future improvements focus on **faster PAUT hardware**.  
➡ **Planned Ring-0 driver optimization** → Bypasses OS-level I/O for sub-millisecond transfers.  

---

## **Technologies Used**  
- **Programming:** Modern **C++23, CUDA**  
- **Real-time Processing:** CUDA, OpenMP, Multi-threading  
- **HPC System Engineering:** Low-latency GPU computing  
- **Computer Vision & AI:** OpenCV, Deep Learning  
- **Robotics Integration:** Custom encoder-free control algorithms  
- **Kernel-Level Optimizations (Planned):** Ring-0 driver for **direct GPU access**  

## **Applications**  
 - **Real-time industrial NDT inspection**  
 - **Autonomous robotic scanning**  
 - **AI-driven adaptive object tracking**  

---

## **Project Status**  
✔ **Solo-developed over 6 months** with mechanical engineering support.  
✔ **Optimized for real-time GPU processing, robotics, and low-latency data management.**  
✔ **Future plans include** kernel-level optimization (Ring-0) to enhance PAUT data throughput.  

---

## **Summary**  
This project delivers **ultra-low latency PAUT scanning** through **HPC GPU optimization**, **autonomous robotic integration**, and **high-speed data streaming**—pushing the boundaries of real-time industrial inspection. 🚀
