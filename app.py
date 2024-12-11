import streamlit as st
import pandas as pd

# Function for FIFO Page Replacement
def fifo(pages, frames):
    frame = [-1] * frames
    count = 0
    page_faults = 0
    data = {"Page": []}

    for i in range(frames):
        data[f"Frame {i+1}"] = []
    data["Status"] = []

    for page in pages:
        if page not in frame:
            frame[count] = page
            count = (count + 1) % frames
            page_faults += 1
            status = "Page Fault"
        else:
            status = "Hit"

        data["Page"].append(page)
        for i in range(frames):
            data[f"Frame {i+1}"].append(frame[i] if frame[i] != -1 and status == "Page Fault" else "")
        data["Status"].append(status)

    return pd.DataFrame(data), page_faults


# Function for LRU Page Replacement
def lru(pages, frames):
    frame = [-1] * frames
    last_used = [-1] * frames
    page_faults = 0
    data = {"Page": []}

    for i in range(frames):
        data[f"Frame {i+1}"] = []
    data["Status"] = []

    for i, page in enumerate(pages):
        if page not in frame:
            lru_index = last_used.index(min(last_used)) if -1 not in frame else frame.index(-1)
            frame[lru_index] = page
            page_faults += 1
            status = "Page Fault"
        else:
            status = "Hit"

        last_used = [i if f == page else t for t, f in zip(last_used, frame)]
        data["Page"].append(page)
        for j in range(frames):
            data[f"Frame {j+1}"].append(frame[j] if frame[j] != -1 and status == "Page Fault" else "")
        data["Status"].append(status)

    return pd.DataFrame(data), page_faults


# Function for Optimal Page Replacement
def optimal(pages, frames):
    frame = [-1] * frames
    page_faults = 0
    data = {"Page": []}

    for i in range(frames):
        data[f"Frame {i+1}"] = []
    data["Status"] = []

    for i, page in enumerate(pages):
        if page not in frame:
            if -1 in frame:
                replace_index = frame.index(-1)
            else:
                future_use = [
                    pages[i+1:].index(f) if f in pages[i+1:] else float("inf")
                    for f in frame
                ]
                replace_index = future_use.index(max(future_use))
            frame[replace_index] = page
            page_faults += 1
            status = "Page Fault"
        else:
            status = "Hit"

        data["Page"].append(page)
        for j in range(frames):
            data[f"Frame {j+1}"].append(frame[j] if frame[j] != -1 and status == "Page Fault" else "")
        data["Status"].append(status)

    return pd.DataFrame(data), page_faults


# Streamlit App
st.title("Page Replacement Algorithms")
st.sidebar.header("Input Parameters")

# User Inputs
n = st.sidebar.number_input("Number of Pages", min_value=1, max_value=50, value=10)
frames = st.sidebar.number_input("Number of Frames", min_value=1, max_value=10, value=3)
pages = st.sidebar.text_input("Page Reference Sequence (comma-separated)", "7,0,1,2,0,3,0,4,2,3")

# Convert page reference sequence to list of integers
pages = [int(p.strip()) for p in pages.split(",")]

# Algorithm Selection
algorithm = st.sidebar.selectbox("Choose Algorithm", ["FIFO", "LRU", "Optimal"])

# Run Selected Algorithm
if st.sidebar.button("Run Algorithm"):
    if algorithm == "FIFO":
        result, faults = fifo(pages, frames)
    elif algorithm == "LRU":
        result, faults = lru(pages, frames)
    elif algorithm == "Optimal":
        result, faults = optimal(pages, frames)

    # Display Results
    st.subheader(f"{algorithm} Page Replacement Results")
    st.write(f"**Total Page Faults: {faults}**")
    st.dataframe(result.set_index("Page"))
