#include "siperpustakaan.h" // Mengimpor file header SiPerpustakaan.h yang berisi deklarasi kelas SiPerpustakaan.
#include "tampilanadmin.h" // Mengimpor file header tampilanadmin.h yang berisi deklarasi kelas TampilanAdmin.
#include "tampilanpengguna.h" // Mengimpor file header tampilanpengguna.h yang berisi deklarasi kelas TampilanPengguna.
#include "ui_siperpustakaan.h" // Mengimpor file header ui_SiPerpustakaan.h yang berisi deklarasi kelas Ui::SiPerpustakaan.
#include <QMessageBox> // Mengimpor header file QMessageBox yang diperlukan untuk menampilkan pesan dialog.

// Implementasi konstruktor SiPerpustakaan
SiPerpustakaan::SiPerpustakaan(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SiPerpustakaan)
{
    ui->setupUi(this); // Menyiapkan antarmuka pengguna yang dihasilkan oleh Qt Designer.
}

// Implementasi destruktor SiPerpustakaan
SiPerpustakaan::~SiPerpustakaan()
{
    delete ui; // Menghapus antarmuka pengguna yang dihasilkan oleh Qt Designer.
}

// Implementasi slot on_loginButton_clicked
void SiPerpustakaan::on_loginButton_clicked()
{
    // Mendapatkan username dan password dari inputan pengguna
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    // Memeriksa apakah username dan password adalah "admin"
    if (username == "admin" && password == "admin") {
        // Menampilkan pesan informasi jika login berhasil sebagai admin
        QMessageBox::information(this, "Login", "Login sebagai admin berhasil!");

        // Membuat instance baru dari TampilanAdmin dan menampilkannya
        TampilanAdmin *tampilanAdmin = new TampilanAdmin();
        tampilanAdmin->show();

        // Menutup jendela login
        this->close();
    }
    // Memeriksa apakah username dan password adalah "user"
    else if (username == "user" && password == "user") {
        // Menampilkan pesan informasi jika login berhasil sebagai user
        QMessageBox::information(this, "Login", "Login sebagai user berhasil!");

        // Membuat instance baru dari TampilanPengguna dan menampilkannya
        TampilanPengguna *tampilanPengguna = new TampilanPengguna();
        tampilanPengguna->show();

        // Menutup jendela login
        this->close();
    }
    // Memeriksa jika username atau password tidak sesuai
    else {
        // Menampilkan pesan peringatan jika login gagal
        QMessageBox::warning(this, "Login", "Username atau password salah!");
    }
}
