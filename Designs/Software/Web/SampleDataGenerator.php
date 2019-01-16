<?php

session_start();
if(!$_SESSION['isLoggedIn']) {
   header("Location: /login.php");
   die();
}

include "dbinfo.php";

$h2o_level = rand(1,256);
$h2o_stored = rand(1,256);
$ph_level = rand(1,256);
$ph_up_stored = rand(1,256);
$ph_down_stored = rand(1,256);
$ec_level = rand(1,256);
$ec_stored = rand(1,256);
$temp_measured = rand(1,256);
$flow_measured = rand(1,256);
$flow_target = rand(1,256);
$ph_target = rand(1,256);
$ec_target = rand(1,256);


$sql = "INSERT INTO `TestTable` (`h2o_level`, `h2o_stored`, `ph_level`, `ph_up_stored`, `ph_down_stored`, `ec_level`, `ec_stored`, `temp_measured`, `flow_measured`, `flow_target`, `ph_target`, `ec_target`, `time`, `table_key`) VALUES ('$h2o_level', '$h2o_stored', '$ph_level', '$ph_up_stored', '$ph_down_stored', '$ec_level', '$ec_stored', '$temp_measured', '$flow_measured', '$flow_target', '$ph_target', '$ec_target', CURRENT_TIMESTAMP, NULL);";

if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

?> 
