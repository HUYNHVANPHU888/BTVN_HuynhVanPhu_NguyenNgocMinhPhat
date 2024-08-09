#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//==============================================================================//
// Dinh nghia ham
int demKhoangTrang(const char* str);
void xoaKhoangTrangThua(char* str);
void chuanHoaChuoi(char* str);
int timKiemTen(const char* hoTen, const char* ten);
void catChuoiHoTen(const char* hoTen, char* hoLot, char* ten);
void xoaTuTrongChuoi(char* str, const char* tuCanXoa);
void lietKeKyTu(const char* str);
void timKytuXuatHienNhieuNhat(const char* str);

//==============================================================================//

int main() {
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Dem co bao nhieu khoang trang trong chuoi\n");
        printf("2. Xoa khoang trang thua trong chuoi\n");
        printf("3. Chuan hoa chuoi (chu in hoa dau tu)\n");
        printf("4. Tim kiem ten trong chuoi ho ten\n");
        printf("5. Cat chuoi ho ten thanh chuoi ho lot va chuoi ten\n");
        printf("6. Xoa mot tu trong chuoi\n");
        printf("7. Liet ke so lan xuat hien cua moi ky tu\n");
        printf("8. Tim kiem ky tu xuat hien nhieu nhat\n");
        printf("0. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        getchar(); // Loại bỏ ký tự newline còn sót lại trong buffer sau khi nhập số

        switch (choice) {
        case 1: {
            char chuoi[100];

            printf("Nhap vao chuoi: ");
            fgets(chuoi, sizeof(chuoi), stdin);
            chuoi[strcspn(chuoi, "\n")] = '\0';  // Loại bỏ ký tự xuống dòng nếu có

            int soLuongKhoangTrang = demKhoangTrang(chuoi);

            printf("So luong khoang trang trong chuoi la: %d\n", soLuongKhoangTrang);

            break;
        }
        case 2: {
            char chuoi[100];

            printf("Nhap vao chuoi: ");
            fgets(chuoi, sizeof(chuoi), stdin);
            chuoi[strcspn(chuoi, "\n")] = '\0';  // Loại bỏ ký tự xuống dòng nếu có

            xoaKhoangTrangThua(chuoi);

            printf("Chuoi sau khi xoa khoang trang thua: \"%s\"\n", chuoi);

            break;
        }
        case 3: {
            char chuoi[100];

            printf("Nhap vao chuoi: ");
            fgets(chuoi, sizeof(chuoi), stdin);
            chuoi[strcspn(chuoi, "\n")] = '\0';  // Loại bỏ ký tự xuống dòng nếu có

            chuanHoaChuoi(chuoi);

            printf("Chuoi sau khi chuan hoa: \"%s\"\n", chuoi);

            break;
        }
        case 4: {
            char hoTen[100];
            char ten[50];

            printf("Nhap vao ho ten: ");
            fgets(hoTen, sizeof(hoTen), stdin);
            hoTen[strcspn(hoTen, "\n")] = '\0';  // Loại bỏ ký tự xuống dòng nếu có

            printf("Nhap vao ten can tim: ");
            fgets(ten, sizeof(ten), stdin);
            ten[strcspn(ten, "\n")] = '\0';  // Loại bỏ ký tự xuống dòng nếu có

            if (timKiemTen(hoTen, ten)) {
                printf("Ten \"%s\" da duoc nhap dung trong ho ten.\n", ten);
            }
            else {
                printf("Ten \"%s\" khong co trong ho ten.\n", ten);
            }

            break;
        }
        case 5: {
            char hoTen[100];
            char hoLot[100];
            char ten[50];

            printf("Nhap vao ho ten: ");
            fgets(hoTen, sizeof(hoTen), stdin);
            hoTen[strcspn(hoTen, "\n")] = '\0';  // Loại bỏ ký tự xuống dòng nếu có

            catChuoiHoTen(hoTen, hoLot, ten);

            printf("Chuoi ho lot: \"%s\"\n", hoLot);
            printf("Chuoi ten: \"%s\"\n", ten);

            break;
        }
        case 6: {
            char chuoi[100];
            char tuCanXoa[50];

            printf("Nhap vao chuoi: ");
            fgets(chuoi, sizeof(chuoi), stdin);
            chuoi[strcspn(chuoi, "\n")] = '\0';  // Loại bỏ ký tự xuống dòng nếu có

            printf("Nhap vao tu can xoa: ");
            fgets(tuCanXoa, sizeof(tuCanXoa), stdin);
            tuCanXoa[strcspn(tuCanXoa, "\n")] = '\0';  // Loại bỏ ký tự xuống dòng nếu có

            xoaTuTrongChuoi(chuoi, tuCanXoa);

            printf("Chuoi sau khi xoa tu \"%s\": \"%s\"\n", tuCanXoa, chuoi);

            break;
        }
        case 7: {
            char chuoi[100];

            printf("Nhap vao chuoi: ");
            fgets(chuoi, sizeof(chuoi), stdin);
            chuoi[strcspn(chuoi, "\n")] = '\0';  // Loại bỏ ký tự xuống dòng nếu có

            lietKeKyTu(chuoi);

            break;
        }
        case 8: {
            char chuoi[100];

            printf("Nhap vao chuoi: ");
            fgets(chuoi, sizeof(chuoi), stdin);
            chuoi[strcspn(chuoi, "\n")] = '\0';  // Loại bỏ ký tự xuống dòng nếu có

            timKytuXuatHienNhieuNhat(chuoi);

            break;
        }
        case 0:
            printf("Thoat chuong trinh.\n");
            break;
        default:
            printf("Lua chon khong hop le.\n");
        }
    } while (choice != 0);

    return 0;
}

