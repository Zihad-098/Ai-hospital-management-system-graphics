# 🏥 3D Hospital Management System

A 3D hospital walkthrough built with **C++** and **OpenGL (freeglut)** as a Computer Graphics Lab project. You can move a camera around a hospital campus and explore the entrance, the emergency department, the outpatient department, and the patient cabins, with animated ambulances and staff.

![Language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)
![OpenGL](https://img.shields.io/badge/graphics-OpenGL%20%2B%20freeglut-green.svg)
![Platform](https://img.shields.io/badge/IDE-Visual%20Studio%202022-purple.svg)

---

## 📖 About the Project

This project models a complete hospital scene in 3D using only OpenGL primitives (boxes, cylinders, spheres), with lighting, depth testing, and timer-based animation. It is split into four sections:

### 1. Entrance
- Main gate
- Parking area
- Ambulance parking bay
- Reception building
- Waiting area with benches
- Security desk
- Trees and outdoor environment

### 2. Emergency Department (ER)
- Emergency beds with patients
- Wheelchairs
- Medical equipment (IV stand, monitor cart, oxygen tank)
- Emergency doctor and nurse station

### 3. Outpatient Department (OPD)
- Registration desk
- Patient waiting queue (chairs and seated patients)
- Two doctor chambers
- Two consultation rooms with examination tables

### 4. Patient Cabins
- **Single Cabin**: bed, visitor chair, TV, AC, attached bathroom
- **VIP Cabin**: bed, sofa, gold trim, TV, AC, attached bathroom
- **General Ward**: 4 beds with curtain dividers, visitors, shared TV, 2 AC units, attached bathroom

---

## ✨ Features

- 🚑 **Animated ambulance** that drives in from the gate, stops at the bay with a blinking light, then reverses out and loops
- 🚶 **Walking characters**: a visitor, a nurse in the ER, and a nurse patrolling the general ward
- 💡 **Lighting and shading** with `GL_LIGHT0`, color material, and normalized normals
- 🎥 **Free camera** with forward/backward movement, turning, and height control
- 🎨 **Consistent light, realistic hospital color theme**
- 🪑 Detailed props: wall clocks, oxygen outlets, bedside tables, laptops, TVs, AC units, bathrooms

---

## 🎮 Controls

| Key | Action |
|-----|--------|
| `↑` Up Arrow | Move camera forward |
| `↓` Down Arrow | Move camera backward |
| `←` Left Arrow | Turn camera left |
| `→` Right Arrow | Turn camera right |
| `W` | Move camera up |
| `S` | Move camera down |
| `R` | Reset camera |
| `Esc` | Quit |

---

## 🛠 Tech Stack

| Component | Technology |
|-----------|-----------|
| Language | C++ |
| Graphics API | OpenGL, GLU |
| Windowing / Input | freeglut (GLUT) |
| IDE | Visual Studio 2022 (toolset v143) |
| Platform | Windows (x86 / x64) |

---

## 📁 Project Structure

```
AI-Hospital-Management-System/
├── main.cpp                 # Entire 3D scene, lighting, camera, and animation
├── abcd.sln                 # Visual Studio solution
├── abcd.vcxproj             # Visual Studio project file
├── abcd_vcxproj.filters     # Visual Studio filters
└── README.md
```

---

## 🚀 Getting Started

### Prerequisites

- A C++ compiler (Visual Studio 2022 or MinGW / g++)
- **freeglut** installed (OpenGL and GLU come with your system / Windows SDK)

### Option 1: Visual Studio (Windows)

1. Clone the repository
   ```bash
   git clone https://github.com/Zihad-098/AI-Hospital-Management-System.git
   ```
2. Open `abcd.sln` in Visual Studio 2022.
3. Install freeglut, for example with vcpkg:
   ```bash
   vcpkg install freeglut:x64-windows
   vcpkg integrate install
   ```
   Alternatively, download freeglut manually and add its `include` folder to *Additional Include Directories* and its `lib` folder to *Additional Library Directories* in the project properties. Then add `freeglut.lib` under *Linker → Input → Additional Dependencies*.
4. Select **Debug / Release** and **x64**, then press **Ctrl + F5** to run.

> Make sure `freeglut.dll` is next to the built `.exe`, or in your system PATH.

### Option 2: MinGW (Windows)

```bash
g++ main.cpp -o hospital.exe -lfreeglut -lopengl32 -lglu32
./hospital.exe
```

### Option 3: Linux

```bash
sudo apt install freeglut3-dev
g++ main.cpp -o hospital -lGL -lGLU -lglut
./hospital
```

---

## 🖼 Screenshots

<img width="840" height="423" alt="image" src="https://github.com/user-attachments/assets/a8690ab1-2d56-4aa0-91e0-9eb6340dbcd4" />
<img width="1530" height="459" alt="image" src="https://github.com/user-attachments/assets/664aa96c-1b8b-4a6a-b505-8b81457190d1" />
<img width="1735" height="564" alt="image" src="https://github.com/user-attachments/assets/8c230aaf-416c-45c8-b3da-3d4a0f8c39d1" />
<img width="1858" height="647" alt="image" src="https://github.com/user-attachments/assets/8c12b57c-6d79-4f58-bdb7-2208ffbfdb64" />





| Entrance | Emergency Department |
|----------|----------------------|
| ![Entrance](screenshots/entrance.png) | ![ER](screenshots/er.png) |

| OPD | Patient Cabins |
|-----|----------------|
| ![OPD](screenshots/opd.png) | ![Cabins](screenshots/cabins.png) |

---

## 🗺 Future Improvements

- [ ] Add textures to walls, floors, and signs
- [ ] Add mouse-based camera control
- [ ] Add more departments (ICU, operation theater, pharmacy)
- [ ] Add sound effects for the ambulance
- [ ] Add day/night lighting

---

## 🎓 Academic Note

Developed as a **Computer Graphics Lab project**.

---

## 👨‍💻 Author

**Zihad**
- GitHub: [@Zihad-098](https://github.com/Zihad-098)

⭐ If you like this project, please give it a star!
