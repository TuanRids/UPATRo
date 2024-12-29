
#pragma once
// https://www.olympus-ims.com/en/.downloads/download/?file=285216846&fl=en_US Catalogue

// List of Documentational Notes
void Class_Relationships();
void Design_principles();
void Diagrams();
void Performance();
void Specific_FrameMouse();
void stateDiagram();

    // Class Relationships
     void Class_Relationships()
    {
        /*
        Class Diagram & Design Patterns:
            --------------------------------
            Root
            ├── statuslogs (Singleton pattern)
            │   ├── + getinstance()
            │   └── + addLogMessage()
            │
            ├── nFactoryFrame (Factory pattern)
            │   ├── + createLogFrame()
            │   └── + createGraphicsFrame()
            │
            ├── nFrame (Composite pattern)
            │   ├── + createFrame()
            │   └── Inherited by:
            │       ├── nLogFrame
            │       │   ├── + createFrame()
            │       │   └── + update()
            │       └── nGraphicsFrame
            │           ├── + createFrame()
            │           └── + update()
            │
            ├── UIFrame (Singleton pattern)
            │   ├── + getInstance()
            │   └── + mainloop()
            │
            ├── nObserver (Observer pattern)
            │   ├── + update()
            │   └── Implemented by:
            │       ├── nLogFrame
            │       └── nGraphicsFrame
            │
            └── ObserverMgr (Observer pattern)
                ├── nSubject
                │   ├── + addObserver(nObserver)
                │   └── + notify()
                └── Notifies Observers:
                    ├── nLogFrame
                    └── nGraphicsFrame

            Sequence Diagram:
            -----------------
            Root
            ├── Program Start
            │   ├── MainLoop calls UIFrame
            │   │   └── UIFrame creates frames via nFactoryFrame
            │   │       ├── createLogFrame()
            │   │       │   └── nLogFrame created
            │   │       └── createGraphicsFrame()
            │   │           └── nGraphicsFrame created
            │   └── UIFrame calls notify() on nSubject
            │
            ├── Notification Phase
            │   ├── nSubject notifies:
            │   │   ├── nLogFrame
            │   │   │   └── nLogFrame calls update()
            │   │   └── nGraphicsFrame
            │   │       └── nGraphicsFrame calls update()
            │
            └── Observers Update
                ├── nLogFrame updates display
                └── nGraphicsFrame updates display
        */
    }
    // Design Patterns & Principles
    void Design_principles()
    {
        /*
    +----------------------------------+       +----------------------------------+
    |           mainwindow (UIFrame)   |       |        ObserverMgr               |
    |----------------------------------|       |----------------------------------|
    | +getInstance(): UIFrame          |<----->| +notify(x,y,z): void             |
    | +mainloop(): int                 |       | +addObserver(nObserver): void    |
    | +refreshxyz(x,y,z): void         |       +----------------------------------+
    | +logical(nFrame*): void          |
    | +receiveData(): void             |
    | +sendDataToProcessor(): void     |
    +----------------------------------+
            |           ^                +----------------------------------+
            |           |                |          AscanProcessor          |
            |           |                |----------------------------------|
            |<----------+--------------->| +analyze(nFrame*): bool          |
            v                            | +processData(): void             |
    +-------------------+----+           +----------------------------------+
    |       FactoryMgr        |
    |-------------------------|              +----------------------------+
    | +LogFrame()           |       nFrame               |
    | +GraphicsFrame()     |----------------------------|
    | +BscanFrame()        | +CreateColorPalette(): void|
    +-----------------------------------------| +setScandat(): void        |
                                              +----------------------------+
                    ^       ^           ^               ^       ^
                    |       |           |               |       |
    +---------------+--+ +--+-----------+-------+   +----+-------+-----+
    |   nLogFrame       | |  CscanFrame (nFrame) |   | BscanFrame (nFrame)|
    |-------------------| |----------------------|   |--------------------|
    | +createFrame(): QWidget| +createFrame(): QWidget| +createFrame(): QWidget|
    | +update(): void        | +update(): void        | +update(): void        |
    +----------------------- +----------------------- +----------------------+
    */
    }

    // Class Diagram & Design Patterns
    void Diagrams()

    {
        /*


        --------------------------------
        +-----------------+              +--------------------------+              +--------------------+
        |   statuslogs    |              |       nFactoryFrame      |              |       nFrame       |
        |-----------------|              |------------------------- |              |--------------------|
        | + getinstance() |<-- Singleton | + createLogFrame()       |<-- Factory   | + createFrame()    |<-- Composite
        | + addLogMessage |              | + createGraphicsFrame()  |              |                    |
        +-----------------+              +--------------------------+              +--------------------+
                ^                                                                 /                    \
                |                                                                /                      \
                |                                                               /                        \
        +----------------------+                                    +--------------------+         +----------------------+
        |      UIFrame         |                                    |    nLogFrame       |         |    nGraphicsFrame    |
        |----------------------|                                    |--------------------|         |----------------------|
        | + getInstance()      |<-- Singleton                       | + createFrame()    |         | + createFrame()      |
        | + mainloop()         |                                    | + update()         |         | + update()           |
        +----------------------+                                    +--------------------+         +----------------------+
                                                                            |                                 |
                                                                    Implements Observer               Implements Observer
                                                                            |
                                                                    +---------------------+
                                                                    |    nObserver        |
                                                                    |---------------------|
                                                                    | + update()          |
                                                                    +---------------------+

        ObserverMgr:
        +-----------------------------------+
        |      nSubject (ObserverMgr)       |
        |-----------------------------------|
        | + addObserver(nObserver)          |
        | + notify()                        |
        +-----------------------------------+
                                |
                          Notifies Observers
                                |
                 +--------------------------+
                 |                          |
          +--------------------+    +----------------------+
          |    nLogFrame       |    |    nGraphicsFrame    |
          +--------------------+    +----------------------+

        Sequence Diagram:
        -----------------
        1. Program Start:
        +--------------+      +----------------+      +----------------------+      +----------------------+
        |   MainLoop   |      |     UIFrame    |      |       nFactoryFrame  |      |      nLogFrame       |
        +--------------+      +----------------+      +----------------------+      +----------------------+
               |                    |                         |                            |
               |                    |    createLogFrame()     |                            |
               |                    +------------------------>+                            |
               |                    |                         +--------------------------->+
               |                    |                         |                            |
               |                    |    createGraphicsFrame()|                            |
               |                    +------------------------>+                            |
               |                    |                         +--------------------------->+
               |                    |                         |                            |
               |------------------- notify() --------------------------------------------------->
        2. nLogFrame and nGraphicsFrame are updated:
        +--------------------+          +----------------------+           +----------------------+
        |    nSubject        |          |      nLogFrame       |           |   nGraphicsFrame      |
        +--------------------+          +----------------------+           +----------------------+
               |                           |                               |
               |------ notifyObservers() --+                               |
               |                           |------- update() --------------+
               |                           |                               |-------- update() -----+
               */
    }

    void stateDiagram()

    {
        /*
        [Initial State] ----------------------> [Waiting for Update]
                                                 |  (notify() called)
                                                 v
                                      [Receiving Data from nSubject]
                                                 |
                                                 v
                                    [Processing Data in nLogFrame]
                                                 |
                                                 v
                                        [Update nGraphicsFrame]
                                                 |
                                                 v
                               [Rendering Graphics in nGraphicsFrame]
                                                 |
                                                 v
                                 [Return to Waiting for Update State]
                                 (notify() called or data change detected)
        ---------------------------------------------------------
        Error State:
           - If data processing or rendering fails, transition to
             [Error State] and log the issue using StatusLogs.
        }
        */
    }

    void Performance()
    {
        /*
        Performance Considerations:


        1. CPU-GPU Workload Division:
           - CUDA for compute-heavy tasks
           - Vulkan for render-heavy tasks (e.g., 3D rendering).
           - Ensure asynchronous data transfer between CPU and GPU.

        2. CUDA-Vulkan Interop:
           - Use CUDA-Vulkan Interop to share resources directly (zero-copy).
           - Avoid data transfer overhead with mapped memory.

        3. GPU Memory Management:
           - Use Unified Memory to share data between CPU and GPU.
           - Implement memory pooling in Vulkan to reduce memory allocation overhead.

        4. Render Pipeline Optimization:
           - Prebuild Vulkan pipeline state objects (PSO) for faster execution.
           - Reuse command buffers and descriptor sets to minimize setup cost.

        5. Scalability:
           - Use Dynamic Level of Detail (LOD) to reduce polygon count.
           - Implement Frustum Culling to avoid rendering unnecessary objects.
           - Take advantage of Vulkan’s multithreading for parallel rendering.

        6. Real-time Rendering:
           - Employ Vulkan async compute to handle continuous data streams.
           - Reduce latency with low-latency rendering (reduce buffer and queue depth).

        7. Error Handling:
           - Use cudaGetLastError() for error checks in CUDA.
           - Enable Vulkan Validation Layers to catch runtime issues.

           */
    }
    // specific Observer Pattern, Factory Pattern & Mouse Event Handling
    void Specific_FrameMouse()
    {
        /*
    Observer Pattern - Core Mechanism for Frame Updates: The observer pattern ensures that when an event (like a mouse click) occurs, the observer notifies all relevant frames
            (Ascan, Bscan, Cscan). This ensures synchronization across different views without direct dependencies between them.

            [Main Frame] --> [Observer] --> [Ascan Frame]
                              |--> [Bscan Frame]
                              |--> [Cscan Frame]

    Mouse Event Handling in ZoomableGraphicsView
            [ZoomableGraphicsView]
            |--> Left Click: Triggers observer to update all frames
            |--> Left + Drag: Frame-specific updates, skipping local frame for efficiency
            |--> Middle Click: Activates panning mode
        Left Click: Calls the observer to refresh all frames.
        Left Drag: The current frame does not refresh to save resources, while other frames are notified to update based on isPanning status.
        Middle Click (Panning): Allows users to navigate the frame without modifying the content.

    Display Mouse Position with Tooltip: Whenever the mouse moves, the current position (X, Y, Z) is displayed in a tooltip
        [Mouse Move Event] --> [Tooltip Display] --> X, Y, Z Coordinates Shown

    Distinguishing Local and Global Panning States
        [isPanning - Global State] --> Manages updates across frames
        [isLocalPanning - Local State] --> Manages updates within the current frame

    Factory Pattern - Creating and Managing Frames: Using the factory pattern, each frame (Ascan, Bscan, Cscan) is created in a modular and extensible manner
        [UIManager] --> [Factory] --> [Ascan, Bscan, Cscan Frames]

    Menu and Settings Management: A settings dialog is accessed via the menu bar, allowing users to adjust system settings such as resolution or toggling the Cscan layer
        [MenuBar] --> [Settings Dialog] --> Modify Resolution, Cscan Layer
    */
    }