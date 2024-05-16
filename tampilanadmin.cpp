#include "tampilanadmin.h" // Mengimpor file header tampilanadmin.h yang berisi deklarasi kelas TampilanAdmin.
#include "ui_tampilanadmin.h" // Mengimpor file header ui_tampilanadmin.h yang berisi deklarasi kelas Ui::TampilanAdmin.
#include <QMessageBox> // Mengimpor header file QMessageBox yang diperlukan untuk menampilkan pesan dialog.
#include <QDebug> // Mengimpor header file qDebug() yang digunakan untuk mencetak pesan debugging.

// Implementasi konstruktor TampilanAdmin
TampilanAdmin::TampilanAdmin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TampilanAdmin)
{
    ui->setupUi(this); // Menyiapkan antarmuka pengguna yang dihasilkan oleh Qt Designer.

    // Inisialisasi model untuk tabel
    model = new QStandardItemModel(this);
    model->setColumnCount(8); // Menyesuaikan jumlah kolom dengan jumlah atribut dalam struktur BukuAdmin
    model->setHorizontalHeaderLabels(QStringList() << "ID" << "Nama Buku" << "Tanggal Pembuatan" << "Penulis" << "Penerbit" << "Tanggal Peminjaman" << "Tanggal Pengembalian" << "Status Buku");

    // Set model untuk QTableView
    ui->tableView->setModel(model);
    ui->tableView->verticalHeader()->setVisible(false); // Mengatur agar header vertikal pada tabel tidak terlihat
}

// Implementasi destruktor TampilanAdmin
TampilanAdmin::~TampilanAdmin()
{
    delete ui; // Menghapus antarmuka pengguna yang dihasilkan oleh Qt Designer.
}

// Implementasi slot on_pushButtonTambah_clicked
void TampilanAdmin::on_pushButtonTambah_clicked()
{
    qDebug() << "Tombol Tambah diklik";

    // Memeriksa apakah jumlah buku belum mencapai batas maksimum sebelum menambahkan buku baru
    if (jumlahBuku < MAX_BUKU) {
        // Membuat objek buku dan mengambil nilai dari elemen-elemen UI untuk mengisi atribut-atributnya
        BukuAdmin buku;
        buku.id = ui->idLineEdit->text(); // Mengambil ID buku dari line edit
        buku.namaBuku = ui->namaBukuLineEdit->text(); // Mengambil nama buku dari line edit
        buku.tanggalPembuatan = ui->tanggalPembuatanDateEdit->date(); // Mengambil tanggal pembuatan dari date edit
        buku.penulis = ui->penulisLineEdit->text(); // Mengambil nama penulis dari line edit
        buku.penerbit = ui->penerbitLineEdit->text(); // Mengambil nama penerbit dari line edit
        buku.tanggalPeminjaman = ui->tanggalPeminjamanDateEdit->date(); // Mengambil tanggal peminjaman dari date edit
        buku.tanggalPengembalian = ui->tanggalPengembalianDateEdit->date(); // Mengambil tanggal pengembalian dari date edit
        buku.statusBuku = ui->statusBukuComboBox->text(); // Mengambil status buku dari combo box


        // Simpan data ke dalam array dataBuku
        dataBuku[jumlahBuku] = buku;

        // Tambahkan jumlahBuku
        jumlahBuku++;

        // Perbarui model dan tampilkan data
        tampilkanData();
    }
}

// Implementasi slot on_pushButtonHapus_clicked
void TampilanAdmin::on_pushButtonHapus_clicked()
{
    // Dapatkan indeks baris yang dipilih
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (!selectedIndexes.isEmpty()) {
        // Hapus data dari model dan array
        int index = selectedIndexes.at(0).row();
        if (index >= 0 && index < jumlahBuku) {
            // Hapus data dari array dataBuku
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

void TampilanAdmin::on_pushButtonUpdate_clicked() {
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
            BukuAdmin buku;
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

// Implementasi fungsi tampilkanData untuk menampilkan data dalam QTableView
void TampilanAdmin::tampilkanData() {
    // Bersihkan model sebelum menambahkan data baru
    model->clear();
    // Set header untuk tabel
    model->setHorizontalHeaderLabels(QStringList() << "ID" << "Nama Buku" << "Tanggal Pembuatan" << "Penulis" << "Penerbit" << "Tanggal Peminjaman" << "Tanggal Pengembalian" << "Status Buku");
    // Melakukan loop melalui setiap data buku dalam array dataBuku
    for (int i = 0; i < jumlahBuku; ++i) {
        // Membuat QList untuk menyimpan pointer QStandardItem untuk setiap baris
        QList<QStandardItem *> rowItems;

        // Menambahkan QStandardItem untuk ID buku
        rowItems << new QStandardItem(dataBuku[i].id);

        // Menambahkan QStandardItem untuk nama buku
        rowItems << new QStandardItem(dataBuku[i].namaBuku);

        // Menambahkan QStandardItem untuk tanggal pembuatan buku diformat sebagai "dd-MM-yyyy"
        rowItems << new QStandardItem(dataBuku[i].tanggalPembuatan.toString("dd-MM-yyyy"));

        // Menambahkan QStandardItem untuk penulis buku
        rowItems << new QStandardItem(dataBuku[i].penulis);

        // Menambahkan QStandardItem untuk penerbit buku
        rowItems << new QStandardItem(dataBuku[i].penerbit);

        // Menambahkan QStandardItem untuk tanggal peminjaman buku diformat sebagai "dd-MM-yyyy"
        rowItems << new QStandardItem(dataBuku[i].tanggalPeminjaman.toString("dd-MM-yyyy"));

        // Menambahkan QStandardItem untuk tanggal pengembalian buku diformat sebagai "dd-MM-yyyy"
        rowItems << new QStandardItem(dataBuku[i].tanggalPengembalian.toString("dd-MM-yyyy"));

        // Menambahkan QStandardItem untuk status buku
        rowItems << new QStandardItem(dataBuku[i].statusBuku);

        // Menambahkan rowItems ke model, mewakili satu baris data buku dalam QTableView
        model->appendRow(rowItems);
    }

}

// Implementasi fungsi binarySearch untuk pencarian biner
int TampilanAdmin::binarySearch(const QString& idCari) {
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

// Implementasi slot on_pushButtonCari_clicked untuk pencarian buku
void TampilanAdmin::on_pushButtonCari_clicked()
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
