#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

struct Date {
	int day, month, year;
};

struct Book {
	char bookId[10];
	char title[30];
	char author[20];
	int quantity;
	int price;
	struct Date publication;
};

struct Member {
	char memberId[10];
	char name[20];
	char phone[10];
	bool status;
	int borrowCount;
	int borrowedCount;
	bool isLocked;
};
 
struct Member m[100];
struct Book b[100];
int bookCount = 0;
int memberCount = 0;

void displayBooks(int *role);
void addBook(int *role);
void editBook(int *role);
void deleteBook(int *role);
void sortBooksByPrice(int *role);
void searchBookByName(int *role);
void loadBooksFromFile();
void saveBooksToFile();
void inputString();
void displayMembers(int *role);
void addMember(int *role);
void editMember(int *role);
void loadMembersFromFile();
void saveMembersToFile();
void lockMember(int *role);
void searchMemberByName(int *role);
void borrowBook(int *role);
void returnBook(int *role);
int loginAdmin();

int main() {
	int role = 0, choice;
	
	loadBooksFromFile();
	loadMembersFromFile();
	
	do {
		if (role == -1) {
			role = 0;
		}
		
	system("clear || cls");
	printf("\tCHOOSE YOUR ROLE\n");
	printf("============================\n");
	printf("[1]. Quan Ly Khach Hang\n");
	printf("[2]. Quan Ly Sach\n");
	printf("[0]. Thoat Chuong Trinh\n");
	printf("============================\n");
	printf("Chon vai tro: ");
	scanf("%d", &role);
	getchar();
	switch (role) {
		case 1:
			if (loginAdmin()) {
			do {
				system("clear || cls");
				printf("\tMENU\n");
				printf("============================\n");
				printf("[1]. Hien thi danh sach khach hang\n");
				printf("[2]. Them khach hang vao danh sach\n");
				printf("[3]. Sua thong tin khach hang theo ID\n");
				printf("[4]. Khoa (Mo khoa) khach hang\n");
				printf("[5]. Tim kiem khach hang theo ten\n");
				printf("[6]. Khach hang muon sach (Toi da 5 quyen)\n");
				printf("[7]. Khach hang tra sach\n");
				printf("[0]. Quay ve\n");
				printf("============================\n");
				printf("Chon chuc nang: ");
				scanf("%d", &choice);
				getchar();
				switch (choice) {
					case 1:
						displayMembers(&role);
						if (role == -1) break;
						break;
					case 2:
						addMember(&role);
						if (role == -1) break;
						break;
					case 3:
						editMember(&role);
						if (role == -1) break;
						break;
					case 4:
						lockMember(&role);
						if (role == -1) break;
						break;
					case 5:
						searchMemberByName(&role);
						if (role == -1) break;
						break;
					case 6:
						borrowBook(&role);
						if (role == -1) break;
						break;
					case 7:
						returnBook(&role);
						if (role == -1) break;
						break;
					case 0:
						saveMembersToFile();
						break;
					default:
						printf("Vui long chon lai\n");
				}
			} while (choice != 0 && role != 1);
		}
			break;
		case 2:
			if (loginAdmin()) {
			do {
				system("clear || cls");
                printf("\tLIBRARY MENU\n");
                printf("============================\n");
                printf("[1]. Hien thi danh sach sach\n");
                printf("[2]. Them sach vao danh sach\n");
                printf("[3]. Sua thong tin sach theo ID\n");
                printf("[4]. Xoa thong tin sach theo ID\n");
                printf("[5]. Sap xep sach theo gia tien\n");
                printf("[6]. Tim kiem sach theo ten\n");
                printf("[0]. Quay ve\n");
                printf("============================\n");
                printf("Chon chuc nang: ");
                scanf("%d", &choice);
                getchar();
                switch (choice) {
                	case 1:
                        displayBooks(&role);
                        if (role == -1) break;  
                        break;
                    case 2:
                        addBook(&role);
                        if (role == -1) break;
                        break;
                    case 3:
                        editBook(&role);
                        if (role == -1) break;
                        break;
                    case 4:
                        deleteBook(&role);
                        if (role == -1) break;
                        break;
                    case 5:
                        sortBooksByPrice(&role);
                        if (role == -1) break;
                        break;
                    case 6:
                        searchBookByName(&role);
                        if (role == -1) break;
                        break;
                    case 0:
                    	saveBooksToFile();
                        break;  
                    default:
                        printf("Vui long chon lai\n");	
				}
			} while (choice != 0 && role != -1);
		}
			break;
		case 0:
        	saveMembersToFile();
        	saveBooksToFile();
        	
            printf("========= Thank You =========\n");
            printf("========= See You Soon ======\n");
            break;
        default:
            printf("Vui long chon lai\n");
	    }
	} while (role != 0);
}
	
