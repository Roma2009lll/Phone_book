# 📚 Hash Table Phonebook

Phonebook application implemented using **Hash Table** data structure with **Chaining** collision resolution in C.

## ✨ Features

- ✅ **Fast Search** - O(1) average time complexity
- ✅ **Add/Delete Contacts** - Name, Phone, Email
- ✅ **QuickSort** - Display contacts alphabetically
- ✅ **Import/Export** - Save/Load contacts from file
- ✅ **Statistics** - View collisions, load factor, distribution
- ✅ **Test Data Generator** - Generate hundreds of contacts instantly
- ✅ **Prefix Search** - Find contacts by name prefix
- ✅ **Visualization** - See hash table distribution

## 🚀 Quick Start

### Compilation

**Windows (MSVC):**
```bash
cl phonebook.c
phonebook.exe
```

**Linux/Mac (GCC):**
```bash
gcc phonebook.c -o phonebook
./phonebook
```

## 📖 Usage
```
+========================================+
|    PHONEBOOK (Hash Table)             |
+========================================+
Contacts: [0]
1. Add Contact
2. Search Contact
3. Delete Contact
4. Show All Contacts (Sorted)
5. Statistics
6. Export to File
7. Import from File
8. Generate Test Data
9. Search Contact by prefix
10. Visualize Distribution
0. Exit
```

### Example: Adding Contacts
```
>> 1
Enter name: John Doe
Enter phone: 555-1234
Enter email: john@example.com
Contact added successfully
```

### Example: Generating Test Data
```
>> 8
How many contacts to generate? 100
Generated [100] contacts successfully!
```

### Example: Statistics
```
>> 5
===== HASH TABLE STATISTICS =====
Table size: 500
Total elements: 100
Empty slots: 425
Collisions: 15
Longest chain: 3
Load factor: 0.20
=================================
```

## 🏗️ Implementation Details

### Hash Function
- **Algorithm:** DJB2
- **Time Complexity:** O(1)
```c
hash = 5381
for each char c in string:
    hash = hash * 33 + c
return hash % table_size
```

### Collision Resolution
- **Method:** Chaining with Linked Lists
- Each table slot contains a linked list of contacts

### Data Structure
```c
struct Contact {
    char name[50];
    char phone[15];
    char email[30];
    struct Contact* next;
};

struct Hash {
    struct Contact** table;
    int size;
    int count;
};
```

### Sorting
- **Algorithm:** QuickSort
- **Time Complexity:** O(n log n)
- Contacts displayed alphabetically by name

## 📊 Performance

| Operation | Average | Worst Case |
|-----------|---------|------------|
| Insert | O(1) | O(n) |
| Search | O(1) | O(n) |
| Delete | O(1) | O(n) |
| Sort & Display | O(n log n) | O(n log n) |

**Tested with 1000+ contacts - instant search!** ⚡

## 🎓 Learning Project

This project was created as part of learning **Data Structures & Algorithms** in C:
- Week 1-2: Basic structures, hash functions
- Week 3-4: Insert, Search operations
- Week 5: Delete operation
- Week 6: Statistics & visualization
- Week 7: File I/O, sorting, final features

### Key Concepts Implemented
✅ Hash Tables  
✅ Collision Resolution (Chaining)  
✅ Dynamic Memory Management  
✅ Linked Lists  
✅ QuickSort Algorithm  
✅ File I/O  
✅ Pointers & Memory  

## 🔧 Technical Stack

- **Language:** C
- **Data Structure:** Hash Table with Chaining
- **Sorting:** QuickSort
- **Memory:** Dynamic allocation (malloc/free)
- **I/O:** File operations (fopen/fprintf/fscanf)

## 📁 Project Structure
```
Hash_Table_Phonebook/
├── phonebook.c       # Main source code
├── README.md         # This file
├── .gitignore        # Git ignore rules
└── phone_book.txt    # Data file (auto-generated)
```

## 🐛 Known Limitations

- Maximum 50 characters for name
- Maximum 15 characters for phone
- Maximum 30 characters for email
- VLA not supported - uses malloc for sorting

## 🎯 Future Improvements

- [ ] Rehashing when load factor > 0.75
- [ ] Edit contact functionality
- [ ] Search by phone/email
- [ ] Multiple phonebooks
- [ ] Undo/Redo operations

## 👨‍💻 Author

**Roman**  
Computer Intelligence & Smart Systems Student  
Learning C and Data Structures

## 📜 License

This is a learning project - feel free to use for educational purposes!

---

**⭐ If you found this helpful, please star the repo!**
