#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// Forward declaration untuk kelas HashTable
class HashTable;

// Struktur untuk data Buku
struct dataBuku
{
    string judul;
    string penulis;
    int tahun;
    string status;
    dataBuku *next;
    // Menambahkan tabel hash untuk fungsionalitas tambahan
    HashTable *hashTable; // Menggunakan pointer ke HashTable

    // Konstruktor
    dataBuku(string j, string p, int t, string s) : judul(j), penulis(p), tahun(t), status(s), next(nullptr), hashTable(nullptr) {}
};

// Struktur data untuk pohon biner
struct TreeNode
{
    string data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(string val) : data(val), left(nullptr), right(nullptr) {}
};

// Struktur data untuk graph
struct GraphNode
{
    string data;
    vector<GraphNode *> neighbors;

    GraphNode(string val) : data(val) {}
};

class Graph
{
public:
    unordered_map<string, GraphNode *> nodes;

    // Fungsi untuk menambahkan node ke graph
    void addNode(string data)
    {
        if (nodes.find(data) == nodes.end())
        {
            nodes[data] = new GraphNode(data);
        }
    }

    // Fungsi untuk menambahkan edge antara dua node dalam graph
    void addEdge(string data1, string data2)
    {
        nodes[data1]->neighbors.push_back(nodes[data2]);
        nodes[data2]->neighbors.push_back(nodes[data1]);
    }
};

dataBuku *head = nullptr; // Menggunakan nullptr daripada NULL

const int TABLE_SIZE = 10; // Ukuran tabel hash

class HashTable
{
private:
    vector<dataBuku *> table;

    // Fungsi hashing sederhana
    int hashFunction(const string &key)
    {
        int hashValue = 0;
        for (char ch : key)
        {
            hashValue += ch;
        }
        return hashValue % TABLE_SIZE;
    }

public:
    HashTable()
    {
        table.resize(TABLE_SIZE, nullptr);
    }