void displayBooks(int *role) {
	char choice;
	do {
		system("clear || cls");
		if (bookCount == 0) {
            printf("Danh sach sach trong\n");
    	} else {
    		printf("===================================================================================================================\n");
            printf("| %-10s | %-30s | %-25s | %-10s | %-10s | %-10s |\n", "ID", "Title", "Author", "Quantity", "Price", "Publication");
            printf("===================================================================================================================\n");
            for (int i = 0; i < bookCount; i++) {
                printf("| %-10s | %-30s | %-25s | %-10d | %-10d | %02d/%02d/%04d  |\n",
                       b[i].bookId,
                       b[i].title,
                       b[i].author,
                       b[i].quantity,
                       b[i].price,
                       b[i].publication.day,
                       b[i].publication.month,
                       b[i].publication.year);
                printf("-------------------------------------------------------------------------------------------------------------------\n");
		}
	}
	
		printf("\nGo back(b) or Exit(0): ");
		scanf("%c", &choice);
		if (choice == '0') {
			*role = -1;
			return;
		}
	} while (choice != 'b');
}

void addBook(int *role) {
	char choice;
	do {
		system("clear || cls");
        
        struct Book newBook;
        int duplicate;
        
        do {
        	duplicate = 0;
        	
        	inputString("Nhap ID sach (Toi da 10 ky tu): ", newBook.bookId, 10);
        	
        	for (int i = 0; i < bookCount; i++) {
        		if (strcmp(b[i].bookId, newBook.bookId) == 0) {
        			printf("ID sach '%s' da ton tai. Vui long nhap lai\n", newBook.bookId);
                    duplicate = 1;
                    break;
				}
			}
		} while (duplicate);
		
		do {
			duplicate = 0;
			
            inputString("Nhap tieu de sach (Toi da 30 ky tu): ", newBook.title, 30);
            
            for (int i = 0; i < bookCount; i++) {
                if (strcmp(b[i].title, newBook.title) == 0) {
                    printf("Tieu de sach '%s' da ton tai. Vui long nhap lai\n", newBook.title);
                    duplicate = 1;
                    break;
                }
            }
		} while (duplicate);
		
		inputString("Nhap ten tac gia (Toi da 20 ky tu): ", newBook.author, 20);
		
		do {
			printf("Nhap so luong sach: ");
            if (scanf("%d", &newBook.quantity) != 1 || newBook.quantity <= 0) {
                printf("So luong sach phai la so nguyen duong. Vui long nhap lai\n");
                fflush(stdin);
            } else {
                break;
            }
		} while (1);
		
		do {
			printf("Nhap gia sach: ");
            if (scanf("%d", &newBook.price) != 1 || newBook.price <= 0) {
                printf("Gia sach phai la so nguyen duong. Vui long nhap lai\n");
                fflush(stdin);
            } else {
                break;
            }
		} while (1);
		
		do {
			printf("Nhap ngay xuat ban (dd mm yyyy): ");
            if (scanf("%d %d %d", &newBook.publication.day, &newBook.publication.month, &newBook.publication.year) != 3 ||
                newBook.publication.day <= 0 || newBook.publication.day > 31 ||
                newBook.publication.month <= 0 || newBook.publication.month > 12 ||
                newBook.publication.year <= 0) {
                printf("Ngay xuat ban khong hop le. Vui long nhap lai\n");
                fflush(stdin);
            } else {
                break;
            }
		} while (1);
		
		getchar();
		
		b[bookCount] = newBook;
        bookCount++;
        
        printf("\nSach da duoc them thanh cong\n");
        
        printf("\nGo back(b) or Exit(0): ");
        scanf(" %c", &choice);
        if (choice == '0') {
            *role = -1;
            return;
        }
	} while (choice != 'b');
}

