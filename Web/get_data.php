<?php
// Kết nối tới cơ sở dữ liệu
include 'db_connection.php';

// Truy vấn dữ liệu từ cơ sở dữ liệu
$sql = "SELECT rfid, status, time FROM history ORDER BY time DESC";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    $stt = 1; // Biến số thứ tự ban đầu
    // Hiển thị dữ liệu dạng bảng HTML
    while($row = $result->fetch_assoc()) {
        // Chuyển đổi trạng thái sang tiếng Việt
        if ($row["status"] == 'in') {
            $status = "Vào";
        } elseif ($row["status"] == 'out') {
            $status = "Ra";
        } elseif ($row["status"] == 'not_valid') {
            $status = "Không hợp lệ";
        } else {
            $status = $row["status"]; // Giữ nguyên nếu không khớp
        }

        echo "<tr>";
        echo "<td>" . $stt . "</td>";
        echo "<td>" . $row["rfid"]. "</td>";
        echo "<td>" . $status . "</td>";
        echo "<td>" . $row["time"]. "</td>";
        echo "</tr>";
        $stt++; // Tăng biến số thứ tự sau mỗi bản ghi
    }
} else {
    echo "<tr><td colspan='4'>Không có dữ liệu</td></tr>";
}
$conn->close();
?>
