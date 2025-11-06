🧠 Mini Search Engine (C Language)

A command-line **Mini Search Engine** built in C for efficient keyword searching across multiple text files.  
It uses **Trie (Prefix Tree)** data structure to index words from files and provides search, export, and indexing features.

---

## ⚙️ Features

| Feature | Description |
| --- | --- |
| ✅ File Reading | Reads multiple `.txt` files from a folder |
| ✅ Tokenization | Splits text into clean words, ignoring punctuation & stopwords |
| ✅ Trie-Based Indexing | Efficient word storage and lookup |
| ✅ Search Functionality | Finds all files containing a given word |
| ✅ Frequency Tracking | Counts how many times a word appears per file |
| ✅ Export Index | Saves the full word–file mapping to a `.txt` file |
| ✅ Display Full Index | Prints all indexed words with file references |
| ✅ User-Friendly CLI | Simple interactive menu system |

---

## 📂 Project Structure

```
MiniSearchEngine/
│
├── include/
│ ├── utils.h
│ ├── index.h
│ └── search_engine.h
│
├── src/
│ ├── utils.c
│ ├── index.c
│ ├── search_engine.c
│ └── main.c
│
├── data/
│ ├── file1.txt
│ ├── file2.txt
│ └── ... (more text files)
│
├── bin/
│ └── search_engine.exe
│
└── README.md
```

---

## 🧑‍💻 How to Compile and Run

### 1️⃣ Compile

```bash
gcc src/*.c -o bin/search_engine
```

### 2️⃣ Run

**Windows:**

```bash
.\bin\search_engine data\
```

---

### 📜 Example Usage

```
--- Starting File Processing for: data\ ---
--- File Processing Complete ---

--- Indexing Complete ---
1. Search a word
2. Show full index
3. Export index to file
4. Exit
Enter your choice: 1
Enter a word to search: computer

Results for 'computer':
 - file1.txt (2)
 - file2.txt (1)

```

---

## 🧩 Team Roles and Contributions

| Member | Role | Responsibilities |
| --- | --- | --- |
| **Member 1: Sunidhi Singh** | File Reader & Tokenizer | Implemented file scanning, stopword filtering, and cleaned input |
| **Member 2: Pratyush Jha** | Index Builder | Developed trie-based indexing, frequency counting, and index export |
| **Member 3: Khushi Kumari** | Search & UI Enhancer | Improved search experience, sorted results, and added user interface |

---

## 🧱 Data Structures Used

- **Trie (Prefix Tree):**  
  For storing and efficiently searching words.
  
- **Linked List:**  
  Used inside each Trie node to maintain the list of files containing that word.
  

---

## 🧠 Future Enhancements

- Implement phrase-based search (e.g., “data structures”)
  
- Add support for `.pdf` or `.docx` parsing
  
- Introduce ranking by word frequency and file length
  
- Add graphical user interface (GUI)
  

---

## 🏁 Conclusion

This project demonstrates **efficient text search** using **Data Structures in C**.  
It simulates the core functionality of a search engine at a smaller scale, combining **tokenization, indexing, and searching** under one interactive console program.

---

## 📅 Project Info

- **Course:** Data Structures (B.Tech CSE – 2nd Year, GGSIPU)
  
- **Language:** C
  
- **Submitted By:** Team MiniSearchEngine
  
  - Sunidhi Singh (Member 1)
    
  - Pratyush Jha (Member 2)
    
  - Khushi Kumari (Member 3)
