#ifndef SIPERPUSTAKAAN_H // Header guard: Mencegah pengulangan pengimporan header.
#define SIPERPUSTAKAAN_H

#include <QMainWindow> // Include directive untuk memasukkan definisi kelas QMainWindow.
#include "ui_siperpustakaan.h" // Include directive untuk memasukkan definisi kelas UI yang dihasilkan oleh Qt Designer.

QT_BEGIN_NAMESPACE // Mulai namespace Qt.
namespace Ui { // Mulai namespace Ui.
class SiPerpustakaan; // Deklarasi kelas SiPerpustakaan dalam namespace Ui.
}
QT_END_NAMESPACE

class SiPerpustakaan : public QMainWindow {
    Q_OBJECT // Makro yang diperlukan untuk mendukung sinyal dan slot.

public:
    SiPerpustakaan(QWidget *parent = nullptr); // Deklarasi konstruktor dengan parameter parent opsional.
    ~SiPerpustakaan(); // Deklarasi destruktor.

private slots:
    void on_loginButton_clicked(); // Deklarasi slot untuk menangani klik tombol login.

private:
    Ui::SiPerpustakaan *ui; // Pointer ke kelas UI yang dihasilkan oleh Qt Designer.
};
#endif // SIPERPUSTAKAAN_H
