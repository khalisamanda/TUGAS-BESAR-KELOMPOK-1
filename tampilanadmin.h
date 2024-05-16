#ifndef TAMPILANADMIN_H // Header guard: Mencegah pengulangan pengimporan header.
#define TAMPILANADMIN_H

#include <QMainWindow> // Include directive untuk memasukkan definisi kelas QMainWindow.
#include <QStandardItemModel> // Include directive untuk memasukkan definisi kelas QStandardItemModel.
#include "ui_tampilanadmin.h" // Include directive untuk memasukkan definisi kelas UI yang dihasilkan oleh Qt Designer.

QT_BEGIN_NAMESPACE // Mulai namespace Qt.
namespace Ui { // Mulai namespace Ui.
class TampilanAdmin; // Deklarasikan kelas TampilanAdmin dalam namespace Ui.
} // Selesai namespace Ui.
QT_END_NAMESPACE // Selesai namespace Qt.

struct BukuAdmin {
    QString id; // ID buku
    QString namaBuku; // Nama buku
    QDate tanggalPembuatan; // Tanggal pembuatan buku
    QString penulis; // Nama penulis buku
    QString penerbit; // Nama penerbit buku
    QDate tanggalPeminjaman; // Tanggal peminjaman buku
    QDate tanggalPengembalian; // Tanggal pengembalian buku
    QString statusBuku; // Status buku (misalnya, tersedia atau dipinjam)
};

class TampilanAdmin : public QMainWindow { // Deklarasi kelas TampilanAdmin yang merupakan turunan dari QMainWindow.
    Q_OBJECT // Makro yang diperlukan untuk mendukung sinyal dan slot.

public:
    explicit TampilanAdmin(QWidget *parent = nullptr); // Deklarasi konstruktor dengan parameter parent opsional.
    ~TampilanAdmin(); // Deklarasi destruktor.

private slots: // Bagian slot khusus.
    void on_pushButtonTambah_clicked(); // Deklarasi slot untuk menangani klik tombol tambah.
    void on_pushButtonHapus_clicked(); // Deklarasi slot untuk menangani klik tombol hapus.
    void on_pushButtonUpdate_clicked(); // Deklarasi slot untuk menangani klik tombol update.
    void on_pushButtonCari_clicked(); // Deklarasi slot untuk menangani klik tombol cari.

private:
    Ui::TampilanAdmin *ui; // Pointer ke kelas UI yang dihasilkan oleh Qt Designer.
    static const int MAX_BUKU = 100; // Deklarasi konstanta untuk jumlah maksimum buku.
    BukuAdmin dataBuku[MAX_BUKU]; // Array untuk menyimpan data buku.
    int jumlahBuku = 0; // Variabel untuk menyimpan jumlah buku saat ini.
    QStandardItemModel *model; // Pointer ke model QStandardItemModel untuk tabel.

    void tampilkanData(); // Deklarasi fungsi untuk menampilkan data buku.
    int binarySearch(const QString& idCari); // Deklarasi fungsi pencarian biner untuk mencari buku berdasarkan ID.
};

#endif // TAMPILANADMIN_H // Penutup preprocessor directive.