void editBook(int *role) {
	char choice;
    do {
        system("clear || cls");
        if (bookCount == 0) {
            printf("Danh sach sach trong, khong the sua\n");
        } else {
            char editId[10];
            
            printf("Nhap ID sach can sua: ");
            fgets(editId, sizeof(editId), stdin);
            editId[strcspn(editId, "\n")] = '\0'; 

            int found = -1;
            
            for (int i = 0; i < bookCount; i++) {
                if (strcmp(b[i].bookId, editId) == 0) {
                    found = i;
                    break;
                }
            }

            if (found == -1) {
                printf("Khong tim thay sach co ID '%s'\n", editId);
            } else {
                printf("\nThong tin cu cua sach:\n");
                printf("Tieu de: %s\n", b[found].title);
                printf("Tac gia: %s\n", b[found].author);
                printf("So luong: %d\n", b[found].quantity);
                printf("Gia: %d\n", b[found].price);
                printf("Ngay xuat ban: %02d/%02d/%04d\n\n",
                       b[found].publication.day,
                       b[found].publication.month,
                       b[found].publication.year);

                char temp[100];
                
				printf("\nNhap thong tin moi (Nhan Enter de giu nguyen gia tri cu):\n");

                printf("Nhap tieu de sach (Nhap '0' de thoat): ");
                fgets(temp, sizeof(temp), stdin);
                if (strcmp(temp, "0\n") == 0) break;
                if (strlen(temp) > 1) {
                    temp[strcspn(temp, "\n")] = '\0';
                    strcpy(b[found].title, temp);
                }

                printf("Nhap ten tac gia (Nhap '0' de thoat): ");
                fgets(temp, sizeof(temp), stdin);
                if (strcmp(temp, "0\n") == 0) break;
                if (strlen(temp) > 1) {
                    temp[strcspn(temp, "\n")] = '\0';
                    strcpy(b[found].author, temp);
                }

                int newQuantity;
                    
                printf("Nhap so luong sach (Nhap '0' de thoat): ");
                fgets(temp, sizeof(temp), stdin);
                if (strcmp(temp, "0\n") == 0) break;
                if (sscanf(temp, "%d", &newQuantity) == 1 && newQuantity >= 0) {
                    b[found].quantity = newQuantity;
                } else {
                    printf("Gia tri khong hop le. So luong giu nguyen\n");
                }

                int newPrice;
                printf("Nhap gia sach (Nhap '0' de thoat): ");
                fgets(temp, sizeof(temp), stdin);
                if (strcmp(temp, "0\n") == 0) break;
                if (sscanf(temp, "%d", &newPrice) == 1 && newPrice >= 0) {
                    b[found].price = newPrice;
                } else {
                    printf("Gia tri khong hop le. Gia giu nguyen\n");
                }

                int day, month, year;
                
                printf("Nhap ngay xuat ban (dd mm yyyy) (Nhap '0' de thoat): ");
                fgets(temp, sizeof(temp), stdin);
                if (strcmp(temp, "0\n") == 0) break;
                if (sscanf(temp, "%d %d %d", &day, &month, &year) == 3 &&
                    day > 0 && day <= 31 &&
                    month > 0 && month <= 12 &&
                    year > 0) {
                    b[found].publication.day = day;
                    b[found].publication.month = month;
                    b[found].publication.year = year;
                } else {
                    printf("Ngay xuat ban khong hop le. Giu nguyen ngay cu\n");
                }
                
                getchar(); 

                printf("\nThong tin sach da duoc cap nhat thanh cong\n");
            }
        }
        
        printf("\nGo back(b) or Exit(0): ");
        scanf(" %c", &choice);  
        if (choice == '0') {
        	*role = -1;
            return;
        }
    } while (choice != 'b');
}