    // Fungsi untuk menambahkan data ke tabel hash
    void insert(const string &judul, const string &penulis, int tahun, const string &status)
    {
        int index = hashFunction(judul);
        dataBuku *newNode = new dataBuku(judul, penulis, tahun, status);

        if (table[index] == nullptr)
        {
            table[index] = newNode;
        }
        else
        {
            // Collision handling: chaining
            dataBuku *current = table[index];
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Fungsi untuk mencari data berdasarkan judul
    dataBuku *search(const string &judul)
    {
        int index = hashFunction(judul);
        dataBuku *current = table[index];
        while (current != nullptr)
        {
            if (current->judul == judul)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr; // Data tidak ditemukan
    }

    // Fungsi untuk menampilkan semua data dalam tabel hash
    void displayTable()
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            cout << "[" << i << "] ";
            dataBuku *current = table[i];
            while (current != nullptr)
            {
                cout << "-> " << current->judul << " ";
                current = current->next;
            }
            cout << endl;
        }
    }
};

HashTable hashTable; // Deklarasi objek HashTable global

// Fungsi untuk mengurutkan buku berdasarkan judul
void sortBukuByJudul()
{
    if (head == nullptr || head->next == nullptr)
    {
        return; // Tidak perlu mengurutkan jika tidak ada atau hanya satu elemen
    }

    dataBuku *current = head;
    dataBuku *nextNode = nullptr;

    bool swapped;
    do
    {
        swapped = false;
        current = head;
        while (current->next != nextNode)
        {
            if (current->judul > current->next->judul)
            {
                // Tukar posisi
                string tempJudul = current->judul;
                string tempPenulis = current->penulis;
                int tempTahun = current->tahun;
                string tempStatus = current->status;

                current->judul = current->next->judul;
                current->penulis = current->next->penulis;
                current->tahun = current->next->tahun;
                current->status = current->next->status;

                current->next->judul = tempJudul;
                current->next->penulis = tempPenulis;
                current->next->tahun = tempTahun;
                current->next->status = tempStatus;

                swapped = true;
            }
            current = current->next;
        }
        nextNode = current;
    } while (swapped);
}

// Fungsi untuk mencari buku berdasarkan judul secara rekursif
dataBuku *cariBukuByJudulRekursif(dataBuku *current, const string &judulCari)
{
    if (current == nullptr)
    {
        return nullptr; // Basis: jika current nullptr, maka buku tidak ditemukan
    }
    if (current->judul == judulCari)
    {
        return current; // Basis: jika judul buku ditemukan
    }
    // Rekursif: cari buku di node selanjutnya
    return cariBukuByJudulRekursif(current->next, judulCari);
}

// Fungsi untuk membalut pencarian rekursif
dataBuku *cariBukuByJudulWrapper(const string &judulCari)
{
    return cariBukuByJudulRekursif(head, judulCari);
}

// Fungsi untuk mencari buku berdasarkan judul
dataBuku *cariBukuByJudul(const string &judulCari)
{
    dataBuku *current = head;
    while (current != nullptr)
    {
        if (current->judul == judulCari)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr; // Buku tidak ditemukan
}

// Fungsi untuk menambahkan buku baru ke akhir daftar
void tambahBuku(dataBuku *newBuku)
{
    if (head == nullptr)
    {
        head = newBuku;
    }
    else
    {
        dataBuku *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newBuku;
    }
}

// Fungsi untuk menambahkan node ke pohon biner
TreeNode *insertTree(TreeNode *root, string data)
{
    if (root == nullptr)
    {
        return new TreeNode(data);
    }
    else
    {
        if (data <= root->data)
        {
            root->left = insertTree(root->left, data);
        }
        else
        {
            root->right = insertTree(root->right, data);
        }
        return root;
    }
}

// Fungsi untuk menampilkan pohon biner
void displayTree(TreeNode *root)
{
    if (root == nullptr)
        return;

    // Preorder traversal untuk menampilkan node
    cout << root->data << " ";
    displayTree(root->left);
    displayTree(root->right);
}

// Fungsi untuk menambahkan node dan edge ke graph
void tambahGraph(Graph &graph)
{
    graph.addNode("Node1");
    graph.addNode("Node2");
    graph.addNode("Node3");
    graph.addNode("Node4");

    graph.addEdge("Node1", "Node2");
    graph.addEdge("Node1", "Node3");
    graph.addEdge("Node2", "Node4");
}

// Fungsi menu admin
void adminMenu()
{
    while (true)
    {
        int pilihanAdminMenu;
        cout << "---- Aplikasi Perpustakaan ----" << endl;
        cout << "-------- Menu ----------\n";
        cout << " 1. Input Buku        \n";
        cout << " 2. Daftar Buku       \n";
        cout << " 3. Laporan           \n";
        cout << " 4. Cari Buku         \n";
        cout << " 5. Tampilkan Tree    \n"; // Menampilkan pohon biner
        cout << " 6. Tampilkan Graph   \n"; // Menampilkan graph
        cout << " 7. Exit Admin Menu   \n";
        cout << "----------------------\n";
        cout << "Masukan Pilihan anda[ 1 s.d. 7 ] = ";
        cin >> pilihanAdminMenu;
        if (pilihanAdminMenu == 1)
        {
            // Input buku
            cout << "Masukkan Judul      : ";
            string judul;
            cin.ignore();
            getline(cin, judul);

            cout << "Masukkan penulis    : ";
            string penulis;
            getline(cin, penulis);

            cout << "Masukkan tahun buku : ";
            int tahun;
            cin >> tahun;

            // Menambahkan buku ke daftar
            dataBuku *newBuku = new dataBuku(judul, penulis, tahun, "Tersedia");
            tambahBuku(newBuku);
            hashTable.insert(judul, penulis, tahun, "Tersedia"); // Menambahkan buku ke tabel hash

            system("cls");
            cout << "Data berhasil ditambahkan !" << endl;
        }
        else if (pilihanAdminMenu == 2)
        {
            // Daftar buku
            sortBukuByJudul();        // Mengurutkan buku sebelum menampilkannya
            hashTable.displayTable(); // Menampilkan tabel hash
        }
        else if (pilihanAdminMenu == 3)
        {
            // Laporan
            // Implementasi laporan berdasarkan data dalam tabel hash
            // ...
            dataBuku *current = head;
            bool adaBukuDipinjam = false;
            bool adaBukuDikembalikan = false;

            cout << "Laporan Peminjaman dan Pengembalian Buku:" << endl;
            while (current != NULL)
            {
                if (current->status == "Dipinjam")
                {
                    cout << "Judul Buku : " << current->judul << " dipinjam." << endl;
                    adaBukuDipinjam = true;
                }
                else if (current->status == "Tersedia")
                {
                    cout << "Judul Buku : " << current->judul << " tersedia." << endl;
                    adaBukuDikembalikan = true;
                }
                current = current->next;
            }

            // Jika tidak ada buku yang dipinjam atau dikembalikan
            if (!adaBukuDipinjam)
            {
                cout << "Tidak ada buku yang sedang dipinjam." << endl;
            }
            if (!adaBukuDikembalikan)
            {
                cout << "Tidak ada buku yang telah dikembalikan." << endl;
            }
        }
        else if (pilihanAdminMenu == 4)
        {
            // Pencarian buku
            cout << "Masukkan judul buku yang ingin dicari: ";
            string judulCari;
            cin.ignore();
            getline(cin, judulCari);

            dataBuku *foundBook = cariBukuByJudulWrapper(judulCari);
            if (foundBook != nullptr)
            {
                cout << "Buku ditemukan!" << endl;
                cout << "Judul Buku : " << foundBook->judul << endl;
                cout << "Penulis : " << foundBook->penulis << endl;
                cout << "Tahun Terbit : " << foundBook->tahun << endl;
                cout << "Status : " << foundBook->status << endl;
            }
            else
            {
                cout << "Buku tidak ditemukan." << endl;
            }
        }
        else if (pilihanAdminMenu == 5)
        {
            // Tampilkan tree
            TreeNode *root = nullptr; // Ganti ini dengan root dari pohon biner Anda
            displayTree(root);
        }
        else if (pilihanAdminMenu == 6)
        {
            // Tampilkan graph
            Graph graph;        // Buat objek graph
            tambahGraph(graph); // Tambahkan node dan edge ke graph
            // Tampilkan graph
            cout << "Graph:\n";
            for (auto const &[key, node] : graph.nodes)
            {
                cout << "Node: " << node->data << " Neighbors: ";
                for (auto neighbor : node->neighbors)
                {
                    cout << neighbor->data << " ";
                }
                cout << endl;
            }
        }
        else if (pilihanAdminMenu == 7)
        {
            system("cls");
            break;
        }
        else
        {
            system("cls");
            cout << "Pilihan tidak valid!" << endl;
        }
    }
}

// Fungsi menu pengguna
void userMenu()
{
    while (true)
    {
        int pilihanUserMenu;
        cout << "---- Aplikasi Perpustakaan ----" << endl;
        cout << "-------- Menu ----------\n";
        cout << " 1. Daftar Buku       \n";
        cout << " 2. Peminjaman      \n";
        cout << " 3. Pengembalian    \n";
        cout << " 4. Cari Buku         \n";
        cout << " 5. Exit User Menu               \n";
        cout << "----------------------\n";
        cout << "Masukan Pilihan anda[ 1 s.d. 5 ] = ";
        cin >> pilihanUserMenu;

        if (pilihanUserMenu == 1)
        {
            // Daftar buku
            sortBukuByJudul();        // Mengurutkan buku sebelum menampilkannya
            hashTable.displayTable(); // Menampilkan tabel hash
        }
        else if (pilihanUserMenu == 2)
        {
            // Peminjaman buku
            // Implementasi peminjaman buku berdasarkan data dalam tabel hash
            // ...
            cout << "Masukkan Judul Buku yang ingin dipinjam : ";
            string judulPinjam;
            cin.ignore();
            getline(cin, judulPinjam);

            // Cari buku berdasarkan judul
            dataBuku *foundBook = cariBukuByJudul(judulPinjam);

            if (foundBook != nullptr)
            {
                if (foundBook->status == "Tersedia")
                {
                    foundBook->status = "Dipinjam";
                    cout << "Buku " << judulPinjam << " berhasil dipinjam." << endl;
                }
                else
                {
                    cout << "Buku " << judulPinjam << " sedang tidak tersedia untuk dipinjam." << endl;
                }
            }
            else
            {
                cout << "Buku tidak ditemukan." << endl;
            }
        }
        else if (pilihanUserMenu == 3)
        {
            // Pengembalian buku
            cout << "Masukkan Judul Buku yang ingin dikembalikan : ";
            string judulKembali;
            cin.ignore();
            getline(cin, judulKembali);

            // Cari buku berdasarkan judul
            dataBuku *foundBook = cariBukuByJudul(judulKembali);

            if (foundBook != nullptr)
            {
                if (foundBook->status == "Dipinjam")
                {
                    foundBook->status = "Tersedia";
                    cout << "Buku " << judulKembali << " berhasil dikembalikan." << endl;
                }
                else
                {
                    cout << "Buku " << judulKembali << " tidak sedang dipinjam." << endl;
                }
            }
            else
            {
                cout << "Buku tidak ditemukan." << endl;
            }
        }
        else if (pilihanUserMenu == 4)
        {
            // Pencarian buku
            cout << "Masukkan judul buku yang ingin dicari: ";
            string judulCari;
            cin.ignore();
            getline(cin, judulCari);

            dataBuku *foundBook = cariBukuByJudulWrapper(judulCari);
            if (foundBook != nullptr)
            {
                cout << "Buku ditemukan!" << endl;
                cout << "Judul Buku : " << foundBook->judul << endl;
                cout << "Penulis : " << foundBook->penulis << endl;
                cout << "Tahun Terbit : " << foundBook->tahun << endl;
                cout << "Status : " << foundBook->status << endl;
            }
            else
            {
                cout << "Buku tidak ditemukan." << endl;
            }
        }
        else if (pilihanUserMenu == 5)
        {
            system("cls");
            break;
        }
        else
        {
            system("cls");
            cout << "Pilihan tidak valid!" << endl;
        }
    }
}

// Fungsi utama
int main()
{
    while (true)
    {
        int pilihanMenuUtama;
        cout << "---- Aplikasi Perpustakaan ----" << endl;
        cout << "-------- Menu ----------\n";
        cout << " 1. Menu Admin         \n";
        cout << " 2. Menu Pengguna      \n";
        cout << " 3. Exit               \n";
        cout << "----------------------\n";
        cout << "Masukan Pilihan anda[ 1 s.d. 3 ] = ";
        cin >> pilihanMenuUtama;

        if (pilihanMenuUtama == 1)
        {
            adminMenu();
        }
        else if (pilihanMenuUtama == 2)
        {
            userMenu();
        }
        else if (pilihanMenuUtama == 3)
        {
            break;
        }
        else
        {
            system("cls");
            cout << "Pilihan tidak valid!" << endl;
        }
    }
    return 0;
}
