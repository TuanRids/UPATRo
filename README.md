# Real-Time Phased Array Ultrasound: Robotic Integration and Vision Detection

## Results (Ongoing)
![Architecture PAUTVis drawio](https://github.com/user-attachments/assets/5c109c0f-47be-4b25-bf87-4c116c2a1f3c)
https://github.com/user-attachments/assets/10336cc9-0363-4367-a08f-b49187899e87

https://github.com/user-attachments/assets/ecc3c03d-404a-428e-8a4e-52ce408c8e0f

https://github.com/user-attachments/assets/5e93d6a6-586f-4af1-8c2d-9144a7439617

![RealtimePAUT GPU All Mode](https://github.com/user-attachments/assets/ef7d6936-ffc7-44f1-a2c9-dd81e2192ca0)
   
Note: The source code is private due to privacy policies. For inquiries, contact:

📧 Email: ngdtuan.dn@gmail.com

🔗 LinkedIn: [Nguyen Tuan](https://www.linkedin.com/in/nguyen-tuan-a2a589128/)
---
## Real-Time Phased Array Ultrasound (PAUT): GPU-Accelerated Robotic Integration for Industrial NDT

### Project Overview
This project develops a GPU-accelerated real-time Phased Array Ultrasound Testing (PAUT) system integrated with robotic control and simplified vision-assisted positioning, designed specifically for industrial Non-Destructive Testing (NDT). The primary objective is achieving stringent latency and throughput benchmarks essential for high-performance industrial inspections, within hardware-imposed constraints (60 MB/s input rate). Optimized CUDA processing, triple-buffered data streaming, and threshold-based synchronization techniques allow sustained real-time data acquisition from PAUT hardware at 588 Hz (1.7 ms per frame), corresponding to a continuous Ethernet input stream of 60 MB/s.
### Key Features and Technical Innovations

#### 1. GPU-Accelerated Low-Latency Pipeline
- Total GPU-side processing latency, including both memory transfers and kernel execution, averages ~0.22 ms per frame, as measured using GPU-side timestamp counters.
- Data transfers are optimized to <0.03 ms via pinned memory and triple-buffered streaming. For reference, CUDA kernel execution alone averages ~0.15 ms/frame, peaking at ~0.35 ms, significantly outperforming standard PAUT hardware latency (~1.7 ms).
- Asynchronous CUDA execution, triple-buffered streaming, and pinned memory techniques minimize CPU-GPU overhead.
- CUDA-OpenGL interoperability is implemented to enable efficient data visualization with minimal overhead

#### 2. Encoder-Free Robotic Synchronization
- Uses GPU-processed ultrasound signals (stitchID) as triggers to initiate and terminate scanning, reducing dependency on physical encoders.
- Positional synchronization is achieved through threshold-based detection combined with simple start-stop robot motion
- Advanced interpolation techniques planned for minimizing positional discrepancies in multiple robotic scans.

#### 3. Simplified Vision-Assisted Positioning
- Intel RealSense camera provides initial spatial reference points before scans, assisting robot alignment. It does not participate directly in real-time scan synchronization due to inherent latency."

#### 4. Optimized Real-Time Data Management
- Custom binary streaming format replaces traditional formats (e.g., HDF5), optimized specifically for immediate processing and low-latency real-time data handling.
- Chunked data streaming (10 MB chunks) ensures continuous data flow without bottlenecks.

#### 5. PAUT Beamforming Challenges
- Structured CUDA kernel pipeline efficiently handles beamforming interdependencies and non-sequential memory accesses (Ascan → Beamforming → Scanline).

### Performance Benchmarks
- **Input Data Rate:** 60 MB/s (hardware limitation)
- **Frame Rate:** 588 Hz (1.7 ms/frame)
- **Total CPU + GPU Latency:** Avg 0.02 + 0.22 ms/frame (compute + transfer)
- **GPU Kernel Latency:** Avg 0.15 ms/frame, Peak 0.35 ms/frame
- **Data Transfer Overhead:** <0.03 ms/frame (triple-buffered)
- **Internal GPU Throughput:** 8–15 Gb/s (internal GPU memory operations)
- **Current Limitation:** PAUT hardware SDK input rate

**CUDA Kernel Execution Timeline:** 
![image](https://github.com/user-attachments/assets/33cee97e-bc1c-465a-8809-69a8667bff67)

**Detailed GPU Kernel Benchmarks:** 
![image](https://github.com/user-attachments/assets/3f95df1f-d302-4e39-9d82-e8680e1f96ae)
*Note: GPU throughput refers to internal computation throughput distinct from external I/O.*

### Software Architecture
The system utilizes a modular architecture:
- **Frame Management:** Implemented via Factory and Observer patterns, facilitating scalable and maintainable data streaming.
- **Critical Parameter and Class Management:** Singleton patterns with carefully managed mutex locks ensure thread safety and consistency.
- **Feature Organization:** Clearly structured folders enabling modularization and abstraction post-R&D phase, allowing for flexible feature integration and maintenance.

### Coding Standards and Practices
- Developed using modern C++20/23 standards, leveraging RAII, smart pointers, and best practices for robust resource management.
- Raw pointers for CUDA memory explicitly managed within encapsulated wrappers, ensuring resource safety and readability.
- Strict adherence to coding standards, static analysis tools, and careful performance profiling ensures reliability and maintainability.

### Validation and Stability Testing
- Extensive validation across multiple samples, including rigorous tests on LG battery samples, with results reviewed by LG experts.
- PAUT results and performance validated and confirmed by ultrasound domain specialists.
- Continuous stability testing under real-world scanning conditions to ensure performance consistency and system robustness.

### Future Enhancements
- Hardware upgrade planned to surpass current 60 MB/s input limitation.
- Development of Ring-0 drivers to enable direct IO triggering from the Yaskawa controller, improving PAUT-robot synchronization and stitching accuracy.

### Technology Stack
- **Languages:** C++23, CUDA
- **Parallel Computing:** CUDA, OpenMP, Multithreading
- **Visualization:** CUDA-OpenGL Interoperability
- **Ultrasound Equipment:** Olympus X3 Series
- **Vision System:** Intel RealSense, OpenCV
- **Robotics Platform:** Yaskawa YRC 1000 (encoder-free synchronization)
- **Future Optimizations:** Direct GPU memory access via Ring-0 driver

### Applications
- Industrial real-time Non-Destructive Testing (NDT)
- Automated robotic scanning
- Real-time positioning and alignment in industrial environments

### Project Status
- Independently developed over a 6-month period, with collaboration from mechanical engineers.
- Optimized for GPU acceleration, robotic integration, and efficient real-time data streaming

### Summary
This project demonstrates effective GPU integration in robotic PAUT systems for industrial NDT applications. The implementation achieves low GPU kernel latency, efficient encoder-free scanning control, and optimized real-time data streaming within hardware constraints