void deleteBook(int *role) {
    char choice;
    do {
        system("clear || cls");
        if (bookCount == 0) {
            printf("Danh sach sach trong, khong the xoa\n");
        } else {
            char deleteId[10];
            printf("Nhap ID sach can xoa: ");
            fgets(deleteId, sizeof(deleteId), stdin);
            deleteId[strcspn(deleteId, "\n")] = '\0';

            int found = -1;
            
            for (int i = 0; i < bookCount; i++) {
                if (strcmp(b[i].bookId, deleteId) == 0) {
                    found = i;
                    break;
                }
            }

            if (found == -1) {
                printf("Khong tim thay sach co Id '%s'\n", deleteId);
            } else {
                printf("\nThong tin sach can xoa:\n");
                printf("ID: %s\n", b[found].bookId);
                printf("Tieu de: %s\n", b[found].title);
                printf("Tac gia: %s\n", b[found].author);
                printf("So luong: %d\n", b[found].quantity);
                printf("Gia: %d\n", b[found].price);
                printf("Ngay xuat ban: %02d/%02d/%04d\n",
                    b[found].publication.day,
                    b[found].publication.month,
                    b[found].publication.year);

                char confirm;
                
                printf("Ban co chac muon xoa sach nay (Y/N): ");
                scanf("%c", &confirm);
                getchar();

                if (confirm == 'Y' || confirm == 'y') {
                    for (int i = found; i < bookCount - 1; i++) {
                        b[i] = b[i + 1];
                    }
                    
                    bookCount--;
                    
                    printf("\nSach co ID '%s' da duoc xoa thanh cong\n", deleteId);
                } else {
                    printf("\nHuy xoa sach\n");
                }
            }
        }
        
        printf("\nGo back(b) or Exit(0): ");
        scanf(" %c", &choice);  
        if (choice == '0') {
        	*role = -1;
            return;
        }
    } while (choice != 'b');
}

void sortBooksByPrice(int *role) {
    char choice;
    do {
        system("clear || cls"); 

        if (bookCount == 0) {
            printf("Danh sach sach trong. Khong co sach de sap xep\n");
        } else {
            int order;
            
            printf("\tSAP XEP SACH THEO GIA TIEN\n");
            printf("=====================================\n");
            printf("[1]. Sap xep theo thu tu tang dan\n");
            printf("[2]. Sap xep theo thu tu giam dan\n");
            printf("=====================================\n");
            printf("Nhap lua chon: ");
            scanf("%d", &order);
            getchar();

            for (int i = 0; i < bookCount - 1; i++) {
                for (int j = i + 1; j < bookCount; j++) {
                    if ((order == 1 && b[i].price > b[j].price) || 
                        (order == 2 && b[i].price < b[j].price)) {
                        struct Book temp = b[i];
                        b[i] = b[j];
                        b[j] = temp;
                    }
                }
            }

            printf("\nDanh sach sach sau khi sap xep:\n");
            printf("=====================================================================================================================\n");
            printf("| %-10s | %-30s | %-25s | %-10s | %-10s | %-15s |\n", "ID", "Title", "Author", "Quantity", "Price", "Publication");
            printf("=====================================================================================================================\n");
            for (int i = 0; i < bookCount; i++) {
                printf("| %-10s | %-30s | %-25s | %-10d | %-10d | %02d/%02d/%04d       |\n",
                       b[i].bookId, b[i].title, b[i].author, b[i].quantity, b[i].price, b[i].publication.day,
                       b[i].publication.month, b[i].publication.year);
                printf("---------------------------------------------------------------------------------------------------------------------\n");
            }
        }

        printf("\nGo back(b) or Exit(0): ");
        scanf(" %c", &choice);  
        if (choice == '0') {
        	*role = -1;
            return;
        }
    } while (choice != 'b');
}

