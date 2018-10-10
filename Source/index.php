<!DOCTYPE html>
<html>
<body>

<?php
echo "Hello World!";
echo "<br>";
$servername = "localhost";
$username = "root";
$password = "jack";

// 创建连接
$conn = mysqli_connect($servername, $username, $password);

// 检测连接
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
echo "连接成功";
?>

</body>
</html>
