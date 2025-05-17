# Ski Resort Weather Forecast ❄️🗻

C-based weather forecasting system for ski resorts. Processes weekly temperature and rainfall data from a file and extracts insights like:

- Min/max temperatures per resort
- Forecast of snow conditions
- Resort filtering by snow prediction

---

## 🔧 Technologies

- Language: **C (ISO C90 compatible)**
- Build: `gcc forecast.c main.c -o forecast`
- Run: `./forecast`
- Input: Plain `.txt` file with resort name and 7 pairs of temperature/precipitation values

---

## 📁 Project Structure

- `forecast.h` – Constants, types (`enum`, `struct`) and function declarations
- `forecast.c` – Core logic (data loading, temperature conversion, condition evaluation)
- `main.c` – Input/output and user interaction

---

## ✅ Implemented Features

### 1. **Data Loading**
Parses ski resort weather data from a text file into a structured array.

### 2. **Temperature Conversion**
Supports both Celsius and Fahrenheit, based on user input.

### 3. **Extreme Temperature Detection**
Calculates the minimum and maximum temperature forecast for each resort.

### 4. **Snow Condition Evaluation**
Flags snowy weeks based on temperature (≤ 0 °C) and rainfall (≥ 10 mm).

### 5. **Resort Filtering**
Builds a new table with only the resorts that are likely to have snow.

---

## 🧠 Key Concepts

- Struct arrays and nested data structures
- Pointers and pass-by-reference
- File I/O with `fscanf`/`fgets` and buffer management
- Conditional logic and user interaction
- Enum-based configuration