//==============================================================================//
int demKhoangTrang(const char* str) {
    int count = 0;
    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] == ' ') {
            count++;
        }
    }
    return count;
}

//==============================================================================//
void xoaKhoangTrangThua(char* str) {
    int n = strlen(str);
    int i, j = 0;
    int khoangTrang = 0;

    // Xóa các khoảng trắng đầu chuỗi
    while (isspace(str[j])) {
        j++;
    }

    for (i = 0; j < n; j++) {
        if (!isspace(str[j])) {
            str[i++] = str[j];
            khoangTrang = 0;
        }
        else if (!khoangTrang) {
            str[i++] = ' ';
            khoangTrang = 1;
        }
    }

    // Xóa các khoảng trắng cuối chuỗi nếu có
    if (i > 0 && isspace(str[i - 1])) {
        i--;
    }

    str[i] = '\0';  // Kết thúc chuỗi mới
}

//==============================================================================//
void chuanHoaChuoi(char* str) {
    int i = 0;
    int inWord = 0;

    while (str[i]) {
        if (isspace(str[i])) {
            inWord = 0;
        }
        else {
            if (!inWord) {
                str[i] = toupper(str[i]);  // Chữ cái đầu từ chuyển thành in hoa
                inWord = 1;
            }
            else {
                str[i] = tolower(str[i]);  // Các chữ cái còn lại chuyển thành thường
            }
        }
        i++;
    }
}

//==============================================================================//
int timKiemTen(const char* hoTen, const char* ten) {
    const char* p = strstr(hoTen, ten);

    // Nếu tìm thấy chuỗi tên
    if (p) {
        // Kiểm tra để chắc chắn rằng đó là một từ hoàn chỉnh
        int len = strlen(ten);
        if ((p == hoTen || isspace(*(p - 1))) && (isspace(*(p + len)) || *(p + len) == '\0')) {
            return 1;  // Tìm thấy tên hoàn chỉnh
        }
    }

    return 0;  // Không tìm thấy tên
}

//==============================================================================//
void catChuoiHoTen(const char* hoTen, char* hoLot, char* ten) {
    const char* lastSpace = strrchr(hoTen, ' ');

    if (lastSpace) {
        // Tách chuỗi họ lót
        strncpy(hoLot, hoTen, lastSpace - hoTen);
        hoLot[lastSpace - hoTen] = '\0';

        // Tách chuỗi tên
        strcpy(ten, lastSpace + 1);
    }
    else {
        // Nếu không có khoảng trắng, toàn bộ là tên
        strcpy(ten, hoTen);
        hoLot[0] = '\0';
    }
}

//==============================================================================//
void xoaTuTrongChuoi(char* str, const char* tuCanXoa) {
    char* p = strstr(str, tuCanXoa);

    if (p) {
        int len = strlen(tuCanXoa);

        // Di chuyển các phần còn lại của chuỗi để xóa từ
        memmove(p, p + len, strlen(p + len) + 1);

        // Xóa các khoảng trắng thừa nếu có sau khi xóa từ
        xoaKhoangTrangThua(str);
    }
}

//==============================================================================//
void lietKeKyTu(const char* str) {
    int count[256] = { 0 };  // Mảng đếm số lần xuất hiện của từng ký tự

    // Đếm số lần xuất hiện của từng ký tự
    for (int i = 0; str[i]; ++i) {
        count[(unsigned char)str[i]]++;
    }

    // In số lần xuất hiện của từng ký tự
    printf("Thong ke so lan xuat hien cua moi ky tu:\n");
    for (int i = 0; i < 256; ++i) {
        if (count[i] > 0) {
            printf("'%c' xuat hien %d lan\n", i, count[i]);
        }
    }
}

//==============================================================================//
void timKytuXuatHienNhieuNhat(const char* str) {
    int count[256] = { 0 };  // Mảng đếm số lần xuất hiện của từng ký tự
    int maxCount = 0;
    char maxChar = '\0';

    // Đếm số lần xuất hiện của từng ký tự
    for (int i = 0; str[i]; ++i) {
        count[(unsigned char)str[i]]++;
    }

    // Tìm ký tự xuất hiện nhiều nhất
    for (int i = 0; i < 256; ++i) {
        if (count[i] > maxCount) {
            maxCount = count[i];
            maxChar = (char)i;
        }
    }

    // In ký tự xuất hiện nhiều nhất
    if (maxCount > 0) {
        printf("Ky tu xuat hien nhieu nhat la '%c' voi %d lan xuat hien.\n", maxChar, maxCount);
    }
    else {
        printf("Khong co ky tu nao trong chuoi.\n");
    }
}
