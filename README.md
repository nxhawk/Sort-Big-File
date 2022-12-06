# Đồ án thực hành cấu trúc dữ liệu và giải thuật

## Đề bài: Sắp xếp dữ liệu lớn

### *Chào thầy và các bạn,* 

Trong bài viết này, chúng em xin trình bày về cách sắp xếp bộ dữ liệu lớn không fit trên RAM.

Đề bài chi tiết của đồ án xem [tại đây](https://docs.google.com/document/d/1OrxWWCzWI4HwbyAYEj0K3Sj5ZK5ZTI1eXet33qozlOY/edit)

Bộ dữ liệu có nguồn [tại](https://www.kaggle.com/datasets/mohamedbakhet/amazon-books-reviews)

Báo cáo chi tiết của nhóm: [link sau](https://github.com/nxhawk/Sort-Big-File/blob/master/report.pdf)

## Thành viên thực hiện đồ án:

| MSSV | Họ và tên |
| ------ | ------ |
| 21120439 | Bùi Minh Duy |
| 21120447 | Nguyễn Nhật Hào |
| 21120453 | Tô Phương Hiếu |

Để có thể sắp xếp một file lớn, ta thực hiện lần lượt các bước: 
+ Chia file lớn thành nhiều file nhỏ để dễ dàng thao tác.
+ Với mỗi file nhỏ, ta thực hiện việc sắp xếp theo id của book
+ Merge các file nhỏ đã được sắp xếp này thành file kết quả

## **1.	Chia File lớn**

**1.1 Ý tưởng thuật toán**

+ Xác định trước kích thước của 1 file nhỏ muốn chia.
+ Dựa vào kích thước đã xác định K ~ 20,000KB, chia thành 140 file nhỏ.
+ Đọc dữ liệu của File lớn vào một bộ nhớ đệm buff (fit trên RAM).
+ Lưu dữ liệu trong bộ nhớ đệm vào file nhỏ với tên X.csv (X là số thứ tự file), lặp lại cho đến khi file nhỏ đạt đến kích thước muốn chia.
+ Khi file nhỏ đạt kích thước mong muốn, kiểm tra ký tự cuối cùng của file nhỏ có phải ký tự xuống dòng không, nếu không thì tiếp tục lưu dữ liệu từ file lớn cho đến khi gặp ký tự xuống dòng để có dữ liệu hoàn chỉnh.
+ Tạo file nhỏ mới lưu với tên X.csv (X là số thứ tự file) và lặp lại quá trình cho đến khi đọc hết dữ liệu từ file lớn.


**1.2 Đánh giá độ phức tạp**

Với k là độ lớn của file nhỏ được xác định trước, L là độ lớn của file lớn, buff là độ lớn của bộ nhớ đệm.

Thuật toán cần tạo ra n = L/k file nhỏ, sử dụng vòng lặp for duyệt n file nhỏ, đồng thời phải sử dụng vòng lặp while duyệt m = k/buff để lưu dữ liệu từ bộ nhớ đệm vào file nhỏ. Tức là cần O(n.m)

## **2.	Sắp xếp file nhỏ**

**2.1 Ý tưởng thuật toán**

+ Lần lượt xử lí từng file nhỏ. Đọc dữ liệu của từng file nhỏ.
+ Lần lượt chuyển dữ liệu của file nhỏ vào một bộ nhớ đệm buff có kích thước định trước (fit trên RAM).
+ Phân tích dữ liệu từng dòng thành dạng struct với 2 trường id và context để dễ sắp xếp.
+ Sắp xếp mảng struct theo id tăng dần với dữ liệu đã được phân tích trước đó bằng thuật toán Quick Sort.
+ Lưu mảng struct đã sắp xếp vào file với đánh dấu đã sắp xếp (X_sorted.csv, với X là số thứ tự của file nhỏ).
+ Lặp lại toàn bộ quá trình cho đến khi đã sắp xếp tất cả file nhỏ.

**2.2 Đánh giá độ phức tạp**

Với k là độ lớn của file nhỏ, L là độ lớn của file lớn, buff là độ lớn của bộ nhớ đệm, a là số phần tử của mảng struct tương đương với số dòng của file nhỏ).

Thuật toán sử dụng vòng lặp for duyệt n = L/k file nhỏ. Sử dụng vòng lặp while duyệt m = k/buff để phân tích dữ liệu từ file nhỏ vào bộ nhớ đệm rồi vào mảng struct. 

Sau đó Sử dụng thuật toán Quick Sort để sắp xếp mảng dữ liệu với độ phức tạp O(a*log(a)) 

Vậy độ phức tạp của thuật toán là O(n*(m+a*logn))

## **3.	Hợp nhất các file nhỏ đã sắp xếp thành file lớn**

**3.1 Ý tưởng thuật toán**

+ Đọc một số lượng dòng nhất định trong tất cả các file nhỏ (giá trị CHUNK_SIZE = 100) để tránh không fit trên Ram.
+ Đưa dữ liệu của từng file nhỏ vào một con trỏ tương ứng, quản lý các con trỏ bằng mảng vector.
+ Đọc dữ liệu từng dòng (số dòng là CHUNK_SIZE) từ con trỏ trong mảng vector, sử dụng kĩ thuật hàng đợi (queue) với dạng priority queue – hàng đợi ưu tiên để sắp xếp các dữ liệu từ các file nhỏ, thuật toán sắp xếp được thư viện hỗ trợ là min-heap, mỗi lần chỉ đưa dữ liệu đầu tiên hiện hành của từng file vào queue.
+ Lấy phần tử đứng đầu trong hàng đợi và đưa vào File lớn (File này sẽ là file kết quả của bài toán) .
+ Kiểm tra nếu trong file nhỏ của phần tử vừa ghi vào File lớn vẫn còn phần kế tiếp thì tiếp tục đưa dữ liệu đó vào queue.
+ Tại một file nhỏ khi đã ghi CHUNK_SIZE dữ liệu vào file lớn, ta tiếp tục đọc CHUNK_SIZE dữ liệu tiếp theo vào con trỏ, việc này dừng lại khi đã lấy hết dữ liệu của file nhỏ.
+ Lặp lại toàn quá trình cho đến khi queue rỗng.
+ Hoàn thành sắp xếp File lớn merge dữ liệu và lưu dưới tên  “sorted_big_file.csv”

**3.2 Đánh giá độ phức tạp**

Với m = CHUNK_SIZE là số dòng tối đã được đọc trong 1 file nhỏ, n là số file nhỏ n = L/k (k là độ lớn của file nhỏ, L là độ lớn của file lớn).

Thuật toán sử dụng vòng lặp for đọc n file dữ liệu và đưa vào queue, thao tác chèn m dòng dữ liệu vào queue có chi phí O(log(m)) nên vòng lặp có chi phí O(nlog(m)).

Thuật toán sử dụng vòng lặp while để đưa dữ liệu vào File lớn đã sắp xếp. Về cơ bản, vòng lặp sẽ thực hiện số lần tương đương với số dòng của File lớn và thêm chi phí của việc chèn m dòng dữ liệu vào queue có chi phí O(log(m)). Nên vòng lặp có chi phí O(N + N/m*log(m)).

Vậy chi phí tổng cộng xấp xỉ O(N) với N là số dòng của File lớn.

## 4. Tổng kết

Ý tưởng cơ bản là như vậy, bạn đọc hãy nghiên cứu [code](https://github.com/nxhawk/Sort-Big-File/tree/master/Sort_Big_File) nhé <(^-^)>.

Qua đồ án này đã giúp chúng em rèn luyện khả năng lập trình. 

Cung cấp các kiến thức mới và cách vận dụng các kiến thức đã học vào bài toán thực tế. 

Đồng thời cũng rèn luyện kĩ năng làm việc nhóm thông qua công cụ quản lý source code github và git: 

![image](https://i.pinimg.com/200x150/5a/73/fc/5a73fc423572b3067edcd1357e10562e.jpg)
