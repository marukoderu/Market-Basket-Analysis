#ifndef MBA_H
#define MBA_H

// Trie Data Structure
typedef char item;
typedef struct TrieElmt *address;
typedef struct TrieElmt {
  item namaItem[20];
  address fc, nb, pr;
  bool terminal;
} Trie ;

// Membuat Node Trie Baru
Trie *createTrieNode(const char *namaItem);

// Menambahkan transaksi ke Trie
void addTransaction(Trie *root, const char *namaItem);

// Mencari node di Trie based on nama item
Trie *searchItem(Trie *root, const char *namaItem);

// Mencetak isi Trie
void printTrie(Trie *root);

#endif