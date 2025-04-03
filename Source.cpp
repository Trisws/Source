#include <iostream>
using namespace std;

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
void insertionSort(int arr[], int n, int& count) {
    count = 0; // Khởi tạo biến đếm
    // Bắt đầu từ phần tử thứ hai trong mảng, vì phần tử đầu tiên đã được coi là đã được sắp xếp
    for (int i = 1; i < n; i++) {
        int key = arr[i];  // Lưu trữ phần tử hiện tại (được gọi là key)
        int j = i - 1;     // Chỉ số của phần tử phía trước phần tử key

        // Duyệt các phần tử đã sắp xếp để tìm vị trí chèn key vào đúng chỗ
        while (j >= 0 && arr[j] > key) {
            count++; // Tăng biến đếm mỗi khi có sự so sánh
            arr[j + 1] = arr[j];  // Di chuyển phần tử arr[j] sang phải
            j--;  // Giảm j để tiếp tục kiểm tra phần tử phía trước
        }

        // Đặt key vào đúng vị trí sau khi di chuyển các phần tử lớn hơn
        arr[j + 1] = key;
    }
}
void shakeSort(int arr[], int n, int& count) {
    count = 0;          // Khởi tạo biến đếm
    int left = 0;          // Biên trái của phần chưa được sắp xếp
    int right = n - 1;     // Biên phải của phần chưa được sắp xếp
    int temp;              // Biến tạm thời dùng để hoán đổi giá trị

    // Vòng lặp sẽ chạy khi biên trái nhỏ hơn biên phải
    while (left < right) {
        // Lượt 1: Duyệt từ trái sang phải ( tìm max )
        for (int i = left; i < right; i++) {
            count++; // Tăng biến đếm mỗi khi có sự so sánh
            // Nếu phần tử hiện tại lớn hơn phần tử tiếp theo, hoán đổi chúng
            if (arr[i] > arr[i + 1]) {
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
        // Sau lượt duyệt từ trái sang phải, giảm biên phải vì phần tử lớn nhất đã được đưa về đúng vị trí
        right--;

        // Lượt 2: Duyệt từ phải sang trái ( tìm min )
        for (int i = right; i > left; i--) {
            count++; // Tăng biến đếm mỗi khi có sự so sánh
            // Nếu phần tử hiện tại nhỏ hơn phần tử trước đó, hoán đổi chúng
            if (arr[i] < arr[i - 1]) {
                temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
            }
        }
        // Sau lượt duyệt từ phải sang trái, tăng biên trái vì phần tử nhỏ nhất đã được đưa về đúng vị trí
        left++;
    }
}

void Heapify(int arr[], int n, int i, int& count) {
    int largest = i;             // Khởi tạo largest là chỉ số của phần tử hiện tại
    int left = 2 * i + 1;        // Chỉ số phần tử con trái
    int right = 2 * i + 2;       // Chỉ số phần tử con phải

    // Kiểm tra nếu con trái lớn hơn phần tử hiện tại
    if (left < n && arr[left] > arr[largest]) {
        count++; // Tăng biến đếm mỗi khi có sự so sánh
        largest = left;
    }

    // Kiểm tra nếu con phải lớn hơn phần tử hiện tại hoặc con trái
    if (right < n && arr[right] > arr[largest]) {
        count++; // Tăng biến đếm mỗi khi có sự so sánh
        largest = right;
    }

    // Nếu largest không phải là phần tử hiện tại, hoán đổi và tiếp tục gọi Heapify
    if (largest != i) {
        swap(arr[i], arr[largest]);
        Heapify(arr, n, largest, count);
    }
}
void Heap_sort(int arr[], int n, int& count) {
    count = 0; // Khởi tạo biến đếm
    // Xây dựng Max-Heap từ nửa mảng dưới (n/2 - 1 là chỉ số của phần tử cha cuối cùng)
    for (int i = n / 2 - 1; i >= 0; i--) {
        Heapify(arr, n, i, count);
    }

    // Một mảng Max-Heap đã được xây dựng, giờ ta thực hiện quá trình sắp xếp
    for (int i = n - 1; i >= 0; i--) {
        // Hoán đổi phần tử đầu tiên (lớn nhất) với phần tử cuối cùng
        swap(arr[0], arr[i]);
        // Gọi Heapify để khôi phục cấu trúc Max-Heap trên phần còn lại của mảng
        Heapify(arr, i, 0, count);
    }
}
void Quick_sort(int arr[], int low, int high, int& count) {
    count = 0; // Khởi tạo biến đếm
    if (low < high) {
        // Chọn pivot (phần tử cuối cùng)
        int pivot = arr[high];
        int i = (low - 1);  // Chỉ số cho phần tử nhỏ hơn pivot

        // Duyệt qua mảng để sắp xếp các phần tử nhỏ hơn pivot ở bên trái
        for (int j = low; j < high; j++) {
            count++; // Tăng biến đếm mỗi khi có sự so sánh
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);  // Hoán đổi nếu phần tử nhỏ hơn pivot
            }
        }

        // Hoán đổi pivot về đúng vị trí
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;  // Vị trí của pivot

        // Gọi đệ quy cho hai phân vùng
        Quick_sort(arr, low, pi - 1, count);
        Quick_sort(arr, pi + 1, high, count);
    }
}
void Radix_sort(int arr[], int n, int& count) {
    count = 0; // Khởi tạo biến đếm
    // Tìm giá trị lớn nhất trong mảng
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        count++; // Tăng biến đếm mỗi khi có sự so sánh
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    // Duyệt qua các chữ số từ thấp đến cao (theo thứ tự hàng đơn vị, hàng chục, ...)
    for (int exp = 1; max / exp > 0; exp *= 10) {
        int* output = new int[n];      // Mảng kết quả sau khi sắp xếp theo từng chữ số
        int count[10] = { 0 };  // Mảng đếm số lần xuất hiện của các chữ số

        // Đếm số lần xuất hiện của các chữ số tại vị trí exp
        for (int i = 0; i < n; i++) {
            count[(arr[i] / exp) % 10]++;
        }

        // Tính tổng dồn để xác định vị trí chính xác cho từng chữ số
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // Sắp xếp mảng theo chữ số tại vị trí exp
        for (int i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        // Cập nhật lại mảng ban đầu với kết quả sau khi sắp xếp theo chữ số
        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }
    }
}
