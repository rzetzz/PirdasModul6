<?php

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "pirdasmodul6";

$conn = new mysqli($servername, $username, $password, $dbname);

    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $sql = "SELECT * FROM data_mpu ORDER BY sensor_id DESC LIMIT 1";
    $result = $conn->query($sql);   
    // $data = array();
    if ($result->num_rows > 0) {
        while ($row = $result->fetch_assoc()) {
            $data = $row;
        }
    } else {
        echo "Tidak ada data.";
    }

$conn->close();
echo json_encode($data);
exit();
?>