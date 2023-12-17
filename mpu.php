<?php

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "pirdasmodul6";

if ($_GET["kondisi"] && $_GET["led"]&& $_GET["buzzer"] && $_GET["x"] && $_GET["y"] && $_GET["z"]) {
    $condition = $_GET["kondisi"];
    $led = $_GET["led"];
    $buzzer = $_GET["buzzer"];
    $x = $_GET["x"];
    $y = $_GET["y"];
    $z = $_GET["z"];

    $conn = new mysqli($servername, $username, $password, $dbname);

    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $sql = "INSERT INTO data_mpu (kondisi,led,buzzer,x,y,z) 
            VALUES ('$condition','$led','$buzzer','$x','$y','$z')";

    if ($conn->query($sql) === TRUE) {
        echo "Data added sucessfully";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
}
$conn->close();
exit();
?>