# Environment Monitor

... dự án này làm gì?

### Các cảm biến môi trường sử dụng:

- [Cảm Biến Độ PH](https://hshop.vn/products/cam-bien-do-ph-dfrobot-gravity-analog-ph-sensor-meter-kit-v2).
- [Cảm Biến Tổng Chất Rắn Hòa Tan](https://hshop.vn/products/cam-bien-tong-chat-ran-hoa-tan-dfrobot-gravity-analog-tds-sensor-meter-for-arduino).
- [Cảm Biến Đo Độ Đục Của Nước](https://hshop.vn/products/cam-bien-do-do-duc-cua-nuoc-water-turbidity-sensor-dfrobot).

### Các thiết bị đo nguồn điện:

- [Cảm Biến Dòng Điện ACS712](https://hshop.vn/products/cam-bien-dong-dien-hall-acs712-30a): loại **5A**.
- Áp dụng nguyên lý *"Điện trở Phân áp"*.

### Bộ nhớ [EEPROM](https://docs.arduino.cc/learn/built-in-libraries/eeprom):

> Bộ nhớ EEPROM được sắp xếp theo chuỗi dài, có giá trị *"địa chỉ [từ 0 đến 1023]"*. Với mỗi địa chỉ là **1 byte**.
>
> Với bo Uno có kích thước EEPROM **1 KB** (ATmega328P) = **1024 bytes**.
>
> Với bo Uno có kích thước EEPROM **4 KB** (ATmega2560) = **4096 bytes**.

### Nền tảng IoT Platform - [Blynk V2](https://blynk.io/):

> Các bước cần chuẩn bị:
>
> 1. Tạo [tài khoản](https://blynk.cloud/dashboard/login) Blynk.
> 2. Chuẩn bị các thiết bị phần cứng có [hỗ trợ](https://docs.blynk.io/en/blynk.edgent-firmware-api/supported-boards#static-provisioning-support).
> 3. Cài đặt IDE. Bạn có thể sử dụng Arduino IDE hoặc PlatformIO hoặc bất kỳ trình chỉnh sửa nào khác.
> 4. Cài đặt Thư viện Blynk trên IDE bạn dùng.

## Doc [ESP8266](https://hshop.vn/products/kit-rf-thu-phat-wifi-esp8266-nodemcu)

> Thư viện ESP8266 đang dùng trên IDE Arduino **Version 3.0.2** (cài đặt trong *"Boards Manager"*).
>
> Board: **NodeMCU 1.0 (ESP-12E Module)**.

### Quy định cấu hình Wifi cho ESP8266:

> Vì ESP8266 mỗi khi khởi động cần truy cập Internet để gửi data lên Blynk. Nó sử dụng thông tin của mạng Wifi lưu trong code để vào.
>
> Do đó, để tiện cho việc di động, ko cần nạp code lại. Mình quy định thông tin Wifi lưu trong ESP8266.
> - **SSID:** Test-ESP
> - **Pass:** 123456789
>
> Lúc này ta có thể dùng điện thoại bật tính năng *"Chia sẽ kết nối"* và cấu hình theo thông tin trên để phát Wifi cho ESP8266 truy cập.

### Kết nối UART:

> Để bo Arduino (MEGA) giao tiếp với ESP8266, ta dùng giao thức UART, trong đó dùng **Serial 1** của MEGA và **Serial 0** của ESP8266.
> - D19 (RX1) <---> GPIO1 (TXD0)
> - D18 (TX1) <---> GPIO3 (RXD0)

## Doc [Cảm Biến Độ PH](https://wiki.dfrobot.com/Gravity__Analog_pH_Sensor_Meter_Kit_V2_SKU_SEN0161-V2)

> Để đọc giá trị pH chính xác, đầu dò cần được hiệu chỉnh.
>
> Cần chuẩn bị 2 lọ dung dịch mẫu với **pH4.0** và **pH7.0** để thực hiện hiệu chỉnh 2 điểm.
>
> Sau khi hoàn thành quá trình *"hiệu chuẩn 2 điểm"*, bạn có thể sử dụng cảm biến để đo thực tế.
>
> Các thông số liên quan trong quá trình hiệu chuẩn đã được lưu vào EEPROM của bo điều khiển chính.

### Hiệu chỉnh pH:

> 1. Mở code example *"DFRobot_PH_Test.ino"* và nạp vào bo mạch.
> 2. Sau khi upload code thành công, mở Serial Monitor với **Baud 115200**.
> 3. Nhập lệnh *[enterph]* trong Serial Monitor để vào chế độ hiệu chỉnh.
> 4. Nhập lệnh *[calph]* trong Serial Monitor để bắt đầu hiệu chuẩn. Chương trình sẽ tự động xác định dung dịch đệm tiêu chuẩn nào trong 2 dung dịch đệm tiêu chuẩn: **4,0** và **7,0**.
> 5. Sau khi hiệu chuẩn, hãy nhập lệnh *[exitph]* trong Serial Monitor để lưu các thông số liên quan và thoát khỏi chế độ hiệu chuẩn. **Lưu ý:** chỉ sau khi nhập lệnh *[exitph]*, các tham số liên quan mới có thể được lưu.

### Vị trí lưu giá trị hiệu chỉnh pH trên EEPROM:

> Từ **[0x00]** đến **[0x07]** cho dung dịch **7.0 pH**.
>
> Từ **[0x08]** đến **[0x0F]** cho dung dịch **4.0 pH**.
>
> Sau khi căn chỉnh xong, đây là các cặp thông số **[ Địa chỉ : Giá trị ]** được lưu trữ trong EEPROM:
>
> - (0;0) (1;110) (2;190) (3;68) (4;192) (5;188) (6;255) (7;68).
> - (8;0) (9;0) (10;128) (11;63) (12;255) (13;255) (14;255) (15;255).

## Doc [Cảm Biến Tổng Chất Rắn Hòa Tan](https://wiki.dfrobot.com/Gravity__Analog_TDS_Sensor___Meter_For_Arduino_SKU__SEN0244)

> Lưu ý, không được sử dụng đầu dò trong nước trên **55 °C**.
> 
> Để có được giá trị TDS chính xác hơn, cần phải hiệu chuẩn trước khi đo. Ngoài ra, nên kết nối cảm biến nhiệt độ để bù nhiệt độ để cải thiện độ chính xác.
> 
> Thông thường, giá trị TDS bằng một nửa giá trị độ dẫn điện, nghĩa là: **[ TDS = EC / 2 ]**.
>
> Trong quá trình hiệu chuẩn, cần sử dụng dung dịch lỏng có độ dẫn điện hoặc giá trị TDS đã biết, chẳng hạn như dung dịch đệm chuẩn **1413us/cm**. Nếu quy đổi sang giá trị TDS là khoảng **707 ppm**.

### Hiệu chỉnh TDS (ppm):

> 1. Mở code example *"GravityTDSExample.ino"* và nạp vào bo mạch.
> 2. Sau khi upload code thành công, mở Serial Monitor với **Baud 115200**.
> 3. Nhập lệnh *[enter]* trong Serial Monitor để vào chế độ hiệu chỉnh.
> 4. Nhập lệnh *[cal:TDS_Value]* trong Serial Monitor để hiệu chuẩn cảm biến. Vd, tôi sử dụng dung dịch đệm **707ppm** nên tôi cần nhập lệnh *[cal:707]*.
> 5. Sau khi hiệu chuẩn, hãy nhập lệnh *[exit]* để lưu và thoát.

## Doc [Cảm Biến Đo Độ Đục Của Nước](https://wiki.dfrobot.com/Turbidity_sensor_SKU__SEN0189)

> Lưu ý, mặt trên của đầu dò không chống nước.
>
> Công tắc tín hiệu đầu ra *"D/A"*:
> - *"A"*: Ngõ ra tín hiệu Analog, giá trị ngõ ra sẽ giảm khi ở chất lỏng có độ đục cao.
> - *"D"*: Đầu ra tín hiệu số, mức cao và mức thấp, có thể điều chỉnh bằng chiết áp ngưỡng.
>
> Vì ta sử dụng ở chế độ *"A"* để đọc giá trị Analog, nên ko cần quan tâm đến việc chỉnh chiết áp.
>
> Đơn vị đo độ đục được thể hiện là **NTU**, còn được gọi là **JTU** (Jackson Turbidity Unit), **1JTU = 1NTU = 1 mg/L**.

## Doc [Cảm Biến Dòng Điện ACS712](https://www.elecrow.com/wiki/index.php?title=ACS712_Current_Sensor-_5A)

> Đo dòng điện​​ DC​:
> 
> Khi đo DC phải mắc tải nối tiếp **Ip+** và **Ip-** đúng chiều, khi dòng điện đi từ Ip+ đến Ip-, Vout sẽ ra mức điện áp tương ứng **2.5 ~ 5VDC** tương ứng dòng **0 ~ (+Max)**, nếu mắc ngược Vout sẽ ra điện thế **2.5 ~ 0VDC** tương ứng với **0 ~ (-Max)**.
> 
> Khi cấp nguồn 5VDC cho module khi chưa có dòng Ip (chưa có tải mắc nối tiếp) thì **Vout = 2,5VDC**.
> 
> Khi dòng Ip( dòng của tải) bằng Max thì **Vout = 5DC**, Vout sẽ tuyến tính với dòng Ip trong khoản **2.5 ~ 5VDC** tương ứng với dòng **0 ~ (+Max)**, để kiểm tra có thể dùng đồng hồ VOM thang đo DC để đo Vout.

## Doc [Mạch Cầu Phân Áp](https://blog.kenhtinhoc.vn/cau-phan-ap-va-cach-tinh/)

> Để đo được một nguồn điện áp lớn trong dãi từ **0~15VDC** bằng bo mạch Vi điều khiển chỉ có khả năng đọc điện áp từ **0~5VDC**.
>
> Ta có thể dùng *"mạch cầu phân áp"* với **tỉ lệ 1/3** để chuyển từ 15VDC sang 5VDC.
>
> Để tạo ra **tỉ lệ 1/3** này, ta có thể dùng 2 điện trở với **R1=10k2** và **R2=5k1**.
>
> Như vậy chỉ bằng cách dùng 3 loại điện trở có bán trên thị trường là **5k1 (5.100 Ohm)**, **10k (10.000 Ohm)** và **200 Ohm**. Ta đã có thể đo điện áp nguồn MAX tận 15VDC.

## Doc [Blynk](https://docs.blynk.io/en/)

### Giới thiệu nền tảng (Platform):

> Nền tảng Blynk bao gồm **4** thành phần chính hoạt động liền mạch với nhau:
>
> - **Blynk.Edgent** - Phần mềm chạy trên thiết bị của bạn (cụ thể ở đây là tạo 1 Gateway bằng ESP8266) và giao tiếp với Blynk.Cloud.
> - **Blynk.Console** - Ứng dụng WEB (Client) nơi bạn có thể định cấu hình, kết nối, giám sát thiết bị của mình, phân tích dữ liệu cảm biến, cập nhật *"Firmware OTA (Over-The-Air)"*, quản lý cách người dùng và tổ chức khác truy cập thiết bị của họ.
> - **Blynk.Apps** - Ứng dụng MOBILE (Client) dành cho iOS và Android, nơi bạn có thể tạo giao diện người dùng cho thiết bị của mình mà không cần code và chia sẻ giao diện người dùng đó với những người dùng khác.
> - **Blynk.Cloud** - Máy chủ (Server) gửi dữ liệu an toàn giữa các thiết bị (Gateway) và ứng dụng (Client) của bạn.

### Giới thiệu chế độ (Mode):

> Blynk hoạt động ở **2** chế độ:
>
> - **Developer Mode** - Là chế độ mà bạn hiện đang sử dụng, cho phép bạn định cấu hình cách thức hoạt động của thiết bị.
> - **User Mode** - Cho phép giám sát và điều khiển các thiết bị, nhưng không cho phép sửa đổi bất kỳ cấu hình nào.
>
> **Lưu ý:** Bạn có thể bật/tắt "chế độ nhà phát triển" trong phần **User Profile**.

### Các khái niệm chính (Key Concept) của nền tảng Blynk:

#### Thiết bị (Device):
>
> Một *"thiết bị"* thường là một bộ vi điều khiển (MCU) như ESP32, Arduino, v.v. Bạn có thể gắn cảm biến và bộ truyền động vào MCU và giám sát hoặc điều khiển chúng bằng Blynk.
>
> Blynk có thể kết nối *"thiết bị"* của bạn với Internet bằng kết nối WiFi, di động hoặc Ethernet.

#### Mẫu thiết bị (Device Template):
>
> Là nơi lưu trữ cấu hình *"thiết bị"*.
>
> Mỗi *"thiết bị"* bắt đầu từ một *"mẫu"*, giúp dễ dàng làm việc với nhiều *"thiết bị"* thực hiện các chức năng tương tự.
>
> Ví dụ: bạn có thể tạo Mẫu cảm biến nhiệt độ và sử dụng lại nó cho tất cả các cảm biến tương tự trong nhà của mình.

#### Các thành phần của mẫu (Template Components).
> Mỗi *"mẫu"* bao gồm:
>
> - **Datastreams** - Các kênh để truyền dữ liệu từ/đến thiết bị.
> - Mobile app UI.
> - Web Dashboard UI.
> - Notifications.
>
> **Lưu ý:** Khi bạn cập nhật một *"mẫu"*, các thay đổi sẽ được áp dụng cho tất cả các *"thiết bị"* được tạo từ *"mẫu"* này.

### What's included in the plans:

> Hiện nền tảng Blynk cung cấp gồm **4** gói:
> - [Free](https://blynk.io/pricing).
> - Plus ($).
> - Pro ($$).
> - Business ($$$).
>
> Vì mình dùng bản Free, nên sẽ có những giới hạn nhất định, ta cần phải xem qua để có thể sử dụng vừa đủ trong nguồn tài nguyên mà Blynk cung cấp Free.

### Setup (1) - Tạo Template mới và cấu hình như sau:

> - Template Name: ESP Gateway
> - Hardware: ESP8266
> - Connection Type: Wifi

### Setup (2) - Cài đặt Datastreams với thuộc tính Virtual Pin như sau:

> **ID 1**
> - Name: DV0_pH
> - Pin: V0
> - Data Type: Double (độ phân giải 0,1)
> - Min: 0 pH
> - Max: 14 pH

> **ID 2**
> - Name: IV1_TDS
> - Pin: V1
> - Data Type: Integer
> - Min: 0 ppm
> - Max: 1.000 ppm

> **ID 3**
> - Name: IV2_NTU
> - Pin: V2
> - Data Type: Integer
> - Min: 0 NTU
> - Max: 3.500 NTU

> **ID 4**
> - Name: DV3_Cur
> - Pin: V3
> - Data Type: Double (độ phân giải 0,1)
> - Min: -5 A
> - Max: 5 A

> **ID 5**
> - Name: DV4_Vol
> - Pin: V4
> - Data Type: Double (độ phân giải 0,1)
> - Min: 0 V
> - Max: 15 V

### Setup (3) - Vào mục Web Dashboard cài đặt:

> Tùy chỉnh kéo thả các **Widget**, rồi cấu hình để tạo một giao diện tổng quan theo ý muốn mình.

### Setup (4) - Thêm Device mới dựa theo nền Template đã tạo:

> Vào mục *"Search -> New Device -> From Template"*.
> - Template: ESP Gateway
> - Device Name: ESP Gateway
