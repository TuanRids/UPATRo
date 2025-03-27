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
## Real-Time Phased Array Ultrasound (PAUT): GPU-Accelerated Robotic Integration for Industrial NDT

### Project Overview
This project develops a GPU-accelerated real-time Phased Array Ultrasound Testing (PAUT) system integrated with robotic control and simplified vision-assisted positioning, specifically designed for industrial Non-Destructive Testing (NDT). The primary objective is achieving stringent latency and throughput benchmarks essential for high-performance industrial inspections, constrained by hardware limitations (60 MB/s input rate). Leveraging optimized CUDA kernels, CUDA Graphs, triple-buffered streaming, and threshold-based synchronization techniques, the system sustains real-time data acquisition from PAUT hardware at 588 Hz (1.7 ms/frame), corresponding to a continuous Ethernet input stream of 60 MB/s.

### Key Features and Technical Innovations

#### 1. GPU-Accelerated Low-Latency Pipeline
- Total GPU-side processing latency averages ~0.15 ms/frame (core kernel pipeline: `AscanProcessing` + `[MakeBView/computeMax]` + `CView`).
- Data transfers optimized (<0.03 ms/frame) via pinned memory and enhanced triple-buffering techniques.
- CUDA Graphs integration stabilizes kernel execution, minimizing overhead and further reducing peak latency.

#### 2. Encoder-Free PAUT Synchronization
- GPU-generated ultrasound signals in PAUT by using (`stitchID`) trigger, combined with robotic start-stop linear operations, eliminating physical encoder dependency.
- Threshold-based detection achieves precise positional synchronization, simplifying robotic motion.
- Planned interpolation improvements via IO board and Ring-0 driver integration for precise hardware-level triggering

#### 3. Simplified Vision-Assisted Positioning
- Intel RealSense camera provides initial spatial reference for robotic alignment without direct real-time synchronization due to latency constraints.

#### 4. Optimized Real-Time Data Management
- Custom binary streaming format optimized for immediate processing and minimal latency.
- Continuous, chunked data streaming (10 MB chunks) maintains consistent throughput without bottlenecks.

#### 5. PAUT Beamforming Challenges
- Structured CUDA kernel pipeline efficiently resolves beamforming interdependencies and complex memory access patterns (`Ascan → Beamforming → Scanline`).

### CUDA Optimization Techniques

- **CUDA Graphs**: Reduce kernel launch overhead and ensure stable multi-stream execution with predictable latency.  
- **Triple Buffering**: Masks CPU-GPU transfer delays, maintaining uninterrupted processing.  
- **Multi-Stream Execution**: Overlapping stages across `compute1`, `compute2`, and `compute5` in graph improves concurrency.  
- **Pinned Memory**: Enables fast, async data transfers between host and device.  
- **Memory Reuse**: Avoids allocation overhead via pooled buffers.  
- **Event Synchronization**: Maintains stage ordering without global sync.  
- **Thread Padding**: Prevents underutilization in small-input scenarios.  
- **OpenGL Interop**: Renders directly from GPU without unnecessary transfers.  
- **Modular Kernel Design**: Clear separation of stages simplifies tuning and maintenance.
- **GPU processing time (~0.15 ms) is already >10× faster than the 1.7 ms frame interval. Further tuning** (e.g., coalesced access, throughput maximization) **was evaluated but deferred due to low impact on critical paths.
Priority was given to architectural gains** (e.g., triple buffering, streams, memory pooling, CUDA Graphs) **which offered higher return on complexity and stability..**
---


### Performance Benchmarks
- **Input Data Rate:** 60 MB/s (hardware limitation)
- **Frame Rate:** 588 Hz (1.7 ms/frame)
- **GPU Kernel Latency:** Avg 0.15 ms/frame (core kernels, Graphs)
- **Data Transfer Overhead:** <0.03 ms/frame (triple-buffered)
- **Current Limitation:** PAUT hardware SDK input rate

**CUDA Kernel Execution Timeline:**  
![image](https://github.com/user-attachments/assets/c625d4c3-2472-4a7b-85ff-b221111d80d0)

**Detailed GPU Kernel Benchmarks:**  
![image](https://github.com/user-attachments/assets/da55fed1-bbdc-43ad-94e5-417b3e12cbec)
*Note: GPU throughput refers to internal computation throughput distinct from external I/O.*

### Software Architecture
The system employs modular architecture:
- **Frame Management:** Factory and Observer patterns for scalable data streaming.
- **Critical Parameter Management:** Singleton patterns with mutex locks for thread-safe operation.
- **Feature Organization:** Clear, modular folder structure enabling flexible integration and simplified maintenance.

### Visualization and Rendering Techniques
Multiple visualization contexts based on latency, synchronization, and rendering priority:
- **Qt3D:** Visualizes robot positions/trajectories, facilitating synchronization and scene management.
- **QOpenGLWindow (separate context):** Real-time primary ultrasound view (`SView`) at highest frequency.
- **QOpenGLWidget (shared context):** Secondary views (`AView`, `BView`, `CView`) optimized for GPU memory efficiency.
- **Separate Context for Vision Integration:** Planned triple-buffered OpenGL context for YOLOv8 vision processing.

### Coding Standards and Practices
- C++23 and CUDA development emphasizing RAII, smart pointers, and encapsulated CUDA memory management.
- Adherence to coding standards, static analysis, and rigorous performance profiling ensures robust system performance.

### Validation and Stability Testing
- Rigorous testing with LG battery samples and industrial validation by ultrasound domain experts.
- Continuous real-world stability testing to ensure reliable performance under operational conditions.

### Future Enhancements
- Planned hardware upgrades to exceed current 60 MB/s limitation.
- Development of Ring-0 drivers for direct IO triggering from Yaskawa controller, enhancing synchronization accuracy.

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

This system was independently designed and implemented from low-level PAUT SDK integration to GPU acceleration and robotic coordination, within a 7-month development cycle.


