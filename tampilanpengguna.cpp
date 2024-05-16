// Mengimpor file header kelas TampilanPengguna
#include "tampilanpengguna.h"
// Mengimpor file header yang dihasilkan oleh Qt Designer untuk kelas Ui::TampilanPengguna
#include "ui_tampilanpengguna.h"
// Mengimpor header file QMessageBox yang diperlukan untuk menampilkan pesan dialog
#include <QMessageBox>
// Mengimpor header file qDebug() yang digunakan untuk debugging
#include <QDebug>

// Implementasi konstruktor TampilanPengguna
TampilanPengguna::TampilanPengguna(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TampilanPengguna)
{
    // Inisialisasi UI
    ui->setupUi(this);

    // Inisialisasi model untuk tabel
    model = new QStandardItemModel(this);

    // Menentukan jumlah kolom dan label horizontal untuk tabel
    model->setColumnCount(8);
    model->setHorizontalHeaderLabels(QStringList() << "ID" << "Nama Buku" << "Tanggal Pembuatan" << "Penulis" << "Penerbit" << "Tanggal Peminjaman" << "Tanggal Pengembalian" << "Status Buku");

    // Mengatur model untuk QTableView
    ui->tableView->setModel(model);
    // Menyembunyikan header vertikal QTableView
    ui->tableView->verticalHeader()->setVisible(false);
}

// Implementasi destruktor TampilanPengguna
TampilanPengguna::~TampilanPengguna()
{
    delete ui;
}

// Implementasi slot untuk tombol Tambah
void TampilanPengguna::on_pushButtonTambah_clicked()
{
    // Debugging: mencetak pesan saat tombol Tambah diklik
    qDebug() << "Tombol Tambah diklik";

    // Memeriksa apakah jumlah buku masih kurang dari batas maksimum
    if (jumlahBuku < MAX_BUKU) {
        // Membuat objek buku dari struktur BukuPengguna
        BukuPengguna buku;

        // Mengisi atribut id buku dengan nilai dari input QLineEdit
        buku.id = ui->idLineEdit->text();

        // Mengisi atribut namaBuku dengan nilai dari input QLineEdit
        buku.namaBuku = ui->namaBukuLineEdit->text();

        // Mengisi atribut tanggalPembuatan dengan nilai dari input QDateEdit
        buku.tanggalPembuatan = ui->tanggalPembuatanDateEdit->date();

        // Mengisi atribut penulis dengan nilai dari input QLineEdit
        buku.penulis = ui->penulisLineEdit->text();

        // Mengisi atribut penerbit dengan nilai dari input QLineEdit
        buku.penerbit = ui->penerbitLineEdit->text();

        // Mengisi atribut tanggalPeminjaman dengan nilai dari input QDateEdit
        buku.tanggalPeminjaman = ui->tanggalPeminjamanDateEdit->date();

        // Mengisi atribut tanggalPengembalian dengan nilai dari input QDateEdit
        buku.tanggalPengembalian = ui->tanggalPengembalianDateEdit->date();

        // Mengisi atribut statusBuku dengan nilai dari input QComboBox
        buku.statusBuku = ui->statusBukuComboBox->text();


        // Simpan data ke dalam array dataBuku
        dataBuku[jumlahBuku] = buku;

        // Tambahkan jumlahBuku
        jumlahBuku++;

        // Perbarui model dan tampilkan data
        tampilkanData();
    }
}

// Implementasi slot untuk tombol Hapus
void TampilanPengguna::on_pushButtonHapus_clicked()
{
    // Dapatkan indeks baris yang dipilih
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (!selectedIndexes.isEmpty()) {
        // Hapus data dari model dan array
        int index = selectedIndexes.at(0).row();
        if (index >= 0 && index < jumlahBuku) {
            // Geser data ke atas untuk menutupi data yang dihapus
            for (int i = index; i < jumlahBuku - 1; ++i) {
                dataBuku[i] = dataBuku[i + 1];
            }

            // Kurangi jumlahBuku karena satu data telah dihapus
            jumlahBuku--;

            // Tampilkan data yang telah diupdate di dalam QTableView
            tampilkanData();
        }
    }
}

