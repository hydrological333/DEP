# 🧠 C++ Mini Projects Collection

This repository includes four C++ mini-projects that demonstrate various core programming concepts such as API consumption, object-oriented design, file compression, and networking using multi-threading. Each task is modular and independent, showcasing different aspects of systems-level and application development in C++.

---

## 🌤️ Task 1: Weather Forecasting System

### 📌 Description
This project implements a basic **weather forecasting system** using live data from the [Open-Meteo API](https://open-meteo.com/). The system retrieves current weather information for two locations: **Islamabad** and **Rawalpindi**.

### 🧩 Features
- API integration using **cURL**
- JSON parsing using **jsoncpp**
- Object-oriented structure with:
  - `WeatherVariable` class for weather data
  - `Location` class for city-specific information
  - `WeatherForecastingSystem` class for API fetching

### 🛠 Technologies
- `cURL` for HTTP requests
- `jsoncpp` for JSON parsing

### 🧪 Sample Output
Islamabad
....................
latitude: 33.5406
longitude: 73.1426
Temp: 32.1
Humidity: 45
Wind Speed: 5.6
Precipitation: 0.0
Time Zone: Asia/Karachi
Current Time: 2025-05-31T14:00



---

## 📇 Task 2: Contact Management System

### 📌 Description
A menu-driven **Contact Management System** that allows users to manage contacts through a console interface.

### 🧩 Features
- Add a new contact
- View all contacts
- Delete a contact by name
- Uses object-oriented classes:
  - `Contact` class: holds name and phone number
  - `ContactManager` class: manages the contact list using `std::vector`

### 🧠 Concepts Demonstrated
- Encapsulation and OOP
- Vector manipulation
- String handling
- Interactive user input

---

## 📦 Task 3: File Compression and Decompression

### 📌 Description
This utility implements basic **Run-Length Encoding (RLE)** to compress and decompress files.

### 🧩 Features
- Reads from `input.txt`
- Compresses repeated characters (e.g., `aaaa` → `a4`)
- Writes compressed output to `compressed.txt`
- Decompresses the data and writes to `decompressed.txt`
- Includes error handling using C++ exceptions

### 🧠 Concepts Demonstrated
- File I/O using `fstream`
- Exception handling (`std::runtime_error`)
- String parsing and conversion (`ostringstream`, `istringstream`)

### 📄 Example
Input: aaabbc
Compressed: a3b2c1
Decompressed: aaabbc



---

## 🌐 Task 4: Multi-Threaded Web Server

### 📌 Description
A basic **multi-threaded web server** using Winsock2 for Windows. It listens on port `8080` and serves static HTML files from a `www/` directory.

### 🧩 Features
- Handles multiple clients using threads
- Supports `GET` requests only
- Serves files like `index.html` or any requested file
- Returns `404 Not Found` if file is missing
- Basic HTTP response formatting

### 🛠 Requirements
- Windows OS
- `Winsock2` library (`-lws2_32`)

### ⚙️ Example
Client requests: GET /index.html
Server responds: 200 OK with HTML content

Client requests: GET /notfound.html
Server responds: 404 Not Found