void toUpper(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

void searchBookByName(int *role) {
    char choice;
    do {
        system("clear || cls"); 

        if (bookCount == 0) {
            printf("Danh sach sach trong. Khong co sach de tim kiem\n");
        } else {
            char searchTerm[30];
            
            printf("Nhap ten sach muon tim kiem: ");
            fgets(searchTerm, sizeof(searchTerm), stdin);
            searchTerm[strcspn(searchTerm, "\n")] = 0;
            
        	toUpper(searchTerm);

            bool found = false;

            printf("\nKet qua tim kiem:\n");
            printf("=====================================================================================================================\n");
            printf("| %-10s | %-30s | %-25s | %-10s | %-10s | %-15s |\n", "ID", "Title", "Author", "Quantity", "Price", "Publication");
            printf("=====================================================================================================================\n");

            for (int i = 0; i < bookCount; i++) {
            	char bookTitle[30];
                strcpy(bookTitle, b[i].title);
                
            	toUpper(bookTitle);
            	
                if (strstr(bookTitle, searchTerm) != NULL) {
                    found = true;
                    printf("| %-10s | %-30s | %-25s | %-10d | %-10d | %02d/%02d/%04d       |\n",
                           b[i].bookId, b[i].title, b[i].author, b[i].quantity, b[i].price, b[i].publication.day,
                           b[i].publication.month, b[i].publication.year);
                    printf("---------------------------------------------------------------------------------------------------------------------\n");
                }
            }

            if (!found) {
                printf("Khong tim thay sach nao co ten chua chuoi '%s'\n", searchTerm);
            } else {
                printf("\n");
            }
        }
        
        printf("\nGo back(b) or Exit(0): ");
        scanf(" %c", &choice);  
        if (choice == '0') {
        	*role = -1;
            return;
        }
    } while (choice != 'b');
}

void loadBooksFromFile() {
    FILE *file = fopen("books.dat", "rb");
    if (file == NULL) {
        printf("Khong the mo file. Du lieu ban dau chua duoc luu\n");
        return;
    }

    fread(&bookCount, sizeof(int), 1, file);
    fread(b, sizeof(struct Book), bookCount, file);
    
    fclose(file);
}

void saveBooksToFile() {
    FILE *file = fopen("books.dat", "wb");
    if (file == NULL) {
        printf("Khong the mo file de ghi du lieu\n");
        return;
    }

    fwrite(&bookCount, sizeof(int), 1, file); 
    fwrite(b, sizeof(struct Book), bookCount, file); 
    
    fclose(file);
}

void inputString(char *prompt, char *destination, int maxLength) {
    int valid;
    do {
        valid = 1;
        printf("%s", prompt);
        fgets(destination, maxLength + 2, stdin);
        destination[strcspn(destination, "\n")] = '\0';

        if (strlen(destination) > maxLength) { 
            printf("Chuoi nhap vao qua dai, vui long nhap lai (Toi da %d ky tu)\n", maxLength);
            valid = 0;
            fflush(stdin);
        } else if (strlen(destination) == 0) { 
            printf("Chuoi khong duoc de trong, vui long nhap lai\n");
            valid = 0;
        }
    } while (!valid);
}

void displayMembers(int *role) {
    char choice;
    do {
        system("clear || cls");
        if (memberCount == 0) {
            printf("Danh sach thanh vien trong\n");
        } else {
            printf("===============================================================================\n");
            printf("| %-10s | %-20s | %-10s | %-10s | %-13s |\n", "ID", "Name", "Phone", "Status", "BorrowedCount");
            printf("===============================================================================\n");
            for (int i = 0; i < memberCount; i++) {
                printf("| %-10s | %-20s | %-10s | %-10s | %-13d |\n",
                       m[i].memberId,
                       m[i].name,
                       m[i].phone,
                       m[i].isLocked ? "Lock" : "Unlock",
                       m[i].borrowedCount);
                printf("-------------------------------------------------------------------------------\n");
            }
        }

        printf("\nGo back(b) or Exit(0): ");
        scanf(" %c", &choice);
        if (choice == '0') {
            *role = -1; 
            return;
        }
    } while (choice != 'b');
}

void addMember(int *role) {
    char choice;
    do {
        system("clear || cls");        
        
        struct Member newMember;
        int duplicate;

        do {
            duplicate = 0;
            inputString("Nhap ID thanh vien (Toi da 10 ky tu): ", newMember.memberId, 10);
            for (int i = 0; i < memberCount; i++) {
                if (strcmp(m[i].memberId, newMember.memberId) == 0) {
                    printf("ID thanh vien '%s' da ton tai, vui long nhap lai\n", newMember.memberId);
                    duplicate = 1;
                    break;
                }
            }
        } while (duplicate);

        inputString("Nhap ten thanh vien (Toi da 20 ky tu): ", newMember.name, 20);

        do {
            duplicate = 0;
            inputString("Nhap so dien thoai (Toi da 10 ky tu): ", newMember.phone, 10);
            for (int i = 0; i < memberCount; i++) {
                if (strcmp(m[i].phone, newMember.phone) == 0) {
                    printf("SDT thanh vien '%s' da ton tai, vui long nhap lai\n", newMember.phone);
                    duplicate = 1;
                    break;
                }    
            }
        } while (duplicate);
        
        newMember.borrowCount = 0;
        newMember.borrowedCount = 0;
        newMember.isLocked = (newMember.status == 0);

        m[memberCount] = newMember;
        memberCount++;

        printf("\nThanh vien da duoc them thanh cong\n");

        printf("\nGo back(b) or Exit(0): ");
        scanf(" %c", &choice);
        if (choice == '0') {
            *role = -1; 
            return;
        }
   } while (choice != 'b');
}

void editMember(int *role) {
    char choice;
    int found = -1;

    do {
        system("clear || cls");
        if (memberCount == 0) {
            printf("Danh sach thanh vien trong\n");
        } else {
        	char memberId[10];
        	
            printf("Nhap ID thanh vien can sua: ");
            fgets(memberId, sizeof(memberId), stdin);
            memberId[strcspn(memberId, "\n")] = '\0';

            for (int i = 0; i < memberCount; i++) {
                if (strcmp(m[i].memberId, memberId) == 0) {
                    found = i;
                    break;
                }
            }

            if (found == -1) {
                printf("\nThanh vien voi ID '%s' khong ton tai\n", memberId);
            } else {
                printf("\nThong tin thanh vien hien tai:\n");
                printf("ID: %s\n", m[found].memberId);
                printf("Ten: %s\n", m[found].name);
                printf("So dien thoai: %s\n", m[found].phone);

                char temp[100];
                getchar();
				
				printf("\nNhap thong tin moi (Nhan Enter de giu nguyen gia tri cu):\n");
				
				printf("Nhap ID moi (Nhap '0' de thoat): ");
                fgets(temp, sizeof(temp), stdin);
                if (strcmp(temp, "0\n") == 0) break;
                if (strlen(temp) > 1) {
                    temp[strcspn(temp, "\n")] = '\0';
                    strcpy(m[found].memberId, temp);
                }
                
                printf("Nhap ten moi (Nhap '0' de thoat): ");
                fgets(temp, sizeof(temp), stdin);
                if (strcmp(temp, "0\n") == 0) break;
                if (strlen(temp) > 1) {
                    temp[strcspn(temp, "\n")] = '\0';
                    strcpy(m[found].name, temp);
                }

                printf("Nhap so dien thoai moi (Nhap '0' de thoat): ");
				fgets(temp, sizeof(temp), stdin);
				if (strcmp(temp, "0\n") == 0) break;
				if (strlen(temp) > 1) {
				    temp[strcspn(temp, "\n")] = '\0';
				    strcpy(m[found].phone, temp); 
				}

                printf("\nThong tin thanh vien da duoc cap nhat thanh cong\n");
            }
        }

        printf("\nGo back(b) or Exit(0): ");
        scanf(" %c", &choice);
        if (choice == '0') {
            *role = -1;
            return;
        }

    } while (choice != 'b');
}

void loadMembersFromFile() {
    FILE *file = fopen("members.dat", "rb");
    if (file == NULL) {
        printf("Khong the mo file. Du lieu ban dau chua duoc luu\n");
        return;
    }

    fread(&memberCount, sizeof(int), 1, file);
    fread(m, sizeof(struct Member), memberCount, file);
    
    fclose(file);
}

void saveMembersToFile() {
    FILE *file = fopen("members.dat", "wb");
    if (file == NULL) {
        printf("Khong the mo file de ghi du lieu\n");
        return;
    }

    fwrite(&memberCount, sizeof(int), 1, file); 
    fwrite(m, sizeof(struct Member), memberCount, file); 
    
    fclose(file);
}

void lockMember(int *role) {
    char memberId[10];
    char choice;
    int found = -1;
	do{ 
        system("clear || cls");

        if (memberCount == 0) {
            printf("Danh sach thanh vien trong\n");
            return;
        }

        printf("Nhap ID thanh vien can khoa : ");
        scanf(" %10s", memberId);

        for (int i = 0; i < memberCount; i++) {
            if (strcmp(m[i].memberId, memberId) == 0) {
                found = i;
                break;
            }
        }

        if (found == -1) {
            printf("\nThanh vien voi ID '%s' khong ton tai\n", memberId);
        } else {
            if (m[found].isLocked == 1) { 
                printf("Khach hang dang bi khoa\n");
                printf("Xac nhan mo khoa khach hang (y/n): ");
                scanf(" %c", &choice);

                if (choice == 'y' || choice == 'Y') {
                    m[found].isLocked = 0; 
                    printf("\nKhach hang voi ID '%s' da duoc mo khoa thanh cong\n", memberId);
                } else {
                    printf("\nKhong thay doi trang thai khach hang\n");
                }
            } else {    
                printf("\nKhach hang dang duoc mo khoa\n");
                printf("Xac nhan khoa khach hang (y/n): ");
                scanf(" %c", &choice);

                if (choice == 'y' || choice == 'Y') {
                    m[found].isLocked = 1;
                    printf("\nKhach hang voi ID '%s' da bi khoa thanh cong\n", memberId);
                } else {
                    printf("\nKhong thay doi trang thai khach hang\n");
                }
            }
        }

        printf("\nGo back(b) or Exit(0): ");
        scanf(" %c", &choice);  
        if (choice == '0') {
        	*role = -1;
            return;
        }
    } while (choice != 'b');
}

void searchMemberByName(int *role) {
	char choice;
    do {
        system("clear || cls"); 	 

        if (memberCount == 0) {
            printf("Danh sach sach trong. Khong co sach de tim kiem\n");
        } else {
            char searchTerm[20];
            
            printf("Nhap ten thanh vien muon tim kiem: ");
            fgets(searchTerm, sizeof(searchTerm), stdin);
            searchTerm[strcspn(searchTerm, "\n")] = 0;

            bool found = false;

            printf("\nKet qua tim kiem:\n");
            printf("============================================================================================================\n");
            printf("| %-10s | %-20s | %-10s | %-10s | %-20s |\n", "ID", "Name", "Phone", "Status", "BorrowedCount");
            printf("============================================================================================================\n");

            for (int i = 0; i < memberCount; i++) {
                if (strstr(m[i].name, searchTerm) != NULL) {
                    found = true;
                    printf("| %-10s | %-20s | %-10s | %-10d | %-20d |\n",
                           m[i].memberId, m[i].name, m[i].phone, m[i].status, m[i].borrowCount);
                    printf("---------------------------------------------------------------------------------------------------------------------\n");
                }
            }

            if (!found) {
                printf("Khong tim thay thanh vien nao co ten chua chuoi '%s'\n", searchTerm);
            } else {
                printf("\n");
            }
        }
        
        printf("\nGo back(b) or Exit(0): ");
        scanf(" %c", &choice);  
        if (choice == '0') {
        	*role = -1;
            return;
        }
    } while (choice != 'b');
}

void borrowBook(int *role) {
    char memberId[10];
    char bookId[10];
    int foundMember = -1, foundBook = -1, borrowCount;
    char choice;

    do {
        system("clear || cls");

        if (memberCount == 0) {
            printf("Danh sach khach hang trong\n");
            return;
        }

        do {
            printf("Nhap ID khach hang muon muon sach: ");
            scanf(" %10s", memberId);
            

            for (int i = 0; i < memberCount; i++) {
                if (strcmp(m[i].memberId, memberId) == 0) {
                    foundMember = i;
                    break;
                }
            }

            if (foundMember == -1) {
                printf("Khong tim thay khach hang voi ID %s. Vui long thu lai\n", memberId);
            } else {
                if (m[foundMember].isLocked) {
                    printf("Khach hang dang bi khoa, khong the muon sach\n");                   
                }

                if (m[foundMember].borrowedCount >= 5) {
                    printf("Khach hang da muon toi da 5 quyen sach. Khong the muon them\n");   
                }
            }
        } while (foundMember == -1);

        if (bookCount == 0) {
            printf("Thu vien khong con sach\n");            
        }

        do {
        	printf("===============================================================================\n");
            printf("| %-10s | %-20s | %-10s | %-10s | %-13s |\n", "ID", "Name", "Phone", "Status", "BorrowedCount");
            printf("===============================================================================\n");
            for (int i = 0; i < memberCount; i++) {
                printf("| %-10s | %-20s | %-10s | %-10s | %-13d |\n",
                       m[i].memberId,
                       m[i].name,
                       m[i].phone,
                       m[i].isLocked ? "Lock" : "Unlock",
                       m[i].borrowedCount);
                printf("-------------------------------------------------------------------------------\n");
        	}
        	
            printf("Nhap ID sach muon muon: ");
            scanf(" %9s", bookId);

            for (int i = 0; i < bookCount; i++) {
                if (strcmp(b[i].bookId, bookId) == 0) {
                    foundBook = i;
                    break;
                }
            }

            if (foundBook == -1) {
                printf("Khong tim thay sach voi ID %s. Vui long thu lai\n", bookId);
            } else if (b[foundBook].quantity <= 0) {
                printf("Sach %s da het. Vui long chon sach khac\n", bookId);
                foundBook = -1;
            }
        } while (foundBook == -1);

        do {
            printf("Nhap so luong sach muon muon (Toi da %d quyen): ", 5 - m[foundMember].borrowedCount);
            if (scanf("%d", &borrowCount) != 1 || borrowCount <= 0 || borrowCount > b[foundBook].quantity || (m[foundMember].borrowedCount + borrowCount) > 5) {
                printf("So luong khong hop le hoac vuot qua gioi han. Vui long thu lai\n");
                while (getchar() != '\n'); 
            } else {
                while (getchar() != '\n'); 
                break;
            }
        } while (1);

        b[foundBook].quantity -= borrowCount;
       
        m[foundMember].borrowedCount += borrowCount;

        printf("\nSach da duoc muon thanh cong\n");

        printf("\nGo back(b) or Exit(0): ");
        scanf(" %c", &choice);  
        if (choice == '0') {
        	*role = -1;
            return;
        }
    } while (choice != 'b');
}

void returnBook(int *role) {
    char memberId[10];
    char bookId[10];
    int foundMember = -1, foundBook = -1, returnCount;
    char choice;

    do {
        system("clear || cls");

        if (memberCount == 0) {
            printf("Danh sach khach hang trong\n");
            return;
        }

        do {
            printf("Nhap ID khach hang muon tra sach: ");
            scanf(" %9s", memberId);

            for (int i = 0; i < memberCount; i++) {
                if (strcmp(m[i].memberId, memberId) == 0) {
                    foundMember = i;
                    break;
                }
            }

            if (foundMember == -1) {
                printf("Khong tim thay khach hang voi ID %s. Vui long thu lai\n", memberId);
            } else if (m[foundMember].borrowedCount == 0) {
                printf("Khach hang chua muon sach nao. Khong the tra sach\n");
                foundMember = -1;
            }
        } while (foundMember == -1);

        if (bookCount == 0) {
            printf("Thu vien khong co sach nao\n");
            return;
        }

        do {
            printf("Nhap ID sach muon tra: ");
            scanf(" %9s", bookId);

            for (int i = 0; i < bookCount; i++) {
                if (strcmp(b[i].bookId, bookId) == 0) {
                    foundBook = i;
                    break;
                }
            }

            if (foundBook == -1) {
                printf("Khong tim thay sach voi ID %s. Vui long thu lai\n", bookId);
            }
        } while (foundBook == -1);

        do {
            printf("Nhap so luong sach muon tra (toi da %d quyen): ", m[foundMember].borrowedCount);
            if (scanf("%d", &returnCount) != 1 || returnCount <= 0 || returnCount > m[foundMember].borrowedCount) {
                printf("So luong khong hop le hoac vuot qua so sach da muon. Vui long thu lai\n");
                while (getchar() != '\n');
            } else {
                while (getchar() != '\n');
                break;
            }
        } while (1);

        b[foundBook].quantity += returnCount;
        m[foundMember].borrowedCount -= returnCount;

        printf("\nSach da duoc tra thanh cong\n");

        printf("\nGo back(b) or Exit(0): ");
        scanf(" %c", &choice);
        if (choice == '0') {
            *role = -1;
            return;
        }
    } while (choice != 'b');
}

int loginAdmin() {
    char username[50], password[50];
    const char adminUser[] = "LLL2006";  
    const char adminPass[] = "12122006"; 

    while (1) { 
        system("clear || cls"); 
        printf("\t   LOGIN\n");
        printf("============================\n");
        printf("Tai khoan: ");
        scanf("%s", username);
        printf("Mat khau: ");
        scanf("%s", password);

        if (strcmp(username, adminUser) == 0 && strcmp(password, adminPass) == 0) {
            printf("Dang nhap thanh cong\n");
            getchar(); 
            return 1;
        } else {
            printf("Sai tai khoan hoac mat khau. Vui long thu lai\n");
            getchar();
            getchar();
        }
    }
}
