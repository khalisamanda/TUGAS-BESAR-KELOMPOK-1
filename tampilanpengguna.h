#ifndef TAMPILANPENGGUNA_H // Header guard: Mencegah pengulangan pengimporan header.
#define TAMPILANPENGGUNA_H

#include <QMainWindow> // Sertakan file header yang diperlukan untuk QMainWindow.
#include <QStandardItemModel> // Sertakan file header yang diperlukan untuk QStandardItemModel.
#include "ui_tampilanpengguna.h" // Sertakan file header yang diperlukan untuk kelas UI yang dihasilkan oleh Qt Designer.

QT_BEGIN_NAMESPACE // Mulai namespace Qt.
namespace Ui { // Mulai namespace Ui.
class TampilanPengguna; // Deklarasikan kelas TampilanPengguna dalam namespace Ui.
} // Selesai namespace Ui.
QT_END_NAMESPACE // Selesai namespace Qt.

struct BukuPengguna {
    QString id; // ID buku
    QString namaBuku; // Nama buku
    QDate tanggalPembuatan; // Tanggal pembuatan buku
    QString penulis; // Penulis buku
    QString penerbit; // Penerbit buku
    QDate tanggalPeminjaman; // Tanggal peminjaman buku
    QDate tanggalPengembalian; // Tanggal pengembalian buku
    QString statusBuku; // Status buku (tersedia, dipinjam, dll.)
};

class TampilanPengguna : public QMainWindow // Deklarasi kelas TampilanPengguna, mewarisi dari QMainWindow.
{
    Q_OBJECT // Makro yang diperlukan untuk mendukung sinyal dan slot.

public:
    explicit TampilanPengguna(QWidget *parent = nullptr); // Deklarasi konstruktor dengan parameter parent opsional.
    ~TampilanPengguna(); // Deklarasi destruktor.


private slots: // Bagian slot khusus.
    void on_pushButtonTambah_clicked(); // Deklarasi slot untuk menangani klik tombol tambah.
    void on_pushButtonHapus_clicked(); // Deklarasi slot untuk menangani klik tombol hapus.
    void on_pushButtonUpdate_clicked(); // Deklarasi slot untuk menangani klik tombol update.
    void on_pushButtonCari_clicked(); // Deklarasi slot untuk menangani klik tombol cari.

private:
    Ui::TampilanPengguna *ui; // Pointer ke kelas UI yang dihasilkan oleh Qt Designer.
    static const int MAX_BUKU = 100; // Deklarasi konstanta untuk jumlah maksimum buku.
    BukuPengguna dataBuku[MAX_BUKU]; // Array untuk menyimpan data buku.
    int jumlahBuku = 0; // Variabel untuk menyimpan jumlah buku saat ini.
    QStandardItemModel *model; // Pointer ke model QStandardItemModel untuk tabel.

    void tampilkanData(); // Deklarasi fungsi untuk menampilkan data buku.
    int binarySearch(const QString& idCari); // Deklarasi fungsi pencarian biner untuk mencari buku berdasarkan ID.
};

#endif // TAMPILANPENGGUNA_H // Penutup preprocessor directive.