// Implementasi slot untuk tombol Update
void TampilanPengguna::on_pushButtonUpdate_clicked() {
    // Dapatkan indeks baris yang dipilih
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (!selectedIndexes.isEmpty()) {
        int index = selectedIndexes.at(0).row();
        // Ambil data dari input teks yang ingin diupdate
        QString id = ui->idLineEdit->text(); // Mengambil ID dari QLineEdit
        QString namaBuku = ui->namaBukuLineEdit->text(); // Mengambil Nama Buku dari QLineEdit
        QDate tanggalPembuatan = ui->tanggalPembuatanDateEdit->date(); // Mengambil Tanggal Pembuatan dari QDateEdit
        QString penulis = ui->penulisLineEdit->text(); // Mengambil Penulis dari QLineEdit
        QString penerbit = ui->penerbitLineEdit->text(); // Mengambil Penerbit dari QLineEdit
        QDate tanggalPeminjaman = ui->tanggalPeminjamanDateEdit->date(); // Mengambil Tanggal Peminjaman dari QDateEdit
        QDate tanggalPengembalian = ui->tanggalPengembalianDateEdit->date(); // Mengambil Tanggal Pengembalian dari QDateEdit
        QString statusBuku = ui->statusBukuComboBox->text(); // Mengambil Status Buku dari QComboBox
        // Update data di dalam array dataBuku
        if (index >= 0 && index < jumlahBuku) {
            BukuPengguna buku;
            buku.id = id;
            buku.namaBuku = namaBuku;
            buku.tanggalPembuatan = tanggalPembuatan;
            buku.penulis = penulis;
            buku.penerbit = penerbit;
            buku.tanggalPeminjaman = tanggalPeminjaman;
            buku.tanggalPengembalian = tanggalPengembalian;
            buku.statusBuku = statusBuku;
            dataBuku[index] = buku;
            // Tampilkan data yang telah diupdate di dalam QTableView
            tampilkanData();
        }
    }
}

// Implementasi fungsi untuk menampilkan data dalam QTableView
void TampilanPengguna::tampilkanData()
{
    // Bersihkan model sebelum menambahkan data baru
    model->clear();

    // Set header untuk tabel
    model->setHorizontalHeaderLabels(QStringList() << "ID" << "Nama Buku" << "Tanggal Pembuatan" << "Penulis" << "Penerbit" << "Tanggal Peminjaman" << "Tanggal Pengembalian" << "Status Buku");

    // Iterasi melalui array 'dataBuku' untuk menambahkan data ke dalam model QStandardItemModel
    for (int i = 0; i < jumlahBuku; ++i) {
        // Membuat QList untuk menyimpan item-item QStandardItem dalam satu baris
        QList<QStandardItem *> rowItems;
        // Menambahkan item QStandardItem untuk atribut 'id' buku ke dalam QList
        rowItems << new QStandardItem(dataBuku[i].id);
        // Menambahkan item QStandardItem untuk atribut 'namaBuku' ke dalam QList
        rowItems << new QStandardItem(dataBuku[i].namaBuku);
        // Menambahkan item QStandardItem untuk atribut 'tanggalPembuatan' (format tanggal) ke dalam QList
        rowItems << new QStandardItem(dataBuku[i].tanggalPembuatan.toString("dd-MM-yyyy"));
        // Menambahkan item QStandardItem untuk atribut 'penulis' buku ke dalam QList
        rowItems << new QStandardItem(dataBuku[i].penulis);
        // Menambahkan item QStandardItem untuk atribut 'penerbit' buku ke dalam QList
        rowItems << new QStandardItem(dataBuku[i].penerbit);
        // Menambahkan item QStandardItem untuk atribut 'tanggalPeminjaman' (format tanggal) ke dalam QList
        rowItems << new QStandardItem(dataBuku[i].tanggalPeminjaman.toString("dd-MM-yyyy"));
        // Menambahkan item QStandardItem untuk atribut 'tanggalPengembalian' (format tanggal) ke dalam QList
        rowItems << new QStandardItem(dataBuku[i].tanggalPengembalian.toString("dd-MM-yyyy"));
        // Menambahkan item QStandardItem untuk atribut 'statusBuku' ke dalam QList
        rowItems << new QStandardItem(dataBuku[i].statusBuku);
        // Menambahkan baris dengan item-item QStandardItem ke dalam model
        model->appendRow(rowItems);
    }

}

// Implementasi fungsi pencarian biner
int TampilanPengguna::binarySearch(const QString& idCari)
{
    int left = 0;
    int right = jumlahBuku - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        // Periksa apakah idCari berada di tengah array
        if (dataBuku[mid].id == idCari)
            return mid;
        // Jika idCari lebih kecil, cari di sebelah kiri
        if (dataBuku[mid].id < idCari)
            left = mid + 1;
        // Jika idCari lebih besar, cari di sebelah kanan
        else
            right = mid - 1;
    }
    // Jika tidak ditemukan, kembalikan -1
    return -1;
}

// Implementasi slot untuk tombol Cari
void TampilanPengguna::on_pushButtonCari_clicked()
{
    // Ambil ID buku yang akan dicari dari QLineEdit
    QString idCari = ui->idLineEdit->text();

    // Lakukan pencarian biner
    int index = binarySearch(idCari);

    // Periksa apakah ID buku ditemukan atau tidak
    if (index != -1) {
        // Jika ditemukan, tampilkan pesan informasi
        QMessageBox::information(this, "Pencarian Berhasil", QString("Buku dengan ID '%1' ditemukan di indeks %2").arg(idCari).arg(index));

        // Pilih baris yang sesuai dengan hasil pencarian di QTableView
        ui->tableView->selectRow(index);
    } else {
        // Jika tidak ditemukan, tampilkan pesan peringatan
        QMessageBox::warning(this, "Pencarian Gagal", QString("Buku dengan ID '%1' tidak ditemukan.").arg(idCari));
    }
}
