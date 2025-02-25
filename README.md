# Page Replacement Algorithms

## Overview
This project implements and visualizes three common page replacement algorithms used in operating systems for memory management: **First-In-First-Out (FIFO), Least Recently Used (LRU), and Optimal Page Replacement**. The goal is to analyze their performance in terms of page faults when handling a given sequence of page references.

## Features
- **FIFO Algorithm**: Replaces the oldest page in memory.
- **LRU Algorithm**: Replaces the least recently used page.
- **Optimal Algorithm**: Replaces the page that will not be used for the longest time in the future.
- **Interactive UI**: Built using **Streamlit** for an easy-to-use interface.
- **Visual Representation**: Displays frame contents and page hit/miss status.

## Installation
### Prerequisites
Ensure you have the following installed:
- Python 3.x
- pip

### Dependencies
Install the required dependencies using:
```sh
pip install streamlit pandas
```

## Usage
1. Run the application:
```sh
streamlit run app.py
```
2. Enter the **number of pages**, **number of frames**, and the **page reference sequence**.
3. Select an algorithm (**FIFO, LRU, or Optimal**).
4. Click "Run Algorithm" to view results.

## File Structure
- `2.c`: C implementation of FIFO, LRU, and Optimal page replacement algorithms.
- `app.py`: Python-based Streamlit application for visualizing the algorithms.
- `abstract.txt`: Project abstract explaining the methodology and results.

## Technologies Used
- **Streamlit**: For UI visualization.
- **Pandas**: For structuring and displaying results.
- **Python & C**: Core programming languages for implementation.

## Future Enhancements
- Add more page replacement algorithms (e.g., MRU, Second-Chance).
- Provide graphical visualization of memory states over time.
- Implement real-time performance comparisons.
